#pragma once

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "NGS/ngl/NGL.h"

NGS_BEGIN

class ImageGUI {
public:

public:
	ImageGUI(std::string_view glsl_version, ngl::objects::Window& window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		bool success;
		success = ImGui_ImplGlfw_InitForOpenGL(window.GetContext(), true);
		NGS_ASSERT(success);
		success = ImGui_ImplOpenGL3_Init(glsl_version.data());
		NGS_ASSERT(success);
	}
	~ImageGUI() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void Render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UpdateUI();

	void NewFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
private:

private:
};

NGS_END