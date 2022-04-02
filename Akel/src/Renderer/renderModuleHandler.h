// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/03/2022
// Updated : 02/04/2022

#ifndef __AK_VK_RENDER_MODULE_HANDLER__
#define __AK_VK_RENDER_MODULE_HANDLER__

#include <Akpch.h>
#include <Core/core.h>
#include <Utils/nonCopyable.h>

#include "renderModule.h"

namespace Ak
{
	class RenderModuleHandler : public non_copyable
	{
		public:
			inline void add_module(std::shared_ptr<RenderModule> module)
			{
				const char* name = module->getName();
				// it is an iterator
				auto it = std::find_if(_modules.begin(), _modules.end(), [&name](auto mod){ return std::strcmp(mod->getName(), name) == 0; })
				if(it != _modules.end())
				{
					Core::log::report(FATAL_ERROR, "Render Module Handler : cannot add a render module named %s (a module with that name already exists)", name);
					return;
				}
				_modules.push_back(std::move(module));
			}

			inline void remove_module(const char* name)
			{
				auto it = std::find_if(_modules.begin(), _modules.end(), [&name](auto mod){ return std::strcmp(mod->getName(), name) == 0; })
				if(it == _modules.end())
				{
					Core::log::report(ERROR, "Render Module Handler : cannot remove a render module named %s (not found)", name);
					return;
				}
				_modules.erase(it);
			}

			inline void clear() { _modules.clear(); }

		private:
			inline void renderAll(const class CommandBuffer& commandBuffer)
			{
				for(auto& mod : _modules)
				{
					if(mod->isEnabled())
						mod->render(commandBuffer);
				}
			}

			std::vector<std::shared_ptr<RenderModule>> _modules;
	};
}

#endif // __AK_VK_RENDER_MODULE_HANDLER__
