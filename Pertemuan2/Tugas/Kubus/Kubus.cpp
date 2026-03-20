#include <gl/glut.h>

// fungsi buat 1 kubus (kotak)
void kotak(float x, float y) {
    float size = 0.2;

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    kotak(-0.4, -0.4);
    kotak(-0.1, -0.4);
    kotak(0.2, -0.4);

    kotak(-0.4, -0.1);
    kotak(0.2, -0.1);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Mangkok 5 Kubus");

    glutDisplayFunc(display);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();
}
