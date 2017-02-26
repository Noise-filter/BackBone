#include "../Loaders.h"

#include <fstream>

using namespace std;
using namespace BackBone::Definitions;

bool ReadMaterialFile(string filename, vector<MaterialInfo>& materials)
{
	ifstream inFile(filename.c_str());
	if (!inFile)
	{
		//Failed to open material file.
		return false;
	}

	bool failed;

	string stringRead;

	MaterialInfo material;

	while (!inFile.eof())
	{
		failed = true;
		inFile >> stringRead;

		if (stringRead == "newmtl")
		{
			if (material.materialName != "")
			{
				materials.push_back(material);
			}
			getline(inFile, material.materialName, '\n');
			material.materialName.erase(material.materialName.begin());
			failed = false;
		}
		else if (stringRead == "Ka")
		{
			inFile >> material.ambientColor.x;
			inFile >> material.ambientColor.y;
			inFile >> material.ambientColor.z;
			failed = false;
		}
		else if (stringRead == "Kd")
		{
			inFile >> material.diffuseColor.x;
			inFile >> material.diffuseColor.y;
			inFile >> material.diffuseColor.z;
			failed = false;
		}
		else if (stringRead == "Ks")
		{
			inFile >> material.specularColor.x;
			inFile >> material.specularColor.y;
			inFile >> material.specularColor.z;
			failed = false;
		}
		else if (stringRead == "Tf")
		{
			inFile >> material.transmissionFilter.x;
			inFile >> material.transmissionFilter.y;
			inFile >> material.transmissionFilter.z;
			failed = false;
		}
		else if (stringRead == "Ns")
		{
			inFile >> material.specularExponent;
			failed = false;
		}
		else if (stringRead == "Ni")
		{
			inFile >> material.opticalDensity;
			failed = false;
		}
		else if (stringRead == "sharpness")
		{
			inFile >> material.reflectionSharpness;
			failed = false;
		}
		else if (stringRead == "map_Ka")
		{
			getline(inFile, material.ambientTexture, '\n');
			material.ambientTexture.erase(material.ambientTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_Kd")
		{
			getline(inFile, material.diffuseTexture, '\n');
			material.diffuseTexture.erase(material.diffuseTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_Ks")
		{
			getline(inFile, material.specularTexture, '\n');
			material.specularTexture.erase(material.specularTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_Ks")
		{
			getline(inFile, material.specularHighlightTexture, '\n');
			material.specularHighlightTexture.erase(material.specularHighlightTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_d")
		{
			getline(inFile, material.alphaTexture, '\n');
			material.alphaTexture.erase(material.alphaTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_bump" || stringRead == "bump")
		{
			getline(inFile, material.bumpTexture, '\n');
			material.bumpTexture.erase(material.bumpTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_disp")
		{
			getline(inFile, material.displacementTexture, '\n');
			material.displacementTexture.erase(material.displacementTexture.begin());
			failed = false;
		}
		else if (stringRead == "map_decal")
		{
			getline(inFile, material.stencilTexture, '\n');
			material.stencilTexture.erase(material.stencilTexture.begin());
			failed = false;
		}
		else
		{
			getline(inFile, stringRead, '\n');
			failed = false;
		}

		if (failed)
		{
			inFile.close();
			return false;
		}
	}

	materials.push_back(material);

	inFile.close();
	return true;
}

namespace BackBone
{
	namespace Loaders
	{
		bool ModelLoader::LoadOBJ(string filename, vector<Vertex>& vertices, vector<int>& indices, vector<MeshGroupInfo>& subset, vector<MaterialInfo>& materials)
		{
			ifstream inFile((modelPath + filename).c_str());
			if (!inFile)
			{
				//Failed to open file
				return false;
			}

			bool failed = false;

			string stringRead;
			int intRead[3][3];
			char charRead;

			unsigned int vIndex = 0;
			unsigned int vnIndex = 0;
			unsigned int vtIndex = 0;

			MeshGroupInfo group;
			group.startIndex = 0;
			group.numIndex = 0;

			while (!inFile.eof())
			{
				failed = true;
				inFile >> stringRead;
					 
				if (stringRead == "v")
				{
					if (vIndex >= vertices.size())
					{
						Vertex vertex;
						inFile >> vertex.pos.x;
						inFile >> vertex.pos.y;
						inFile >> vertex.pos.z;
						vertices.push_back(vertex);
					}
					else
					{
						inFile >> vertices.at(vIndex).pos.x;
						inFile >> vertices.at(vIndex).pos.y;
						inFile >> vertices.at(vIndex).pos.z;
					}

					vIndex++;
					failed = false;
				}
				else if (stringRead == "vt")
				{
					if (vtIndex >= vertices.size())
					{
						Vertex vertex;
						inFile >> vertex.tex.x;
						inFile >> vertex.tex.y;
						vertices.push_back(vertex);
					}
					else
					{
						inFile >> vertices.at(vtIndex).tex.x;
						inFile >> vertices.at(vtIndex).tex.y;
					}

					vtIndex++;
					failed = false;
				}
				else if (stringRead == "vn")
				{
					if (vnIndex >= vertices.size())
					{
						Vertex vertex;
						inFile >> vertex.normal.x;
						inFile >> vertex.normal.y;
						inFile >> vertex.normal.z;
						vertices.push_back(vertex);
					}
					else
					{
						inFile >> vertices.at(vnIndex).normal.x;
						inFile >> vertices.at(vnIndex).normal.y;
						inFile >> vertices.at(vnIndex).normal.z;
					}

					vnIndex++;
					failed = false;
				}
				else if (stringRead == "f")
				{
					inFile >> intRead[0][0];
					inFile.get(charRead);
					inFile >> intRead[0][1];
					inFile.get(charRead);
					inFile >> intRead[0][2];
					inFile.get(charRead);

					inFile >> intRead[1][0];
					inFile.get(charRead);
					inFile >> intRead[1][1];
					inFile.get(charRead);
					inFile >> intRead[1][2];

					inFile >> intRead[2][0];
					inFile.get(charRead);
					inFile >> intRead[2][1];
					inFile.get(charRead);
					inFile >> intRead[2][2];

					indices.push_back(intRead[2][0] - 1);
					indices.push_back(intRead[2][1] - 1);
					indices.push_back(intRead[2][2] - 1);

					indices.push_back(intRead[1][0] - 1);
					indices.push_back(intRead[1][1] - 1);
					indices.push_back(intRead[1][2] - 1);

					indices.push_back(intRead[0][0] - 1);
					indices.push_back(intRead[0][1] - 1);
					indices.push_back(intRead[0][2] - 1);

					failed = false;
				}
				else if (stringRead == "g")
				{
					getline(inFile, stringRead, '\n');
					if (group.startIndex >= 0)
					{
						group.numIndex = (unsigned int)indices.size() - group.startIndex;
						if (group.numIndex > 0)
							subset.push_back(group);
					}
					group.startIndex = (unsigned int)indices.size();

					failed = false;
				}
				else if (stringRead == "usemtl")
				{
					getline(inFile, group.materialName, '\n');
					group.materialName.erase(group.materialName.begin());
					failed = false;
				}
				else if (stringRead == "mtllib")
				{
					string matFilename;

					getline(inFile, matFilename, '\n');
					matFilename.erase(matFilename.begin());
					if (!ReadMaterialFile(modelPath + matFilename, materials))
					{
						inFile.close();
						return false;
					}
					failed = false;
				}
				else
				{
					getline(inFile, stringRead, '\n');
					failed = false;
				}

				//Check to see if the loop is stuck in an infinite-loop.
				if (failed)
				{
					inFile.close();
					return false;
				}
			}

			group.numIndex = (unsigned int)indices.size() - group.startIndex;
			subset.push_back(group);

			//Set all pos, tex and normals
			for (unsigned int i = vIndex, j = 0; i < vertices.size(); i++, j += 3)
			{
				vertices.at(i).pos = vertices.at(indices.at(j)).pos;
			}

			for (unsigned int i = vtIndex, j = 1; i < vertices.size(); i++, j += 3)
			{
				vertices.at(i).tex = vertices.at(indices.at(j)).tex;
			}

			for (unsigned int i = vnIndex, j = 2; i < vertices.size(); i++, j += 3)
			{
				vertices.at(i).normal = vertices.at(indices.at(j)).normal;
			}

			inFile.close();
			return true;
		}
	}
}