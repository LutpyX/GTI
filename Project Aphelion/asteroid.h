#pragma once
#include "globals.h"

void spawnAsteroid(int i) {
    asteroids[i].x        = randFloat(-2.5f, 2.5f);
    asteroids[i].y        = randFloat(-2.0f, 2.0f);
    asteroids[i].z        = spawnZ;
    asteroids[i].size     = randFloat(0.3f, 0.55f);
    asteroids[i].rotSpeed = randFloat(20.0f, 80.0f);
    asteroids[i].rotAngle = randFloat(0.0f, 360.0f);
    asteroids[i].rotAxisX = randFloat(-1.0f, 1.0f);
    asteroids[i].rotAxisY = randFloat(-1.0f, 1.0f);
    asteroids[i].rotAxisZ = randFloat(-1.0f, 1.0f);
}

void initAsteroids() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_ASTEROID; i++) {
        spawnAsteroid(i);
        asteroids[i].z = randFloat(spawnZ, -5.0f);
    }
}

void drawAsteroids() {
    if (!meteorQuadric) return;

    // ── Pass 1: Shadow blob ───────────────────────────────────
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    for (int i = 0; i < MAX_ASTEROID; i++) {
        float distZ   = fabsf(asteroids[i].z);
        float maxDist = fabsf(spawnZ);
        float t       = 1.0f - distZ / maxDist;
        if (t < 0.0f) t = 0.0f;
        float alpha   = 0.12f + t * 0.45f;

        glColor4f(0.0f, 0.0f, 0.06f, alpha);
        glPushMatrix();
            glTranslatef(asteroids[i].x + asteroids[i].size * 0.30f,
                         asteroids[i].y - asteroids[i].size * 0.28f,
                         asteroids[i].z);
            glScalef(1.50f, 0.65f, 1.0f);
            glutSolidSphere(asteroids[i].size, 10, 7);
        glPopMatrix();
    }
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    // ── Pass 2: Asteroid bertekstur + pencahayaan ─────────────
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, meteorTexture);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat specM[] = {0.20f, 0.20f, 0.18f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specM);
    glMaterialf (GL_FRONT, GL_SHININESS, 14.0f);

    for (int i = 0; i < MAX_ASTEROID; i++) {
        glPushMatrix();
            glTranslatef(asteroids[i].x, asteroids[i].y, asteroids[i].z);
            glRotatef(asteroids[i].rotAngle,
                      asteroids[i].rotAxisX,
                      asteroids[i].rotAxisY,
                      asteroids[i].rotAxisZ);
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(meteorQuadric, asteroids[i].size, 14, 12);
        glPopMatrix();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
}
