#define USER1 "put_username1_here"
#define USER2 "put_username2_here"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include "glew/glew.h"
#include <SFML/Window.hpp>
#include "simplePNG.h"
#define RESOLUTION 512

GLuint shaderProg;

GLuint positionBuffer;
GLuint colorBuffer;

GLuint positionSlot;
GLuint colorSlot;

/* x ,y */
GLfloat positions[104] = {
    /* LINES */
    -1,0.8,
    1,0.8,
    
    /* TRAIANGLE */
    -0.95,0.75,
    -0.95,0.5,
    -0.6,0.75,
    
    /* POINTS (6) */
    0.3,-0.5,
    0.305,-0.5,
    0.31,-0.5,
    0.315,-0.5,
    0.32,-0.5,
    0.325,-0.5,
    0.33,-0.5,
    0.335,-0.5,
    0.34,-0.5,
    0.345,-0.5,
    0.35,-0.5,
    0.355,-0.5,
    0.36,-0.5,
    0.365,-0.5,
    0.37,-0.5,
    0.375,-0.5,
    0.38,-0.5,
    0.385,-0.5,
    0.39,-0.5,
    0.395,-0.5,
    0.4,-0.5,
    
    /* LINES (26,27)*/
    0.8,1,
    0.8,-1,
    
    /* TRIANGLE_FANS circle (28)*/
    0,0,
    0.1,0,
    0.086,0.05,
    0,0.1,
    -0.081,0.05,
    -0.1,0,
    -0.081,-0.058,
    0,-0.1,
    0.086,-0.05,
    
    /* POINTS (37)*/
    0.18,-0.05,
    0.17,0.05,
    0.16,-0.04,
    0.13,0.01,
    
    /* LINES_LOOP (41)*/
    -0.3,0.3,
    -0.6,0.3,
    -0.6,-0.3,
    -0.3,-0.3,
    0.3,-0.3,
    0.3,-0.2,
    -0.3,-0.2,
    -0.3,0.15,
    0.5,0.15,
    0.5,-0.5,
    0.4,-0.5,
};

GLfloat colors[156] = {
    /* white */
    1,1,1,
    /* gray */
    0.5,0.5,0.5,
    /* red */
    1,0,0,
    /* green */
    0,1,0,
    /* blue */
    0,0,1,
    
    /* yellow for POINTS */
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    
    /* rose LINES */
    0.91,0.33,0.42,
    0.90,0,0.2,
    
    /* white and gray circle TRIANGLE */
    1,1,1,
    0.5,0.5,0.5,
    1,1,1,
    0.5,0.5,0.5,
    1,1,1,
    0.5,0.5,0.5,
    1,1,1,
    0.5,0.5,0.5,
    1,1,1,
    
    /* yellow */
    1,1,0,
    1,1,0,
    1,1,0,
    1,1,0,
    
    /* green LINE_LOOP */
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
    0.53,0.79,0.49,
};

void printProgramLinkLog(GLuint obj);
void printProgramCompileLog(GLuint obj);

/*
 Draw a single frame
 */
void display()
{
	// Clear the color bits in the display buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Use a simple shader to render the line
	glUseProgram(shaderProg);
	
	// Render using vertex attributes (data already on GPU) (~2008, 3.0)
	// https://web.archive.org/web/20150225192608/http://www.arcsynthesis.org/gltut/Basics/Tut01%20Following%20the%20Data.html
	
	// Tell OpenGL we want to use a buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	
	// Tell OpenGL what shader data slot we want to use
	glEnableVertexAttribArray(positionSlot);
	
	// Tell OpenGL how to interpret the data
	glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Do the same thing for colors
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glEnableVertexAttribArray(colorSlot);
	glVertexAttribPointer(colorSlot, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Draw some primitives as: glDrawArrays(type, first, count)
	glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 26, 2);
	glDrawArrays(GL_TRIANGLES, 2, 3);
    
    // yellow points line
    glDrawArrays(GL_POINTS, 5, 21);
    
    // white pac-man.
    glDrawArrays(GL_TRIANGLE_FAN, 28, 9);
    
    // feed.
    glDrawArrays(GL_POINTS, 37, 4);
    
    // green path.
    glDrawArrays(GL_LINE_STRIP, 41, 11);
	
	// Tell OpenGL we are done with the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Tell OpenGL we are done with the shader slot
	glDisableVertexAttribArray(positionSlot);
	glDisableVertexAttribArray(colorSlot);
	
	// Tell OpenGL we are done with the shader
	glUseProgram(0);
}

