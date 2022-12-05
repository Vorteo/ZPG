#include "Factory.h"
#include "AssimpModel.h"
#include "Models.h"
#include "SkyBox.h"

enum shaders
{
	CONSTANT = 0,
	LAMBERT = 1,
	PHONG = 2,
	BLINNPHONG = 3,
	TEXTURE = 4,
	SKYBOX = 5,
	PHONG_LIGHTS = 6,
	PHONG_LIGHTS_TEXTURE = 7,
};

Factory* Factory::instance = 0;

Factory* Factory::getInstance()
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

DrawableObject* Factory::createPlaineObjectWithTexture(glm::mat4 transformationMatrix, const char* textureName)
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

DrawableObject* Factory::createSkyBoxObject()
{
	SkyBox* skybox = new SkyBox();
	return new DrawableObject((Model*)skybox, nullptr, new Transformation(), true);
}

DrawableObject* Factory::createAssimpObject(std::string filePath, const char* textureName, glm::mat4 transformationMatrix)
{
	AssimpModel* assimpModel = new AssimpModel();
	assimpModel->load(filePath);
	assimpModel->loadTexture(textureName);

	return new DrawableObject( (Model*) assimpModel, true, new ShaderProgram("PhongLightsTextureShader.frag", "PhongLightsTextureShader.vert"), new Transformation(transformationMatrix));
}

//****************************************************************************************************************************
// Scene

void Factory::addTreeOnPosition(Scene* scene, glm::vec3 pos)
{
	glm::mat4 M0 = glm::mat4(1.0f);
	M0 = glm::translate(M0, pos);
	M0 = glm::scale(M0, glm::vec3(0.2f));

	scene->addDrawableObject(this->createAssimpObject("AssimpModels/tree/tree.obj", "AssimpModels/tree/tree.png", M0), PHONG_LIGHTS_TEXTURE);
}

Scene* Factory::createSpheresScene()
{
	Scene* scene = new Scene();
	scene->setCamera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))), CONSTANT);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))), LAMBERT);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))), PHONG);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))), BLINNPHONG);
	
	return scene;
}

Scene* Factory::TestLightsScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	PointLight* p = new PointLight();
	p->setPosition(glm::vec3(0.0f,2.0f,0.0f));

	scene->addLight(p);
	scene->addLight(new SpotLight());

	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 0.0f))), PHONG_LIGHTS);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 3.0f))), PHONG_LIGHTS);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 1.0f, 0.0f))), PHONG_LIGHTS);
	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -3.0f))), PHONG_LIGHTS);

	glm::mat4 M0 = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
	scene->addDrawableObject(this->createPlaineObjectWithTexture(M0, "grass.png"), PHONG_LIGHTS_TEXTURE);

	return scene;
}

Scene* Factory::createMultipleObjectsScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(-10.0f, 5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 M0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	M0 = glm::scale(M0, glm::vec3(100.0f));

	scene->addDrawableObject(this->createObject(4, M0), LAMBERT);

	srand(time(NULL));
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 3 + 1;	
		scene->addDrawableObject(this->createObject(7, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand() % 100), 0.0f, 0.0f + (rand()% 100)))),rand_shader);
		scene->addDrawableObject(this->createObject(6, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand() % 100), 0.0f, 0.0f + (rand() % 100)))), rand_shader);
	}
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 3 + 1;
		int rand_model = rand() % 5 + 1;
		scene->addDrawableObject(this->createObject(rand_model, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand()% 100), 0.0f, 0.0f + (rand()% 100)))), rand_shader);
	}

	return scene;
}

Scene* Factory::createSkyBoxScene()
{
	Scene* scene = new Scene();
	scene->setSkybox(this->createSkyBoxObject());

	scene->addDrawableObject(this->createAssimpObject("AssimpModels/teren/teren.obj", "AssimpModels/teren/grass.png", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))), TEXTURE);

	return scene;
}

Scene* Factory::createComplexScene()
{
	Scene* scene = new Scene();

	scene->addLight(new SpotLight());
	scene->addLight(new DirectionalLight(glm::vec3(1.0f, 0.72f, 0.56f), glm::vec3(0.0f, 0.0f, 1.0f)));
	scene->addLight(new DirectionalLight(glm::vec3(1.0f, 0.72f, 0.56f), glm::vec3(5.0f, -1.0f, -5.0f)));

	scene->setSkybox(this->createSkyBoxObject());

	scene->addDrawableObject(this->createAssimpObject("AssimpModels/teren/teren.obj", "AssimpModels/teren/grass.png", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))), PHONG_LIGHTS_TEXTURE);
	scene->addDrawableObject(this->createAssimpObject("AssimpModels/zombie/zombie.obj","AssimpModels/zombie/zombie.png", glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -1.0f, 0.0f))), PHONG_LIGHTS_TEXTURE);
	scene->addDrawableObject(this->createAssimpObject("AssimpModels/tree/tree.obj", "AssimpModels/tree/tree.png", glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -1.0f, -5.0f))), PHONG_LIGHTS_TEXTURE);
	scene->addDrawableObject(this->createAssimpObject("AssimpModels/house/model.obj", "AssimpModels/house/model.png", glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -1.0f, 0.0f))), PHONG_LIGHTS_TEXTURE);
	scene->addDrawableObject(this->createAssimpObject("AssimpModels/wall/zed.obj", "AssimpModels/wall/bake.png", glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f,-1.0f,5.0f))), PHONG_LIGHTS_TEXTURE);

	scene->addDrawableObject(this->createObject(1, glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 1.0f, 2.0f))), PHONG_LIGHTS);

	return scene;
}
