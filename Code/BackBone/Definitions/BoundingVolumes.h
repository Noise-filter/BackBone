#ifndef BOUNDING_VOLUMES_H
#define BOUNDING_VOLUMES_H

#include <DirectXMath.h>

namespace BackBone
{
	namespace BoundingVolumes
	{
		struct AxisAlignedBox
		{
			DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT3 extents;	//Vector from center to a corner.
		};

		struct Sphere
		{
			DirectX::XMFLOAT3 center;
			float radius;
		};

		void ComputeBoundingAxisAlignedBox(AxisAlignedBox& out, unsigned int vertexCount, 
			DirectX::XMFLOAT3* vertexPos, unsigned int vertexStride);

		void ComputeBoundingSphere(Sphere& out, unsigned int vertexCount, 
			DirectX::XMFLOAT3* vertexPos, unsigned int vertexStride);
	}
}

#endif