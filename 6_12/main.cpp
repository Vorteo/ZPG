#include "Application.h"

int main(void)
{
	Application* application = application->getInstance();

	int sceneType;

	printf("Scene options 1-5: ");
	scanf_s("%d", &sceneType);

	switch (sceneType)
	{
	case 1:
		application->setScene(Factory::getInstance()->createSpheresScene());
		break;
	case 2:
		application->setScene(Factory::getInstance()->TestLightsScene());
		break;
	case 3:
		application->setScene(Factory::getInstance()->createMultipleObjectsScene());
		break;
	case 4:
		application->setScene(Factory::getInstance()->createSkyBoxScene());
		break;
	case 5:
		application->setScene(Factory::getInstance()->createComplexScene());
		break;
	}

	application->run();
}