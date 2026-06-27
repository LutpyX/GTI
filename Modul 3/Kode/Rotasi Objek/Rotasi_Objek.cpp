#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

void Segitiga(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(0.25f, -0.25f, 0.0f);
    glRotated(60.0, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);  glVertex3f(-0.05f, -0.05f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);  glVertex3f( 0.15f, -0.05f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);  glVertex3f(-0.05f,  0.05f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Rotasi Objek");
    glutDisplayFunc(Segitiga);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
