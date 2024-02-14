# pragma once
# include <concepts>
# include <string_view>
namespace aeos
{
	struct Null {};

	template <typename T>
	concept null = std::derived_from<T, Null>;

	template <typename T>
	concept nonnull = !null<T>;

	template <typename T, std::string_view & TEXT>
	struct WithError: Null
	{
		inline static constexpr char const* error { TEXT.data() };
	};

	template <typename T, std::string_view & TEXT>
		requires requires {
			{ T::error } -> std::convertible_to<char const*>;
		}
	struct WithError<T, TEXT>: Null
	{
	};

}
