#include <application.hpp>
#include <appContext.hpp>
#include <camera.hpp>
#include <glfwInput.hpp>
#include <world.hpp>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>




void Application::singlePlayerInit() {
	World world;

	G.camera = new Camera(glm::vec3(0, 32, 3)); // Later, Initialize camera position based on (EITHER, surface level on 0,0 OR latest player postion saved on world)


	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	 

	m_Renderer.drawMesh(glm::ivec3(0, 0, 0));
	m_Renderer.uploadMesh(glm::ivec3(0, 0, 0));
}


void Application::singlePlayerLoop() {

	processInput(m_Window);
	
	
	

	//m_Renderer.createWorldMesh(world, G.camera);
	
	m_Renderer.renderAll();
}