#include <GL/glut.h>
#include <math.h>

void drawCloud(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1, 1, 1);
    float cx[] = {0, 25, -25, 40, -40};
    float cy[] = {0, -8, -8, -15, -15};
    float cr[] = {22, 18, 18, 14, 14};
    for (int i = 0; i < 5; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 30; j++) {
            float a = j * 2 * 3.14159f / 30;
            glVertex2f(cx[i] + cr[i]*cos(a), cy[i] + cr[i]*sin(a));
        }
        glEnd();
    }
    glPopMatrix();
}

void drawTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.4f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-8, 0);
    glVertex2f(8, 0);
    glVertex2f(8, 60);
    glVertex2f(-8, 60);
    glEnd();
    glColor3f(0.13f, 0.45f, 0.13f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i++) {
        float a = i * 2 * 3.14159f / 8 - 3.14159f/8;
        glVertex2f(50*cos(a), 60 + 50*sin(a));
    }
    glEnd();
    glPopMatrix();
}

void drawGrass(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.1f, 0.5f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-12, 0); glVertex2f(12, 0); glVertex2f(0, 20);
    glVertex2f(-8, 0);  glVertex2f(6, 0);  glVertex2f(-10, 18);
    glVertex2f(-6, 0);  glVertex2f(14, 0); glVertex2f(10, 18);
    glEnd();
    glPopMatrix();
}

void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++) {
        float a = i * 2 * 3.14159f / 32;
        glVertex2f(38*cos(a), 38*sin(a));
    }
    glEnd();
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++) {
        float a = i * 2 * 3.14159f / 32;
        glVertex2f(28*cos(a), 28*sin(a));
    }
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 16; i++) {
        float a = i * 2 * 3.14159f / 16;
        glVertex2f(10*cos(a), 10*sin(a));
    }
    glEnd();
    for (int s = 0; s < 4; s++) {
        glPushMatrix();
        glRotatef(s * 90.0f, 0, 0, 1);
        glColor3f(0.15f, 0.15f, 0.15f);
        glBegin(GL_QUADS);
        glVertex2f(-4, 10); glVertex2f(4, 10);
        glVertex2f(4, 28);  glVertex2f(-4, 28);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void drawCar(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(0.0f, 0.18f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(340, 0);
    glVertex2f(340, 80);
    glVertex2f(0, 80);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(50, 80);
    glVertex2f(90, 160);
    glVertex2f(260, 160);
    glVertex2f(310, 80);
    glEnd();

    glColor3f(0.55f, 0.72f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(100, 85);
    glVertex2f(130, 150);
    glVertex2f(205, 150);
    glVertex2f(205, 85);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(215, 85);
    glVertex2f(215, 150);
    glVertex2f(255, 150);
    glVertex2f(290, 85);
    glEnd();

    glColor3f(0.0f, 0.12f, 0.55f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(210, 85); glVertex2f(210, 155);
    glEnd();

    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(200, 30);
    glVertex2f(255, 30);
    glVertex2f(255, 50);
    glVertex2f(200, 50);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(5, 30);
    glVertex2f(30, 30);
    glVertex2f(30, 55);
    glVertex2f(5, 55);
    glEnd();

    glColor3f(0.85f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(308, 28);
    glVertex2f(330, 28);
    glVertex2f(330, 50);
    glVertex2f(308, 50);
    glEnd();

    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(0, -18);
    glVertex2f(50, -18);
    glVertex2f(50, 5);
    glVertex2f(0, 5);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(290, -18);
    glVertex2f(340, -18);
    glVertex2f(340, 5);
    glVertex2f(290, 5);
    glEnd();

    drawWheel(75, -18);
    drawWheel(265, -18);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int W = 800, H = 500;

    glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(W, 0);
    glVertex2f(W, H); glVertex2f(0, H);
    glEnd();

    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(0, 120); glVertex2f(W, 120);
    glVertex2f(W, 210); glVertex2f(0, 210);
    glEnd();

    glColor3f(1, 1, 1);
    int dashes[] = {30, 150, 270, 390, 510, 630, 750};
    for (int i = 0; i < 7; i++) {
        glBegin(GL_QUADS);
        glVertex2f(dashes[i], 158); glVertex2f(dashes[i]+80, 158);
        glVertex2f(dashes[i]+80, 172); glVertex2f(dashes[i], 172);
        glEnd();
    }

    glColor3f(0.18f, 0.6f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(W, 0);
    glVertex2f(W, 120); glVertex2f(0, 120);
    glEnd();

    float gx[] = {60,140,230,310,400,490,580,660,750};
    for (int i = 0; i < 9; i++) drawGrass(gx[i], 70);
    float gx2[] = {30,100,190,280,370,450,560,640,720};
    for (int i = 0; i < 9; i++) drawGrass(gx2[i], 95);

    drawCloud(140, 430);
    drawCloud(360, 420);
    drawCloud(570, 425);

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++) {
        float a = i * 2 * 3.14159f / 32;
        glVertex2f(730 + 32*cos(a), 460 + 32*sin(a));
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    float rays[][4] = {
        {730,500,730,510},{730,420,730,410},
        {690,460,680,460},{770,460,780,460},
        {703,487,696,494},{757,487,764,494},
        {703,433,696,426},{757,433,764,426}
    };
    for (int i = 0; i < 8; i++) {
        glBegin(GL_LINES);
        glVertex2f(rays[i][0], rays[i][1]);
        glVertex2f(rays[i][2], rays[i][3]);
        glEnd();
    }

    drawTree(60, 210);
    drawTree(710, 210);

    drawCar(215, 168);

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Car Scene");
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
