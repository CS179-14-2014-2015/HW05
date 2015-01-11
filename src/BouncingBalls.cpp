//============================================================================
// Name        : BouncingBalls.cpp
// Author      : Marta Villarrubia & Guillaume Robbe
// Version     : 1.0
// Copyright   : Open Source
// Description : Bouncing balls simulation
//============================================================================

#include <SFML/Graphics.hpp>
#include <list>

#include "Ball.h"

using namespace sf;
using namespace std;

int main() {

	//Variables
	unsigned const int width = 1000;
	unsigned const int height = 500;
    RenderWindow  window(VideoMode(width, height), "Bouncing Balls Simulator", Style::Close | Style::Titlebar);
    list<Ball> balls;
    Clock clock;
    short ballCounter = 0;

    //set up the frame rate
    window.setFramerateLimit(60);

    //main loop
    while (window.isOpen()) {

    	//get events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //clear the window
        window.clear(Color::White);

        //create new ball if enough elapsed time
        if(clock.getElapsedTime().asSeconds() > 0.5 && ballCounter < 60) {
        	balls.push_back(Ball(width, height));
        	ballCounter++;
        	clock.restart();
        }

        //update the balls and draw them
        for(list<Ball>::iterator it = balls.begin(); it != balls.end(); it++) {
        	it->update(width, height);
        	window.draw(*it);
        }

        //show the drawing
        window.display();
    }

    return EXIT_SUCCESS;
}
