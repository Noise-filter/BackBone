#include "ResourceMgr.h"

#include <vector>
#include <memory>

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
	models.clear();
}

void ResourceMgr::SetModelDefaultPath(std::string path)
{
	ModelLoader::modelPath = path;
}

std::shared_ptr<ModelColored> ResourceMgr::CreateModel(std::string filename)
{
	std::shared_ptr<ModelColored> model = models[filename];

	if (model == nullptr)
	{
		//Load model
		FileFormat format = GetFileFormat(filename);
		if (format == FileFormat::Unknown)
		{
			return nullptr;
		}
		else
		{
			std::vector<Vertex> vertices;
			std::vector<int> indices;
			std::vector<MaterialInfo> materials;
			std::vector<MeshGroupInfo> subsets;
			
			switch (format)
			{
			case FileFormat::OBJ:
				if (!ModelLoader::LoadOBJ(filename, vertices, indices, subsets, materials))
				{
					return nullptr;
				}

				//model = std::make_shared<ModelColored>(vertices, indices);
				//if (!model->Init(vertices, indices, subsets, materials))
				{
					return nullptr;
				}

				models[filename] = model;
				break;

			default:
				return nullptr;
				break;
			}
		}
	}

	return model;
}

bool ResourceMgr::IsFileFormatSupported(std::string filename)
{
	FileFormat format = GetFileFormat(filename);
	return format != FileFormat::Unknown;
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

	return FileFormat::OBJ;
}