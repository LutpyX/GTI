#pragma once
#include "globals.h"

// ============================================================
//  HELPER: drawCylinder
// ============================================================
void drawCylinder(float radius, float height, int slices) {
    float step = 2.0f * PI / slices;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float a = i * step;
        glVertex3f(cos(a)*radius, sin(a)*radius, 0.0f);
        glVertex3f(cos(a)*radius, sin(a)*radius, height);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);
    for (int i = 0; i <= slices; i++) {
        float a = i * step;
        glVertex3f(cos(a)*radius, sin(a)*radius, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,height);
    for (int i = slices; i >= 0; i--) {
        float a = i * step;
        glVertex3f(cos(a)*radius, sin(a)*radius, height);
    }
    glEnd();
}

// ============================================================
//  COLLISION
// ============================================================
bool checkCollision(Asteroid& a) {
    float dx = playerX - a.x;
    float dy = playerY - a.y;
    float dz = 0.0f   - a.z;
    float dist = sqrt(dx*dx + dy*dy + dz*dz);
    return dist < (a.size + 0.22f);
}

// ============================================================
//  API / EXHAUST ENGINE
// ============================================================
void drawExhaust() {
    float t = engineTime;
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);

    // --- Lapisan inti: putih-kuning, pendek, terang ---
    int coreN = 7;
    for (int i = 0; i < coreN; i++) {
        float frac  = (float)i / coreN;
        float len   = (0.22f + 0.06f * sin(t * 22.0f)) * frac;
        float wobX  = 0.012f * sin(t * 19.0f + i * 1.4f);
        float wobY  = 0.012f * cos(t * 16.0f + i * 1.1f);
        float rad   = (0.055f - frac * 0.038f) * (1.0f + 0.12f * sin(t * 25.0f + i));
        float alpha = (1.0f - frac) * 0.92f;
        float green = 1.0f - frac * 0.45f;
        float blue  = (frac < 0.25f) ? (1.0f - frac * 4.0f) : 0.0f;
        glPushMatrix();
            glTranslatef(wobX, wobY, 0.52f + len);
            glColor4f(1.0f, green, blue, alpha);
            glutSolidSphere(rad, 8, 6);
        glPopMatrix();
    }

    // --- Lapisan tengah: oranye-kuning, lebih panjang ---
    int midN = 8;
    for (int i = 0; i < midN; i++) {
        float frac  = (float)i / midN;
        float len   = (0.42f + 0.09f * sin(t * 14.0f + 0.8f)) * frac;
        float wobX  = 0.022f * sin(t * 13.0f + i * 2.1f);
        float wobY  = 0.022f * cos(t * 11.0f + i * 1.7f);
        float rad   = (0.075f - frac * 0.06f) * (1.0f + 0.1f * sin(t * 18.0f + i * 0.9f));
        float alpha = (1.0f - frac) * 0.65f;
        float green = 0.55f - frac * 0.35f;
        glPushMatrix();
            glTranslatef(wobX, wobY, 0.52f + len);
            glColor4f(1.0f, green, 0.0f, alpha);
            glutSolidSphere(rad, 7, 5);
        glPopMatrix();
    }

    // --- Lapisan luar: merah-oranye, panjang, transparan ---
    int outerN = 6;
    for (int i = 0; i < outerN; i++) {
        float frac  = (float)i / outerN;
        float len   = (0.65f + 0.12f * sin(t * 10.0f + 1.2f)) * frac;
        float wobX  = 0.035f * sin(t * 9.0f  + i * 2.5f);
        float wobY  = 0.035f * cos(t * 7.5f  + i * 2.0f);
        float rad   = (0.07f - frac * 0.055f) * (1.0f + 0.15f * sin(t * 12.0f + i));
        float alpha = (1.0f - frac) * 0.38f;
        glPushMatrix();
            glTranslatef(wobX, wobY, 0.52f + len);
            glColor4f(0.95f, 0.25f - frac * 0.1f, 0.0f, alpha);
            glutSolidSphere(rad, 6, 4);
        glPopMatrix();
    }

    // --- Percikan kecil (spark points) ---
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 14; i++) {
        float age  = fmod(t * 9.0f + i * 0.71f, 1.0f);
        float zOff = 0.54f + age * 0.7f;
        float spd  = age * 0.14f;
        float sx   = spd * sin(i * 2.39f + t * 6.0f);
        float sy   = spd * cos(i * 1.81f + t * 5.0f);
        float al   = (1.0f - age) * 0.7f;
        float heat = 1.0f - age * 0.6f;
        glColor4f(1.0f, heat * 0.8f, 0.0f, al);
        glVertex3f(sx, sy, zOff);
    }
    glEnd();
    glPointSize(1.0f);

    glDepthMask(GL_TRUE);
}

