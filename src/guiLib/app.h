#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>

#include "imgui_multiplot.h"

#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg.h"
#include "nanovg_gl.h"

#include <iostream>
#include <map>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

class App
{
public:
	App() { }

	~App() {
		// Cleanup
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

	int setupWindow(int width, int height, const char * title){

		// Setup window
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
			return 1;

		// Decide GL+GLSL versions
	#if __APPLE__
		// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
	#else
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	#endif

		// Create window with graphics context
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (window == NULL)
			return 1;
		glfwSetWindowCenter(window);
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glfwSwapInterval(0); // Enable vsync (1)

		// Initialize OpenGL loader
	#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
		bool err = gl3wInit() != 0;
	#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
		bool err = glewInit() != GLEW_OK;
	#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
		bool err = gladLoadGL() != 0;
	#endif
		if (err)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}

		// Setup Dear ImGui binding
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		// Setup style
	//	ImGui::StyleColorsDark();
		ImGui::StyleColorsClassic();

		vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG);

		return 0;
	}

	void run() {
		glfwSetWindowUserPointer(window, this);
		auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods){
			if(ImGui::GetIO().WantCaptureKeyboard)
				return;

			if(action == GLFW_PRESS){
				auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
				app->keyDown[key] = true;
				app->keyPressed(key, mods);
			}
			if(action == GLFW_RELEASE){
				auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
				app->keyDown[key] = false;
				app->keyReleased(key, mods);
			}
		};
		glfwSetKeyCallback(window, key_callback);

		auto mouse_callback = [](GLFWwindow* window, int button, int action, int mods){
			if(ImGui::GetIO().WantCaptureMouse)
				return;

			auto app = static_cast<App*>(glfwGetWindowUserPointer(window));

			if(action == GLFW_PRESS){
				app->mouseDown[button] = true;
				app->mousePressed(button);
			}
			if(action == GLFW_RELEASE){
				app->mouseDown[button] = false;
				app->mouseReleased(button);
			}
		};
		glfwSetMouseButtonCallback(window, mouse_callback);

		auto cursor_callback = [](GLFWwindow* window, double xpos, double ypos){
			if(ImGui::GetIO().WantCaptureMouse)
				return;

			auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
			app->cursorPos[0] = xpos;
			app->cursorPos[1] = ypos;

		};
		glfwSetCursorPosCallback(window, cursor_callback);
		while (!glfwWindowShouldClose(window))
		{

			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();
			process();

			// draw
			glfwMakeContextCurrent(window);
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();

			ImGui::NewFrame();
			nvgBeginFrame(vg, display_w, display_h, 2.f);
			drawScene();
			nvgEndFrame(vg);
			ImGui::EndFrame();

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwMakeContextCurrent(window);
			glfwSwapBuffers(window);
		}
	}

protected:
	virtual void process() {

	}

	virtual void drawScene() {

		{
			ImGui::Begin("Hello World!");
			ImGui::Checkbox("Demo Window", &show_demo_window);
			ImGui::End();
		}

		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		nvgBeginPath(vg);
		nvgRect(vg, 100.f, 100.f, 120.f, 30.f);
		nvgFillColor(vg, nvgRGBA(255,192,0,255));
		nvgFill(vg);
		nvgClosePath(vg);
	}

	virtual void keyPressed(int key, int mods) { }

	virtual void keyReleased(int key, int mods) { }

	virtual void mousePressed(int button) {	}

	virtual void mouseReleased(int button) { }

	static void glfwSetWindowCenter(GLFWwindow* window) {
		// Get window position and size
		int window_x, window_y;
		glfwGetWindowPos(window, &window_x, &window_y);

		int window_width, window_height;
		glfwGetWindowSize(window, &window_width, &window_height);

		// Halve the window size and use it to adjust the window position to the center of the window
		window_width *= 0.5;
		window_height *= 0.5;

		window_x += window_width;
		window_y += window_height;

		// Get the list of monitors
		int monitors_length;
		GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

		if(monitors == nullptr) {
			// Got no monitors back
			return;
		}

		// Figure out which monitor the window is in
		GLFWmonitor *owner = nullptr;
		int owner_x, owner_y, owner_width, owner_height;

		for(int i = 0; i < monitors_length; i++) {
			// Get the monitor position
			int monitor_x, monitor_y;
			glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

			// Get the monitor size from its video mode
			int monitor_width, monitor_height;
			GLFWvidmode *monitor_vidmode = (GLFWvidmode*) glfwGetVideoMode(monitors[i]);

			if(monitor_vidmode == nullptr) {
				// Video mode is required for width and height, so skip this monitor
				continue;

			} else {
				monitor_width = monitor_vidmode->width;
				monitor_height = monitor_vidmode->height;
			}

			// Set the owner to this monitor if the center of the window is within its bounding box
			if((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
				owner = monitors[i];

				owner_x = monitor_x;
				owner_y = monitor_y;

				owner_width = monitor_width;
				owner_height = monitor_height;
			}
		}

		if(owner != nullptr) {
			// Set the window position to the center of the owner monitor
			glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
		}
	}

protected:
	GLFWwindow* window;
	int display_w, display_h;
	struct NVGcontext* vg;

	std::map<int, bool> keyDown;
	std::map<int, bool> mouseDown;
	double cursorPos[2];

public:
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
