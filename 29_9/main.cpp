#include "Application.h";
#include "Model.h"

//GLM test
// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model1 = glm::mat4(1.0f);

float points[] = {
	 -0.5f, 0.5f, 0.0f, // top left point
	0.5f, 0.5f, 0.0f, // top right point
	0.5f, -0.5f, 0.0f, // bottom right point
	0.5f, -0.5f, 0.0f, // bottom right point
	-0.5f, -0.5f, 0.0f, // bottom left point
	-0.5f, 0.5f, 0.0f, // top left point
};

int main(void)
{
	//**** Run
	Application* Application = Application->GetInstance();

	Model* model = new Model(points, sizeof(points)/sizeof(points[0]));
	Application->AddModel(model);
	Application->CheckStatus();
	Application->Run();
}