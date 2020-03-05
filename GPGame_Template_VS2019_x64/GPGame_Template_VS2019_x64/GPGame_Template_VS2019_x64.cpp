// Simplified Renderer application for GP course
// Features:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// Added FPS camera functionality
// Update 2019/01 updated libraries and created project for VS2017 including directory dependant links to libraries.
// Update 2020/01 updated libraries for x64 and for VS2020, also adding MAC compiled Libraries.

// Suggestions or extra help please do email me at S.Padilla@hw.ac.uk

// Standard C++ libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

// Helper graphic libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include "physic_object.h"

// MAIN FUNCTIONS
void startup();
void updateCamera();
void updateSceneElements();
void renderScene();

//CROWD FUNCTION
void changer();
void direction();

//OTHER FUNCTIONS
bool sphereSphereCollision(Non_physic_object sphere_1, Non_physic_object sphere_2);
bool boxBoxCollision(Non_physic_object box_1, Non_physic_object box_2);
bool sphereBoxCollision(Non_physic_object sphere, Non_physic_object cube);
glm::vec3 sphereBoxCollisionPoint(Physic_object sphere, Non_physic_object cube);
void addGravity(Physic_object& object, GLfloat delta_time);

// CALLBACK FUNCTIONS
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

// VARIABLES
bool        quit = false;
float       delta_time = 0.0f;    // Keep track of time per frame.
float       lastTime = 0.0f;    // variable to keep overall time.
bool        keyStatus[1024];    // Hold key status.
bool		mouseEnabled = true; // keep track of mouse toggle.
bool		camera_locked = false; //locking camera height

// MAIN GRAPHICS OBJECT
Graphics    myGraphics;        // Runing all the graphics in this object

// Some global variable to do the animation.
float t = 0.0f;            // Global variable for animation

//CROWD
constexpr auto nbFoule = 10;
glm::vec3	destination[nbFoule] = { glm::vec3(5, 3, 0) };
Sphere	Foule[nbFoule];
glm::vec3 Coo_Foule[nbFoule] = { glm::vec3(0.0f, 3.0f, 0.0f) };

// DEMO OBJECTS
#pragma region
vector<Physic_object> vec_physic_box;
vector<Physic_object> vec_physic_sphere;
vector<Non_physic_object> vec_nonphysic_box;

Cube floor_1, floor_2, floor_3, floor_4;
Non_physic_object non_physic_floor_1, non_physic_floor_2, non_physic_floor_3, non_physic_floor_4;
glm::vec3 floor_1_pos = glm::vec3(-20.0f, -0.5f, 0.0f),
	floor_2_pos = glm::vec3(0.0f, -0.5f, 20.0f),
	floor_3_pos = glm::vec3(20.0f, -0.5f, 0.0f),
	floor_4_pos = glm::vec3(0.0f, -0.5f, -20.0f);
glm::vec3 floor_1_scale = glm::vec3(20.0f, 1.0f, 60.0f),
	floor_2_scale = glm::vec3(20.0f, 1.0f, 20.0f),
	floor_3_scale = glm::vec3(20.0f, 1.0f, 60.0f),
	floor_4_scale = glm::vec3(20.0f, 1.0f, 20.0f);

Cube ballpit_floor, ballpit_wall_1, ballpit_wall_2, ballpit_wall_3, ballpit_wall_4;
Non_physic_object non_physic_ballpit_floor, non_physic_ballpit_wall_1, non_physic_ballpit_wall_2, non_physic_ballpit_wall_3, non_physic_ballpit_wall_4;
glm::vec3 ballpit_floor_pos = glm::vec3(0.0f, -21.0f, 0.0f),
	ballpit_wall_1_pos = glm::vec3(-10.5f, -11.0f, 0.0f),
	ballpit_wall_2_pos = glm::vec3(0.0f, -11.0f, 10.5f),
	ballpit_wall_3_pos = glm::vec3(10.5f, -11.0f, 0.0f),
	ballpit_wall_4_pos = glm::vec3(0.0f, -11.0f, -10.5f);
