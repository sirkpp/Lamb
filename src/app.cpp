//We have documentation on docs.gl
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "loadObject.hpp"
#include<vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "transform.h"
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define pi 3.1459
using namespace glm;

/*
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

*/





int main() {
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "graphics project : Lamborgini", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	//Drawing triangle
	
	

	// An array of 3 vectors which represents 3 vertices


	// Read our .obj file
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	bool res = loadObj("C:\\dev\\graphics\\project\\myCar\\myCar\\myCar2.txt", vertices, uvs, normals);
	static const GLfloat g_vertex_buffer_data[] = {
	-0.5f,-0.5f,-0.5f, // triangle 1 : begin
	-0.5f,-0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, // triangle 1 : end
	0.5f, 0.5f,-0.5f, // triangle 2 : begin
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f, // triangle 2 : end
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f
	};



	// This will identify our vertex buffer
	GLuint VBO, VAO;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);



	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(float) * 3,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !









	// Create and compile our GLSL program from the shaders
	Shader ourShaders("vertexShader.glsl", "fragmentShader.glsl");
	ourShaders.use();
	glClear(GL_COLOR_BUFFER_BIT);
	float anglee = 0;
	float ztranslate = 0;
	Transform transform;
	
	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		

		// Use our shader
		// be sure to activate the shader


		float *transX = transform.rotateX(anglee/10);
		float *transY = transform.rotateY(anglee/2);
		float *transZ = transform.rotateZ(anglee);
		float *projection = transform.getPerspectiveMatrix(pi/4, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.0);
		float *view = transform.translate(0, 0, -ztranslate);
		
		ourShaders.use();

		ourShaders.use();
		unsigned int transformLoc = glGetUniformLocation(ourShaders.program, "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transY);
		/*glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transX);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transZ);*/
		
		unsigned int projectLoc = glGetUniformLocation(ourShaders.program, "projection");
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, projection);


		unsigned int translateLoc = glGetUniformLocation(ourShaders.program, "view");
		glUniformMatrix4fv(translateLoc, 1, GL_FALSE, view);
		


		//Adding Camera feature
		//Camera start


		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		



		//Camera stop





				//		// create transformations
				//		/*glm::mat4 model = glm::mat4(1.0f);*/ // make sure to initialize matrix to identity matrix first
				//glm::mat4 view = glm::mat4(1.0f);
				//glm::mat4 projection = glm::mat4(1.0f);
				//		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.3f, -1.0f, 0.0f));
				//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
				//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
				//		// retrieve the matrix uniform locations
				//		//unsigned int modelLoc = glGetUniformLocation(ourShaders.program, "model");
				//unsigned int viewLoc = glGetUniformLocation(ourShaders.program, "view");
				//		// pass them to the shaders (3 different ways)
				//		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
				//		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
				//ourShaders.setMat4("projection", projection);













		
		//glm::mat4 trans = glm::mat4(1.0f);
		///*trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));*/
		//trans = glm::rotate(trans, (float)glm::radians(anglee), glm::vec3(1.0f, 1.0f, 0.0f));
		//ourShaders.use();
		//std::cout << glm::to_string(trans) << std::endl;
		//unsigned int transformLoc = glGetUniformLocation(ourShaders.program, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// update the uniform color
		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(programID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		// Draw triangle...

		// render container
		glBindVertexArray(VBO);

		
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()*sizeof(glm::vec3)); // Starting from vertex 0; 3 vertices total -> 1 triangle
		
		anglee += 0.02;
		ztranslate += -0.1;
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete transX;
		delete transY;
		delete transZ;
		delete projection;
		delete view;
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return 0;
}



//static unsigned int CompileShader(unsigned int type, const std::string &source) {
//	unsigned int id = glCreateShader(type);
//	const char *src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	glCompileShader(id);
//
//
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//
//
//	//error handling
//	if (result == GL_FALSE) {
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char* message = (char *)alloca(length * sizeof(char));
//		glGetShaderInfoLog(id, length, &length, message);
//		std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
//		std::cout << message << std::endl;
//		glDeleteShader(id);
//		return 0;
//	}
//
//	
//	
//
//	return id;
//}
//
//static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//	return program;
//}
//
//
//int main(void)
//{
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//
//	glfwMakeContextCurrent(window);
//
//	if (glewInit() != GLEW_OK) {
//		std::cout << "cherno is awesome";
//	};
//
//
//	std::cout << glGetString(GL_VERSION) << std::endl;
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	float positions[6] = {
//		-0.5f, -0.5f,
//		0.0f, 0.5f,
//		0.5f, -0.5f
//	};
//
//	unsigned int buffer;
//	glGenBuffers(1, &buffer);//creating buffer
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);//select buffer
//	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);
//
//	//Enabling the vertex. For more info google it.
//	glEnableVertexAttribArray(0);
//
//	//tells opengl how the vertex are formatted in the memory as stated in the position array above.
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
//
//	std::string vertexShader = 
//		"#version 330 core\n"
//		"\n"
//		"layout(location=0) in vec4 position;\n"
//		"\n"
//		"void main(){\n"
//		"  glPosition= position;\n"
//		"}";
//
//
//	std::string fragmentShader =
//		"#version 330 core\n"
//		"\n"
//		"layout(location=0) out vec4 color;\n"
//
//		"void main(){\n"
//		"  color = vec4(1.0, 0.0, 0.0, 1.0);\n" //rgba normalized
//		"}";
//
//
//	unsigned int shader = CreateShader(vertexShader, fragmentShader);
//	glUseProgram(shader);
//
//	//vertex shader runs for all vertices individually---one for each vertex. It determines the position of screen.
//	//fragment shader runs for each pixel. It determine the color of each pixel.
//	//shader is a program that runs on gpu.
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glDeleteShader(shader);
//
//	glfwTerminate();
//	return 0;
//}