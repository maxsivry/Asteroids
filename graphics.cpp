#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include "Button.h"
#include "Quad.h"
#include "laser.h"
#include "spaceship.h"
#include "stars.h"
using namespace std;

// global variable for colors used
GLdouble width, height;
int wd;
const color white(1, 1, 1);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color black(0, 0, 0);
const color neon(1, 95/255.0, 31/255.0);
const color yellow(1,1,0);

//for displaying each screen
enum screen{startScreen, onePlayerScreen, twoPlayerScreen, endScreen};
screen Active;

//objects of each shap to be displayed
vector<Circle> asteroids;
vector<laser> lasers;
SpaceShip spaceShip(point2D(250,250),point2D(230,290),point2D(270,290));
SpaceShip spaceShip2(point2D(320,250),point2D(300,290),point2D(340, 290));
Rect user;
vector<Stars> stars;

//Buttons for choosing how many players
Button onePlayer({1, 1, 1}, {100, 200}, 100, 50, "One Player");
Button twoPlayer({1, 1, 1}, {300, 200}, 100, 50, "Two Players");


bool isCrash(Circle &c, SpaceShip s){
    if(c.getRightX()<s.getLeftX() || c.getLeftX()>s.getRightX()){
        return false;
    }
    if(c.getBottomY()<s.getTopY()||c.getTopY()>s.getBottomY()){
        return false;
    }
    return true;
}

//initialization of asteroids
void initAsteroid() {

    asteroids.clear();
    // add asteroids to array
    asteroids.push_back(Circle(white, rand() % 600, 0, 50));
    asteroids.push_back(Circle(white, 0, rand() % 600, 50));
    asteroids.push_back(Circle(white, rand() % 600, 0, 50));
    asteroids.push_back(Circle(white, rand() % 600, 0, 50));
    asteroids.push_back(Circle(white, 0, rand() % 600, 50));
    //set the velocities and radius
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i].setRadius(40);
        asteroids[i].setVelocity(rand() % 5, rand() % 5);
    }
}

void initSpaceShip() {
    //set color of each spaceship
    spaceShip.setColor(darkBlue);
    spaceShip2.setColor(yellow);
}

void initUser() {
    // centered in the top left corner of the graphics window
    user.setCenter(0,0);
    user.setSize(20,20);
    user.setColor(white);
}

void initStars() {
    //initializing stars, code from jeopardy
    for (int i = 0; i < 150; ++i) {
        stars.push_back(Stars(1, 1, 1, 1, rand() % int(width), -(rand() % int(height)), rand() % 5 + 1));
    }
}

