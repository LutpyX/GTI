#include <GL/glut.h>
#include <math.h>

float sudutRoda = 0.0;
float radius = 1.0;

void gambarRoda()
{
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
    {
        float theta=i*3.14159/180;
        glVertex2f(radius*cos(theta),radius*sin(theta));
    }
    glEnd();

    // jari roda
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(radius,0);

        glVertex2f(0,0);
        glVertex2f(-radius,0);

        glVertex2f(0,0);
        glVertex2f(0,radius);

        glVertex2f(0,0);
        glVertex2f(0,-radius);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glColor3f(0,0,0);

    // roda kiri
    glPushMatrix();
        glTranslatef(-2,-1,0);
        glRotatef(sudutRoda,0,0,1);
        gambarRoda();
    glPopMatrix();

    // roda kanan
    glPushMatrix();
        glTranslatef(2,-1,0);
        glRotatef(sudutRoda,0,0,1);
        gambarRoda();
    glPopMatrix();

    // rangka sepeda
    glBegin(GL_LINES);
        glVertex2f(-2,-1);
        glVertex2f(0,1);

        glVertex2f(0,1);
        glVertex2f(2,-1);
    glEnd();

    glutSwapBuffers();
}

void animasi()
{
    sudutRoda -= 3; // roda berputar
    glutPostRedisplay();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-5,5);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Roda Berputar");

    glClearColor(1,1,1,1);

    glutDisplayFunc(display);
    glutIdleFunc(animasi);
    glutReshapeFunc(reshape);

    glutMainLoop();
}
