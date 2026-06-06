#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define PI 3.14159265358979f

// ============================================================
//  WINDOW
// ============================================================
extern int windowWidth;
extern int windowHeight;

// ============================================================
//  STATE PROYEKSI
// ============================================================
enum ProjectionMode  { PERSPECTIVE, ORTHOGRAPHIC };
enum PerspectivePoint { ONE_POINT, TWO_POINT, THREE_POINT };

extern ProjectionMode   projMode;
extern PerspectivePoint perspPoint;

// ============================================================
//  PLAYER
// ============================================================
extern float playerX;
extern float playerY;
extern float velX;
extern float velY;
extern float playerMaxSpeed;
extern float playerAccel;
extern float playerFriction;
extern float batasArena;

extern bool keyUp, keyDown, keyLeft, keyRight;

// ============================================================
//  HEALTH POINT & GAME STATE
// ============================================================
extern int   playerHP;
extern bool  gameOver;
extern bool  invincible;
extern float invincibleTimer;
extern float invincibleDuration;
extern float lastTime;
extern bool  playerVisible;
extern int   score;
extern float engineTime;

// ============================================================
//  FUEL
// ============================================================
extern float fuel;
extern float maxFuel;
extern float fuelDrainRate;
extern bool  fuelDepleted;
extern float fuelFallTimer;
extern float fuelFallDuration;
extern float fuelFallSpeed;

// ============================================================
//  POWER-UP (PIERCE)
// ============================================================
struct PowerUp {
    float x, y, z;
    bool  active;
    float rotAngle;
};
extern PowerUp powerup;
extern float   powerupSpawnTimer;
extern float   powerupSpawnInterval;
extern bool    pierceMode;
extern float   pierceTimer;
extern float   pierceDuration;

// ============================================================
//  FUEL PICKUP
// ============================================================
struct FuelPickup {
    float x, y, z;
    bool  active;
    float rotAngle;
};
extern FuelPickup fuelPickup;
extern float      fuelPickupCooldown;
extern float      fuelPickupAmount;
extern float      fuelCollectFlash;
extern float      fuelPickupLeadTime;

// ============================================================
//  BINTANG LATAR
// ============================================================
#define MAX_STARS 300
struct Star {
    float x, y, z;
    float r, g, b;
    float size;
};
extern Star starField[MAX_STARS];

// ============================================================
//  ASTEROID
// ============================================================
#define MAX_ASTEROID 6
struct Asteroid {
    float x, y, z;
    float size;
    float rotSpeed;
    float rotAngle;
    float rotAxisX, rotAxisY, rotAxisZ;
};
extern Asteroid asteroids[MAX_ASTEROID];

extern float asteroidSpeed;
extern float spawnZ;
extern float despawnZ;

extern GLuint      meteorTexture;
extern GLUquadric* meteorQuadric;

// ============================================================
//  GAME SCREEN STATE
// ============================================================
enum GameScreen { SCREEN_LOBBY, SCREEN_PLAYING };
extern GameScreen gameScreen;

// ============================================================
//  RANDOM HELPER
// ============================================================
inline float randFloat(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}
