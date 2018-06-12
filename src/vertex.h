#pragma once
#include "common.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
	glm::vec2 uv;
	Vertex(const glm::vec3& p, const glm::vec2& _uv) : pos(p) , uv(_uv) {}
	Vertex(const glm::vec3& p, const glm::vec4& _c) : pos(p), color(_c) {}
};