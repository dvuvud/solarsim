#pragma once

class Texture
{
	public:
		// the program ID
		unsigned int ID, unit;
		int width, height, nrChannels;

		// constructor reads and builds the texture
		Texture(const char* texturePath, unsigned int textureUnit = 0, bool useMipmap = true);
		// use/activate the texture
		void bind();
};
