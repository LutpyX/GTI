#pragma once
#include "globals.h"

// ============================================================
//  TEKS HUD
// ============================================================
void drawText(float x, float y, const char* text, float r, float g, float b,
              void* font = GLUT_BITMAP_HELVETICA_12) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c; c++)
        glutBitmapCharacter(font, *c);
}

// ============================================================
//  HATI HP
// ============================================================
void drawHeartShape(float cx, float cy, float size, bool filled) {
    int n = 50;
    const float scale = size / 16.0f;

    if (filled) glColor3f(1.0f, 0.15f, 0.25f);
    else        glColor3f(0.25f, 0.08f, 0.1f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy + size * 0.1f);
    for (int i = 0; i <= n; i++) {
        float t = i * 2.0f * PI / n;
        float hx = 16.0f * sin(t)*sin(t)*sin(t);
        float hy = 13.0f*cos(t) - 5.0f*cos(2*t) - 2.0f*cos(3*t) - cos(4*t);
        glVertex2f(cx + hx * scale, cy + hy * scale);
    }
    glEnd();

    if (filled) glColor3f(0.6f, 0.0f, 0.05f);
    else        glColor3f(0.5f, 0.2f, 0.2f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= n; i++) {
        float t = i * 2.0f * PI / n;
        float hx = 16.0f * sin(t)*sin(t)*sin(t);
        float hy = 13.0f*cos(t) - 5.0f*cos(2*t) - 2.0f*cos(3*t) - cos(4*t);
        glVertex2f(cx + hx * scale, cy + hy * scale);
    }
    glEnd();
    glLineWidth(1.0f);
}

// ============================================================
//  PANEL BACKGROUND (gradient + double border)
// ============================================================
void drawPanel(float x, float y, float w, float h,
               float r, float g, float b, float a) {
    glEnable(GL_BLEND);
    float sd = 5.0f;
    glColor4f(0.0f, 0.0f, 0.0f, 0.42f);
    glBegin(GL_QUADS);
        glVertex2f(x+sd,   y-sd);
        glVertex2f(x+w+sd, y-sd);
        glVertex2f(x+w+sd, y+h-sd);
        glVertex2f(x+sd,   y+h-sd);
    glEnd();
    glBegin(GL_QUADS);
        glColor4f(r*0.50f, g*0.50f, b*0.50f, a);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glColor4f(r,    g,    b,    a);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();
    glColor4f(0.0f, 0.0f, 0.0f, 0.95f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,   y);   glVertex2f(x+w, y);
        glVertex2f(x+w, y+h); glVertex2f(x,   y+h);
    glEnd();
    float gr = r*2.0f > 1.0f ? 1.0f : r*2.0f;
    float gg = g*2.0f > 1.0f ? 1.0f : g*2.0f;
    float gb = b*2.0f > 1.0f ? 1.0f : b*2.0f;
    glColor4f(gr, gg, gb, 0.45f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x+2,   y+2);   glVertex2f(x+w-2, y+2);
        glVertex2f(x+w-2, y+h-2); glVertex2f(x+2,   y+h-2);
    glEnd();
}

// ============================================================
//  PROGRESS BAR HELPER
// ============================================================
void drawProgressBar(float x, float y, float w, float h,
                     float ratio, float fr, float fg, float fb) {
    glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x,   y); glVertex2f(x+w, y);
        glVertex2f(x+w, y+h); glVertex2f(x,  y+h);
    glEnd();
    float fw = w * ratio;
    if (fw > 1.0f) {
        glBegin(GL_QUADS);
            glColor4f(fr*0.65f, fg*0.65f, fb*0.65f, 0.95f);
            glVertex2f(x,    y); glVertex2f(x+fw, y);
            glColor4f(fr,    fg,    fb,    0.95f);
            glVertex2f(x+fw, y+h); glVertex2f(x,  y+h);
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 0.08f);
        float mid = y + h * 0.45f;
        glBegin(GL_QUADS);
            glVertex2f(x,    mid); glVertex2f(x+fw, mid);
            glVertex2f(x+fw, y+h); glVertex2f(x,   y+h);
        glEnd();
    }
    glColor4f(0.25f, 0.25f, 0.25f, 0.9f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,   y); glVertex2f(x+w, y);
        glVertex2f(x+w, y+h); glVertex2f(x, y+h);
    glEnd();
}

