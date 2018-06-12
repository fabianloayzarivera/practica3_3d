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
	std::shared_ptr<Camera> camera1(new Camera(60.0f,(float)SCREEN_WIDTH ,(float)SCREEN_HEIGHT,0.1f, 100.0f));
	camera1->setClearColor(glm::vec3(1, 1, 1));
	camera1->setPosition(glm::vec3(0, 1, 3));
	camera1->setRotation(glm::vec3(-20, 0, 0));
	world->addEntity(camera1);
	
	//--- Creating a buffer 
	glm::vec3 v1(-1, -1,  1);
	glm::vec3 v2( 1, -1,  1);
	glm::vec3 v3( 1,  1,  1);
	glm::vec3 v4(-1,  1,  1);
	glm::vec3 v5( 1, -1, -1);
	glm::vec3 v6( 1,  1, -1);
	glm::vec3 v7(-1, -1, -1);
	glm::vec3 v8(-1,  1, -1);

	glm::vec2 uv1(0, 0);
	glm::vec2 uv2(1, 0);
	glm::vec2 uv3(1, 1);
	glm::vec2 uv4(0, 1);


	std::vector<Vertex> vertices = {

		Vertex(v1,uv1), //0
		Vertex(v2,uv2), //1
		Vertex(v3,uv3), //2
		Vertex(v4,uv4), //3
		Vertex(v2,uv1), //4
		Vertex(v5,uv2), //5
		Vertex(v6,uv3), //6
		Vertex(v3,uv4), //7
		Vertex(v5,uv1), //8
		Vertex(v7,uv2), //9
		Vertex(v8,uv3), //10
		Vertex(v6,uv4), //11
		Vertex(v7,uv1), //12
		Vertex(v1,uv2), //13
		Vertex(v4,uv3), //14
		Vertex(v8,uv4), //15
		Vertex(v4,uv1), //16
		Vertex(v3,uv2), //17
		Vertex(v5,uv3), //18
		Vertex(v7,uv4)	//19


	};

	std::vector<uint16_t> indexesTop = {16,17,6, 16,6,15, 0,1,18, 0,18,19};

	std::vector<uint16_t> indexesFront = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11, 12,13,14, 12,14,15};

	std::shared_ptr<Texture> texTop = Texture::load("data/top.png");
	std::shared_ptr<Texture> texFront = Texture::load("data/front.png");

	std::shared_ptr<Buffer> bufferTop = std::make_shared<Buffer>(vertices, indexesTop);
	std::shared_ptr<Buffer> bufferFront = std::make_shared<Buffer>(vertices, indexesFront);

	std::shared_ptr<Material> materialTop = std::make_shared<Material>(texTop);
	std::shared_ptr<Material> materialFront = std::make_shared<Material>(texFront);

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->addBuffer(bufferTop, *materialTop);
	mesh->addBuffer(bufferFront, *materialFront);

	std::shared_ptr<Model> modelCube = std::make_shared<Model>(mesh);
	modelCube->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	world->addEntity(modelCube);
	//------------------------------	
	
	float angle = 0;
	float angleVariation = 62.0f;

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
