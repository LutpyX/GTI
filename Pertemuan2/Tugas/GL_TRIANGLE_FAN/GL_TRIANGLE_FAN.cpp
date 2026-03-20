#include <gl/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0); // pusat
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.5, -0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("TRIANGLE FAN");
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();
}
