#pragma once
#include "globals.h"

void initStars() {
    for (int i = 0; i < MAX_STARS; i++) {
        starField[i].x = randFloat(-25.0f, 25.0f);
        starField[i].y = randFloat(-18.0f, 18.0f);
        starField[i].z = randFloat(-20.0f, -90.0f);

        float roll = randFloat(0.0f, 1.0f);
        if (roll < 0.07f) {
            starField[i].r = 0.7f; starField[i].g = 0.85f; starField[i].b = 1.0f;
            starField[i].size = randFloat(2.5f, 3.5f);
        } else if (roll < 0.14f) {
            starField[i].r = 1.0f; starField[i].g = 0.95f; starField[i].b = 0.7f;
            starField[i].size = randFloat(2.0f, 3.0f);
        } else if (roll < 0.20f) {
            starField[i].r = 1.0f; starField[i].g = 0.6f; starField[i].b = 0.6f;
            starField[i].size = randFloat(1.8f, 2.5f);
        } else {
            float b = randFloat(0.5f, 1.0f);
            starField[i].r = b; starField[i].g = b; starField[i].b = b;
            starField[i].size = randFloat(1.0f, 2.0f);
        }
    }
}

void drawStars() {
    glDisable(GL_DEPTH_TEST);
    float curSize = -1.0f;
    for (int i = 0; i < MAX_STARS; i++) {
        if (starField[i].size != curSize) {
            if (curSize >= 0) glEnd();
            curSize = starField[i].size;
            glPointSize(curSize);
            glBegin(GL_POINTS);
        }
        glColor3f(starField[i].r, starField[i].g, starField[i].b);
        glVertex3f(starField[i].x, starField[i].y, starField[i].z);
    }
    glEnd();
    glPointSize(1.0f);
    glEnable(GL_DEPTH_TEST);
}
