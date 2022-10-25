#include "Application.h";
#include "Model.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
 
int main(void)
{
	//**** Run
	Application* Application = Application->GetInstance();

	Model* sphereModel = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	Application->AddModel(sphereModel);

	Model* sphereModel1 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	Application->AddModel(sphereModel1);

	Model* sphereModel2 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	Application->AddModel(sphereModel2);

	Model* sphereModel3 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	Application->AddModel(sphereModel3);

	Application->CheckStatus();
	Application->Run();
}