// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 01/02/2024

#include <Plugins/ELTM/ELTM.h>
#include <Plugins/ELTM/Token.h>

namespace Ak
{
	class TkIterator
	{
		public:
			TkIterator(class StreamStack& tokens);

			inline const Token& operator*() const noexcept { return m_current; }
			inline const Token* operator->() const noexcept { return &m_current; }
			inline TkIterator& operator++() noexcept { m_current = m_get_next_token(); return *this; }
			inline TkIterator operator++(int) noexcept
			{
				TkIterator old = *this;
				operator++();
				return old;
			}
			inline bool operator()() const noexcept { return !m_current.IsEof(); }

		private:
			Token m_current;
			func::function<Token()> m_get_next_token;
	};
}
