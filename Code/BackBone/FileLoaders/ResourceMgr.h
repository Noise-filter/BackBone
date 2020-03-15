#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <map>
#include <memory>
#include "../Model/Model.h"

namespace BackBone
{
	enum class FileFormat
	{
		OBJ,

		Count,
		Unknown = -1
	};

	class ResourceMgr
	{
	public:
		ResourceMgr();
		~ResourceMgr();

		void Flush();

		void SetModelDefaultPath(std::string path);
		std::shared_ptr<ModelColored> CreateModel(std::string filename);

		bool IsFileFormatSupported(std::string filename);

	private:
		FileFormat GetFileFormat(std::string filename);

	private:
		std::map<std::string, std::shared_ptr<ModelColored>> models;

	};
}

#endif