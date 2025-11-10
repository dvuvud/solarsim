#pragma once

class Texture
{
	public:
		unsigned int ID, unit;
		int width, height, nrChannels;

		Texture(const char* texturePath, unsigned int textureUnit = 0, bool useMipmap = true);
		void bind();
};
