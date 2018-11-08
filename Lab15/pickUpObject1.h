//FileName:		cube.h
//Programmer:	Dan Cliburn
//Date:			4/2/2015
//Purpose:		This file defines the header for a cube that is centered at the origin

#ifndef PICKUPOBJECT1_H
#define PICKUPOBJECT1_H

#include <glew.h>  //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead

class PickUpObject1
{
private:
	bool initialized;

	GLfloat positions[8][3];  //each vertex has an x, y, and z value for its position
	GLuint VAO;
	GLuint Buffer;  //We'll need a buffer for the vertex positions

public:
	PickUpObject1();

	bool init();
	void draw();
};

#endif