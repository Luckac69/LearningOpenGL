#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#include <cmath>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Usage
std::string vertexCode = readFile("shaders/vertex.glsl");
std::string fragmentCodeOrange = readFile("shaders/fragmentOrange.glsl");
std::string fragmentCodeYellow = readFile("shaders/fragmentYellow.glsl");
std::string fragmentCode = readFile("shaders/fragment.glsl");
const char* vertexShaderSource = vertexCode.c_str();
const char* fragmentShaderSourceOrange= fragmentCodeOrange.c_str();
const char* fragmentShaderSourceYellow = fragmentCodeYellow.c_str();
const char* fragmentShaderSource = fragmentCode.c_str();

// Tutorial Code
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

// Vertex shader

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	// Create window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Check for Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	// VERTEX
	// createing shader object (ref by ID again)
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // got paramter 3 from top
	glCompileShader(vertexShader);

	// Fragment shader
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); 
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//unsigned int shaderProgramOrange = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();
	unsigned int shaderProgram = glCreateProgram();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	//glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);


	// create shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
//	glAttachShader(shaderProgramOrange, vertexShader);
//	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
//	glLinkProgram(shaderProgramOrange);
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);
//	// delete unneeded shader objects
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShaderOrange);
//	glDeleteShader(fragmentShaderYellow);

	int success;
	char infoLog[512];
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// vertex data!
	float firstTriangle[] = {


		-0.45f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, -0.5f, 0.0f,   0.0f, 0.0f, 1.1f
	};
	float secondTriangle[] = {
		0.0f, 0.5f, 0.0f,
		0.9f, 0.5f, 0.0f,
		0.45f, -0.5f, 0.0f


	};

//	unsigned int EBO;
//	glGenBuffers(1, &EBO);


	unsigned int VAOs[2], VBOs[2];
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	
	// triangle 1
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// triangle 2
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);  


	//[...]
	//// TROLLLED AGAIN

	//unbind stuff
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//////    uncomment for wireframe
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	

	// window loop
	while (!glfwWindowShouldClose(window)){



		processInput(window);

		// render
		// clear color buffer
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//activate shader
		glUseProgram(shaderProgram);

		// update uniform color
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// delete stuff when done
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);
	//glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}




