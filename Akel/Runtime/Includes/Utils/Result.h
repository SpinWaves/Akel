// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_UTILS_RESULT_H
#define AK_UTILS_RESULT_H

#include <Utils/PreCompiled.h>

namespace Ak
{
	template<typename T>
	class Ok
	{
		public:
			explicit constexpr Ok(T value) : m_value(std::move(value)) {}
			constexpr T&& AquireValue() { return std::move(m_value); }
			constexpr T GetValue() { return m_value; }

		private:
			T m_value;
	};

	template<typename T>
	class Err
	{
		public:
			explicit constexpr Err(T value) : m_value(std::move(value)) {}
			constexpr T&& AquireValue() { return std::move(m_value); }
			constexpr T GetValue() { return m_value; }

		private:
			T m_value;
	};

	struct DefaultError {};

	template<typename OkT, typename ErrT = DefaultError>
	class Result
	{
		using VariantT = std::variant<Ok<OkT>, Err<ErrT>>;

		public:
			constexpr Result() : m_variant(Err<ErrT>{ {} }) {}
			constexpr Result(Ok<OkT> value) : m_variant(std::move(value)) {}
			constexpr Result(Err<ErrT> value) : m_variant(std::move(value)) {}

			constexpr bool IsOk() const { return std::holds_alternative<Ok<OkT>>(m_variant); }
			constexpr bool IsError() const { return std::holds_alternative<Err<ErrT>>(m_variant); }

			constexpr OkT OkValue() const { return std::get<Ok<OkT>>(m_variant).GetValue(); }
			constexpr ErrT ErrorValue() const { return std::get<Err<ErrT>>(m_variant).GetValue(); }

			constexpr OkT&& AquireOkValue() { return std::get<Ok<OkT>>(m_variant).AquireValue(); }
			constexpr ErrT&& AquireErrorValue() { return std::get<Err<ErrT>>(m_variant).AquireValue(); }

		private:
			VariantT m_variant;
	};
}

#endif
