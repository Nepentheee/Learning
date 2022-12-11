#include "CubeMap.h"
#include "STB/stb_image.h"
#include <vector>

CubeMap::CubeMap()
{
	glGenTextures(1, &m_RenderID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID);

	vector<std::string> faces
	{
		CubeMap0, CubeMap1, CubeMap2, CubeMap3, CubeMap4, CubeMap5,
	};

	int width, height, nrChannels;
	unsigned char* data;

	for (unsigned int i = 0; i < 6; i++)
	{
		stbi_set_flip_vertically_on_load(false); /* ´¹Ö±·­×ªÎÆÀí */
		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data != nullptr)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

CubeMap::~CubeMap()
{
}

void CubeMap::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID);
}

void CubeMap::UnBind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int CubeMap::GetCubeMapRenderID()
{
	return m_RenderID;
}