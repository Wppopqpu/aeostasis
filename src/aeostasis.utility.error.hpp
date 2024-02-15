# pragma once
# include "aeostasis.string.hpp"
# include <concepts>
namespace aeos
{
	struct Null {};

	template <typename T>
	concept null = std::derived_from<T, Null>;

	template <typename T>
	concept nonnull = !null<T>;

	template <typename T, String TEXT>
	struct WithError: Null
	{
		inline static constexpr char const* error { TEXT.text };
	};

	template <typename T, String TEXT>
		requires requires {
			{ T::error } -> std::convertible_to<char const*const>;
		}
	struct WithError<T, TEXT>: Null
	{
	};

}
