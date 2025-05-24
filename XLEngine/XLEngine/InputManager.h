#pragma once

/*
* IMGUI로부터 인풋 정보를 받아 처리하는 클래스
* 25. 5. 23. jimangseng
*/
class InputManager
{
public:
	static void Update();

public:
	static bool sceneViewportFocused;
	static bool sceneViewportHovered;
};