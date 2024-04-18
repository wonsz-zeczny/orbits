#include "Texture.hpp"

#include <stb_image.h>

#include <iostream>


Texture::Texture(std::string_view texture_filepath, const TextureGLParams& texture_gl_params,
	std::string_view texture_uniform_name)
	: texture_gl_params{ texture_gl_params }, texture_uniform_name{ texture_uniform_name },
	texture_unit{ active_texture_units_count++ } {

	glGenTextures(1, &texture_id);

	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(texture_gl_params.texture_type, texture_id);

	unsigned char* pixels{ stbi_load(texture_filepath.data(), &width, &height, &channels, 0)};

	glTexImage2D(texture_gl_params.texture_type, texture_gl_params.mipmap_level,
		texture_gl_params.format_to_store, width, height, 0, texture_gl_params.input_format,
		texture_gl_params.pixels_data_type, pixels);
	
	glGenerateMipmap(texture_gl_params.texture_type);

	stbi_image_free(pixels);
}

void Texture::bind() const {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(texture_gl_params.texture_type, texture_id);
}

void Texture::setParameteri(GLenum parameter_name, GLint parameter_value) const {
	bind();

	glTexParameteri(texture_gl_params.texture_type, parameter_name, parameter_value);
}

int Texture::getTextureUnit() const {
	return texture_unit;
}

std::string_view Texture::getTextureUniformName() const {	
	return texture_uniform_name;
}