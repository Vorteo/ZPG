#include "Application.h";
#include "Model.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
 
const float b[] = {
		0.1f, 0.0f, 0.0f,   1, 0, 0,
	    0.1f, 0.5f, 0.0f,  0, 1, 0,
	    0.5f, 0.0f, 0.0f,  0, 0, 1,

		0.5f, 0.5f, 0.0f,   1, 0, 0,
		0.1f, 0.5f, 0.0f,  0, 1, 0,
		0.5f, 0.0f, 0.0f,  0, 0, 1,
};

const float c[] = {
		-0.1f, 0.0f, 0.0f,   1, 1, 0,
		-0.1f, 0.5f, 0.0f,  0, 1, 1,
		-0.5f, 0.0f, 0.0f,  1, 0, 1,
};
 
int main(void)
{
	// Run
	Application* Application = Application->GetInstance();

	// sphere model loading
	Model* sphereModel = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	Application->AddModel(sphereModel);

	//Model* sphereModel1 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	//Application->AddModel(sphereModel1);

	//Model* sphereModel2 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	//Application->AddModel(sphereModel2);


	Application->CheckStatus();
	Application->Run();
}