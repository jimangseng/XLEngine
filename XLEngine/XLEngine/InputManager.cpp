#include "InputManager.h"
#include <iostream>
#include "DebugLog.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

bool InputManager::sceneViewportHovered = false;
bool InputManager::sceneViewportFocused = false;

void InputManager::Update()
{
	//ImGuiIO& io{ ImGui::GetIO() };

	// RButton Down
	if (ImGui::IsMouseDown(1))
	{
		if (sceneViewportHovered)
		{
			static ImVec2 prevMousePos = ImGui::GetMousePos();
			if (ImGui::GetMousePos().x != prevMousePos.x || ImGui::GetMousePos().y != prevMousePos.y)
			{
				//DebugLog::Add("Mouse Pos: " + std::to_string(ImGui::GetMousePos().x) + ", " + std::to_string(ImGui::GetMousePos().y));
				//DebugLog::Add("Delta: " + std::to_string(ImGui::GetMouseDragDelta().x) + ", " + std::to_string(ImGui::GetMouseDragDelta().y));
				prevMousePos = ImGui::GetMousePos();
			}

			// W Key Down
			if (ImGui::IsKeyDown(ImGuiKey_W)) {
				//DebugLog::Add("W Key Down \n");
			}

			// S Key Down
			if (ImGui::IsKeyDown(ImGuiKey_S)) {
				//DebugLog::Add("S Key Down \n");
			}

			// A Key Down
			if (ImGui::IsKeyDown(ImGuiKey_A)) {
				//DebugLog::Add("A Key Down \n");
			}

			// D Key Down
			if (ImGui::IsKeyDown(ImGuiKey_D)) {
				//DebugLog::Add("D Key Down \n");
			}
		}
	}
}
