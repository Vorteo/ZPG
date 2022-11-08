
#include "Application.h";

int main(void)
{
	Application* application = application->GetInstance();

	int sceneType;

	printf("Scene type 1-3: ");
	scanf_s("%d", &sceneType);

	switch (sceneType)
	{
	case 1:
		application->setScene(Factory::GetInstance()->createSpheresScene());
		break;
	case 2:
		application->setScene(Factory::GetInstance()->createOneSphereScene());
		break;
	case 3:
		application->setScene(Factory::GetInstance()->createMultipleObjectsScene());
		break;
	}
	application->Run();


}