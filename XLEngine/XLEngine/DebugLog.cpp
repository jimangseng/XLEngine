#include "DebugLog.h"
#include <imgui.h>

void DebugLog::Add(const std::string& msg)
{
	if (logs.size() >= maxLogs)
		logs.pop_front();
	logs.push_back(msg);
}

void DebugLog::Clear()
{
	logs.clear();
}

void DebugLog::DrawPanel()
{
	ImGui::Begin("Debug");

	if (ImGui::Button("Clear Log"))
		Clear();

	ImGui::Separator();

	ImGui::BeginChild("LogScroll", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	for (const auto& msg : logs)
		ImGui::TextUnformatted(msg.c_str());

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f); // 자동 스크롤

	ImGui::EndChild();
	ImGui::End();
}