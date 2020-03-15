#pragma once

#include "../BackBone/BackBone.h"

#include <memory>

class Game
{
public:
	Game(unsigned int screenWidth, unsigned int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {}

	virtual ~Game()
	{
		BackBone::API::Flush();
	}

	int Update(float deltaTime);
	int Render();
	int Init(HWND hWnd);

private:
	unsigned int screenWidth;
	unsigned int screenHeight;

	std::unique_ptr<BackBone::ModelInstance> cube1;
	std::unique_ptr<BackBone::ModelInstance> cude2;

	float rot = 0.01f;
};
