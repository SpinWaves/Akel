// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/05/2021
// Updated : 09/05/2022

#ifndef __AK_DUETS_ARRAY__
#define __AK_DUETS_ARRAY__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
	template <class T>
	struct default_t;

	template <typename __first, typename __second>
	class duets_array
	{
		using __type = std::pair<__first, __second>;

		public:
			using iterator = typename std::vector<__type>::const_iterator;
			using const_iterator = iterator;

			duets_array() = default;
			duets_array(std::initializer_list<__type> duets)
			{
				_array.reserve(duets.size());
				_array = std::move(duets);
			}
			duets_array& operator= (const duets_array&& array) noexcept
			{
				_array = std::move(array);
				return *this;
			}

			duets_array& set_duet(const __first&& first, const __second&& second) noexcept
			{
				_array.push_back(__type(std::move(first), std::move(second)));
				return *this;
			}

			constexpr const __second& operator[](__first duet) noexcept
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].first == duet)
						return _array[i].second;
				}
				return default_t<__second>::get();
			}
			constexpr const __first& operator[](__second duet) noexcept
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].second == duet)
						return _array[i].first;
				}
				return default_t<__first>::get();
			}
			constexpr const __type& operator[](int index) noexcept
			{
				if(index < _array.size())
						return _array[index];
				return default_t<__type>::get();
			}
			constexpr const __second& at(__first duet) noexcept
			{
				return this[duet];
			}
			constexpr const __first& at(__second duet) noexcept
			{
				return this[duet];
			}
			constexpr std::size_t size() noexcept
			{
				return _array.size();
			}
			constexpr bool empty() noexcept
			{
				return size() == 0;
			}
			constexpr std::size_t max_size() noexcept
			{
				return _array.max_size();
			}
			bool erase(__first& duet) noexcept // if object cannot erase its duet, function return false
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].first == duet)
					{
						_array.erase(_array.begin() + i);
						return true;
					}
				}
				return false;
			}
			bool erase(__second& duet) noexcept // if object cannot erase its duet, function return false
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].second == duet)
					{
						_array.erase(_array.begin() + i);
						return true;
					}
				}
				return false;
			}
			void clear() noexcept
			{
				_array.clear();
			}
			bool have(const __first& duet)
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].first == duet)
						return true;
				}
				return false;
			}
			bool have(const __second& duet)
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].second == duet)
						return true;
				}
				return false;
			}

			iterator begin()
			{
				return _array.begin();
			}
			
			iterator end()
			{
				return _array.end();
			}

			const_iterator cbegin() const
			{
				return _array.cbegin();
			}
			
			const_iterator cend() const
			{
				return _array.cend();
			}

			friend std::ostream& operator<<(std::ostream& target, const duets_array& source)
			{
				for(int i = 0; i < source.size(); i++)
					target << source[i].first << "	" << source[i].second << std::endl;
				return target;
			}

		private:
			std::vector<__type> _array;
	};
}

#endif // __AK_DUETS_ARRAY__