glm::vec3 ballpit_floor_scale = glm::vec3(20.0f, 1.0f, 20.0f),
	ballpit_wall_1_scale = glm::vec3(1.0f, 20.0f, 20.0f),
	ballpit_wall_2_scale = glm::vec3(20.0f, 20.0f, 1.0f),
	ballpit_wall_3_scale = glm::vec3(1.0f, 20.0f, 20.0f),
	ballpit_wall_4_scale = glm::vec3(20.0f, 20.0f, 1.0f);

Cube static_cube_1, static_cube_2;
Non_physic_object non_physic_static_cube_1, non_physic_static_cube_2;
glm::vec3 static_cube_1_pos = glm::vec3(-20.0f, 0.5f, 10.0f),
	static_cube_2_pos = glm::vec3(-20.0f, 0.5f, -10.0f);
glm::vec3 static_cube_1_scale = glm::vec3(1.0f, 1.0f, 1.0f),
	static_cube_2_scale = glm::vec3(1.0f, 1.0f, 1.0f);

Cube bouncing_cube_1, bouncing_cube_2, bouncing_cube_3;
Physic_object physic_bouncing_cube_1, physic_bouncing_cube_2, physic_bouncing_cube_3;
glm::vec3 bouncing_cube_1_pos = glm::vec3(-20.0f, 8.0f, 10.0f),
	bouncing_cube_2_pos = glm::vec3(-20.0f, 1.0f, 5.0f),
	bouncing_cube_3_pos = glm::vec3(-20.0f, 1.0f, -5.0f);

Sphere test_sphere_1, test_sphere_2, test_sphere_3, test_sphere_4, test_sphere_5, test_sphere_6, test_sphere_7, test_sphere_8, test_sphere_9;
Physic_object physic_test_sphere_1, physic_test_sphere_2, physic_test_sphere_3, physic_test_sphere_4, physic_test_sphere_5, physic_test_sphere_6, physic_test_sphere_7, physic_test_sphere_8, physic_test_sphere_9;
glm::vec3 test_sphere_1_pos = glm::vec3(-6.0f, -5.0f, 6.0f),
	test_sphere_2_pos = glm::vec3(0.0f, -5.0f, 6.0f),
	test_sphere_3_pos = glm::vec3(6.0f, -5.0f, 6.0f),
	test_sphere_4_pos = glm::vec3(-6.0f, -5.0f, 0.0f),
	test_sphere_5_pos = glm::vec3(0.0f, -5.0f, 0.0f),
	test_sphere_6_pos = glm::vec3(6.0f, -5.0f, 0.0f),
	test_sphere_7_pos = glm::vec3(-6.0f, -5.0f, -6.0f),
	test_sphere_8_pos = glm::vec3(0.0f, -5.0f, -6.0f),
	test_sphere_9_pos = glm::vec3(6.0f, -5.0f, -6.0f);
#pragma endregion

//some values
#pragma region
glm::vec3 default_scale = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 default_rot = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec4 sand_color = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
glm::vec4 grey_color = glm::vec4(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f);	// grey color
glm::vec4 light_grey_color = glm::vec4(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f, 1.0f);	// light grey color
glm::vec4 black_color = glm::vec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);	// black color
glm::vec4 purple_color = glm::vec4(128.0f / 255.0f, 0.0f / 255.0f, 128.0f / 255.0f, 1.0f);	// purple color
glm::vec4 orange_color = glm::vec4(255.0f / 255.0f, 127.0f / 255.0f, 80.0f / 255.0f, 1.0f);	// orange color
#pragma endregion

// CONSTANTS
const GLfloat PI = 3.1415f;
const glm::vec3 GRAVITY = glm::vec3(0.0f, -9.8f, 0.0f);

