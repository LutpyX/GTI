/*
 * ============================================================
 *  PROJECT APHELION - 3D Space Dodge
 *  Pertemuan 1
 *  Nama    : [Nama Kamu]
 *  NIM     : [NIM Kamu]
 *  Kelas   : [Kelas Kamu]
 * ============================================================
 *
 *  CARA COMPILE (macOS / Linux):
 *    g++ main.cpp globals.cpp -o aphelion \
 *        -framework OpenGL -framework GLUT   (macOS)
 *    g++ main.cpp globals.cpp -o aphelion \
 *        -lGL -lGLU -lglut                   (Linux)
 * ============================================================
 */

#include "globals.h"
#include "imageloader.h"
#include "stars.h"
#include "texture.h"
#include "player.h"
#include "asteroid.h"
#include "pickups.h"
#include "hud.h"
#include "camera.h"
#include "lobby.h"

// ============================================================
//  RESET GAME
// ============================================================
void resetGame() {
    playerX = 0.0f; playerY = 0.0f;
    velX = 0.0f; velY = 0.0f;
    keyUp = keyDown = keyLeft = keyRight = false;
    playerHP = 3;
    score = 0;
    gameOver = false;
    invincible = false;
    invincibleTimer = 0.0f;
    playerVisible = true;
    asteroidSpeed = 0.18f;
    fuel = maxFuel;
    fuelDepleted = false;
    fuelFallTimer = 0.0f;
    fuelPickup.active = false;
    fuelPickupCooldown = 0.0f;
    fuelCollectFlash = 0.0f;
    powerup.active = false;
    powerupSpawnTimer = 0.0f;
    pierceMode = false;
    pierceTimer = 0.0f;
    initAsteroids();
    initStars();
    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

// ============================================================
//  UPDATE (game loop)
// ============================================================
void update(int value) {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = currentTime - lastTime;
    lastTime = currentTime;
    if (dt > 0.1f) dt = 0.1f;
    engineTime += dt;

    // LOBBY: animasi bintang pelan, skip semua game logic
    if (gameScreen == SCREEN_LOBBY) {
        for (int i = 0; i < MAX_STARS; i++) {
            starField[i].z += 0.04f * (dt * 60.0f);
            if (starField[i].z > 5.0f) starField[i].z = -80.0f;
        }
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }

    if (!gameOver) {
        // ASTEROID UPDATE
        for (int i = 0; i < MAX_ASTEROID; i++) {
            asteroids[i].z += asteroidSpeed * (dt * 60.0f);
            asteroids[i].rotAngle += asteroids[i].rotSpeed * dt;
            if (asteroids[i].z > despawnZ) {
                spawnAsteroid(i);
                score += 10;
                asteroidSpeed = 0.18f + score * 0.0003f;
            }
        }

        // FUEL DRAIN
        fuel -= fuelDrainRate * dt;
        if (fuel < 0.0f) fuel = 0.0f;
        if (fuel <= 0.0f && !fuelDepleted && !invincible) {
            fuelDepleted    = true;
            fuelFallTimer   = 0.0f;
            playerHP--;
            invincible      = true;
            invincibleTimer = 0.0f;
            playerVisible   = true;
            if (playerHP <= 0) { playerHP = 0; gameOver = true; }
        }
        if (fuelDepleted) {
            fuelFallTimer += dt;
            playerY -= fuelFallSpeed * dt;
            if (playerY < -batasArena) playerY = -batasArena;
            if (fuelFallTimer >= fuelFallDuration) {
                fuelDepleted = false;
                fuel = maxFuel * 0.5f;
            }
        }

        // SMOOTH MOVEMENT
        {
            float inX = 0.0f, inY = 0.0f;
            if (!fuelDepleted) {
                if (keyRight) inX =  1.0f;
                if (keyLeft)  inX = -1.0f;
                if (keyUp)    inY =  1.0f;
                if (keyDown)  inY = -1.0f;
            }
            if (inX != 0.0f && inY != 0.0f) { inX *= 0.7071f; inY *= 0.7071f; }

            velX += inX * playerAccel * dt;
            velY += inY * playerAccel * dt;
            if (inX == 0.0f) velX *= fmaxf(0.0f, 1.0f - playerFriction * dt);
            if (inY == 0.0f) velY *= fmaxf(0.0f, 1.0f - playerFriction * dt);
            float spd = sqrtf(velX*velX + velY*velY);
            if (spd > playerMaxSpeed) { velX *= playerMaxSpeed/spd; velY *= playerMaxSpeed/spd; }

            playerX += velX * dt;
            playerY += velY * dt;
            if (playerX >  batasArena) { playerX =  batasArena; if (velX > 0) velX = -velX * 0.3f; }
            if (playerX < -batasArena) { playerX = -batasArena; if (velX < 0) velX = -velX * 0.3f; }
            if (playerY >  batasArena) { playerY =  batasArena; if (velY > 0) velY = -velY * 0.3f; }
            if (playerY < -batasArena) { playerY = -batasArena; if (velY < 0) velY = -velY * 0.3f; }
        }

        // FUEL PICKUP — spawn sebelum bensin habis
        if (fuelPickupCooldown > 0.0f) fuelPickupCooldown -= dt;
        if (fuelCollectFlash  > 0.0f) fuelCollectFlash  -= dt;
        {
            float timeLeft = (fuelDrainRate > 0) ? fuel / fuelDrainRate : 99.0f;
            if (!fuelPickup.active && !fuelDepleted
                && timeLeft < fuelPickupLeadTime
                && fuelPickupCooldown <= 0.0f) {
                spawnFuelPickup();
            }
        }
        if (fuelPickup.active) {
            fuelPickup.z        += asteroidSpeed * (dt * 60.0f);
            fuelPickup.rotAngle += 55.0f * dt;
            if (fuelPickup.z > despawnZ) {
                fuelPickup.active    = false;
                fuelPickupCooldown   = 3.0f;
            } else {
                float dfx    = playerX - fuelPickup.x;
                float dfy    = playerY - fuelPickup.y;
                float xyDist = sqrtf(dfx*dfx + dfy*dfy);
                float zDist  = fabsf(fuelPickup.z);
                if (xyDist < 1.1f && zDist < 2.5f) {
                    fuelPickup.active  = false;
                    fuelPickupCooldown = 0.0f;
                    fuel = fuel + fuelPickupAmount;
                    if (fuel > maxFuel) fuel = maxFuel;
                    fuelCollectFlash   = 1.4f;
                }
            }
        }

        // POWER-UP SPAWN & UPDATE
        powerupSpawnTimer += dt;
        if (!powerup.active && powerupSpawnTimer >= powerupSpawnInterval) {
            spawnPowerUp();
            powerupSpawnTimer = 0.0f;
        }
        if (powerup.active) {
            powerup.z        += asteroidSpeed * (dt * 60.0f);
            powerup.rotAngle += 95.0f * dt;
            if (powerup.z > despawnZ) {
                powerup.active    = false;
                powerupSpawnTimer = 0.0f;
            } else {
                float dpx    = playerX - powerup.x;
                float dpy    = playerY - powerup.y;
                float xyDist = sqrtf(dpx*dpx + dpy*dpy);
                float zDist  = fabsf(powerup.z);
                if (xyDist < 1.2f && zDist < 2.5f) {
                    powerup.active    = false;
                    powerupSpawnTimer = 0.0f;
                    pierceMode        = true;
                    pierceTimer       = 0.0f;
                }
            }
        }

        // PIERCE TIMER
        if (pierceMode) {
            pierceTimer += dt;
            if (pierceTimer >= pierceDuration) {
                pierceMode  = false;
                pierceTimer = 0.0f;
            }
        }

        // INVINCIBLE FLASH
        if (invincible) {
            invincibleTimer += dt;
            playerVisible = ((int)(invincibleTimer / 0.12f) % 2 == 0);
            if (invincibleTimer >= invincibleDuration) {
                invincible = false;
                playerVisible = true;
                invincibleTimer = 0.0f;
            }
        }

        // COLLISION ASTEROID (skip jika pierce aktif)
        if (!invincible && !pierceMode) {
            for (int i = 0; i < MAX_ASTEROID; i++) {
                if (checkCollision(asteroids[i])) {
                    playerHP--;
                    invincible = true;
                    invincibleTimer = 0.0f;
                    playerVisible = true;
                    asteroids[i].z += 2.0f;
                    if (playerHP <= 0) {
                        playerHP = 0;
                        gameOver = true;
                    }
                    break;
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ============================================================
//  DISPLAY
// ============================================================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (projMode == PERSPECTIVE) applyPerspectiveCamera();
    else                          applyOrthographicCamera();

    GLfloat lp[] = {5.0f, 8.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lp);

    drawStars();

    if (gameScreen == SCREEN_LOBBY) {
        drawLobbyScreen();
    } else {
        drawAsteroids();
        drawPowerUp();
        drawFuelPickup();
        if (!gameOver) drawPlayer();
        drawHUD();
    }

    glutSwapBuffers();
}

// ============================================================
//  RESHAPE
// ============================================================
void reshape(int w, int h) {
    windowWidth  = w;
    windowHeight = (h == 0) ? 1 : h;
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (double)windowWidth / (double)windowHeight;
    if (projMode == ORTHOGRAPHIC) {
        double s = 4.0;
        glOrtho(-s*aspect, s*aspect, -s, s, 0.1, 100.0);
    } else {
        gluPerspective(60.0, aspect, 0.1, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

// ============================================================
//  KEYBOARD
// ============================================================
void keyboard(unsigned char key, int x, int y) {
    if (gameScreen == SCREEN_LOBBY) {
        if (key == 13 || key == ' ') {   // Enter atau Space = mulai game
            gameScreen = SCREEN_PLAYING;
            resetGame();
        }
        if (key == 27) exit(0);
        glutPostRedisplay();
        return;
    }
    if (gameOver) {
        if (key == 'r' || key == 'R') resetGame();
        if (key == 27) exit(0);
        glutPostRedisplay();
        return;
    }
    switch (key) {
        case 'w': case 'W': keyUp    = true; break;
        case 's': case 'S': keyDown  = true; break;
        case 'a': case 'A': keyLeft  = true; break;
        case 'd': case 'D': keyRight = true; break;
        case 'p': case 'P': projMode = PERSPECTIVE;  reshape(windowWidth, windowHeight); break;
        case 'o': case 'O': projMode = ORTHOGRAPHIC; reshape(windowWidth, windowHeight); break;
        case '1': perspPoint = ONE_POINT;   projMode = PERSPECTIVE; reshape(windowWidth, windowHeight); break;
        case '2': perspPoint = TWO_POINT;   projMode = PERSPECTIVE; reshape(windowWidth, windowHeight); break;
        case '3': perspPoint = THREE_POINT; projMode = PERSPECTIVE; reshape(windowWidth, windowHeight); break;
        case 'r': case 'R': resetGame(); break;
        case 27: exit(0);
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if (gameScreen == SCREEN_LOBBY) return;
    switch (key) {
        case 'w': case 'W': keyUp    = false; break;
        case 's': case 'S': keyDown  = false; break;
        case 'a': case 'A': keyLeft  = false; break;
        case 'd': case 'D': keyRight = false; break;
    }
}

void specialKeys(int key, int x, int y) {
    if (gameScreen == SCREEN_LOBBY || gameOver) return;
    switch (key) {
        case GLUT_KEY_UP:    keyUp    = true; break;
        case GLUT_KEY_DOWN:  keyDown  = true; break;
        case GLUT_KEY_LEFT:  keyLeft  = true; break;
        case GLUT_KEY_RIGHT: keyRight = true; break;
    }
}

void specialKeysUp(int key, int x, int y) {
    if (gameScreen == SCREEN_LOBBY) return;
    switch (key) {
        case GLUT_KEY_UP:    keyUp    = false; break;
        case GLUT_KEY_DOWN:  keyDown  = false; break;
        case GLUT_KEY_LEFT:  keyLeft  = false; break;
        case GLUT_KEY_RIGHT: keyRight = false; break;
    }
}

// ============================================================
//  INIT GL
// ============================================================
void initGL() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.04f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat amb[]  = {0.10f, 0.11f, 0.14f, 1.0f};
    GLfloat diff[] = {0.92f, 0.88f, 0.82f, 1.0f};
    GLfloat spec[] = {0.45f, 0.42f, 0.36f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glEnable(GL_LIGHT0);

    generateMeteorTexture();
    meteorQuadric = gluNewQuadric();
    gluQuadricTexture(meteorQuadric, GL_TRUE);
    gluQuadricNormals(meteorQuadric, GLU_SMOOTH);

    initAsteroids();
    initStars();
    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

// ============================================================
//  MAIN
// ============================================================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(80, 60);
    glutCreateWindow("Project Aphelion");

    initGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}



