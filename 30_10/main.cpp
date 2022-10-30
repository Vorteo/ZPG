
#include "Application.h";

int main(void)
{
	Application* application = application->GetInstance();

	int sceneType;

	printf("Scene type 1-3: ");
	scanf_s("%d", &sceneType);

	switch (sceneType)
	{
		// 4 spheres with phong shader
	case 1:
		application->setScene(Factory::GetInstance()->createSpheresScene());
		break;
		// 1 sphere with phong
	case 2:
		application->setScene(Factory::GetInstance()->createOneSphereScene());
		break;
	case 3:
		// multiple models and shaders scene
		application->setScene(Factory::GetInstance()->createMultipleObjectsScene());
		break;
	}
	application->Run();
}