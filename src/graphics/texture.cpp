#define STB_IMAGE_IMPLEMENTATION
#include <graphics/texture.hpp>
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

namespace solarsim {
	Texture::Texture(const char* texturePath, unsigned int textureUnit, bool useMipmap) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		unit = textureUnit;

		// Setting texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (useMipmap) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Loading image
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
		if (data) {
			GLenum format;
			if (nrChannels == 1) {
				format = GL_RED;
			} else if (nrChannels == 3) {
				format = GL_RGB;
			} else if (nrChannels == 4) {
				format = GL_RGBA;
			} else {
				format = GL_RGB;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

			if (useMipmap) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		} else {
			std::cerr << "Failed to load texture: " << texturePath << std::endl;
		}

		stbi_image_free(data);
	}

	void Texture::bind() {
		glActiveTexture(GL_TEXTURE0+unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}
