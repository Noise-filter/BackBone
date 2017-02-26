#include "BoundingVolumes.h"

using namespace DirectX;
using namespace BackBone::BoundingVolumes;

void BackBone::BoundingVolumes::ComputeBoundingAxisAlignedBox(AxisAlignedBox& out, unsigned int vertexCount,
	XMFLOAT3* vertexPos, unsigned int vertexStride)
{
	XMFLOAT3 minF3(INFINITY, INFINITY, INFINITY);
	XMFLOAT3 maxF3(-INFINITY, -INFINITY, -INFINITY);

	XMVECTOR min = XMLoadFloat3(&minF3);
	XMVECTOR max = XMLoadFloat3(&maxF3);

	float* p = &vertexPos->x;
	XMFLOAT3* asd = vertexPos;

	for (unsigned int i = 0; i < vertexCount; i++, p += 8)
	{
		asd = (XMFLOAT3*)p;
		XMVECTOR p = XMLoadFloat3(asd);
		min = XMVectorMin(min, p);
		max = XMVectorMax(max, p);
	}

	XMStoreFloat3(&out.center, 0.5f*(min + max));
	XMStoreFloat3(&out.extents, 0.5f*(max - min));
}

void BackBone::BoundingVolumes::ComputeBoundingSphere(Sphere& out, unsigned int vertexCount,
	XMFLOAT3* vertexPos, unsigned int vertexStride)
{
	AxisAlignedBox box;
	ComputeBoundingAxisAlignedBox(box, vertexCount, vertexPos, vertexStride);

	out.center = box.center;
	XMVECTOR v = XMLoadFloat3(&box.extents);
	v = XMVector3Length(v);
	XMStoreFloat(&out.radius, v);
}