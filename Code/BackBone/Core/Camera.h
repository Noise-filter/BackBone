#ifndef CAMERA_H
#define CAMERA_H

#include "Directx11Includes.h"

namespace BackBone
{
	class Camera
	{
	public:
		Camera(float fov, float aspectRatio, float nearZ, float farZ)
		{
			view = DirectX::XMMatrixLookAtLH(camPosition, camTarget, camUp);
			projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
		}

		~Camera() = default;

		DirectX::XMMATRIX getView() { return view; }
		DirectX::XMMATRIX getProjection() { return projection; }

	private:
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;

		DirectX::XMVECTOR camPosition = DirectX::XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
		DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	};
}

#endif