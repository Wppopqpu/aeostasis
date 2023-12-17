export module aeostasis.utility.occasion;

namespace aeos
{
	template <bool BOOL, typename A, typename B>
	struct If_impl
	{
		using Type = A;
	};
	
	template <typename A, typename B>
	struct If_impl<false, A, B>
	{
		using Type = B;
	};

	export
	template <bool BOOL, typename A, typename B>
	using If = typename If_impl<BOOL, A, B>::Type;

	// You can use Assert<> to invoke an error.
	// The second parameter is used to enable using this struct in a using
	// declaration. For example:
	//
	// template <typename T> using Get = Assert<my_concept<T>, T>;
	//
	// It is also used to prevent instantiation
	template <bool BOOL, typename T>
	struct Assert_impl {};
	template <typename T>
	struct Assert_impl<true, T> { using Type = T; };
	export template <bool BOOL = false, typename T = void>
	using Assert = typename Assert_impl<BOOL, T>::Type;
} // namespace
