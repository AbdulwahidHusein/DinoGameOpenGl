#include <GL/glut.h>

// Lighting initialization function
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.5f, 4.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_DEPTH_TEST);
}

void drawStreetLight() {
    // Draw the pole
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, 2.0f, 0.0f);
    glScalef(0.1f, 4.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the arm
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, 4.0f, 0.0f);
    glScalef(1.0f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the light bulb (an ellipsoid shape)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.5f, 4.0f, 0.0f);
    glScalef(0.2f, 0.3f, 0.2f);  // Scaling to make the sphere look like an ellipsoid
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(2.0, 5.0, 10.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);

    // Set material properties for the light bulb
    GLfloat bulbEmission[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, bulbEmission);

    drawStreetLight();

    // Reset emission to default
    GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glutSwapBuffers();
}

void setup() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    initLighting();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Street Light");
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
