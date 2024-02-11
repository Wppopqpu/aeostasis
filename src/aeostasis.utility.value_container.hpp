# pragma once
# include <cstddef>
# include <concepts>
namespace aeos
{
	//Base classes.

	namespace
	{
		struct ValueContainer_base {};
	
		template <typename T>
		struct SpecificValueContainer_base: ValueContainer_base {};
	}

	//The protagonist.

	template <typename T, T VALUE>
	struct ValueContainer: SpecificValueContainer_base<T>
	{
		using Type = T;
		inline static constexpr T value { VALUE };
	};


	//Some concepts.

	template <typename T>
	concept value_container = std::derived_from<T, ValueContainer_base>
		&& requires {
			typename T::Type;
			{ T::value } -> std::same_as<typename T::Type>;
		};

	template <typename T, typename VALUE_TYPE>
	concept specific_value_container = value_container<T>
		&& std::derived_from<T, SpecificValueContainer_base<VALUE_TYPE>>;


	//Alias for bool.

	template <typename T>
	concept boolean = specific_value_container<T, bool>;

	template <bool BOOL>
	using Boolean = ValueContainer<bool, BOOL>;

	using True = Boolean<true>;
	using False = Boolean<false>;


	//Alias for std::size_t.
	

	template <typename T>
	concept index = specific_value_container<T, std::size_t>;

	template<std::size_t VALUE>
	using Index = ValueContainer<std::size_t, VALUE>;
}//namespace
