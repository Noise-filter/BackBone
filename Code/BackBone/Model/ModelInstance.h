#pragma once

#include "Model.h"

namespace BackBone {
	class ModelInstance
	{
	public:
		ModelInstance::ModelInstance(std::shared_ptr<ModelColored> model) : model(std::move(model))
		{
		}

		virtual ~ModelInstance() = default;

		void Render(ID3D11DeviceContext* const deviceContext) { model->Render(deviceContext); }

		DirectX::XMMATRIX getWorld() const { return world; }
		void setWorld(const DirectX::XMMATRIX& world) { this->world = world; }

	private:
		DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
		std::shared_ptr<ModelColored> model;

	};

}