/*
 Initialize the graphics state
 */
void graphicsInit()
{
	// glew will help us use GL functions, so set it up here
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	
	// Shaders are programs that do the actual rendering on the GPU
	// We will discuss these in detail later, for now, just set them up
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	char const * vertSource = "attribute vec2 pos; attribute vec3 color; varying vec4 smoothColor; void main() { gl_Position=vec4(pos.xy, 0, 1); smoothColor=vec4(color.xyz, 1); }";
	char const * fragSource = "varying vec4 smoothColor; void main() { gl_FragColor = smoothColor; }";
	
	glShaderSource(vertShader, 1, (char const **)&vertSource, NULL);
	glShaderSource(fragShader, 1, (char const **)&fragSource, NULL);
	
	glCompileShader(vertShader);
	printProgramCompileLog(vertShader);
	glCompileShader(fragShader);
	printProgramCompileLog(fragShader);
	
	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, fragShader);
	
	glLinkProgram(shaderProg);
	printProgramLinkLog(shaderProg);
	
	// The data we will render needs to be on the GPU
	// These commands upload the data
	
	// Find out where the shader expects the data
	positionSlot = glGetAttribLocation(shaderProg, "pos");
	colorSlot = glGetAttribLocation(shaderProg, "color");

	// Generate a GPU side buffer
	glGenBuffers(1, &positionBuffer);
	
	// Tell OpenGL we want to work with the buffer we just made
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	
	// Allocate and upload data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	
	// Do the same thing for the color data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void saveBuffer(sf::Window const & window)
{
    unsigned char *dest;
    unsigned int w = window.getSize().x;
    unsigned int h = window.getSize().y;
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    dest = (unsigned char *) malloc( sizeof(unsigned char)*w*h*3);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, dest);
    
    simplePNG_write("_program1.png", w, h, dest);
    free(dest);
}

class GLBox
{
public:
	GLBox()
	{
		// Create the main window
		sf::Window window(sf::VideoMode(RESOLUTION, RESOLUTION, 32), "program1");
		
		graphicsInit();
        unsigned int frameCount = 0;
		
		// Start render loop
		while (window.isOpen())
		{			
			// Set the active window before using OpenGL commands
			// It's not needed here because the active window is always the same,
			// but don't forget it if you use multiple windows or controls
            window.setActive();
			
			// Handle any events that are in the queue
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window : exit
				//if (event.type == sf::Event::Closed)
				//	window.close();
				
				// Escape key : exit
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
					window.close();
				
				// This is for grading your code. DO NOT REMOVE
				if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal)
				{
                    saveBuffer(window);
				}
			}
			
			// Render the scene
			display();
            frameCount++;
            if(frameCount == 100)
                saveBuffer(window);
			
			// Finally, display rendered frame on screen
			window.display();
		}
	}
	
	~GLBox()
	{
		// Clean up the buffer
		glDeleteBuffers(1, &positionBuffer);
	}
private:
	sf::Window *App;
};

void printProgramCompileLog(GLuint obj)
{
	GLint infologLength;
	GLint status;
	int charsWritten = 0;
	char *infoLog;
	
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
		return;
	
	printf("Error compiling shader: ");
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s",infoLog);
		free(infoLog);
	}
	printf("\n");
}

void printProgramLinkLog(GLuint obj)
{
	GLint infologLength;
	GLint status;
	char *infoLog;
	int charsWritten  = 0;
	
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if (status == GL_TRUE)
		return;
	
	printf("Error linking shader: ");
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s",infoLog);
		free(infoLog);
	}
	printf("\n");
}

int main()
{
	printf("Program by %s+%s\n", USER1, USER2);
	GLBox prog;
	
    return EXIT_SUCCESS;
}
