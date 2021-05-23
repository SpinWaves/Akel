// This file is a part of AtlasEngine
// CREATED : 23/05/2021
// UPDATED : 23/05/2021

#ifndef __DUETS_ARRAY__
#define __DUETS_ARRAY__

#include <AEpch.h>

namespace AE
{
	template <typename __first, typename __second>
	class duets_array
	{
		typedef std::pair<__first, __second> __type;
		#define __mv std::move

		public:
			duets_array(std::initializer_list<__type> duets)
			{
				assert(duets.size() <= _array.max_size());
				_array = __mv(duets);
			}
			duets_array& operator= (const duets_array&& array) noexcept	// copy duets_array from another
			{
				_array = __mv(array);
				return *this;
			}

			duets_array& set_duet(const __first&& first, const __second&& second) noexcept
			{
				_array.push_back(__type(__mv(first), __mv(second)));
				return *this;
			}

			constexpr const __second& operator[](__first duet) noexcept
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].first == duet)
						return _array[i].second;
				}
				return __second();
			}
			constexpr const __first& operator[](__second duet) noexcept
			{
				for(int i = 0; i < _array.size(); i++)
				{
					if(_array[i].second == duet)
						return _array[i].first;
				}
				return __first();
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

		private:
			std::vector<__type> _array;
	};
}

#endif // __DUETS_ARRAY__

