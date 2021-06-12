#include <GL/freeglut.h>
#include <ctime>
#include <cstdlib>

GLfloat angle = 0;
GLfloat col[12];

void renderString(float x, float y, float z, void *font, char *string)
{ //Doesn't fucking work
    char *c;
    glRasterPos3f(x, y, z);
    for(c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void spin()
{
    angle += 1;
    if(angle > 360) {
        angle = 0;
    }
    glutPostRedisplay();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glColor3f(0.5, 0.2, 0.7);
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < 12; i++) {
        col[i] = (double)rand()/RAND_MAX;
    }
}

void face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glBegin(GL_POLYGON);
        glColor3f(col[0], col[1], col[2]);
        glVertex3fv(A);
        glColor3f(col[3], col[4], col[5]);
        glVertex3fv(B);
        glColor3f(col[6], col[7], col[8]);
        glVertex3fv(C);
        glColor3f(col[9], col[10], col[11]);
        glVertex3fv(D);
    glEnd();
}

void cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], 
          GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    //glColor3f(1, 0, 0);
    face(V0, V1, V2, V3);

    //glColor3f(0, 1, 0);
    face(V4, V5, V6, V7);

    //glColor3f(0, 0, 1);
    face(V0, V3, V7, V4);

    //glColor3f(0, 1, 1);
    face(V1, V2, V6, V5);

    //glColor3f(1, 0, 1);
    face(V0, V1, V5, V4);

    //glColor3f(1, 1, 0);
    face(V3, V2, V6, V7);
}

void draw()
{
    GLfloat V[8][3] = {
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5},

        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(angle, 1, 1, 1);

    cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(600, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Overklig Motor 1.0");
    init();
    glutDisplayFunc(draw);
    glutIdleFunc(spin);
    glutMainLoop();
    return 0;
}