#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "shapes.h"

class Non_physic_object {

public:

	Non_physic_object();
	Non_physic_object(Shapes* shape, glm::vec3 scl, glm::vec3 pos, glm::vec3 rot, glm::vec4 color);
	~Non_physic_object();

	void setMass(GLfloat val);
	GLfloat getMass() const;

	void setPosition(glm::vec3 val);
	glm::vec3 getPosition() const;

	void setRotation(glm::vec3 val);
	glm::vec3 getRotation() const;

	void setScale(glm::vec3 val);
	glm::vec3 getScale() const;

	void setMVMatrix(glm::mat4 val);
	glm::mat4 getMVMatrix() const;

	Shapes* getMyShape();

	glm::mat4 updateMVMatrix();

protected:

	GLfloat mass;

	glm::vec3 scale;
	glm::vec3 position;

	glm::vec3 rotation;

	glm::mat4 mv_matrix;

	Shapes* my_shape;
};


