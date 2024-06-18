#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include<fstream>

using namespace std;

// Constants
static const int factor = 4;
static const int xcoord = 80;
static const double DEG2RAD = 3.1415926535897932384 / 180;

// Variables
static int gameLevel = 12;
static int pause = 0;
static double dino_y = 200;
static int canJump = 0;
static int walk = 0;
static int tree_x = 2500;
static int score = 0;
static int count = 100;
static int highScore = 0;

void animate(int);
void keyInput(unsigned char, int, int);
bool collision(double);
void specialKeyInput(int, int, int);
void generate_tree(int, double);
void reset();
void render();
void setup();
void drawDino(double, double, int);

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1230, 650);
    glutInitWindowPosition(50, 0);
    glutCreateWindow("Dino");
    setup();
    glutDisplayFunc(render);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();
    return 0;
}

void animate(int) {
    if (pause) {
        glutPostRedisplay();
        glutTimerFunc(gameLevel, animate, 1);
    }
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case ' ':
            pause = !pause;
            if (pause) animate(1);
            break;
    }
}

void getHighScore(){
    ifstream myfile;
    myfile.open("highscore.txt");
    myfile>>highScore;
}

void setHighScore(){
    ofstream myfile;
    myfile.open("highscore.txt");
    myfile<<highScore;
}
bool collision(double len) {
    if (abs(xcoord - tree_x) <= 70) {
        return (dino_y <= 650);
    }
    return false;
}

void specialKeyInput(int key, int x, int y) {
    if (key == GLUT_KEY_UP && canJump == 0 && dino_y <= 200.0) {
        canJump = 1;
    }
    //glutPostRedisplay();
}

void draw_tree(int tree_x, float len) {
    if (tree_x < 10) {
        score += 1;
        if (score % 9 == 0) {
            if (gameLevel > 1) { gameLevel -= 1; }
        }
    }

    len -= 0.15;
    // Color for the trunk
    glColor3f(0.55f, 0.27f, 0.07f);

    // Draw the trunk
    glBegin(GL_POLYGON);
    glVertex2f(tree_x - 15, 250 * len);
    glVertex2f(tree_x - 15, 650 * len);
    glVertex2f(tree_x + 15, 650 * len);
    glVertex2f(tree_x + 15, 250 * len);
    glEnd();

    // Color for the branches/leaves
    glColor3f(0.0f, 0.8f, 0.0f);

    // Draw the leaves
    for (int i = 0; i < 15; i++) {
        int base = tree_x;
        int ht = 15 - i;

        //left leaves
        glBegin(GL_POLYGON);
        glVertex2f(base + 4 * i, 600 * len + 10 * ht);
        glVertex2f(base + 4 * i + 6, 600 * len + 10 * ht);
        glVertex2f(base + 4 * i + 6, 600 * len);
        glVertex2f(base + 4 * i, 600 * len);
        glEnd();

        //right leaves
        glBegin(GL_POLYGON);
        glVertex2f(base - 4 * i, 600 * len + 10 * ht);
        glVertex2f(base - 4 * i - 6, 600 * len + 10 * ht);
        glVertex2f(base - 4 * i - 6, 600 * len);
        glVertex2f(base - 4 * i, 600 * len);
        glEnd();
    }

    // Draw a second layer of leaves
    len -= 0.1;
    for (int i = 0; i < 15; i++) {
        int base = tree_x;
        int ht = 15 - i;

        //left leaves
        glBegin(GL_POLYGON);
        glVertex2f(base + 4 * i, 600 * len + 10 * ht);
        glVertex2f(base + 4 * i + 6, 600 * len + 10 * ht);
        glVertex2f(base + 4 * i + 6, 600 * len);
        glVertex2f(base + 4 * i, 600 * len);
        glEnd();

        //right leaves
        glBegin(GL_POLYGON);
        glVertex2f(base - 4 * i, 600 * len + 10 * ht);
        glVertex2f(base - 4 * i - 6, 600 * len + 10 * ht);
        glVertex2f(base - 4 * i - 6, 600 * len);
        glVertex2f(base - 4 * i, 600 * len);
        glEnd();
    }
}

void reset() {
    dino_y = 200;
    canJump = 0;
    walk = 0;
    tree_x = 2500;
    pause = 1;
    gameLevel = 12;
    count = 100;
    highScore = highScore > score ? highScore : score;
    setHighScore();
    score = 0;
}

