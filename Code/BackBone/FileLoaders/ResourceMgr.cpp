#include "ResourceMgr.h"

#include <vector>

#include "Loaders.h"
#include "../Definitions/GraphicalDefinitions.h"

using namespace std;
using namespace BackBone;
using namespace Definitions;
using namespace Loaders;

std::string ModelLoader::modelPath;

ResourceMgr::ResourceMgr()
{
	ModelLoader::modelPath = "../Content/Models/";
}

ResourceMgr::~ResourceMgr()
{
}

void ResourceMgr::Flush()
{
	for (map<string, Model*>::iterator i = models.begin(); i != models.end(); i++)
	{
		if (i->second)
		{
			i->second->Release();
			SAFE_DELETE(i->second);
		}
	}
}

void ResourceMgr::SetModelDefaultPath(std::string path)
{
	ModelLoader::modelPath = path;
}

Model* ResourceMgr::CreateModel(std::string filename)
{
	Model* model = models[filename];

	if (model == NULL)
	{
		//Load model
		FileFormat format = GetFileFormat(filename);
		if (!IsFileFormatSupported(format))
		{
			return NULL;
		}
		else
		{
			std::vector<Vertex> vertices;
			std::vector<int> indices;
			std::vector<MaterialInfo> materials;
			std::vector<MeshGroupInfo> subsets;
			
			switch (format)
			{
			case FileFormat_OBJ:
				if (!ModelLoader::LoadOBJ(filename, vertices, indices, subsets, materials))
				{
					return NULL;
				}

				model = new Model();
				if (!model->Init(vertices, indices, subsets, materials))
				{
					SAFE_DELETE(model);
					return NULL;
				}

				models[filename] = model;
				break;

			default:
				return NULL;
				break;
			}
		}
	}

	return model;
}

bool ResourceMgr::IsFileFormatSupported(std::string filename)
{
	FileFormat format = GetFileFormat(filename);
	return IsFileFormatSupported(format);
}

bool ResourceMgr::IsFileFormatSupported(FileFormat format)
{
	if (format >= 0 && format < FileFormat_Count)
		return true;
	return false;
}

FileFormat ResourceMgr::GetFileFormat(std::string filename)
{
	//Split the string on '.'.
	//Then find the last part of the string.
	//That should be for example "obj" or "png" etc.
	//If there is no '.' use the entire string.

	//Then check if we support that fileformat.

	//Lastly return that fileformat.

	//If we don't support the fileformat return Unknown.

	return FileFormat_OBJ;
}