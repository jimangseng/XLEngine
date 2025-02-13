#include "Game.h"

#include "XLEngine.h"
#include "Cube.h"

using namespace XL::GamePlay;
using namespace XL::Math;
using namespace XL::GameObjects;

void Game::Start()
{
	//std::vector<Cube> cubes;

	Cube cube1;
	cube1.size = 0.8f;
	cube1.color = Vector4(0.1f, 0.3f, 0.6f, 1.0f);	// �ϴ�
	cube1.Translate(0.0f, 0.0f, 4.0f);
	scene.AddObject(cube1);

	Cube cube2;
	cube2.size = 0.4f;
	cube2.color = Vector4(0.6f, 0.1f, 0.1f, 1.0f);	// ����
	cube2.Translate(0.0f, 0.0f, 10.0f);
	scene.AddObject(cube2);

	//Cube cube3;
	//cube3.size = 0.3f;
	//cube3.color = XL::Math::Vector4( 0.1f, 0.1f, 0.6f, 1.0f );	// �Ķ�
	//scene.AddObject(cube3);

	//Cube cube4;
	//cube4.size = 0.1f;
	//cube4.color = XL::Math::Vector4( 0.5f, 0.5f, 0.2f, 1.0f );	// ���
	//cube4.Translate(0.1f, 0.0f, 0.0f);
	////cube4.Yaw(30.0f);	// todo: Transform ����
	////cube4.Rotate(0.0f, 30.0f, 0.0f);
	//scene.AddObject(cube4);

}

void Game::Update()
{
	// todo: Timer
	time += 0.02f;

	float t = cos(time);

	// todo: scene ������ �������� �ʵ��� ����
	//scene.GetObject(0)->Translate(0.0f, 0.0f, 10.0f);
	scene.GetObject(0)->Translate(0.05f * t, 0.0f, 0.0f);
	//scene.GetObject(1)->SetPosition(sin(time), 0.0f, 0.0f);
	//scene.GetObject(2)->SetPosition(cos(time), sin(time), 0.0f);
	
	scene.GetObject(0)->Rotate(time, time, time);
	scene.GetObject(1)->Rotate(time, time, -time);
	//scene.GetObject(2)->Rotate(time, 0.0f, time);
	//scene.GetObject(3)->Rotate(0.0f, time, time);
}

void Game::Finish()
{
}
