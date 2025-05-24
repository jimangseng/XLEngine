#pragma once
#include <deque>
#include <string>
/*
* IMGUI ����� �α� â
* 25. 5. 23. jimangseng
*/
class DebugLog
{
public:
	static void Add(const std::string& msg);
	static void Clear();
	static void DrawPanel(); // ImGui â ���

private:
	static inline std::deque<std::string> logs;
	static inline const size_t maxLogs = 1000;
};