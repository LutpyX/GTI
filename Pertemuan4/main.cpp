#include <GL/glut.h>

static int shoulder = 0, elbow = 0;
static int wrist = 0;
static int finger = 0;

// ================= GRID =================
void drawGrid() {
    int i;

    float size = 5.0;   // luas grid
    float step = 0.2;   // jarak garis

    glBegin(GL_LINES);

    for (i = -25; i <= 25; i++) {
        float pos = i * step;

        // garis tebal tiap 5 garis
        if (i % 5 == 0)
            glLineWidth(2.0);
        else
            glLineWidth(1.0);

        glColor3f(0.5, 0.5, 0.5); // abu-abu

        // vertikal
        glVertex3f(pos, -size, 0.0);
        glVertex3f(pos,  size, 0.0);

        // horizontal
        glVertex3f(-size, pos, 0.0);
        glVertex3f( size, pos, 0.0);
    }

    glEnd();

    // ===== SUMBU X =====
    glLineWidth(3.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(-size, 0.0, 0.0);
        glVertex3f( size, 0.0, 0.0);
    glEnd();

    // ===== SUMBU Y =====
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, -size, 0.0);
        glVertex3f(0.0,  size, 0.0);
    glEnd();
}

// ================= INIT =================
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// ================= DISPLAY =================
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // FIX kamera (biar tidak hitam)
    glTranslatef(0.0, 0.0, -5.0);

    // GRID
    drawGrid();

    glPushMatrix();

    // ================= SHOULDER =================
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ================= ELBOW =================
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ================= WRIST =================
    glTranslatef(1.0, 0.0, 0.0);

    // tetap horizontal
    glRotatef(-(GLfloat)(shoulder + elbow), 0.0, 0.0, 1.0);
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);

    // telapak pipih
    glPushMatrix();
        glScalef(0.8, 0.8, 0.2);
        glutWireCube(1.0);
    glPopMatrix();

    // ================= 4 JARI =================
    float posisiJari[4] = {0.3, 0.1, -0.1, -0.3};

    for (int i = 0; i < 4; i++) {
        glPushMatrix();

            glTranslatef(0.5, posisiJari[i], 0.0);
            glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);
            glTranslatef(0.3, 0.0, 0.0);

            glScalef(0.6, 0.15, 0.1);
            glutWireCube(1.0);

        glPopMatrix();
    }

    // ================= JEMPOL =================
    glPushMatrix();

        glTranslatef(0.2, -0.5, 0.0);
        glRotatef(-40.0, 0.0, 0.0, 1.0);
        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);
        glTranslatef(0.3, 0.0, 0.0);

        glScalef(0.5, 0.2, 0.1);
        glutWireCube(1.0);

    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

// ================= RESHAPE =================
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
}

// ================= KEYBOARD =================
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;

        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;

        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;

        case 'f': finger = (finger + 5) % 360; break;
        case 'F': finger = (finger - 5) % 360; break;

        case 27: exit(0);
    }

    glutPostRedisplay();
}

// ================= MAIN =================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Lengan + Grid Milimeter FULL FINAL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
