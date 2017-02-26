#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Definitions/GraphicalDefinitions.h"

namespace BackBone
{
	class Material
	{
	public:
		Material();
		~Material();

		bool Init(Definitions::MaterialInfo materialInfo);

		void Release();

		void Apply();

	private:
		//cbuffer
		//Textures
	};
}

#endif