// ============================================================
//  GAMBAR ROKET PLAYER (menghadap depan / arah -Z)
// ============================================================
void drawPlayer() {
    if (!playerVisible) return;

    // Shadow blob di belakang roket (tidak tulis depth buffer)
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glColor4f(0.0f, 0.02f, 0.10f, 0.30f);
    glPushMatrix();
        glTranslatef(playerX + 0.10f, playerY - 0.13f, 0.0f);
        glScalef(1.28f, 0.50f, 0.90f);
        glutSolidSphere(0.28f, 10, 7);
    glPopMatrix();
    glDepthMask(GL_TRUE);

    glPushMatrix();
    glTranslatef(playerX, playerY, 0.0f);

        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

    bool flash = invincible;

    // BADAN UTAMA - silinder putih
    glPushMatrix();
        if (flash) glColor3f(1.0f, 0.4f, 0.4f);
        else       glColor3f(0.85f, 0.88f, 0.95f);
        glTranslatef(0.0f, 0.0f, -0.35f);
        drawCylinder(0.13f, 0.7f, 20);
    glPopMatrix();

    // NOSECONE - kerucut merah
    glPushMatrix();
        if (flash) glColor3f(1.0f, 0.6f, 0.6f);
        else       glColor3f(0.9f, 0.15f, 0.15f);
        glTranslatef(0.0f, 0.0f, -0.35f);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.13f, 0.38f, 20, 4);
    glPopMatrix();

    // CINCIN BIRU
    glPushMatrix();
        if (flash) glColor3f(0.9f, 0.5f, 0.5f);
        else       glColor3f(0.4f, 0.6f, 0.9f);
        glTranslatef(0.0f, 0.0f, -0.1f);
        drawCylinder(0.137f, 0.06f, 20);
    glPopMatrix();

    // NOZEL - abu gelap
    glPushMatrix();
        glColor3f(0.3f, 0.3f, 0.35f);
        glTranslatef(0.0f, 0.0f, 0.35f);
        glutSolidCone(0.1f, 0.15f, 20, 4);
    glPopMatrix();

    // 4 SIRIP - merah
    if (flash) glColor3f(1.0f, 0.6f, 0.6f);
    else       glColor3f(0.9f, 0.15f, 0.15f);
    glPushMatrix();
        glTranslatef(0.13f, 0.0f, 0.2f);
        glScalef(0.18f, 0.04f, 0.28f);
        glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.13f, 0.0f, 0.2f);
        glScalef(0.18f, 0.04f, 0.28f);
        glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 0.13f, 0.2f);
        glScalef(0.04f, 0.18f, 0.28f);
        glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -0.13f, 0.2f);
        glScalef(0.04f, 0.18f, 0.28f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // ENGINE GLOW - berdenyut mengikuti api
    float gPulse = 0.07f + 0.025f * sin(engineTime * 22.0f);
    float gInner = 0.04f + 0.018f * sin(engineTime * 28.0f + 0.5f);
    glPushMatrix();
        glColor3f(1.0f, 0.5f + 0.15f * sin(engineTime * 20.0f), 0.0f);
        glTranslatef(0.0f, 0.0f, 0.52f);
        glutSolidSphere(gPulse, 12, 12);
    glPopMatrix();
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.5f + 0.3f * sin(engineTime * 26.0f));
        glTranslatef(0.0f, 0.0f, 0.54f);
        glutSolidSphere(gInner, 10, 10);
    glPopMatrix();

    // API EXHAUST
    drawExhaust();

    // PIERCE SHIELD - lingkaran cyan saat aktif
    if (pierceMode) {
        float shieldR = 0.35f + 0.05f * sin(engineTime * 15.0f);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glColor4f(0.0f, 0.85f, 1.0f, 0.18f + 0.08f * sin(engineTime * 12.0f));
        glutSolidSphere(shieldR, 16, 12);
        glColor4f(0.3f, 1.0f, 1.0f, 0.6f);
        glutWireSphere(shieldR + 0.01f, 14, 10);
        glDepthMask(GL_TRUE);
    }

    glPopMatrix();
}
