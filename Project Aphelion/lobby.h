#pragma once
#include "globals.h"
#include "hud.h"

// ============================================================
//  LOBBY SCREEN
// ============================================================

static inline float _lbTextW(void* font, const char* str) {
    return (float)glutBitmapLength(font, (const unsigned char*)str);
}

static void _lbText(float x, float y, const char* str,
                    float r, float g, float b, float a, void* font) {
    glColor4f(r, g, b, a);
    glRasterPos2f(x, y);
    for (const char* c = str; *c; c++)
        glutBitmapCharacter(font, *c);
}

static void _lbCenterText(float cx, float y, const char* str,
                           float r, float g, float b, float a, void* font) {
    float x = cx - _lbTextW(font, str) * 0.5f;
    _lbText(x, y, str, r, g, b, a, font);
}

// ── BINTANG DEKORATIF KECIL (simbol bintang 4 sudut) ────────
static void _lbDrawStar4(float cx, float cy, float r1, float r2,
                          float red, float grn, float blu, float a) {
    glColor4f(red, grn, blu, a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 8; i++) {
        float ang = i * (2.0f * PI / 8.0f);
        float rad = (i % 2 == 0) ? r1 : r2;
        glVertex2f(cx + cosf(ang) * rad, cy + sinf(ang) * rad);
    }
    glEnd();
}

// ── BINGKAI DEKORATIF DI SUDUT ───────────────────────────────
static void _lbDrawCornerFrame(float W, float H) {
    float sz = 28.0f;
    glColor4f(0.35f, 0.62f, 1.0f, 0.55f);
    glLineWidth(1.5f);

    // Sudut kiri bawah
    glBegin(GL_LINE_STRIP);
        glVertex2f(12, 12 + sz); glVertex2f(12, 12); glVertex2f(12 + sz, 12);
    glEnd();
    // Sudut kanan bawah
    glBegin(GL_LINE_STRIP);
        glVertex2f(W-12-sz, 12); glVertex2f(W-12, 12); glVertex2f(W-12, 12+sz);
    glEnd();
    // Sudut kiri atas
    glBegin(GL_LINE_STRIP);
        glVertex2f(12, H-12-sz); glVertex2f(12, H-12); glVertex2f(12+sz, H-12);
    glEnd();
    // Sudut kanan atas
    glBegin(GL_LINE_STRIP);
        glVertex2f(W-12-sz, H-12); glVertex2f(W-12, H-12); glVertex2f(W-12, H-12-sz);
    glEnd();

    glLineWidth(1.0f);
}

