#include <GL/freeglut.h>

// Variables for rotation
float angleX = 10.0f; // Initial rotation on X-axis
float angleY = 30.0f; // Initial rotation on Y-axis

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to draw a simple cube representing TV
void drawTV() {
    // TV Frame
    glPushMatrix();
    glColor3f(0.13f, 0.13f, 0.13f);  // Light gray for the frame
    glScalef(2.0f, 1.0, 0.1f);   // Scale to make it look like a TV frame
    glutSolidCube(1.0);
    glPopMatrix();

    // TV Screen
    glPushMatrix();
    glColor3f(0.04f, 0.04f, 0.04f);  // Black for the screen
    glTranslatef(0.0f, 0.0f, 0.06f);  // Move slightly forward for the screen
    glScalef(1.8f, 0.9f, 0.01f);  // Scale the screen
    glutSolidCube(1.0);
    glPopMatrix();

    // TV Stand
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark gray for the stand
    glTranslatef(0.0f, -0.7f, 0.0f); // Move the stand below the TV
    glScalef(0.5f, 0.05f, 0.5f);   // Scale to form a flat stand
    glutSolidCube(1.0);
    glPopMatrix();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera
    gluLookAt(0.0, 0.0, 5.0,  // Camera position
        0.0, 0.0, 0.0,  // Look at point
        0.0, 1.0, 0.0); // Up direction

    // Apply rotation transformations
    glRotatef(angleX, 1.0, 0.0, 0.0);  // Rotate slightly on X-axis
    glRotatef(angleY, 0.0, 1.0, 0.0);  // Rotate on Y-axis to give 3D effect

    // Draw the TV
    drawTV();

    glutSwapBuffers();
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    if (key == 27)  // ESC to exit
        exit(0);
}

// Function to handle special key input (arrow keys)
void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT)
        angleY += 5.0f;
    else if (key == GLUT_KEY_LEFT)
        angleY -= 5.0f;
    else if (key == GLUT_KEY_UP)
        angleX -= 5.0f;
    else if (key == GLUT_KEY_DOWN)
        angleX += 5.0f;

    glutPostRedisplay();  // Redraw the scene with new transformations
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D TV with FreeGLUT");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Set up callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Set clear color (background color)
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
