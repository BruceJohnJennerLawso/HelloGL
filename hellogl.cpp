// hellogl.cpp /////////////////////////////////////////////////////////////////
// Babys first OpenGL program. How cute! ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Headers.hpp"
//#include "Source.cpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "VectorVictor3.hpp"

#define cameraMove 6


void Draw_cube(float size);
void Draw_point(float x, float y, float z);
void Draw_pyramid();

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
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

	float cameraDistance = -200;

	sf::RectangleShape rect(sf::Vector2f(1500, 50));
	rect.setFillColor(sf::Color(0, 255, 0, 128));

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
			{	if(event.key.code = sf::Keyboard::Up)
				{	cubeSize += 1;
				}
				if(event.key.code = sf::Keyboard::Down)
				{	cubeSize -= 1;
				}
			}
			if(event.type == sf::Event::MouseWheelMoved)
			{	cameraDistance += event.mouseWheel.delta*cameraMove;
			}
			
			
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // erases any previously drawn stuff...
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // beats me...
        glTranslatef(0.0f, 0.0f, cameraDistance);
        // what the, why does it translate every frame
		
		// ohhh, so we can be 200 units back from wherever the 
		
		glRotatef(20*cos((clock.getElapsedTime().asSeconds()*0.5)), 1.f, 0.f, 0.f);
		glRotatef((clock.getElapsedTime().asSeconds()*30), 0.f, 1.f, 0.f);
		//glRotatef((clock.getElapsedTime().asSeconds()*90), 0.f, 0.f, 1.f);
		// rotate the camera view a wee bit

		// lets just try with the z axis rotate
		// okay, no
		
		// that does not work

        // draw...
		//Draw_cube(cubeSize);
		Draw_pyramid();
		Draw_point(25, 25, 25);
		window.pushGLStates();

		window.draw(rect);

		window.popGLStates();
		
		int points = std::rand()%10 + 1;
		for(int cy = 0; cy != points; ++cy)
		{	Draw_point((20 + std::rand()%10),(20 + std::rand()%10),(20 + std::rand()%10));
		}
		// kewl

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}

void Draw_cube(float size)
{	glBegin(GL_QUADS);

	glColor3f(0,0,255);
	// lancelots favourite cube
	
	// I dont care if the joke is old by now dammit!

	glVertex3f(-size, -size, -size);
	glVertex3f(-size,  size, -size);
	glVertex3f( size,  size, -size);
	glVertex3f( size, -size, -size);
	// I guess we define them one at a time in sets of four, hence the quads
	// part...
		
	// and each set of four defines a face...

	glColor3f(0,128,128);

	glVertex3f(-size, -size, size);
	glVertex3f(-size,  size, size);
	glVertex3f( size,  size, size);
	glVertex3f( size, -size, size);
	
	glColor3f(128,128,0);
	
	glVertex3f(-size, -size, -size);
	glVertex3f(-size,  size, -size);
	glVertex3f(-size,  size,  size);
	glVertex3f(-size, -size,  size);

	glColor3f(255,0,0);

	glVertex3f(size, -size, -size);
	glVertex3f(size,  size, -size);
	glVertex3f(size,  size,  size);
	glVertex3f(size, -size,  size);

	glColor3f(128,0,128);

	glVertex3f(-size, -size,  size);
	glVertex3f(-size, -size, -size);
	glVertex3f( size, -size, -size);
	glVertex3f( size, -size,  size);

	glColor3f(0,0,255);

	glVertex3f(-size, size,  size);
	glVertex3f(-size, size, -size);
	glVertex3f( size, size, -size);
	glVertex3f( size, size,  size);



	glEnd();
}

void Draw_point(float x, float y, float z)
{	glBegin(GL_POINTS);
	glColor3f(255,0,0);
	// aha, that works nicely
	glVertex3f(x, y, z);
	glEnd();
}

void Draw_pyramid()
{
	
		glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor3f(10.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 10.0f, 0.0f);					// Top Of Triangle (Front)
		glColor3f(0.0f,10.0f,0.0f);						// Green
		glVertex3f(-10.0f,-10.0f, 10.0f);					// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,10.0f);						// Blue
		glVertex3f( 10.0f,-10.0f, 10.0f);					// Right Of Triangle (Front)
		glColor3f(10.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 10.0f, 0.0f);					// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,10.0f);						// Blue
		glVertex3f( 10.0f,-10.0f, 10.0f);					// Left Of Triangle (Right)
		glColor3f(0.0f,10.0f,0.0f);						// Green
		glVertex3f( 10.0f,-10.0f, -10.0f);					// Right Of Triangle (Right)
		glColor3f(10.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 10.0f, 0.0f);					// Top Of Triangle (Back)
		glColor3f(0.0f,10.0f,0.0f);						// Green
		glVertex3f( 10.0f,-10.0f, -10.0f);					// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,10.0f);						// Blue
		glVertex3f(-10.0f,-10.0f, -10.0f);					// Right Of Triangle (Back)
		glColor3f(10.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 10.0f, 0.0f);					// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,10.0f);						// Blue
		glVertex3f(-10.0f,-10.0f,-10.0f);					// Left Of Triangle (Left)
		glColor3f(0.0f,10.0f,0.0f);						// Green
		glVertex3f(-10.0f,-10.0f, 10.0f);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid

}
