#include "state.h"
#include <iostream>
#include "vertex.h"

std::shared_ptr<Shader> State::defaultShader;
glm::mat4 				State::projectionMatrix;
glm::mat4 				State::viewMatrix;
glm::mat4 				State::modelMatrix;