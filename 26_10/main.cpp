#include "Application.h";
#include "Model.h"
#include "Models/sphere.h"
 
int main(void)
{
	//**** Run
	Application* application = application->GetInstance();

	//application->setScene(Factory::GetInstance()->createSpheresScene());

 
	Model* sphereModel = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	application->AddModel(sphereModel);

	Model* sphereModel1 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	application->AddModel(sphereModel1);

	Model* sphereModel2 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	application->AddModel(sphereModel2);

	Model* sphereModel3 = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	application->AddModel(sphereModel3);

	application->Run();
}