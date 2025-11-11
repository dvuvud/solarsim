#pragma once

namespace solarsim {
	class Texture
	{
		public:
			unsigned int m_ID, m_unit;
			int m_width, m_height, m_nrChannels;

			Texture(const char* p_texturePath, unsigned int p_textureUnit = 0, bool p_useMipmap = true);
			void bind();
	};
}
