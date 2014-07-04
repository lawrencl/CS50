//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // PRNG

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// constants for paddles
#define PADDLEHEIGHT 10
#define PADDLEWIDTH 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    // input time to generate different outputs
    srand48(time(NULL));

    // instantiate window
    // gwindow.h header file
    // function newGWindow return value is stored in a variable called 'window' whose type is GWindow,
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks 
    // bricks that pop aligned top of window when game starts
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // calls scoreboard function
    updateScoreboard(window, label, points);

    // wait for click before starting
    waitForClick();
    
    // initial velocity
    double velocity_X = 2.0*drand48();
    double velocity_Y = 3.0;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        
        // PADDLE CODE
        
        // create mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // validate event
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor
                double x = getX(event) - getWidth(paddle)/2;
                double y = 500;
                
                if (x <= 0)
                {
                    // sets min x value so paddle does not go off left screen
                    x = 0;
                }
                else if (x >= WIDTH-PADDLEWIDTH)
                {
                    // sets max x value so paddle does not go off right screen
                    x = WIDTH-PADDLEWIDTH;
                }
                setLocation(paddle, x, y);
            }
        }
        
        // BALL CODE
                
        // move ball (up and down and at angles)
        move(ball, velocity_X, velocity_Y);
        
        // *** CHEAT CODE FOR TESTING ***
        // setLocation(paddle, getX(ball)+RADIUS-PADDLEWIDTH/2, 500);
        
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_X = -velocity_X;
        }
        
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity_X = -velocity_X;
        }
        
        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            velocity_Y = -velocity_Y;
        }

        /*/ Ultimately, be sure that the ball still bounces off edges, including the window’s bottom for now.
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            velocity_Y = -velocity_Y;
        }*/
        
        // if ball hits bottom of window - lose life, re-position, keep track of lives 
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {   
            lives = lives - 1;
            waitForClick();
            setLocation(ball, 190, 290);
            setLocation(paddle, WIDTH/2 - PADDLEWIDTH/2, 500);
        }              
                
        // detect ball bounce
        GObject object = detectCollision (window, ball);
        
        // if ball hits paddle     
        if (object == paddle && velocity_Y > 0)
        {
            velocity_Y = -velocity_Y;
        }
        
        // if ball hits brick, brick disappears, scoreboard updated
        if (object != NULL)
        {         
            // if object (brick) hit (not the paddle or scoreboard)
            if (strcmp(getType(object), "GRect") == 0 && object != paddle && object != label)
            {
                removeGWindow(window, object);
                velocity_Y = -velocity_Y;
                points = points + 1;
                bricks = bricks - 1;
                updateScoreboard(window, label, points);
            }
        }
        
        pause(10);
    }
    
    // Message labels Win or Lose.
    if (bricks > 0)
    {
        GLabel game_over = newGLabel("YOU LOSE!");
        setFont(game_over, "SansSerif-70");
        setColor(game_over, "RED");
        add(window, game_over);
        setLocation(game_over, 15, 300);
    }
    else
    {
        GLabel game_over = newGLabel("YOU WIN!");
        setFont(game_over, "SansSerif-70");
        setColor(game_over, "GREEN");
        add(window, game_over);
        setLocation(game_over, 15, 300);
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    // initialize variables
    int i, j, y, x = -38;

    // instantiate bricks in window, 10x ROWS and 5x COLS represent grid dimensions
    // iterate over columns
    for (j = 0; j < COLS; j++)
    { 
        // row of 10 brick columns 
        // WIDTH/10 = 40 starting from 2
        x = x + 40; 
        y = 50; // from the top left
        GRect brick = newGRect(x, y, 36, 10); // 2+36+4+36+4+36+4+36+4+36+4+36+4+36+4+36+4+36+4+36+2 = WIDTH
        add (window, brick);
        setColor(brick, "RED");
        setFilled(brick, true);
           
        // loop remaining 4x ROWS 
        for (i = 0; i < ROWS - 1; i++)
        {
            y = y + 12;
            GRect brick = newGRect(x, y, 36, 10);
            add (window, brick);
            
            // if statements to set colors for each row
            if (i == 0)
            {
                setColor(brick, "GREEN");
                setFilled(brick, true);
            }
            
            if (i == 1)
            {
                setColor(brick, "ORANGE");
                setFilled(brick, true);
            }
            
            if (i == 2)
            {
                setColor(brick, "PINK");
                setFilled(brick, true);
            }
            
            if (i == 3)
            {
                setColor(brick, "BLUE");
                setFilled(brick, true);
            }
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    // return NULL;
    
    // instantiate ball, center bottom of window
    // HEIGHT/2 - C/2 = 290
    // WIDTH/2 - C/2 = 190
    GOval ball = newGOval (190, 290, 20, 20);

    // add ball to window
    add(window, ball);
    
    // color and fill
    setColor(ball, "BLACK");
    setFilled(ball, true);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    // return NULL;
    
    // instantiate paddle object, centered bottom middle
    // Window width subtract Paddle width for top left corner position
    GRect paddle = newGRect (WIDTH/2 - PADDLEWIDTH/2, 500, PADDLEWIDTH, PADDLEHEIGHT);

    // add paddle to window
    add(window, paddle);
    
    // colored and filled
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    // return NULL;
    
    // instantiate scoreboard, value is a number (a char*)
    GLabel label = newGLabel (" ");
    
    // add scoreboard to window
    add (window, label);
    
    // location of scoreboard
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    // font/size of scoreboard
    setFont(label, "Arial-40");
    setColor(label, "Gray");
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
