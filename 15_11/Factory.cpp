#include "Factory.h"

enum shaders
{
	CONSTANT = 0,
	LAMBERT = 1,
	PHONG = 2,
	BLINNPHONG = 3,
	TEXTURE = 4,
	SKYBOX = 5,
	LIGHTS = 6,
};

Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

Factory::Factory()
{
	models["sphere"] = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	models["suziFlat"] = new Model(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]));
	models["suziSmooth"] = new Model(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]));
	models["plain"] = new Model(plain, sizeof(plain) / sizeof(plain[0]));
	models["gift"] = new Model(gift, sizeof(gift) / sizeof(gift[0]));
	models["bushes"] = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]));
	models["tree"] = new Model(tree, sizeof(tree) / sizeof(tree[0]));
	
}

DrawableObject* Factory::createObject(int modelType, glm::mat4 transformationMatrix)
{
	switch (modelType)
	{
		// sphere
	case 1:
		return new DrawableObject(models.find("sphere")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// suziFlat
	case 2:
		return new DrawableObject(models.find("suziFlat")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// suziSmooth
	case 3:
		return new DrawableObject(models.find("suziSmooth")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// plain
	case 4:
		return new DrawableObject(models.find("plain")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// gift
	case 5:
		return new DrawableObject(models.find("gift")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// bushes
	case 6:
		return new DrawableObject(models.find("bushes")->second, nullptr, new Transformation(transformationMatrix));
		break;
		// tree
	case 7:
		return new DrawableObject(models.find("tree")->second, nullptr, new Transformation(transformationMatrix));
		break;
	}
}

DrawableObject* Factory::createObjectTexture(glm::mat4 transformationMatrix, const char* textureName)
{
	const float plain_texture[] = {
		//vrchol, normála, uv souøadnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};


	return new DrawableObject(new Model(plain_texture, sizeof(plain_texture) / sizeof(plain_texture[0]), 1), nullptr, new Transformation(transformationMatrix), textureName);
}

DrawableObject* Factory::createSkyBox()
{
	SkyBox* skybox = new SkyBox();
	return new DrawableObject((Model*)skybox, nullptr, new Transformation(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))), 1);
}

Scene* Factory::createSpheresScene()
{
	Scene* scene = new Scene();
	scene->setCamera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))), PHONG);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))), PHONG);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))), PHONG);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))), PHONG);
	
	return scene;
}
Scene* Factory::createOneSphereScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))), PHONG);

	return scene;
}
Scene* Factory::createMultipleObjectsScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(-10.0f, 5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))), CONSTANT);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))), LAMBERT);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))), PHONG );
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))), BLINNPHONG);

	srand(time(NULL));
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 4 + 0;	
		scene->addDrawableObject(this->createObject(7, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand() % 100), 0.0f, 0.0f + (rand()% 100)))),rand_shader);
		scene->addDrawableObject(this->createObject(6, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand() % 100), 0.0f, 0.0f + (rand() % 100)))), rand_shader);
	}
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 4 + 0;
		int rand_model = rand() % 5 + 1;
		scene->addDrawableObject(this->createObject(rand_model, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand()% 100), 0.0f, 0.0f + (rand()% 100)))), rand_shader);
	}

	return scene;
}

Scene* Factory::createTextureScene()
{
	Scene* scene = new Scene();
	scene->setCamera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObjectTexture(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)),"test.png"), TEXTURE);
	scene->addDrawableObject(this->createObjectTexture(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f)), "grass.png"), TEXTURE);
	scene->addDrawableObject(this->createObjectTexture(glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f)), "wooden_fence.png"), TEXTURE);

	return scene;
}

Scene* Factory::createSkyBoxScene()
{
	Scene* scene = new Scene();
	scene->addDrawableObject(this->createSkyBox(), SKYBOX);

	return scene;
}
