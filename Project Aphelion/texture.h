#pragma once
#include "globals.h"
#include "imageloader.h"

void generateMeteorTexture() {
    printf("Mencoba load meteor.bmp...\n");
    fflush(stdout);

    Image* image = loadBMP("meteor.bmp");

    if (!image) {
        printf("ERROR: image null!\n");
        fflush(stdout);
        return;
    }

    printf("Load berhasil! Ukuran: %dx%d\n", image->width, image->height);
    printf("Pixels pointer: %p\n", (void*)image->pixels);
    fflush(stdout);

    if (!image->pixels) {
        printf("ERROR: pixels null!\n");
        fflush(stdout);
        delete image;
        return;
    }

    glGenTextures(1, &meteorTexture);
    glBindTexture(GL_TEXTURE_2D, meteorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    printf("Memanggil glTexImage2D...\n");
    fflush(stdout);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    printf("glTexImage2D selesai!\n");
    fflush(stdout);

    delete image;
}