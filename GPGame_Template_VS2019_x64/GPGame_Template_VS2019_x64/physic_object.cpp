#include "physic_object.h"


Physic_object::Physic_object() {}

Physic_object::Physic_object(Shapes* shape, glm::vec3 scl, glm::vec3 pos, glm::vec3 rot, GLfloat m, glm::vec4 color)
{
	speed = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = rot;
	rotation_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	position = pos;
	my_shape = shape;
	mass = m;
	scale = scl;
	just_collided = 0;

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

Physic_object::~Physic_object()
{
}

void Physic_object::setSpeed(glm::vec3 val) { this->speed = val; }
glm::vec3 Physic_object::getSpeed() const { return this->speed; }

void Physic_object::setRotationSpeed(glm::vec3 val) { this->rotation_speed = val; }
glm::vec3 Physic_object::getRotationSpeed() const { return this->rotation_speed; }


glm::vec3 Physic_object::updatePosition(GLfloat deltaTime)
{
	this->position += this->speed * deltaTime;
	return this->position;
}

glm::vec3 Physic_object::updateSpeed(GLfloat deltaTime, glm::vec3 acceleration)
{
	this->speed += acceleration * deltaTime;

	GLfloat max_speed = 20.0f;

	if (glm::length(this->speed) < 0.005f) this->speed = glm::vec3(0.0f, 0.0f, 0.0f);

	if (this->speed.x > max_speed) {
		this->speed.x = max_speed;
	}
	else if (this->speed.x < -max_speed) {
		this->speed.x = -max_speed;
	}

	if (this->speed.y > max_speed) {
		this->speed.y = max_speed;
	}
	else if (this->speed.y < -max_speed) {
		this->speed.y = -max_speed;
	}

	if (this->speed.z > max_speed){
		this->speed.z = max_speed;
	}
	else if (this->speed.z < -max_speed) {
		this->speed.z = -max_speed;
	}
	return this->speed;
}
glm::vec3 Physic_object::updateSpeed(glm::vec3 added_speed)
{
	return this->updateSpeed(1.0f, added_speed);
}


glm::vec3 Physic_object::updateRotation(GLfloat delta_time)
{
	this->rotation += this->rotation_speed * delta_time;
	return this->rotation;
}

glm::vec3 Physic_object::updateRotationSpeed(GLfloat delta_time, glm::vec3 rotation_acceleration)
{
	this->rotation_speed += rotation_acceleration * delta_time;
	if (glm::length(this->rotation_speed) < 0.001f) this->rotation_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	return this->rotation_speed;
}
glm::vec3 Physic_object::updaterotationSpeed(glm::vec3 added_rotation_speed)
{
	this->rotation_speed += added_rotation_speed;
	if (glm::length(this->rotation_speed) < 0.001f) this->rotation_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	return this->rotation_speed;
}

int Physic_object::getJustCollided(){ return this->just_collided; }
void Physic_object::setJustCollided(int val){ this->just_collided = val; }

void Physic_object::decrementJustCollided()
{
	this->just_collided -= 1;
	if (just_collided < 0)
		just_collided = 0;
}

void Physic_object::resetJustCollided()
{
	just_collided = 10;
}



