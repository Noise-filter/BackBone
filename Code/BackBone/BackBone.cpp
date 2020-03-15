#include "BackBone.h"
#include "Core\Core.h"

using namespace BackBone;
using namespace Definitions;

bool API::Init(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen)
{
	DirectX::XMUINT2 resolution(width, height);
	if (!Core::Init::CreateDeviceAndSwapChain(hwnd, resolution, fullscreen))
	{
		return false;
	}

	if (!Core::Init::CreateDepthStencil(resolution))
	{
		return false;
	}

	if (!Core::Init::CreateBackBuffer())
	{
		return false;
	}

	Core::Init::CreateViewPort(DirectX::XMUINT2(0, 0), resolution);
	Core::Init::CreateWireFrameRasterizer();

	Core::deviceContext->RSSetViewports(1, &Core::viewPort);
	Core::deviceContext->OMSetRenderTargets(1, &Core::backBufferRTV, Core::depthStencil);

	Core::resourceMgr.SetModelDefaultPath("../Content/Models/");

	Core::Init::InitPipeline();

	return true;
}

void API::Flush()
{
	Core::Flush();
}

void API::BeginFrame()
{
	Core::deviceContext->ClearRenderTargetView(Core::backBufferRTV, Core::getClearColor().data());
	Core::deviceContext->ClearDepthStencilView(Core::depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void API::EndFrame()
{
	Core::swapChain->Present(0, 0);
}

void API::RenderModel(std::unique_ptr<ModelInstance>& model)
{
	Core::perObjectConstantBuffer.WVP = XMMatrixTranspose(model->getWorld() * Core::camera.getView() * Core::camera.getProjection());
	Core::deviceContext->UpdateSubresource(Core::cbPerObjectBuffer, 0, NULL, &Core::perObjectConstantBuffer, 0, 0);
	Core::deviceContext->VSSetConstantBuffers(0, 1, &Core::cbPerObjectBuffer);
	model->Render(Core::deviceContext);
}

void API::RenderScene()
{

}

std::unique_ptr<ModelInstance> API::CreateModel(std::string filename)
{
	//auto model = std::make_unique<ModelInstance>();
	//model->model = std::dynamic_pointer_cast<BackBone::Definitions::ModelInstance::Model>(Core::resourceMgr.CreateModel(filename));
	return nullptr;
}

std::unique_ptr<ModelInstance> API::CreateModel(std::vector<Definitions::VertexColored> vertices)
{
	auto model = std::make_shared<ModelColored>(vertices);
	return std::make_unique<ModelInstance>(model);

	//auto model = std::make_unique<ModelInstance>();
	//model->model = std::dynamic_pointer_cast<BackBone::Definitions::ModelInstance::Model>(Core::resourceMgr.CreateModel(filename));
	//return model;
}

std::unique_ptr<ModelInstance> API::CreateModel(std::vector<Definitions::VertexColored> vertices, std::vector<unsigned int> indices)
{
	auto model = std::make_shared<ModelColored>(vertices, indices);
	return std::make_unique<ModelInstance>(model);

	//auto model = std::make_unique<ModelInstance>();
	//model->model = std::dynamic_pointer_cast<BackBone::Definitions::ModelInstance::Model>(Core::resourceMgr.CreateModel(filename));
	//return model;
}

void API::CreateTexture(std::string filename)
{

}

void API::DeleteTexture()
{

}

void API::SetOptions(bool wireFrame)
{
	Core::deviceContext->RSSetState(wireFrame == true ? Core::wireFrame : nullptr);
}