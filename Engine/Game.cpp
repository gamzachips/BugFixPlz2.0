#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Renderer.h"

Game::Game()
{
	persistentWorld = std::make_unique<World>();
	timeManager = std::make_unique<TimeManager>();
	inputManager = std::make_unique<InputManager>();
	resourceManager = std::make_unique<ResourceManager>();
	renderer = std::make_unique<Renderer>();

	timeManager->Init();
	resourceManager->Init();
	renderer->Init();
}

Game::~Game()
{
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
	if (nowWorld)
		nowWorld->Init();
	persistentWorld->Init();
}

void Game::Update()
{
	timeManager->Update();
	inputManager->Update();

	if (nowWorld)
		nowWorld->Update();
	persistentWorld->Update();

	if (nextWorld)
		ChangeWorld();
}

void Game::Render()
{
	renderer->GetRenderTarget().Get()->BeginDraw();
	if (nowWorld)
		nowWorld->Render();
	persistentWorld->Render();
	renderer->GetRenderTarget().Get()->EndDraw();

}

void Game::ChangeWorld()
{
	nowWorld = nextWorld;
	nextWorld = nullptr;

	nowWorld->Init();
}
