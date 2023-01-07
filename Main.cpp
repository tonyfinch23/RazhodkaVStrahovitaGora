#include<filesystem>
namespace fs = std::filesystem;

#include"Model.h"


const unsigned int width = 1280;
const unsigned int height = 720;


int main()
{
		glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
		if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
		glfwMakeContextCurrent(window);

		gladLoadGL();
			glViewport(0, 0, width, height);





		Shader shaderProgram("default.vert", "default.frag");
	Shader shaderProgramDay("default.vert", "defaultDay.frag");


		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	shaderProgramDay.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);





		glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

		Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model ground("models/ground/scene.gltf");
	Model trees("models/trees/scene.gltf");

	


		while (!glfwWindowShouldClose(window))
	{
				glClearColor(0.027f, 0.12f, 0.09f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				camera.Inputs(window);
				camera.updateMatrix(45.0f, 0.1f, 100.0f);

				ground.Draw(shaderProgram, camera);
		trees.Draw(shaderProgram, camera);

				glfwSwapBuffers(window);
				glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{

			while (!glfwWindowShouldClose(window))
			{
								glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
								glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

								camera.Inputs(window);
								camera.updateMatrix(45.0f, 0.1f, 100.0f);

								ground.Draw(shaderProgramDay, camera);
				trees.Draw(shaderProgramDay, camera);

								glfwSwapBuffers(window);
								glfwPollEvents();
			}

		}
	}



		shaderProgram.Delete();
	shaderProgramDay.Delete();
		glfwDestroyWindow(window);
		glfwTerminate();
	return 0;
}