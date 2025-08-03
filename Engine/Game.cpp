#include "pch.h"
#include "Game.h"


Game::Game()
{
	persistentWorld = std::make_unique<World>();
}

World* Game::CreateWorld(std::string _name)
{ 
	worlds[_name] = std::make_unique<World>();
	return worlds[_name].get();
}

void Game::SetWorld(std::string _name)
{
	nextWorld = worlds[_name].get();
}

void Game::DontDestroyOnLoad(Object* _object)
{
	//TODO : ���� _object�� ���忡�� �����ϰ�
	//persisteneWorld�� ����ִ´�.  �������� ����������. 
}

void Game::Init()
{
	if(nowWorld)
		nowWorld->Init();
	persistentWorld->Init();

}

void Game::Update()
{
	if (nowWorld)
		nowWorld->Update();
	persistentWorld->Update();

	if (nextWorld)
		ChangeWorld();
}

void Game::Render()
{
	if (nowWorld)
		nowWorld->Render();
	persistentWorld->Render();
}

void Game::ChangeWorld()
{
	nowWorld = nextWorld;
	nextWorld = nullptr;

	nowWorld->Init();
}
