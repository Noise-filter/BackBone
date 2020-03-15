#include "Game.h"

#include <vector>
#include "../BackBone/Definitions/GraphicalDefinitions.h"

using namespace std;
using namespace BackBone;
using namespace Definitions;

int Game::Update(float deltaTime)
{
	rot += .0005f;
	if (rot > 6.28f)
		rot = 0.0f;

	auto rotaxis = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	auto Rotation = DirectX::XMMatrixRotationAxis(rotaxis, rot);
	auto Translation = DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	cube1->setWorld(Translation * Rotation);

	Rotation = DirectX::XMMatrixRotationAxis(rotaxis, -rot);
	auto Scale = DirectX::XMMatrixScaling(1.3f, 1.3f, 1.3f);
	cude2->setWorld(Rotation * Scale);

	return 0;
}

int Game::Render()
{
	API::BeginFrame();

	// Render models
	API::RenderModel(cube1);
	API::RenderModel(cude2);

	API::EndFrame();
	return 0;
}

int Game::Init(HWND hWnd)
{
	if (!API::Init(hWnd, screenWidth, screenHeight, false))
	{
		return -1;
	}


	std::vector<VertexColored> vertices =
	{
		{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
	};

	std::vector<unsigned int> indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	cube1 = API::CreateModel(vertices, indices);
	cude2 = API::CreateModel(vertices, indices);

	//auto m1 = API::CreateModel("bth.obj");
	//auto m2 = API::CreateModel("bth.obj");

	return 0;
}