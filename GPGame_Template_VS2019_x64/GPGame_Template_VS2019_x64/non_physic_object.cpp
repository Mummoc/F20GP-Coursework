#include "non_physic_object.h"


Non_physic_object::Non_physic_object() {}

Non_physic_object::Non_physic_object(Shapes* shape, glm::vec3 scl, glm::vec3 pos, glm::vec3 rot, glm::vec4 color)
{
	rotation = rot;
	position = pos;
	my_shape = shape;
	scale = scl;
	mass = -1.0f;

	my_shape->Load();
	my_shape->fillColor = color;
	my_shape->lineColor = color;

	mv_matrix =
		glm::translate(position) *
		glm::scale(scale) *
		glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::mat4(1.0f);

}

Non_physic_object::~Non_physic_object()
{
}

void Non_physic_object::setMass(GLfloat val) { this->mass = val; }
GLfloat Non_physic_object::getMass() const { return this->mass; }

void Non_physic_object::setPosition(glm::vec3 val) { this->position = val; }
glm::vec3 Non_physic_object::getPosition() const { return this->position; }

void Non_physic_object::setRotation(glm::vec3 val) { this->rotation = val; }
glm::vec3 Non_physic_object::getRotation() const { return this->rotation; }

void Non_physic_object::setScale(glm::vec3 val) { this->scale = val; }
glm::vec3 Non_physic_object::getScale() const { return this->scale; }

void Non_physic_object::setMVMatrix(glm::mat4 val) { this->mv_matrix = val; }
glm::mat4 Non_physic_object::getMVMatrix() const { return this->mv_matrix; }

Shapes* Non_physic_object::getMyShape() { return this->my_shape; }

glm::mat4 Non_physic_object::updateMVMatrix()
{
	this->mv_matrix =
		glm::translate(this->position) *
		glm::scale(this->scale) *
		glm::rotate(this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::mat4(1.0f);

	return this->mv_matrix;
}



