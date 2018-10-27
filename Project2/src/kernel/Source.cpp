#include <inc/glew.h>
#include <inc/glfw3.h>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <math.h>

#include "Window.h"
#include "Renderer.h"

int main(void)
{
	
	Window* window = Window::get_instance();
	window->build(1400, 1050);

	Renderer renderer;
	TextureCache* texture_cache = TextureCache::get_texture_cache();
	Camera* camera = Camera::get_instance();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->get_GLFWWindow(), false);
	ImGui_ImplOpenGL3_Init("#version 400");
	ImGui::StyleColorsDark();

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1);

	double time = glfwGetTime();

	double now = time;
	double last_time = time, delta = 0, timer = 0, last_tick = time;
	int tick = 0;
	int fps = 30;

	bool depth_test = true, cull_face = true, pause = false;
	bool polygon_mode = false;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static float f = 0.0f;
	int count = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window->get_GLFWWindow()))
	{
		

		now = glfwGetTime();
		delta += (now - last_time) * fps;
		last_time = now;

		if (delta >= 1.0f) {
			delta--;

			if (!pause) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				camera->update(last_time - last_tick);

				renderer.update();

				renderer.render();
				
			}


			

			
			last_tick = last_time;


			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Camera");

			ImGui::Text("Position : [%.3f, %.3f, %.3f]", camera->get_position()->x, -camera->get_position()->y, camera->get_position()->z);
			ImGui::Text("Rotation : [%.3f, %.3f, %.3f]", 
				acosf(cosf(camera->get_rotation()->x * M_PI / 180)) / M_PI * 180, 
				acosf(cosf(camera->get_rotation()->y * M_PI / 180)) / M_PI * 180,
				acosf(cosf(camera->get_rotation()->z * M_PI / 180)) / M_PI * 180
			);

			ImGui::Text("Movement speed (s) :     ");
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::SliderFloat("", camera->get_movement_speed(), 5, 100);
			
			ImGui::Text("Rotation speed (deg/s) : ");
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			ImGui::SliderFloat(" ", camera->get_rotation_speed(), 5, 100);

			ImGui::End();

			ImGui::Begin("Options");

			ImGui::Checkbox("Depth Test", &depth_test);
			ImGui::SameLine();
			ImGui::Checkbox("Pause", &pause);

			ImGui::Checkbox("Cull face", &cull_face); 
			ImGui::Checkbox("Polygon mode", &polygon_mode);

			if(polygon_mode)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (cull_face)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);

			if (depth_test)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);

			ImGui::Text("FPS : ");
			ImGui::SameLine();
			ImGui::SliderInt("", &fps, 1, 100);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			tick++;

			if (last_time - timer >= 1.0f) {
				timer = last_time;
				tick = 0;
			}
			
			if(!pause)
				glfwSwapBuffers(window->get_GLFWWindow());

			glfwPollEvents();
		}

			
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}