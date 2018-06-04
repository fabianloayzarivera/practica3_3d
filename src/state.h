#pragma once
#include "common.h"
#include "shader.h"

class State 
{
private:
	State() {}
	~State() {} //Delete DefaultShader?
public:
	static std::shared_ptr<Shader>	defaultShader;
	static glm::mat4 				projectionMatrix;
	static glm::mat4 				viewMatrix;
	static glm::mat4 				modelMatrix;

};