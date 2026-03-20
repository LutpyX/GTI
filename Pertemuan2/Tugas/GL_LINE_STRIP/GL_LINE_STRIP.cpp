#include <gl/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.5, 0.0);
        glVertex2f(-0.2, 0.5);
        glVertex2f(0.2, 0.0);
        glVertex2f(0.5, 0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("LINE STRIP");
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();
}
