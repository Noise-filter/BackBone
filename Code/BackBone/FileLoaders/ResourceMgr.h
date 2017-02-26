#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <map>
#include "../Model/Model.h"

namespace BackBone
{
	enum FileFormat
	{
		FileFormat_OBJ,

		FileFormat_Count,
		FileFormat_Unknown = -1
	};

	class ResourceMgr
	{
	public:
		ResourceMgr();
		~ResourceMgr();

		void Flush();

		void SetModelDefaultPath(std::string path);
		Model* CreateModel(std::string filename);

		bool IsFileFormatSupported(std::string filename);
		bool IsFileFormatSupported(FileFormat format);

	private:
		FileFormat GetFileFormat(std::string filename);

	private:
		std::map<std::string, Model*> models;

	};
}

#endif