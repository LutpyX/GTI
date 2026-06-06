#include "globals.h"

int windowWidth  = 900;
int windowHeight = 650;

ProjectionMode   projMode   = PERSPECTIVE;
PerspectivePoint perspPoint = ONE_POINT;

float playerX        = 0.0f;
float playerY        = 0.0f;
float velX           = 0.0f;
float velY           = 0.0f;
float playerMaxSpeed = 3.5f;
float playerAccel    = 22.0f;
float playerFriction = 10.0f;
float batasArena     = 2.5f;

bool keyUp    = false, keyDown  = false;
bool keyLeft  = false, keyRight = false;

int   playerHP           = 3;
bool  gameOver           = false;
bool  invincible         = false;
float invincibleTimer    = 0.0f;
float invincibleDuration = 1.5f;
float lastTime           = 0.0f;
bool  playerVisible      = true;
int   score              = 0;
float engineTime         = 0.0f;

float fuel             = 100.0f;
float maxFuel          = 100.0f;
float fuelDrainRate    = 7.0f;
bool  fuelDepleted     = false;
float fuelFallTimer    = 0.0f;
float fuelFallDuration = 2.0f;
float fuelFallSpeed    = 1.5f;

PowerUp powerup              = {0,0,0,false,0};
float   powerupSpawnTimer    = 0.0f;
float   powerupSpawnInterval = 15.0f;
bool    pierceMode           = false;
float   pierceTimer          = 0.0f;
float   pierceDuration       = 8.0f;

FuelPickup fuelPickup         = {0,0,0,false,0};
float      fuelPickupCooldown = 0.0f;
float      fuelPickupAmount   = 55.0f;
float      fuelCollectFlash   = 0.0f;
float      fuelPickupLeadTime = 8.0f;

Star     starField[MAX_STARS];
Asteroid asteroids[MAX_ASTEROID];

float asteroidSpeed = 0.18f;
float spawnZ        = -45.0f;
float despawnZ      = 3.0f;

GLuint      meteorTexture = 0;
GLUquadric* meteorQuadric = NULL;

GameScreen gameScreen = SCREEN_LOBBY;
