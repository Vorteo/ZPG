#include "Application.h";
#include "Model.h"

float points[] = {
	 //position			// color
   -0.5f, 0.5f, 0.f,  1.0f, 0.0f, 0.0f, // top left point
	0.5f, 0.5f, 0.f,  0.0f, 1.0f, 0.0f,// top right point
	0.5f, -0.5f, 0.f, 0.0f, 0.0f, 1.0f, // bottom right point
	0.5f, -0.5f, 0.f, 1.0f, 1.0f, 0.0f,// bottom right point
   -0.5f, -0.5f, 0.f, 0.0f, 1.0f, 1.0f,// bottom left point
   -0.5f, 0.5f, 0.f,  1.0f, 0.0f, 1.0f,// top left point
};

 
float b[] = {
		0.1f, 0.0f, 0.0f,   1, 0, 0,
	    0.1f, 0.5f, 0.0f,  0, 1, 0,
	    0.5f, 0.0f, 0.0f,  0, 0, 1,

		0.5f, 0.5f, 0.0f,   1, 0, 0,
		0.1f, 0.5f, 0.0f,  0, 1, 0,
		0.5f, 0.0f, 0.0f,  0, 0, 1,
};

float c[] = {
		-0.1f, 0.0f, 0.0f,   1, 1, 0,
		-0.1f, 0.5f, 0.0f,  0, 1, 1,
		-0.5f, 0.0f, 0.0f,  1, 0, 1,
};
 
int main(void)
{
	//**** Run
	Application* Application = Application->GetInstance();


	Model* model = new Model(b, sizeof(b)/sizeof(b[0]));
	Model* model2 = new Model(c, sizeof(c) / sizeof(c[0]));

	Application->AddModel(model);
	Application->AddModel(model2);

	Application->CheckStatus();
	Application->Run();
}