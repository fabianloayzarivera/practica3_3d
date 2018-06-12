#pragma once
#include "common.h"
#include "texture.h"
#include "shader.h"
#include "state.h"

class Material 
{
private:
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Shader> shader;
public:
	Material(const std::shared_ptr<Texture>& tex = nullptr,
	const std::shared_ptr<Shader>& shader = nullptr);
	const std::shared_ptr<Shader>& getShader() const { return shader ? shader: State::defaultShader; }
	std::shared_ptr<Shader>& getShader() { return shader ? shader : State::defaultShader; }
	void setShader(const std::shared_ptr<Shader>& _shader) { shader = _shader; }
	const std::shared_ptr<Texture>& getTexture() const { return texture; }
	void setTexture(const std::shared_ptr<Texture>& tex) { texture = tex; }
	void prepare();

};