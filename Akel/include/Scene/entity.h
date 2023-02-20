// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2021
// Updated : 20/02/2023

#ifndef __AK_ENTITY__
#define __AK_ENTITY__

#include <Akpch.h>

#include <Maths/maths.h>
#include <Utils/nonCopyable.h>
#include <Scene/scene.h>

namespace Ak
{
	class AK_API Entity : public non_copyable
	{
		public:
			Entity(entt::entity entity, Scene* scene) : _entity(entity), _scene(scene) {}

			inline entt::entity getSubEntity() const noexcept { return _entity; }

			template <typename T, typename ... Args>
			inline T& addAttribute(Args&& ... args) { return _scene->getRegistry().emplace<T>(_entity, std::forward<Args>(args)...); }
			template <typename T, typename ... Args>
			inline T& getOrAddAttribute(Args&& ... args) { return _scene->getRegistry().get_or_emplace<T>(_entity, std::forward<Args>(args)...); }
			template <typename T>
			inline T& getAttribute() { return _scene->getRegistry().get<T>(_entity); }
			template <typename T>
			inline T* tryGetAttribute() { return _scene->getRegistry().try_get<T>(_entity); }
			template <typename T>
			inline void removeAttribute() { _scene->getRegistry().remove<T>(_entity); }
			template <typename T>
			inline void tryRemoveAttribute() { removeAttribute<T>(); }

			~Entity() = default;

		private:
			Scene* _scene = nullptr;
			entt::entity _entity = entt::null;
	};
}

#endif // __AK_ENTITY__
