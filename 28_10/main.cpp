
#include "Application.h";

int main(void)
{
	Application* application = application->GetInstance();

	// 1 scena
	//application->setScene(Factory::GetInstance()->createSpheresScene());
	
	// 2 scena
	//application->setScene(Factory::GetInstance()->createOneSphereScene());
	
	// 3 scena
	application->setScene(Factory::GetInstance()->createMultipleObjectsScene());

	application->Run();
}