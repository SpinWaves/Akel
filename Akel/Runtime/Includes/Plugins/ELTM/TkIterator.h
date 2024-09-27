// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_ELTM_TOKEN_ITERATOR__
#define __AK_ELTM_TOKEN_ITERATOR__

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

#endif
