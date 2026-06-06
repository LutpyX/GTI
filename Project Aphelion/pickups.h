#pragma once
#include "globals.h"
#include "player.h"   // butuh drawCylinder

void spawnPowerUp() {
    powerup.x        = randFloat(-2.0f, 2.0f);
    powerup.y        = randFloat(-1.5f, 1.5f);
    powerup.z        = spawnZ;
    powerup.active   = true;
    powerup.rotAngle = 0.0f;
}

void spawnFuelPickup() {
    fuelPickup.x        = randFloat(-2.0f, 2.0f);
    fuelPickup.y        = randFloat(-1.5f, 1.5f);
    fuelPickup.z        = spawnZ;
    fuelPickup.active   = true;
    fuelPickup.rotAngle = randFloat(0.0f, 360.0f);
}

// ============================================================
//  GAMBAR POWER-UP (Pierce)
// ============================================================
void drawPowerUp() {
    if (!powerup.active) return;
    float pulse = 1.0f + 0.12f * sin(engineTime * 6.0f);

    glPushMatrix();
        glTranslatef(powerup.x, powerup.y, powerup.z);

        // Aura luar berdenyut
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        float aurAlpha = 0.12f + 0.07f * sin(engineTime * 9.0f);
        glColor4f(0.0f, 1.0f, 0.85f, aurAlpha);
        glutSolidSphere(0.5f * pulse, 12, 8);
        glDepthMask(GL_TRUE);

        // Gem berputar
        glRotatef(powerup.rotAngle, 0.6f, 1.0f, 0.4f);
        float s = 0.26f * pulse;
        glScalef(s, s, s);

        glColor3f(0.0f, 1.0f, 0.85f);
        glutSolidOctahedron();

        glColor4f(0.6f, 1.0f, 1.0f, 0.8f);
        glScalef(1.08f, 1.08f, 1.08f);
        glutWireOctahedron();
    glPopMatrix();
}

// ============================================================
//  GAMBAR FUEL PICKUP
// ============================================================
void drawFuelPickup() {
    if (!fuelPickup.active) return;
    float bob   = 0.06f * sin(engineTime * 3.8f);
    float pulse = 1.0f  + 0.09f * sin(engineTime * 7.0f);

    glPushMatrix();
        glTranslatef(fuelPickup.x, fuelPickup.y + bob, fuelPickup.z);

        // Aura oranye berdenyut
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glColor4f(1.0f, 0.5f, 0.0f, 0.11f + 0.05f * sin(engineTime * 9.0f));
        glutSolidSphere(0.32f * pulse, 10, 8);
        glDepthMask(GL_TRUE);

        // Putar lambat di sumbu Y
        glRotatef(fuelPickup.rotAngle, 0.0f, 1.0f, 0.0f);
        // Rebahkan supaya drum tegak (Z → Y)
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        // Badan drum oranye — centered di Z
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, -0.11f);
            glColor3f(1.0f, 0.45f, 0.0f);
            drawCylinder(0.13f, 0.22f, 16);
        glPopMatrix();

        // Strip kuning di tengah
        glColor3f(1.0f, 0.9f, 0.2f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
            for (int j = 0; j <= 16; j++) {
                float a = j * 2.0f * PI / 16;
                glVertex3f(cos(a)*0.132f, sin(a)*0.132f, 0.0f);
            }
        glEnd();
        glLineWidth(1.0f);

        // Nozzle atas
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.11f);
            glColor3f(0.8f, 0.3f, 0.0f);
            drawCylinder(0.055f, 0.06f, 10);
        glPopMatrix();

    glPopMatrix();
}
