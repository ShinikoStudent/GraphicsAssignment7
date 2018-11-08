//FileName:		cube.h
//Programmer:	Dan Cliburn
//Date:			4/2/2015
//Purpose:		This file defines the header for a cube that is centered at the origin

#ifndef PICKUPOBJECTHIDEBEDROOM1_H
#define PICKUPOBJECTHIDEBEDROOM1_H

#include <glew.h>  //glew.h is supposed to be included before gl.h.  To be safe, you can just include glew.h instead

class PickUpObjectHideBedroom1
{
private:
	bool initialized;

	GLfloat positions[8][3];  //each vertex has an x, y, and z value for its position
	GLuint VAO;
	GLuint Buffer;  //We'll need a buffer for the vertex positions

public:
	PickUpObjectHideBedroom1();

	bool init();
	void draw();
};

#endif