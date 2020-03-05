#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "shapes.h"
#include "non_physic_object.h"

class Physic_object : public Non_physic_object {

public:

	Physic_object();
	Physic_object(Shapes* shape, glm::vec3 scl, glm::vec3 pos, glm::vec3 rot, GLfloat m, glm::vec4 color);
	~Physic_object();

	void setSpeed(glm::vec3 val);
	glm::vec3 getSpeed() const;

	void setRotationSpeed(glm::vec3 val);
	glm::vec3 getRotationSpeed() const;

	glm::vec3 updatePosition(GLfloat delta_time);

	glm::vec3 updateSpeed(GLfloat delta_time, glm::vec3 acceleration);
	glm::vec3 updateSpeed(glm::vec3 added_speed);

	glm::vec3 updateRotation(GLfloat delta_time);

	glm::vec3 updateRotationSpeed(GLfloat delta_time, glm::vec3 rotation_acceleration);
	glm::vec3 updaterotationSpeed(glm::vec3 added_rotation_speed);

	int getJustCollided();
	void setJustCollided(int val);
	void decrementJustCollided();
	void resetJustCollided();

private:

	glm::vec3 speed;

	glm::vec3 rotation_speed;

	int just_collided;
};


