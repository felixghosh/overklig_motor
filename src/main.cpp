#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

GLFWwindow* window;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

int init(){
	//Init glfw and set version/profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and set the OpenGL context to the context of our window
	window = glfwCreateWindow(800, 600, "Overklig", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main()
{
	init();
	
	//Main loop
	while(!glfwWindowShouldClose(window)) {
		//handle input
		processInput(window);

		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	//Terminate the program
	glfwTerminate();
	return 0;
	
}