// ============================================================
//  HUD UTAMA
// ============================================================
void drawHUD() {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();

    const float M = 15.0f;
    char buf[128];

    // ── PANEL KIRI ATAS : SCORE + MODE ───────────────────────
    {
        float pw = 235, ph = 68;
        float px = M, py = windowHeight - ph - M;
        drawPanel(px, py, pw, ph, 0.04f, 0.09f, 0.22f, 0.82f);

        glColor4f(0.35f, 0.60f, 1.0f, 0.45f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        drawText(px+10, py+ph-15, "SCORE",
                 0.50f, 0.78f, 1.0f, GLUT_BITMAP_HELVETICA_12);

        sprintf(buf, "%d", score);
        drawText(px+10, py+ph-44, buf,
                 0.90f, 1.0f, 0.45f, GLUT_BITMAP_HELVETICA_18);

        if (projMode == PERSPECTIVE) {
            const char* pts[] = { "1-Titik", "2-Titik", "3-Titik" };
            sprintf(buf, "Perspektif  %s", pts[perspPoint]);
            drawText(px+10, py+8, buf, 0.50f, 0.78f, 0.52f, GLUT_BITMAP_HELVETICA_12);
        } else {
            drawText(px+10, py+8, "Ortografis  Top-Down",
                     0.88f, 0.78f, 0.32f, GLUT_BITMAP_HELVETICA_12);
        }
    }

    // ── PANEL KANAN ATAS : HEALTH ─────────────────────────────
    {
        float pw = 168, ph = 62;
        float px = windowWidth - pw - M;
        float py = windowHeight - ph - M;
        drawPanel(px, py, pw, ph, 0.20f, 0.04f, 0.07f, 0.84f);

        glColor4f(1.0f, 0.30f, 0.42f, 0.42f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        drawText(px+10, py+ph-15, "HEALTH",
                 1.0f, 0.48f, 0.58f, GLUT_BITMAP_HELVETICA_12);

        float totalHW  = 3 * 30.0f;
        float startHX  = px + (pw - totalHW) * 0.5f + 15;
        float heartY   = py + 20;
        for (int i = 0; i < 3; i++)
            drawHeartShape(startHX + i * 30, heartY, 13.0f, i < playerHP);
    }

    // ── PANEL KANAN BAWAH : FUEL ──────────────────────────────
    {
        float pw = 190, ph = 54;
        float px = windowWidth - pw - M;
        float py = M;
        drawPanel(px, py, pw, ph, 0.04f, 0.14f, 0.04f, 0.84f);

        float ratio = fuel / maxFuel;
        float fr    = (ratio < 0.5f) ? 1.0f : (2.0f - ratio * 2.0f);
        float fg    = (ratio > 0.5f) ? 1.0f : (ratio * 2.0f);
        bool  blink = ratio < 0.2f && (int)(engineTime / 0.25f) % 2 == 0;
        if (blink) { fr = 1.0f; fg = 0.0f; }

        glColor4f(0.20f, 0.80f, 0.20f, 0.38f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        if (fuelDepleted)
            drawText(px+10, py+ph-15, "FUEL  HABIS!",
                     1.0f, 0.20f, 0.20f, GLUT_BITMAP_HELVETICA_12);
        else
            drawText(px+10, py+ph-15, "FUEL",
                     0.30f, 1.0f, 0.30f, GLUT_BITMAP_HELVETICA_12);

        sprintf(buf, "%d%%", (int)(ratio * 100));
        drawText(px+pw-36, py+ph-15, buf, fr, fg, 0.0f, GLUT_BITMAP_HELVETICA_12);

        if (!blink)
            drawProgressBar(px+8, py+8, pw-16, 14, ratio, fr, fg, 0.0f);
        else {
            glColor4f(0.35f, 0.04f, 0.04f, 0.85f);
            glBegin(GL_QUADS);
                glVertex2f(px+8, py+8);    glVertex2f(px+pw-8, py+8);
                glVertex2f(px+pw-8, py+22); glVertex2f(px+8, py+22);
            glEnd();
        }
    }

    // ── PANEL PIERCE (kanan, di atas fuel — hanya saat aktif) ─
    if (pierceMode) {
        float pw = 190, ph = 50;
        float px = windowWidth - pw - M;
        float py = M + 54 + 8;
        drawPanel(px, py, pw, ph, 0.0f, 0.13f, 0.20f, 0.87f);

        glColor4f(0.0f, 0.75f, 0.85f, 0.38f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        drawText(px+10, py+ph-15, "PIERCE",
                 0.0f, 1.0f, 0.90f, GLUT_BITMAP_HELVETICA_12);
        sprintf(buf, "%.1fs", pierceDuration - pierceTimer);
        drawText(px+pw-36, py+ph-15, buf,
                 0.50f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);

        float ratio = 1.0f - pierceTimer / pierceDuration;
        drawProgressBar(px+8, py+8, pw-16, 12, ratio, 0.0f, 1.0f, 0.85f);
    }

    // ── PANEL KIRI BAWAH : KONTROL ────────────────────────────
    {
        float pw = 298, ph = 55;
        float px = M, py = M;
        drawPanel(px, py, pw, ph, 0.04f, 0.07f, 0.18f, 0.78f);

        glColor4f(0.30f, 0.52f, 0.95f, 0.38f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        drawText(px+10, py+ph-15, "KONTROL",
                 0.50f, 0.75f, 1.0f, GLUT_BITMAP_HELVETICA_12);
        drawText(px+10, py+27, "WASD / Arrow : Gerak      ESC : Keluar",
                 0.65f, 0.70f, 0.88f, GLUT_BITMAP_HELVETICA_12);
        drawText(px+10, py+10, "P / O : Proyeksi      1 / 2 / 3 : Kamera",
                 0.65f, 0.70f, 0.88f, GLUT_BITMAP_HELVETICA_12);
    }

    // ── NOTIFIKASI TENGAH : +FUEL ─────────────────────────────
    if (fuelCollectFlash > 0.0f) {
        float alpha = fuelCollectFlash > 0.4f ? 1.0f : fuelCollectFlash / 0.4f;
        glColor4f(0.0f, 0.0f, 0.0f, alpha * 0.55f);
        glRasterPos2f(windowWidth*0.5f - 26, windowHeight*0.5f + 44);
        const char* txt = "+FUEL";
        for (const char* c = txt; *c; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        glColor4f(1.0f, 0.88f, 0.0f, alpha);
        glRasterPos2f(windowWidth*0.5f - 27, windowHeight*0.5f + 45);
        for (const char* c = txt; *c; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // ── NOTIFIKASI HIT ────────────────────────────────────────
    if (invincible && !gameOver) {
        float flashA = (int)(invincibleTimer / 0.10f) % 2 == 0 ? 1.0f : 0.65f;
        glColor4f(1.0f, 0.10f, 0.12f, flashA);
        glRasterPos2f(windowWidth*0.5f - 38, windowHeight*0.5f + 62);
        const char* hit = "!! KENA !!";
        for (const char* c = hit; *c; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // ── GAME OVER OVERLAY ─────────────────────────────────────
    if (gameOver) {
        glColor4f(0.0f, 0.0f, 0.03f, 0.84f);
        glBegin(GL_QUADS);
            glVertex2f(0, 0); glVertex2f(windowWidth, 0);
            glVertex2f(windowWidth, windowHeight); glVertex2f(0, windowHeight);
        glEnd();

        float gW = 430, gH = 245;
        float gX = (windowWidth  - gW) * 0.5f;
        float gY = (windowHeight - gH) * 0.5f;
        drawPanel(gX, gY, gW, gH, 0.20f, 0.02f, 0.05f, 0.96f);

        glColor4f(1.0f, 0.22f, 0.30f, 0.65f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(gX+14, gY+gH-50); glVertex2f(gX+gW-14, gY+gH-50);
        glEnd();
        glLineWidth(1.0f);

        drawText(gX + gW*0.5f - 74, gY+gH-38,
                 "GAME  OVER", 1.0f, 0.15f, 0.22f, GLUT_BITMAP_TIMES_ROMAN_24);

        sprintf(buf, "Skor Akhir :  %d", score);
        drawText(gX + gW*0.5f - 55, gY+gH-84,
                 buf, 1.0f, 0.88f, 0.35f, GLUT_BITMAP_HELVETICA_18);

        drawText(gX + gW*0.5f - 80, gY+gH-114,
                 "Roket kamu hancur di luar angkasa...",
                 0.82f, 0.55f, 0.58f, GLUT_BITMAP_HELVETICA_12);

        float totalHW = 3 * 38.0f;
        float shx = gX + (gW - totalHW) * 0.5f + 19;
        for (int i = 0; i < 3; i++)
            drawHeartShape(shx + i * 38, gY + 82, 14.0f, false);

        glColor4f(0.55f, 0.12f, 0.18f, 0.45f);
        glBegin(GL_LINES);
            glVertex2f(gX+14, gY+46); glVertex2f(gX+gW-14, gY+46);
        glEnd();

        float blinkA = (int)(engineTime / 0.55f) % 2 == 0 ? 1.0f : 0.38f;
        glColor4f(0.92f, 0.92f, 0.92f, blinkA);
        glRasterPos2f(gX + gW*0.5f - 78, gY + 26);
        const char* rt = "Tekan  [ R ]  untuk  Restart";
        for (const char* c = rt; *c; c++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
