#pragma once


#include <glad/gl.h>

#include <string_view>


class Texture {
	public:
		struct TextureGLParams {
			GLenum texture_type{ GL_TEXTURE_2D };
			GLint mipmap_level{ 0 };
			GLint format_to_store{ GL_RGB };
			GLint input_format{ GL_RGB };
			GLenum pixels_data_type{ GL_UNSIGNED_BYTE };
		};

		Texture(std::string_view texture_filepath, const TextureGLParams& texture_params,
			std::string_view texture_uniform_name);

		Texture() = delete;

		void bind() const;
		void setParameteri(GLenum parameter_name, GLint parameter_value) const;
		int getTextureUnit() const;
		std::string_view getTextureUniformName() const;

	private:
		unsigned int texture_id{ 0 };
		int width{ 0 };
		int height{ 0 };
		int channels{ 0 };
		int texture_unit{ 0 };
		std::string_view texture_uniform_name;
		TextureGLParams texture_gl_params;
		inline static int active_texture_units_count{ 0 };
};