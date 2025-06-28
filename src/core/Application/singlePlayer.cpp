#include <application.hpp>
#include <appContext.hpp>
#include <camera.hpp>
#include <glfwInput.hpp>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

float vertices[] = {
	// posX, posY, posZ,    u, v
	-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // 0
	 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // 1
	 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, // 2
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, // 3
	-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, // 4
	 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, // 5
	 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, // 6
	-0.5f,  0.5f,  0.5f,    0.0f, 1.0f  // 7
};

unsigned int indices[] = {
	// Frente (z+)
	4, 5, 6,
	6, 7, 4,
	// Tras (z-)
	1, 0, 3,
	3, 2, 1,
	// Esquerda (x-)
	0, 4, 7,
	7, 3, 0,
	// Direita (x+)
	5, 1, 2,
	2, 6, 5,
	// Topo (y+)
	3, 7, 6,
	6, 2, 3,
	// Fundo (y-)
	0, 1, 5,
	5, 4, 0
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
unsigned int VAO;


void Application::singlePlayerInit() {
	G.camera = new Camera(glm::vec3(0, 0, 3));


	


	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	 // Later, Initialize camera position based on (EITHER, surface level on 0,0 OR latest player postion saved on world)

	unsigned int  VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Atributos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

}


void Application::singlePlayerLoop() {
	processInput(m_Window);
	
	glm::mat4 projection = glm::perspective(glm::radians(G.camera->fov), (float)WIDTH / (float)HEIGHT, 0.01f, 5000.0f);
	e_Shaders[shaderType::MAIN].setMat4("projection", projection);
	glm::mat4 view = G.camera->GetViewMatrix();
	e_Shaders[shaderType::MAIN].setMat4("view", view);

	glBindVertexArray(VAO);
	e_Shaders[shaderType::MAIN].use();
	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		e_Shaders[shaderType::MAIN].setMat4("model", model);
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//renderer render mesh---


	//---------






}