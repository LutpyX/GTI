#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

const float BOX_SIZE = 7.0f;

float _angle = 0.0f;

GLuint _textureId;

// =======================================
// HANDLE KEYBOARD
// =======================================
void handleKeypress(unsigned char key, int x, int y) {

    switch (key) {

    case 27:
        exit(0);

    }
}

// =======================================
// MEMBUAT TEXTURE
// =======================================
GLuint loadTexture(Image* image) {

    GLuint textureId;

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image->width,
                 image->height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image->pixels);

    return textureId;
}

// =======================================
// INIT RENDERING
// =======================================
void initRendering() {

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);

    // LOAD GAMBAR BMP
    Image* image = loadBMP("bg.bmp");

    _textureId = loadTexture(image);

    delete image;
}

// =======================================
// HANDLE RESIZE
// =======================================
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0,
                   (double)w / (double)h,
                   1.0,
                   200.0);
}

// =======================================
// DRAW SCENE
// =======================================
void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -20.0f);

    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
                   ambientLight);

    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};

    GLfloat lightPos[] = {-20.0f,
                           20.0f,
                           20.0f,
                           1.0f};

    glLightfv(GL_LIGHT0,
              GL_DIFFUSE,
              lightColor);

    glLightfv(GL_LIGHT0,
              GL_POSITION,
              lightPos);

    // ROTASI
    glRotatef(_angle,
              1.0f,
              1.0f,
              0.0f);

    // AKTIFKAN TEXTURE
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glColor3f(1.0f, 1.0f, 1.0f);

    // ===================================
    // KUBUS
    // ===================================
    glBegin(GL_QUADS);

    // DEPAN
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    // BELAKANG
    glNormal3f(0.0f, 0.0f, -1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    // KANAN
    glNormal3f(1.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    // KIRI
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    // ATAS
    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE/2,
                BOX_SIZE/2,
                BOX_SIZE/2);

    // BAWAH
    glNormal3f(0.0f, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
               -BOX_SIZE/2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-BOX_SIZE/2,
               -BOX_SIZE/2,
                BOX_SIZE/2);

    glEnd();

    glutSwapBuffers();
}

// =======================================
// UPDATE ANIMASI
// =======================================
void update(int value) {

    _angle += 1.0f;

    if (_angle > 360) {
        _angle -= 360;
    }

    glutPostRedisplay();

    glutTimerFunc(25,
                  update,
                  0);
}

// =======================================
// MAIN
// =======================================
int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);

    glutInitWindowSize(500, 500);

    glutCreateWindow("Kubus 6 Texture");

    initRendering();

    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);

    glutReshapeFunc(handleResize);

    glutTimerFunc(25,
                  update,
                  0);

    glutMainLoop();

    return 0;
}
