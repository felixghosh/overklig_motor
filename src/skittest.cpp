#include <GL/freeglut.h>

void renderString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y, z);
    for(c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

static void renderSceneCB()
{
    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(-0.8, -0.8);
    glColor3f(0, 1, 0);
    glVertex2f(0.8, -0.8);
    glColor3f(0, 0, 1);
    glVertex2f(0, 0.9);
    glEnd();
    glutSwapBuffers();
    renderString(10.0f, 10.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "HAR NI FRÅGOR? HAR NI PROBLEM?");
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCB);
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(400, 600);
    glutCreateWindow("Overklig Motor 1.0");
    initializeGlutCallbacks();
    glutMainLoop();
    return 0;
}