void drawLobbyScreen() {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();
    glEnable(GL_BLEND);

    float W  = (float)windowWidth;
    float H  = (float)windowHeight;
    float cx = W * 0.5f;

    // ── DARK VIGNETTE OVERLAY ──────────────────────────────────
    glColor4f(0.0f, 0.0f, 0.06f, 0.74f);
    glBegin(GL_QUADS);
        glVertex2f(0,0); glVertex2f(W,0); glVertex2f(W,H); glVertex2f(0,H);
    glEnd();

    // ── BINGKAI SUDUT ─────────────────────────────────────────
    _lbDrawCornerFrame(W, H);

    // ── TITLE ─────────────────────────────────────────────────
    {
        void* font = GLUT_BITMAP_TIMES_ROMAN_24;
        const char* title = "PROJECT  APHELION";
        float ty = H * 0.748f;

        // Lapisan glow biru
        struct { float off, a; } glow[] = {{4,0.08f},{3,0.16f},{2,0.28f},{1,0.42f}};
        for (int g = 0; g < 4; g++) {
            float ox = glow[g].off, oy = glow[g].off;
            float tw = _lbTextW(font, title);
            _lbText(cx - tw*0.5f + ox, ty - oy, title, 0.20f, 0.55f, 1.0f, glow[g].a, font);
            _lbText(cx - tw*0.5f - ox, ty + oy, title, 0.20f, 0.55f, 1.0f, glow[g].a, font);
        }
        // Teks utama
        _lbCenterText(cx, ty, title, 0.62f, 0.88f, 1.0f, 1.0f, font);
    }

    // ── BINTANG DEKORATIF DI KIRI-KANAN JUDUL ─────────────────
    {
        float sy  = H * 0.748f + 7.0f;
        float pul = (engineTime * 1.8f);
        float pulse = 0.70f + 0.30f * sinf(pul);
        float br = 0.45f * pulse, bg = 0.72f * pulse, bb = 1.0f * pulse;
        _lbDrawStar4(cx - 205, sy, 7.0f, 3.5f, br, bg, bb, 0.85f);
        _lbDrawStar4(cx + 205, sy, 7.0f, 3.5f, br, bg, bb, 0.85f);
        _lbDrawStar4(cx - 190, sy - 1, 4.0f, 2.0f, br, bg, bb, 0.50f);
        _lbDrawStar4(cx + 190, sy - 1, 4.0f, 2.0f, br, bg, bb, 0.50f);
    }

    // ── SUBTITLE ──────────────────────────────────────────────
    {
        void* f12 = GLUT_BITMAP_HELVETICA_12;
        const char* sub = "3 D   S P A C E   D O D G E";
        float sy = H * 0.748f - 26.0f;
        _lbCenterText(cx, sy, sub, 0.40f, 0.68f, 0.95f, 0.88f, f12);
    }

    // ── DIVIDER ───────────────────────────────────────────────
    float divY = H * 0.748f - 42.0f;
    glColor4f(0.28f, 0.55f, 1.0f, 0.55f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(cx - 220, divY); glVertex2f(cx + 220, divY);
    glEnd();
    glColor4f(0.20f, 0.40f, 0.80f, 0.25f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(cx - 210, divY - 3); glVertex2f(cx + 210, divY - 3);
    glEnd();

    // ── PANEL KONTROL ─────────────────────────────────────────
    {
        float pw = 420, ph = 120;
        float px = cx - pw * 0.5f;
        float py = divY - ph - 14.0f;
        drawPanel(px, py, pw, ph, 0.04f, 0.09f, 0.24f, 0.84f);

        glColor4f(0.28f, 0.55f, 1.0f, 0.40f);
        glBegin(GL_LINES);
            glVertex2f(px+8, py+ph-22); glVertex2f(px+pw-8, py+ph-22);
        glEnd();

        void* f12 = GLUT_BITMAP_HELVETICA_12;
        drawText(px+12, py+ph-14, "KONTROL", 0.48f, 0.76f, 1.0f, f12);
        drawText(px+16, py+ph-40,  "WASD / Arrow     :  Gerak", 0.70f, 0.80f, 1.0f, f12);
        drawText(px+16, py+ph-58,  "P / O            :  Toggle Proyeksi", 0.70f, 0.80f, 1.0f, f12);
        drawText(px+16, py+ph-76,  "1 / 2 / 3        :  Mode Kamera", 0.70f, 0.80f, 1.0f, f12);
        drawText(px+16, py+ph-96,  "R  :  Restart                ESC  :  Keluar", 0.70f, 0.80f, 1.0f, f12);
    }

    // ── BLINKING START PROMPT ─────────────────────────────────
    {
        void* f18 = GLUT_BITMAP_HELVETICA_18;
        const char* prompt = "[ ENTER ]  atau  [ SPACE ]  untuk  Mulai";
        float pa   = (int)(engineTime / 0.65f) % 2 == 0 ? 1.0f : 0.25f;
        float py   = divY - 120.0f - 14.0f - 44.0f;
        float tw   = _lbTextW(f18, prompt);

        // Shadow
        glColor4f(0.0f, 0.0f, 0.0f, pa * 0.65f);
        glRasterPos2f(cx - tw*0.5f + 1, py - 1);
        for (const char* c = prompt; *c; c++) glutBitmapCharacter(f18, *c);
        // Teks
        glColor4f(0.88f, 1.0f, 0.48f, pa);
        glRasterPos2f(cx - tw*0.5f, py);
        for (const char* c = prompt; *c; c++) glutBitmapCharacter(f18, *c);
    }

    // ── FOOTER ────────────────────────────────────────────────
    {
        void* f12 = GLUT_BITMAP_HELVETICA_12;
        const char* footer = "Grafika dan Teknik Interaktif  |  Kelompok 9 |  2026";
        _lbCenterText(cx, 16.0f, footer, 0.32f, 0.42f, 0.68f, 0.68f, f12);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
