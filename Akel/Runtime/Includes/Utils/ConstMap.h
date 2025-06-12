// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_UTILS_CONST_MAP_H
#define AK_UTILS_CONST_MAP_H

#include <Utils/PreCompiled.h>

namespace Ak
{
	template<typename Key, typename Value>
	class ConstMap
	{
		public:
			using ValueType = std::pair<Key, Value>;
			using ContainerType = std::vector<ValueType>;

			using iterator = typename ContainerType::const_iterator;
			using const_iterator = iterator;

		public:
			ConstMap(std::initializer_list<ValueType> init) : m_container(init)
			{
				std::sort(m_container.begin(), m_container.end());
			}

			ConstMap(ContainerType container) : m_container(std::move(container))
			{
				std::sort(m_container.begin(), m_container.end());
			}

			inline const_iterator begin() const { return m_container.begin(); }
			inline const_iterator end() const { return m_container.end(); }

			template<typename K>
			inline const_iterator Find(const K& key) const
			{
				const_iterator it = std::lower_bound(begin(), end(), key,
					[](const ValueType& p, const K& key)
					{
						return p.first < key;
					}
				);
				return it != end() && it->first == key ? it : end();
			}

			template<typename K>
			inline bool Has(const K& key) const
			{
				return Find(key) != end();
			}

			inline std::size_t Size() const { return m_container.size(); }

			~ConstMap() = default;

		private:
			ContainerType m_container;
	};
}

#endif
