#pragma once
#include "globals.h"

void applyPerspectiveCamera() {
    switch (perspPoint) {
        case ONE_POINT:
            gluLookAt(playerX, playerY+0.8f, 4.5f,
                      playerX, playerY,      0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
        case TWO_POINT:
            gluLookAt(playerX+1.5f, playerY+1.0f, 4.5f,
                      playerX,      playerY,       0.0f,
                      0.0f, 1.0f, 0.0f);
            break;
        case THREE_POINT:
            gluLookAt(playerX+2.0f, playerY+2.5f, 3.5f,
                      playerX,      playerY,      -5.0f,
                      0.0f, 1.0f, 0.0f);
            break;
    }
}

void applyOrthographicCamera() {
    gluLookAt(playerX, 8.0f, -10.0f,
              playerX, 0.0f, -10.0f,
              0.0f,    0.0f,  -1.0f);
}