int main()
{
	int errorGraphics = myGraphics.Init();			// Launch window and graphics context
	if (errorGraphics) return 0;					// Close if something went wrong...

	startup();										// Setup all necessary information for startup (aka. load texture, shaders, models, etc).


	// MAIN LOOP run until the window is closed
	while (!quit) {

		// Update the camera transform based on interactive inputs or by following a predifined path.
		updateCamera();

		// Update position, orientations and any other relevant visual state of any dynamic elements in the scene.
		updateSceneElements();

		// Render a still frame into an off-screen frame buffer known as the backbuffer.
		renderScene();

		// Swap the back buffer with the front buffer, making the most recently rendered image visible on-screen.
		glfwSwapBuffers(myGraphics.window);        // swap buffers (avoid flickering and tearing)

	}


	myGraphics.endProgram();            // Close and clean everything up...

   // cout << "\nPress any key to continue...\n";
   // cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {
	// Keep track of the running time
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	delta_time = currentTime;                        // start delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Callback graphics and key update functions - declared in main to avoid scoping complexity.
	// More information here : https://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);            // Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);                    // Set Callback for keys
	glfwSetMouseButtonCallback(myGraphics.window, onMouseButtonCallback);    // Set callback for mouse click
	glfwSetCursorPosCallback(myGraphics.window, onMouseMoveCallback);        // Set callback for mouse move
	glfwSetScrollCallback(myGraphics.window, onMouseWheelCallback);            // Set callback for mouse wheel.

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	//Random number generator
	srand(time(NULL));

	// Load Geometry examples
#pragma region
	non_physic_floor_1 = Non_physic_object(&floor_1, floor_1_scale, floor_1_pos, default_rot, sand_color);
	vec_nonphysic_box.emplace_back(non_physic_floor_1);
	non_physic_floor_2 = Non_physic_object(&floor_2, floor_2_scale, floor_2_pos, default_rot, sand_color);
	vec_nonphysic_box.emplace_back(non_physic_floor_2);
	non_physic_floor_3 = Non_physic_object(&floor_3, floor_3_scale, floor_3_pos, default_rot, sand_color);
	vec_nonphysic_box.emplace_back(non_physic_floor_3);
	non_physic_floor_4 = Non_physic_object(&floor_4, floor_4_scale, floor_4_pos, default_rot, sand_color);
	vec_nonphysic_box.emplace_back(non_physic_floor_4);

	non_physic_ballpit_floor = Non_physic_object(&ballpit_floor, ballpit_floor_scale, ballpit_floor_pos, default_rot, grey_color);
	non_physic_ballpit_wall_1 = Non_physic_object(&ballpit_wall_1, ballpit_wall_1_scale, ballpit_wall_1_pos, default_rot, light_grey_color);
	non_physic_ballpit_wall_2 = Non_physic_object(&ballpit_wall_2, ballpit_wall_2_scale, ballpit_wall_2_pos, default_rot, light_grey_color);
	non_physic_ballpit_wall_3 = Non_physic_object(&ballpit_wall_3, ballpit_wall_3_scale, ballpit_wall_3_pos, default_rot, light_grey_color);
	non_physic_ballpit_wall_4 = Non_physic_object(&ballpit_wall_4, ballpit_wall_4_scale, ballpit_wall_4_pos, default_rot, light_grey_color);
	vec_nonphysic_box.emplace_back(non_physic_ballpit_floor);
	vec_nonphysic_box.emplace_back(non_physic_ballpit_wall_1);
	vec_nonphysic_box.emplace_back(non_physic_ballpit_wall_2);
	vec_nonphysic_box.emplace_back(non_physic_ballpit_wall_3);
	vec_nonphysic_box.emplace_back(non_physic_ballpit_wall_4);

	non_physic_static_cube_1 = Non_physic_object(&static_cube_1, static_cube_1_scale, static_cube_1_pos, default_rot, grey_color);
	vec_nonphysic_box.emplace_back(non_physic_static_cube_1);
	non_physic_static_cube_2 = Non_physic_object(&static_cube_2, static_cube_2_scale, static_cube_2_pos, default_rot, grey_color);
	vec_nonphysic_box.emplace_back(non_physic_static_cube_2);

	physic_bouncing_cube_1 = Physic_object(&bouncing_cube_1, default_scale, bouncing_cube_1_pos, default_rot, 10.0f, orange_color);
	physic_bouncing_cube_2 = Physic_object(&bouncing_cube_2, default_scale, bouncing_cube_2_pos, default_rot, 10.0f, orange_color);
	physic_bouncing_cube_3 = Physic_object(&bouncing_cube_3, default_scale, bouncing_cube_3_pos, default_rot, 5.0f, orange_color);
	vec_physic_box.emplace_back(physic_bouncing_cube_1);
	vec_physic_box.emplace_back(physic_bouncing_cube_2);
	vec_physic_box.emplace_back(physic_bouncing_cube_3);

	physic_test_sphere_1 = Physic_object(&test_sphere_1, default_scale, test_sphere_1_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_2 = Physic_object(&test_sphere_2, default_scale, test_sphere_2_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_3 = Physic_object(&test_sphere_3, default_scale, test_sphere_3_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_4 = Physic_object(&test_sphere_4, default_scale, test_sphere_4_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_5 = Physic_object(&test_sphere_5, default_scale, test_sphere_5_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_6 = Physic_object(&test_sphere_6, default_scale, test_sphere_6_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_7 = Physic_object(&test_sphere_7, default_scale, test_sphere_7_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_8 = Physic_object(&test_sphere_8, default_scale, test_sphere_8_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_9 = Physic_object(&test_sphere_9, default_scale, test_sphere_9_pos, default_rot, 10.0f, orange_color);
	physic_test_sphere_1.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_2.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_3.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_4.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_5.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_6.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_7.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_8.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	physic_test_sphere_9.setSpeed(glm::vec3(rand() % 20 - 10, 0.0f, rand() % 20 - 10));
	vec_physic_sphere.emplace_back(physic_test_sphere_1);
	vec_physic_sphere.emplace_back(physic_test_sphere_2);
	vec_physic_sphere.emplace_back(physic_test_sphere_3);
	vec_physic_sphere.emplace_back(physic_test_sphere_4);
	vec_physic_sphere.emplace_back(physic_test_sphere_5);
	vec_physic_sphere.emplace_back(physic_test_sphere_6);
	vec_physic_sphere.emplace_back(physic_test_sphere_7);
	vec_physic_sphere.emplace_back(physic_test_sphere_8);
	vec_physic_sphere.emplace_back(physic_test_sphere_9);
#pragma endregion

	//CROWD
	for (int i = 0; i < nbFoule; i++) {
		Foule[i].Load();
		Foule[i].fillColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Optimised Graphics
	myGraphics.SetOptimisations();        // Cull and depth testing

}

void updateCamera() {

	// calculate movement for FPS camera
	GLfloat xoffset = myGraphics.mouseX - myGraphics.cameraLastX;
	GLfloat yoffset = myGraphics.cameraLastY - myGraphics.mouseY;    // Reversed mouse movement
	myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	myGraphics.cameraYaw += xoffset;
	myGraphics.cameraPitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (myGraphics.cameraPitch > 89.0f) myGraphics.cameraPitch = 89.0f;
	if (myGraphics.cameraPitch < -89.0f) myGraphics.cameraPitch = -89.0f;

	// Calculating FPS camera movement (See 'Additional Reading: Yaw and Pitch to Vector Calculations' in VISION)
	glm::vec3 front;
	front.x = cos(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));
	front.y = sin(glm::radians(myGraphics.cameraPitch));
	front.z = sin(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));

	myGraphics.cameraFront = glm::normalize(front);

	// Update movement using the keys
	GLfloat cameraSpeed = 10.0f * delta_time;
	GLfloat camera_height_temp = myGraphics.cameraPosition.y;
	if (keyStatus[GLFW_KEY_W]) myGraphics.cameraPosition += cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_S]) myGraphics.cameraPosition -= cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_A]) myGraphics.cameraPosition -= glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;
	if (keyStatus[GLFW_KEY_D]) myGraphics.cameraPosition += glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;

	if (camera_locked) {
		myGraphics.cameraPosition.y = camera_height_temp;
	}

	// IMPORTANT PART
	// Calculate my view matrix using the lookAt helper function
	if (mouseEnabled) {
		myGraphics.viewMatrix = glm::lookAt(myGraphics.cameraPosition,			// eye
			myGraphics.cameraPosition + myGraphics.cameraFront,					// centre
			myGraphics.cameraUp);												// up
	}
}

void updateSceneElements() {


	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	delta_time = currentTime - lastTime;                // Calculate delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

	vector < pair<Non_physic_object*, Physic_object*>> nonPhysicBox_physicBox_vector;
	vector < pair<Non_physic_object*, Physic_object*>> nonPhysicBox_physicSphere_vector;

	vector <pair<Physic_object*, Physic_object*>> physicBox_physicBox_vector;
	vector <pair<Physic_object*, Physic_object*>> physicSphere_physicBox_vector;
	vector <pair<Physic_object*, Physic_object*>> physicSpere_physicSpere_vector;

	//adding gravity
	for (auto& box : vec_physic_box) {
		addGravity(box, delta_time);
	}
	for (auto& sphere : vec_physic_sphere) {
		addGravity(sphere, delta_time);
	}
	//check for physic boxes collision and add to vector
	for (auto& box : vec_physic_box) {
		if (box.getJustCollided() != 0) {
			box.decrementJustCollided();
		}
		else {
			for (auto& box_2 : vec_physic_box) {
				//check if box is box_2 to not collide with itself
				if (&box != &box_2) {
					if (boxBoxCollision(box, box_2)) {
						physicBox_physicBox_vector.push_back({ &box, &box_2 });
						box.resetJustCollided();
					}
				}
			}
			for (auto& sphere : vec_physic_sphere) {
				if (sphereBoxCollision(sphere, box)) {
					physicSphere_physicBox_vector.push_back({ &box, &sphere });
					box.resetJustCollided();
				}
			}
			for (auto& wall : vec_nonphysic_box) {
				if (boxBoxCollision(box, wall)) {
					nonPhysicBox_physicBox_vector.push_back({ &wall, &box });
					box.resetJustCollided();
				}
			}
		}
	}
	//check or physic spheres collision and add to vector
	for (auto& sphere : vec_physic_sphere) {
		if (sphere.getJustCollided() != 0) {
			sphere.decrementJustCollided();
		}
		else {
			for (auto& sphere_2 : vec_physic_sphere) {
				//check if sphere is sphere_2 to not collide with itself
				if (&sphere != &sphere_2) {
					if (sphereSphereCollision(sphere, sphere_2)) {
						physicSpere_physicSpere_vector.push_back({ &sphere, &sphere_2 });
						sphere.resetJustCollided();
					}
				}
			}
			for (auto& box : vec_physic_box) {
				if (sphereBoxCollision(sphere, box)) {
					physicSphere_physicBox_vector.push_back({ &sphere, &box });
					sphere.resetJustCollided();
				}
			}
			for (auto& wall : vec_nonphysic_box) {
				if (sphereBoxCollision(sphere, wall)) {
					nonPhysicBox_physicSphere_vector.push_back({ &wall, &sphere });
					sphere.resetJustCollided();
				}
			}
		}
	}

	//look through vectors to resolve collision
	for (auto& pair : nonPhysicBox_physicBox_vector) {
		pair.second->setSpeed(pair.second->getSpeed() * -0.95f);
	}
	for (auto& pair : nonPhysicBox_physicSphere_vector) {

		glm::vec3 collision_point = sphereBoxCollisionPoint(*pair.second, *pair.first);

		glm::vec3 normal = glm::normalize(pair.second->getPosition() - collision_point);

		glm::vec3 temp_speed = pair.second->getSpeed();
		if (normal.x != 0.0f) {
			pair.second->setSpeed(glm::vec3(temp_speed.x * glm::abs(normal.x) * -1.0f, temp_speed.y, temp_speed.z));
		}
		if (normal.y != 0.0f) {
			pair.second->setSpeed(glm::vec3(temp_speed.x, temp_speed.y * glm::abs(normal.y) * -1.0f, temp_speed.z));
		}
		if (normal.z != 0.0f) {
			pair.second->setSpeed(glm::vec3(temp_speed.x, temp_speed.y, temp_speed.z * glm::abs(normal.z) * -1.0f));
		}
	}
	for (auto& pair : physicBox_physicBox_vector) {

	}
	for (auto& pair : physicSphere_physicBox_vector) {
		
	}
	for (auto& pair : physicSpere_physicSpere_vector) {
		GLfloat dist = sqrt(
			(pair.first->getPosition().x - pair.second->getPosition().x) * (pair.first->getPosition().x - pair.second->getPosition().x) +
			(pair.first->getPosition().y - pair.second->getPosition().y) * (pair.first->getPosition().y - pair.second->getPosition().y) +
			(pair.first->getPosition().z - pair.second->getPosition().z) * (pair.first->getPosition().z - pair.second->getPosition().z));

		glm::vec3 normal = (pair.second->getPosition() - pair.first->getPosition()) / dist;

		glm::vec3 tangent = glm::vec3(normal.y * -1.0f, normal.x, (normal.y + normal.x) / 2.0f);

		GLfloat dpTan1 = pair.first->getSpeed().x * tangent.x + pair.first->getSpeed().y * tangent.y + pair.first->getSpeed().z * tangent.z;
		GLfloat dpTan2 = pair.second->getSpeed().x * tangent.x + pair.second->getSpeed().y * tangent.y + pair.second->getSpeed().z * tangent.z;

		GLfloat dpNorm1 = pair.first->getSpeed().x * normal.x + pair.first->getSpeed().y * normal.y + pair.first->getSpeed().z * normal.z;
		GLfloat dpNorm2 = pair.second->getSpeed().x * normal.x + pair.second->getSpeed().y * normal.y + pair.second->getSpeed().z * normal.z;

		GLfloat m1 = (dpNorm1 * (pair.first->getMass() - pair.second->getMass()) + 2.0f * pair.second->getMass() * dpNorm2) / (pair.first->getMass() + pair.second->getMass());
		GLfloat m2 = (dpNorm2 * (pair.second->getMass() - pair.first->getMass()) + 2.0f * pair.first->getMass() * dpNorm1) / (pair.first->getMass() + pair.second->getMass());

		pair.first->setSpeed(tangent * dpTan1 + normal * m1);
	}

	//update position and display matrix
	for (auto& box : vec_physic_box) {

		box.updatePosition(delta_time);

		box.updateMVMatrix();

		box.getMyShape()->mv_matrix = myGraphics.viewMatrix * box.getMVMatrix();
		box.getMyShape()->proj_matrix = myGraphics.proj_matrix;
	}
	for (auto& sphere : vec_physic_sphere) {

		sphere.updatePosition(delta_time);

		sphere.updateMVMatrix();

		sphere.getMyShape()->mv_matrix = myGraphics.viewMatrix * sphere.getMVMatrix();
		sphere.getMyShape()->proj_matrix = myGraphics.proj_matrix;
	}
	for (auto& wall : vec_nonphysic_box) {

		wall.updateMVMatrix();

		wall.getMyShape()->mv_matrix = myGraphics.viewMatrix * wall.getMVMatrix();
		wall.getMyShape()->proj_matrix = myGraphics.proj_matrix;
	}

	//CROWD
	// Calculate crowd
	glm::mat4 mv_matrix_foule[nbFoule];
	for (int i = 0; i < nbFoule; i++) {
		mv_matrix_foule[i] =
			glm::translate(Coo_Foule[i]) *
			glm::scale(glm::vec3(0.3f, 0.3f, 0.3f)) *
			glm::mat4(1.0f);
		Foule[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_foule[i];
		Foule[i].proj_matrix = myGraphics.proj_matrix;
	}

	t += 0.01f; // increment movement variable
	direction();

	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.

}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	for (auto box : vec_physic_box) {
		box.getMyShape()->Draw();
	}
	for (auto sphere : vec_physic_sphere) {
		sphere.getMyShape()->Draw();
	}
	for (auto wall : vec_nonphysic_box) {
			wall.getMyShape()->Draw();
	}

	//CROWD
	for (int i = 0; i < nbFoule; i++) {
		Foule[i].Draw();
	}
}

// CallBack functions low level functionality.
void onResizeCallback(GLFWwindow* window, int w, int h) {    // call everytime the window is resized
	//myGraphics.windowWidth = w;
	//myGraphics.windowHeight = h;

	glfwGetFramebufferSize(window, &myGraphics.windowWidth, &myGraphics.windowHeight);

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (action == GLFW_PRESS) keyStatus[key] = true;
	else if (action == GLFW_RELEASE) keyStatus[key] = false;

	// toggle showing mouse.
	if (keyStatus[GLFW_KEY_M]) {
		mouseEnabled = !mouseEnabled;
		myGraphics.ToggleMouse();
	}

	if (keyStatus[GLFW_KEY_C]) {
		camera_locked = !camera_locked;
	}

	// If exit key pressed.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	myGraphics.mouseX = mouseX;
	myGraphics.mouseY = mouseY;

	// helper variables for FPS camera
	if (myGraphics.cameraFirstMouse) {
		myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX; myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY; myGraphics.cameraFirstMouse = false;
	}
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}

//CROWD
void changer() {
	//cout << "atteint\n";
	int x = rand() % 11 + (-5);
	int y = rand() % 11 + 1;
	int z = rand() % 11 + (-5);

	for (int i = 0; i < nbFoule; i++) {
		destination[i][0] = x + (rand() % 11 + (-5)) / 2;
		destination[i][1] = y + (rand() % 11 + (-5)) / 2;
		destination[i][2] = z + (rand() % 11 + (-5)) / 2;
	}
}
void direction() {
	for (int i = 0; i < nbFoule; i++) {

		if (Coo_Foule[i][0] > destination[i][0]) {
			Coo_Foule[i][0] -= 0.01f;
		}
		else {
			Coo_Foule[i][0] += 0.01f;
		}
		if (Coo_Foule[i][1] > destination[i][1]) {
			Coo_Foule[i][1] -= 0.01f;
		}
		else {
			Coo_Foule[i][1] += 0.01f;
		}
		if (Coo_Foule[i][2] > destination[i][2]) {
			Coo_Foule[i][2] -= 0.01f;
		}
		else {
			Coo_Foule[i][2] += 0.01f;
		}
		if (destination[i][0] - 0.2 <= Coo_Foule[i][0] && Coo_Foule[i][0] <= destination[i][0] + 0.2 &&
			destination[i][1] - 0.2 <= Coo_Foule[i][1] && Coo_Foule[i][1] <= destination[i][1] + 0.2 &&
			destination[i][2] - 0.2 <= Coo_Foule[i][2] && Coo_Foule[i][2] <= destination[i][2] + 0.2) {
			changer();
		}
	}
}
//OTHER FUNCTIONS
bool boxBoxCollision(Non_physic_object box_1, Non_physic_object box_2) {
	struct box {

		box(glm::vec3 position, glm::vec3 scale) {
			xmax = position.x + scale.x / 2;
			xmin = position.x - scale.x / 2;
			ymax = position.y + scale.y / 2;
			ymin = position.y - scale.y / 2;
			zmax = position.z + scale.z / 2;
			zmin = position.z - scale.z / 2;
		};
		~box() {};

		GLfloat xmax, ymax, zmax;
		GLfloat xmin, ymin, zmin;
	};

	box cube_1(box_1.getPosition(), box_1.getScale()), cube_2(box_2.getPosition(), box_2.getScale());

	return	(((cube_2.xmax >= cube_1.xmax && cube_1.xmax >= cube_2.xmin) || (cube_2.xmax >= cube_1.xmin && cube_1.xmin >= cube_2.xmin)) &&
		((cube_2.ymax >= cube_1.ymax && cube_1.ymax >= cube_2.ymin) || (cube_2.ymax >= cube_1.ymin && cube_1.ymin >= cube_2.ymin)) &&
		((cube_2.zmax >= cube_1.zmax && cube_1.zmax >= cube_2.zmin) || (cube_2.zmax >= cube_1.zmin && cube_1.zmin >= cube_2.zmin)))
		||
		(((cube_1.xmax >= cube_2.xmax && cube_2.xmax >= cube_1.xmin) || (cube_1.xmax >= cube_2.xmin && cube_2.xmin >= cube_1.xmin)) &&
		((cube_1.ymax >= cube_2.ymax && cube_2.ymax >= cube_1.ymin) || (cube_1.ymax >= cube_2.ymin && cube_2.ymin >= cube_1.ymin)) &&
			((cube_1.zmax >= cube_2.zmax && cube_2.zmax >= cube_1.zmin) || (cube_1.zmax >= cube_2.zmin && cube_2.zmin >= cube_1.zmin)));
}
bool sphereSphereCollision(Non_physic_object sphere_1, Non_physic_object sphere_2) {

	GLfloat arbitrary_value = 0.98f; //arbitrary value to make sphere collides closer, otherwise collision gets detected but no visual contact can be seen.

	glm::vec3 two_centers_vec;
	two_centers_vec.x = sphere_1.getPosition().x - sphere_2.getPosition().x;
	two_centers_vec.y = sphere_1.getPosition().y - sphere_2.getPosition().y;
	two_centers_vec.z = sphere_1.getPosition().z - sphere_2.getPosition().z;

	return ((sphere_1.getScale().x + sphere_2.getScale().x) / 2) * arbitrary_value >= glm::length(two_centers_vec);
}
bool sphereBoxCollision(Non_physic_object sphere, Non_physic_object cube) {

	GLfloat arbitrary_value = 0.98f; //arbitrary value to make sphere collides closer, otherwise collision gets detected but no visual contact can be seen.

	struct box {

		box(glm::vec3 position, glm::vec3 scale) {
			xmax = position.x + scale.x / 2;
			xmin = position.x - scale.x / 2;
			ymax = position.y + scale.y / 2;
			ymin = position.y - scale.y / 2;
			zmax = position.z + scale.z / 2;
			zmin = position.z - scale.z / 2;
		};
		~box() {};

		GLfloat xmax, ymax, zmax;
		GLfloat xmin, ymin, zmin;
	};

	box my_box(cube.getPosition(), cube.getScale());

	glm::vec3 distance;
	distance.x = max(my_box.xmin, min(sphere.getPosition().x, my_box.xmax));
	distance.y = max(my_box.ymin, min(sphere.getPosition().y, my_box.ymax));
	distance.z = max(my_box.zmin, min(sphere.getPosition().z, my_box.zmax));

	distance -= sphere.getPosition();

	return glm::length(distance) <= (sphere.getScale().x / 2) * arbitrary_value;
}
glm::vec3 sphereBoxCollisionPoint(Physic_object sphere, Non_physic_object cube) {

	GLfloat arbitrary_value = 0.98f; //arbitrary value to make sphere collides closer, otherwise collision gets detected but no visual contact can be seen.

	struct box {

		box(glm::vec3 position, glm::vec3 scale) {
			xmax = position.x + scale.x / 2;
			xmin = position.x - scale.x / 2;
			ymax = position.y + scale.y / 2;
			ymin = position.y - scale.y / 2;
			zmax = position.z + scale.z / 2;
			zmin = position.z - scale.z / 2;
		};
		~box() {};

		GLfloat xmax, ymax, zmax;
		GLfloat xmin, ymin, zmin;
	};

	box my_box(cube.getPosition(), cube.getScale());

	glm::vec3 collision_point;
	collision_point.x = max(my_box.xmin, min(sphere.getPosition().x, my_box.xmax));
	collision_point.y = max(my_box.ymin, min(sphere.getPosition().y, my_box.ymax));
	collision_point.z = max(my_box.zmin, min(sphere.getPosition().z, my_box.zmax));

	return collision_point;
}
void addGravity(Physic_object& object, GLfloat delta_time) {
	object.updateSpeed(delta_time, GRAVITY);
}