void init() {
    width = 600;
    height = 600;
    srand(time(0));
    initStars();
    initSpaceShip();
    initAsteroid();
    initUser();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(black.red, black.green, black.blue, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    if(Active == startScreen){
        glViewport(0, 0, width*2, height*2);

        // do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        /*
         * Draw here
         */

        //draw start method and such

        onePlayer.draw();
        twoPlayer.draw();
        string startMessage = "Welcome to Asteroids";
        glRasterPos2i(100, 100);
        for (const char &letter : startMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glFlush();
    }

    //if twoplayerscreen option is selected
    if(Active == twoPlayerScreen){
        glViewport(0, 0, width*2, height*2);

        // do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //draw the stars, code from jeopardy
        for (Stars star : stars) {
            star.draw();
        }

        //draw the asteroids
        for (Circle asteroid : asteroids) {
            // #polymorphism
            asteroid.draw();
        }

        //draw both spaceships
        spaceShip.draw();
        spaceShip2.draw();

        //if asteroid hits either spaceship
        for (int i = 0; i < asteroids.size(); i += 1) {
            if (isCrash(asteroids[i], spaceShip) || isCrash(asteroids[i], spaceShip2)){

                //return to start screen
                Active = startScreen;
            }
        }
        glFlush();
    }

    //if one player mode...
    if(Active == onePlayerScreen){
        glViewport(0, 0, width*2, height*2);

        // do an orthographic parallel projection with the coordinate
        // system set to first quadrant, limited by screen/window size
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //draw the stars, code from jeopardy
        for (Stars &star : stars) {
            star.draw();
        }

        //draw single spaceship
        spaceShip.draw();

        //draw asteroids
        for (Circle asteroid : asteroids) {
            // #polymorphism
            asteroid.draw();
        }
        for (int i = 0; i < asteroids.size(); i += 1) {
            if (isCrash(asteroids[i], spaceShip)){

                //return to start screen
                Active = startScreen;
            }
        }
        glFlush();
    }
    // Render now
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {

    //escape from window
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    //press . to rotate the spaceShip
    if (key == '.') {
        spaceShip.rotate(PI / 100);
    }


    //if two player mode...
    if (Active == twoPlayerScreen) {
        //if w,s,a,d, moves second spaceship
        if (key == 's') {
            spaceShip2.move(0,5);
        }
        if (key == 'a') {
            spaceShip2.move(-5,0);
        }
        if (key == 'd') {
            spaceShip2.move(5,0);
        }
        if (key == 'w') {
            spaceShip2.move(0,-5);
        }
        //press q to rotate second ship
        if (key == 'q') {
            spaceShip2.rotate(PI / 100);
        }

    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {

    //logic for moving the first spaceship
    switch(key) {
        case GLUT_KEY_DOWN:
            spaceShip.move(0,5);
            break;
        case GLUT_KEY_LEFT:
            spaceShip.move(-5,0);
            break;
        case GLUT_KEY_RIGHT:
            spaceShip.move(5,0);
            break;
        case GLUT_KEY_UP:
            spaceShip.move(0,-5);
            lasers.push_back(laser(0,-10,spaceShip.getCenter()));
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    //set user center to cursor
    user.setCenter(x,y);
    glutPostRedisplay();
    //logic for selecting each screen selector
    if (onePlayer.isOverlapping(x,y)){
        onePlayer.hover();
    }
    else{
        onePlayer.release();
    }
    if (twoPlayer.isOverlapping(x,y)){
        twoPlayer.hover();
    }
    else{
        twoPlayer.release();
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    //for selecting each button...
    if(button == GLUT_LEFT_BUTTON) {
        if ((state == GLUT_DOWN) && onePlayer.isOverlapping(x, y)) {
            onePlayer.pressDown();
            Active = onePlayerScreen;
        }

        //if mouse is released over one player button, set active to one player
        if ((state == GLUT_UP) && onePlayer.isOverlapping(x, y)) {
            Active = onePlayerScreen;
        }

        if ((state == GLUT_DOWN) && twoPlayer.isOverlapping(x, y)) {
            twoPlayer.pressDown();
            Active = twoPlayerScreen;
        }

        if ((state == GLUT_UP) && twoPlayer.isOverlapping(x, y)) {
            Active = twoPlayerScreen;
        }
/*        if((state == GLUT_DOWN) && Active == twoPlayerScreen){
            lasers.push_back(laser())
        }*/
    }
    glutPostRedisplay();
}


void timer(int dummy) {


    //logic for bouncing asteroids, taken from screensaver...
    for (Circle &asteroid : asteroids) {
        asteroid.move(asteroid.getXVelocity(), asteroid.getYVelocity());
        if (asteroid.getCenterX() < asteroid.getRadius()) {
            asteroid.bounceX();
            asteroid.setCenterX(asteroid.getRadius());
        } else if (asteroid.getCenterX() > (width-asteroid.getRadius())) {
            asteroid.bounceX();
            asteroid.setCenterX(width-asteroid.getRadius());
        }
        if (asteroid.getCenterY() < asteroid.getRadius()) {
            asteroid.bounceY();
            asteroid.setCenterY(asteroid.getRadius());
        } else if (asteroid.getCenterY() > (height-asteroid.getRadius())) {
            asteroid.bounceY();
            asteroid.setCenterY(height-asteroid.getRadius());
        }
    }
    //if asteroids overlap with each other call collide...
    for (int i = 0; i < asteroids.size() - 1; ++i) {
        for (int j = i + 1; j < asteroids.size(); ++j) {
            if (asteroids[i].isOverlapping(asteroids[j])) {
                asteroids[i].collide(asteroids[j]);
            }
        }
    }
    //logic for moving stars, taken from jeopardy
    for (Stars &star : stars) {
        star.moveY(star.getRadius());
        if (star.getTopY() > height) {
            star.setCenter(rand() % int(width), -star.getRadius());
        }
    }
    //if one player mode...

        //if laser overlaps with asteroid

            //destroy asteroid

       //if spaceship overlaps with asteroid

            //destroy spaceship

    //if two player mode...

        //if laser overlaps with asteroid

            //destroy asteroid

        //if spaceship overlaps with asteroid

            //destroy spaceship

        //if spaceship2 overlaps with asteroid

            //destroy spaceship2
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Asteroids" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);

    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
