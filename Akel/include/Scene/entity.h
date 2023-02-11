// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2021
// Updated : 11/02/2023

#ifndef __AK_ENTITY__
#define __AK_ENTITY__

#include <Akpch.h>

#include <Maths/maths.h>
#include <Uitls/nonCompyable.h>

namespace Ak
{
	class AK_API Entity : public non_copyable
	{
		public:
			Entity(entt::entity entity, class Scene* scene);

			inline entt::entity getSubEntity() const noexcept { return _entity; }

			template <typename T, typename ... Args>
			inline T& add_extension(Args&& ... args) { return _scene->getRegistry().emplace<T>(_entity, std::forward<Args>(args)...); }
			template <typename T, typename ... Args>
			inline T& get_or_add_extension(Args&& ... args) { return _scene.getRegistry().get_or_emplace<T>(_entity, std::forward<Args>(args)...); }
			template <typename T>
			inline T& get_extension() { return _scene.getRegistry().emplace_or_replace<T>(_entity, std::forward<Args>(args)...); }
			template <typename T>
			inline T* try_get_extension() { return _scene->GetRegistry().try_get<T>(_entity); }
			template <typename T>
			inline bool has_extension() { return _scene->GetRegistry().has<T>(_entity); }
			template <typename T>
			inline void remove_extension() { _scene->GetRegistry().remove<T>(_entity); }
			template <typename T>
			inline void try_remove_extension() { if(has_extension<T>()) remove_extension<T>(); }

			~Entity() = default;

		private:
			class Scene* _scene = nullptr;
			entt::entity _entity = entt::null;
	};
}

#endif // __AK_ENTITY__
