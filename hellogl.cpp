// hellogl.cpp /////////////////////////////////////////////////////////////////
// Babys first OpenGL program. How cute! ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Headers.hpp"
//#include "Source.cpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

void Draw_cube(float size);
void Draw_point(float x, float y, float z);

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...

	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// ummm just transparent apparently
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);

	float cubeSize = 20;

	sf::Clock clock;
    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
                // this would be better done with forcing the window size back
                // to some constant values
            
				// or at least forced to a specific scale, as if you change the
				// width/height ratio, the image ends up being distorted
            }
            if(event.type == sf::Event::KeyPressed)
			{	if(event.key.code = sf::Keyboard::Space)
				{	cubeSize += 1;
				}
			}
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // erases any previously drawn stuff...
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // beats me...
        glTranslatef(0.0f, 0.0f, -200.0f);
		//glRotatef((clock.getElapsedTime().asSeconds()*50), 1.f, 0.f, 0.f);
		glRotatef((clock.getElapsedTime().asSeconds()*30), 0.f, 1.f, 0.f);
		//glRotatef((clock.getElapsedTime().asSeconds()*90), 0.f, 0.f, 1.f);
		// rotate the camera view a wee bit

		// lets just try with the z axis rotate
		// okay, no

        // draw...
		Draw_cube(cubeSize);
		Draw_point(25, 25, 25);
		// kewl

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}

void Draw_cube(float size)
{	glBegin(GL_QUADS);

	glVertex3f(-size, -size, -size);
	glVertex3f(-size,  size, -size);
	glVertex3f( size,  size, -size);
	glVertex3f( size, -size, -size);
	// I guess we define them one at a time in sets of four, hence the quads
	// part...
		
	// and each set of four defines a face...
	glVertex3f(-size, -size, size);
	glVertex3f(-size,  size, size);
	glVertex3f( size,  size, size);
	glVertex3f( size, -size, size);
	
	glVertex3f(-size, -size, -size);
	glVertex3f(-size,  size, -size);
	glVertex3f(-size,  size,  size);
	glVertex3f(-size, -size,  size);

	glVertex3f(size, -size, -size);
	glVertex3f(size,  size, -size);
	glVertex3f(size,  size,  size);
	glVertex3f(size, -size,  size);

	glVertex3f(-size, -size,  size);
	glVertex3f(-size, -size, -size);
	glVertex3f( size, -size, -size);
	glVertex3f( size, -size,  size);

	glVertex3f(-size, size,  size);
	glVertex3f(-size, size, -size);
	glVertex3f( size, size, -size);
	glVertex3f( size, size,  size);

	glEnd();
}

void Draw_point(float x, float y, float z)
{	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
}
