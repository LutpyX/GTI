#include <GL/glut.h>

void point()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // ukuran titik
    glPointSize(5.0f);

    glBegin(GL_POINTS);

        // warna merah
        glColor3f(1.0f, 0.0f, 0.0f);

        // posisi titik
        glVertex3f(0.25f, 0.25f, 0.0f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutCreateWindow("Titik");

    glutDisplayFunc(point);

    glClearColor(0.0f,0.0f,1.0f,1.0f);

    glutMainLoop();

    return 0;
}
