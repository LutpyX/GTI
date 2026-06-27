#include <GL/glut.h>
#include <math.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++)
    {
        float sudut = i * 3.14159 / 180.0;
        glVertex2f(0.5 * cos(sudut), 0.5 * sin(sudut));
    }
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lingkaran");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