void drawDino(double w, double walk, int factor) {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the dino

    float vertices[][2] = {
        {10, 75}, {10, 45}, {15, 65}, {15, 40}, {20, 60}, {20, 35}, {25, 55}, {25, 35},
        {30, 55}, {30, 35}, {35, 55}, {35, 25}, {40, 60}, {40, 5 - walk}, {45, 65}, {45, 15},
        {45, 10 - walk}, {45, 5 - walk}, {50, 10 - walk}, {50, 5 - walk}, {55, 10 - walk},
        {55, 5 - walk}, {50, 65}, {50, 20}, {55, 70}, {55, 25}, {63, 75}, {63, 20}, {70, 115},
        {70, 5 + walk}, {78, 120}, {78, 25}, {78, 10 + walk}, {78, 5 + walk}, {85, 10 + walk},
        {85, 5 + walk}, {87, 120}, {87, 115}, {87, 110}, {87, 30}, {95, 120}, {95, 35}, {103, 120},
        {103, 75}, {103, 65}, {103, 60}, {110, 65}, {110, 60}, {118, 65}, {118, 55}, {112, 120},
        {112, 85}, {112, 80}, {112, 75}, {120, 120}, {120, 85}, {120, 80}, {120, 75}, {126, 120},
        {126, 85}, {126, 80}, {126, 75}, {135, 120}, {135, 85}, {135, 80}, {135, 75}, {142, 120},
        {142, 85}, {150, 120}, {150, 85}, {157, 115}, {157, 85}
    };

    for (int i = 0; i < 70; i += 2) {
        glVertex2f(vertices[i][0] + xcoord, vertices[i][1] * factor + w);
        glVertex2f(vertices[i + 1][0] + xcoord, vertices[i + 1][1] * factor + w);
    }

    glEnd();
}

void drawStar(float x, float y, float size) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for the star

    for (int i = 0; i < 5; ++i) {
        // Outer vertex
        glVertex2f(
            x + size * cos(i * 4 * M_PI / 5),
            y + size * sin(i * 4 * M_PI / 5)
        );
        // Inner vertex
        glVertex2f(
            x + (size / 2) * cos((i * 4 + 2) * M_PI / 5),
            y + (size / 2) * sin((i * 4 + 2) * M_PI / 5)
        );
    }

    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

        drawStar(2000, 1600 , 30);
        drawStar(1000 , 1000 , 20);
        drawStar(1500 , 1000 , 27);
        drawStar(10  + 10, 800 , 15);
        drawStar(120  + 50, 1500 , 20);
        drawStar(280  + 200, 1600 , 30);
        drawStar(1100, 500 , 5);
        drawStar(1100, 1500 , 25);
        drawStar(500, 600 , 6);
        drawStar(1600, 400 , 5);

    // Display score
    glColor3f(1.0, 1.0, 1.0); // White color for the score text
    glRasterPos2f(1700, 1700);
    string scoreStr = "Score: " + to_string(score);
    for (char c : scoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    getHighScore();
    glRasterPos2f(1700, 1900);
    string highScoreStr = "High Score: " + to_string(highScore);
    for (char c : highScoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Generate tree
    draw_tree(tree_x, 1.0);

    if (tree_x >= 0)
        tree_x -= 5;
    else
        tree_x = 2000 + rand() % 200;

    // Draw ground line
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0); // White color for the ground line
    glVertex2f(0, 250);
    glVertex2f(2000, 250);
    glEnd();

    // Draw Dino
    drawDino(dino_y, walk, factor);

    // Check for collision
    if (collision(1.0)) {
        reset();
    }

    // Update walk animation
    if (dino_y <= 200) {
        walk = (walk == -20) ? 20 : -20;
    } else {
        walk = 0;
    }

    // Handle jump logic
    if (canJump == 1) {
        if (dino_y <= 1000) {
            dino_y += 8;
        } else {
            canJump = 0;
        }

    } else if (dino_y >= 200) {
        dino_y -= 8;
    }

    if (count == 0) {
        count = 100;
    }
    if (count % 3 != 0)
        glutPostRedisplay();
    count -= 1;

    glFlush();
}

void setup() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 2000, 0.0, 2000);
}
