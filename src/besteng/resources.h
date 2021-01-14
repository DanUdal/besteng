#pragma once
#include "core.h"

namespace besteng
{
	struct Cache
	{
	private:
		std::weak_ptr<Core> core;
		std::vector<std::shared_ptr<Resource>> resources;
	public:
		template <typename T>
		std::shared_ptr<T> load(std::string path)
		{

		}
		template <typename T>
		std::shared_ptr<T> create()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			resources.push_back(rtn);

			return rtn;
		}
	};

	struct Resource
	{
	private:
		std::string path;
		std::weak_ptr<Cache> cache;
		virtual void onLoad();
		virtual void onCreate();
	};
}