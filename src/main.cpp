#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Matrix
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

int main() {

	// init glfw
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
	// Shader
	Shader ourShader("shaders/shader.vs.glsl", "shaders/shader.fs.glsl");
	Shader yellowShader("shaders/vertex.glsl", "shaders/fragmentYellow.glsl");

	float verticies[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f    // top left
	};
	unsigned int indicies[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// texture stuff
	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	
	float boarderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f }; 




	unsigned int VAOs[2], VBOs[2], EBO;
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture stuff //////////?########################
	stbi_set_flip_vertically_on_load(true);  // flips images
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// between texals
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int textureWidth, textureHeight, nrChannels;
	unsigned char *data = stbi_load("textures/container.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Faild to load texture" << std::endl;
	}
	// free image data variable thingy
	stbi_image_free(data);

	// texture 2 //////////////////////////////////
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// between texals
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, texture1);

	data = stbi_load("textures/awesomeface.png", &textureWidth, &textureHeight, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // GL_RGBA instead of GL_RGB for alpha
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Faild to load texture" << std::endl;
	}


	// free image data variable thingy
	stbi_image_free(data);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glBindVertexArray(VAOs[0]);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	// tell open gl to add pictures to uniform
	ourShader.use();
	ourShader.setInt("texture0", 0);
	ourShader.setInt("texture1", 1);






	// window loop
	while (!glfwWindowShouldClose(window)){


		processInput(window);
		// render
		// clear color buffer
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// MATRIX EXPIREMENTS
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		// send matrix to shader
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// draw first box
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// second box
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = static_cast<float>(sin(glfwGetTime()));
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		// draw second box
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ourShader.use();
		glUniform2f(glGetUniformLocation(ourShader.ID, "offset"), 0, 0);

		glBindVertexArray(VAOs[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// delete stuff when done
	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgramOrange);
	//glDeleteProgram(shaderProgramYellow);
	//glDeleteProgram(shaderProgram);
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




