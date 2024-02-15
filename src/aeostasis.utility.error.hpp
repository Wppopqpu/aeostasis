# pragma once
# include <concepts>
namespace aeos
{
	struct Null {};

	template <typename T>
	concept null = std::derived_from<T, Null>;

	template <typename T>
	concept nonnull = !null<T>;

	template <typename T, char const TEXT[]>
	struct WithError: Null
	{
		inline static constexpr char const* error { TEXT };
	};

	template <typename T, char const TEXT[]>
		requires requires {
			{ T::error } -> std::convertible_to<char const*const>;
		}
	struct WithError<T, TEXT>: Null
	{
	};

}
