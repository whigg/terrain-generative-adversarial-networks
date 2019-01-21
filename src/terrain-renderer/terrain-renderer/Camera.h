#ifndef CAMERA_H
#define CAMERA_H

#include "cgmath.h"

class Camera 
{
private:
	vec3  position;
	vec3  direction;
	float speed;
public:
	Camera();
	Camera(const Camera&);
	Camera(Camera&&);
	~Camera();
	Camera& operator=(const Camera&);
	Camera& operator=(Camera&&);

	void processInput(int key, int button);
};

#endif