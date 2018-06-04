#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "../lib/glfw/glfw3.h"
#include <fstream>
#include "vertex.h"
#include "shader.h"
#include "buffer.h"
#include "state.h"
#include "model.h"
#include "world.h"
#include "mesh.h"
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


std::string readString(const std::string& filename) {
	std::ifstream ifs(filename.c_str(), std::ios_base::binary | std::ios_base::ate);
	std::vector<char> chars(ifs.tellg());
	ifs.seekg(0);
	ifs.read(chars.data(), chars.size());
	return std::string(chars.data(), chars.size());
}

bool init() 
{
	// initialize opengl extensions
	if (glewInit() != GLEW_OK) {
		std::cout << "could not initialize opengl extensions" << std::endl;
		glfwTerminate();
		return false;
	}
	// initialize opengl states
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	// load shaders code
	std::string vertexShaderSource = readString("data/vertex.glsl");
	std::string fragmentShaderSource = readString("data/fragment.glsl");

	std::shared_ptr<Shader> shader(Shader::create(vertexShaderSource, fragmentShaderSource));

	if (shader->getError().size() > 0)
	{
		glDeleteProgram(shader->getId());
		glfwTerminate();
		return false;
	}	
	State::defaultShader = shader;	
	return true;
}

int main() {
	
	// init glfw
	if (!glfwInit()) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	if(!init()){
		std::cout << "Error Initializing Engine" << std::endl;
		return -1;
	}

	//State::defaultShader->use();
	std::shared_ptr<World> world(new World());
	std::shared_ptr<Camera> camera1(new Camera(60.0f,(float)SCREEN_WIDTH ,(float)SCREEN_HEIGHT,0.1f, 1000.0f));
	camera1->setClearColor(glm::vec3(0, 0, 0));
	camera1->setPosition(glm::vec3(0, 0, 6));
	world->addEntity(camera1);

	//--- Creating a buffer 
	glm::vec3 v1( 0,  0.5, 0);
	glm::vec3 v2(-0.5, -0.5, 0);
	glm::vec3 v3(0.5, -0.5, 0);
	glm::vec4 c1( 1,  1, 1, 1);	
	glm::vec4 c2( 1,  1, 1, 1);
	glm::vec4 c3( 1,  1, 1, 1);

	// define triangle
	std::vector<Vertex> vertices = {
		
		Vertex(v1,c1),
		Vertex(v2,c2),
		Vertex(v3,c3)

	};

	std::vector<uint32_t> indexes = {0,1,2};
	// store triangle in vram
	std::shared_ptr<Buffer> buffer(new Buffer(vertices, indexes));

	//------------------------------
	std::shared_ptr<Mesh> mesh(new Mesh());
	mesh->addBuffer(buffer);

	int x = -3;
	int y = 0;
	int z = 0;

	for (int i = 0; i < 3; i++)
	{
		z = 0;
		for (int j = 0; j < 3; j++)
		{
			std::shared_ptr<Model> model(new Model(mesh));
			model->setPosition(glm::vec3(x, y, z));
			model->setRotation(glm::vec3(0, 0, 0));
			model->setScale(glm::vec3(1, 1, 1));
			world->addEntity(model);
			z -= 3;
		}
		x += 3;
	}	
	
	float angle = 0;
	float angleVariation = 32.0f;

	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		camera1->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

		//Rotate triangles!
		int numEntities;
		numEntities = world->getNumEntities();
		for (int i = 0; i < numEntities; i++) 
		{
			std::shared_ptr<Entity> Entity = world->getEntity(i);
			if (Entity != camera1) 
			{
				Entity->setRotation(glm::vec3(0, angle, 0));
			}
		}
		
		world->update(deltaTime);
		world->draw();
		angle += angleVariation * deltaTime;

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();		
		
	}

	glfwTerminate();

}
