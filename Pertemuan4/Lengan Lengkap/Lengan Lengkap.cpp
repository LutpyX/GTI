#include <GL/glut.h>

static int shoulder = 0, elbow = 0;
static int wrist = 0;
static int finger = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // ================= SHOULDER =================
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

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

    glTranslatef(1.0, 0.0, 0.0);

    // netralkan rotasi
    glRotatef(-(GLfloat)(shoulder + elbow), 0.0, 0.0, 1.0);

    // rotasi wrist
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);

    // telapak pipih
    glPushMatrix();
        glScalef(0.8, 0.8, 0.2);
        glutWireCube(1.0);
    glPopMatrix();

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

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Lengan + Tangan + Jari + Jempol");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
