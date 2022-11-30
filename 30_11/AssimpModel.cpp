#include "AssimpModel.h"

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags


struct Vertex
{
	float position[3];
	float normal[3];
	float texture[2];
};


AssimpModel::AssimpModel()
{
	this->indicesCount = 0;
	this->IBO = 0;
	this->textureID = 0;
}

AssimpModel::~AssimpModel()
{

}

void AssimpModel::load(std::string fileName)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes						// slouceni malych plosek
		| aiProcess_JoinIdenticalVertices				// NUTNE jinak hodne duplikuje
		| aiProcess_Triangulate							// prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;					// vypocet tanget, nutny pro spravne pouziti normalove mapy
		//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene)
	{
		// pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
			{
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);
			}
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			Vertex* pVertices = new Vertex[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].position[0] = mesh->mVertices[i].x;
					pVertices[i].position[1] = mesh->mVertices[i].y;
					pVertices[i].position[2] = mesh->mVertices[i].z;
				}

				if (mesh->HasNormals())
				{
					pVertices[i].normal[0] = mesh->mNormals[i].x;
					pVertices[i].normal[1] = mesh->mNormals[i].y;
					pVertices[i].normal[2] = mesh->mNormals[i].z;
				}

				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].texture[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].texture[1] = mesh->mTextureCoords[0][i].y;
				}
			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{
				pIndices = new unsigned int[mesh->mNumFaces * 3];

				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}

			this->VBO = 0;
			glGenBuffers(1, &this->VBO);	// generate VBO
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, &pVertices[0], GL_STATIC_DRAW);

			this->IBO = 0;
			glGenBuffers(1, &this->IBO);	// generate IBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, &pIndices[0], GL_STATIC_DRAW);

			this->VAO = 0;
			glGenVertexArrays(1, &this->VAO);	// generate VAO
			glBindVertexArray(this->VAO);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 3));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 6));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl;
			}

			this->indicesCount = mesh->mNumFaces * 3;
			
			delete[] pVertices;
			delete[] pIndices;
		}
	}

	else
	{
		printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
	}

	glBindVertexArray(0);
}

void AssimpModel::loadTexture(const char* textureName)
{
	//glGenTextures(1, &this->textureID);

	//glBindTexture(GL_TEXTURE_2D, this->textureID);
	this->textureID = SOIL_load_OGL_texture(textureName, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (this->textureID == 0)
	{
		fprintf(stderr, "Failed to load texture %s\n", textureName);
		exit(1);
	}
}

int AssimpModel::getIndices()
{
	return this->indicesCount;
}

GLuint AssimpModel::getTextureID()
{
	return this->textureID;
}

void AssimpModel::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
}

void AssimpModel::unbindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
