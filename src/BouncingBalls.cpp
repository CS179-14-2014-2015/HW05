//============================================================================
// Name        : BouncingBalls.cpp
// Author      : Marta Villarrubia & Guillaume Robbe
// Version     : 1.0
// Copyright   : Open Source
// Description : Bouncing balls simulation
//============================================================================

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ball.h"

using namespace sf;
using namespace std;

int main() {

	//Variables
	unsigned const int width = 1000;
	unsigned const int height = 500;
    RenderWindow  window(VideoMode(width, height), "Bouncing Balls Simulator", Style::Close | Style::Titlebar);
    vector<Ball> balls;
    Clock clock;
    short ballCounter = 0;
    bool colorSwap = false;
    bool slowDown = false;
    bool speedUp = false;

    //set up the frame rate and initialize the time
    window.setFramerateLimit(60);
	srand(time(NULL));

    //main loop
    while (window.isOpen()) {

    	//get events
        Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
            	colorSwap = !colorSwap;

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
            	speedUp = true;
            if(event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
            	speedUp = false;

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
            	slowDown = true;
            if(event.type == Event::KeyReleased && event.key.code == Keyboard::Down)
            	slowDown = false;
        }

        //clear the window
        window.clear(Color::White);

        //slow down the balls
        if(slowDown) {
        	for(short i = 0; i < balls.size(); i++) {
        		float currentSpeed = balls[i].getSpeed().getMagnitude();
        		currentSpeed -= 0.1;
        		if(currentSpeed > 0)
        			balls[i].getSpeed().setMagnitude(currentSpeed);
        	}
        }

        //speed up the balls
        if(speedUp) {
        	for(short i = 0; i < balls.size(); i++) {
        		float currentSpeed = balls[i].getSpeed().getMagnitude();
        		currentSpeed += 0.1;
        		balls[i].getSpeed().setMagnitude(currentSpeed);
        	}
        }

        //create new ball if enough elapsed time
        if(clock.getElapsedTime().asSeconds() > 0.5 && ballCounter < 100) {
        	balls.push_back(Ball(width, height));
        	ballCounter++;
        	clock.restart();
        }

        //look for ball collisions
        for(short i1 = 0; i1 < balls.size() - 1; i1++) {
        	for(short i2 = i1 + 1; i2 < balls.size(); i2++) {
        		if(balls[i1].isColliding(balls[i2]))
        			balls[i1].collide(balls[i2], colorSwap);
        	}
        }

        //update the balls and draw them
        for(vector<Ball>::iterator it = balls.begin(); it != balls.end(); it++) {
        	it->update(width, height);
        	window.draw(*it);
        }

        //show the drawing
        window.display();
    }
    return EXIT_SUCCESS;
}
