#include <gl/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.8, -0.5);
        glVertex2f(-0.6, 0.5);
        glVertex2f(-0.4, -0.5);
        glVertex2f(-0.2, 0.5);
        glVertex2f(0.0, -0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Triangle Strip FIX");
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();
}
