#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <math.h>
#include </home/felixghosh/prog/c++/motor/src/shader.h>

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

int init() {
	//Init glfw and set version/profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and set the OpenGL context to the context of our window
	window = glfwCreateWindow(800, 800, "Overklig", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glViewport(0, 0, 800, 600);

	
	//Init GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}

int main()
{
	//initialize glfw and glad
	if(init() == -1) return -1;

	//load and compile our shaders
	Shader ourShader("src/vShader.vs", "src/fShader.fs");

	/*float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};    */
	float vertices [] = {
		 0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
	 	 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f
	};

	unsigned int indices[] = {
		0, 4, 3,	//back
		4, 3, 7,
		0, 1, 4,	//right
		1, 4, 5,
		4, 5, 7,	//bottom
		5, 7, 6,	
		0, 1, 3,	//top
		1, 3, 2,	
		5, 6, 1,	//front
		6, 1, 2,
		3, 7, 2,	//left
		7, 2, 6
	};

	//generate vertex array object and buffer object
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind Vertex Array Object
	glBindVertexArray(VAO);

	//bind VBO and copy vertices into it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set vertex attribute pointer to the first three values of our vertex array to represent positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*//set vertex attribute pointer to the last three values of our vertex array to represent color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);*/

	//glUseProgram(shaderProgram);
	//ourShader.use();
	float thetaValue = 0.0f;
	double t0 = glfwGetTime();
	double elapsedTime = 0.0f;
	double fps;
	long frames = 0;
	//Main loop
	while(!glfwWindowShouldClose(window)) { 
		//handle input
		processInput(window);

		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//fix time stuff
		float timeValue = glfwGetTime();
		float colorValue = (sin(timeValue) / 2.0f) + 0.5f;
		thetaValue += 0.002f;
		ourShader.use();
		ourShader.setFloat("theta", thetaValue);
		ourShader.setFloat("colorValue", colorValue);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 66, GL_UNSIGNED_INT, 0);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		frames++;
		elapsedTime = glfwGetTime() - t0;
		std::cout << frames / elapsedTime << std::endl;
	}

	//dealocate memory and terminate the program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderProgram);
	
	glfwTerminate();
	return 0;	
}