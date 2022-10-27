#include "Application.h";
 
int main(void)
{
	Application* application = application->GetInstance();

	application->setScene(Factory::GetInstance()->createSpheresScene());

	//application->setScene(Factory::GetInstance()->createOneSphereScene());

	application->Run();
}