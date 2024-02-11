# pragma once
# include <concepts>
# include "aeostasis.map.conceptual.hpp"

namespace aeos
{
	struct FetchOrder_base {};


	// Take advantage of template template parameter,
	// to offer requirement.

	namespace
	{
		template <template <typename> typename T> struct Checker {};
	}

	template <typename T>
	concept fetch_order = std::derived_from<T, FetchOrder_base>
		&& requires {
			typename Checker<T::template Get>;
	};


	// A set of fetch orders.
	

	template <typename T>
	struct Fetch
	{
		template <map M, map M1 = M> using Get = T;
	};
	template <fetch_order T>
	struct Fetch<T>
	{
		template <map M, map M1 = M> using Get = typename T::template Get<M>;
	};
	template <typename T>
	struct Fetch<Fetch<T>>
	{
		template <map M, map M1 = M> using Get = typename Fetch<T>::template Get<M1>;
	};
	template <typename T, map M, map M1 = M>
	using From = typename Fetch<T>::template Get<M, M1>;

	template <typename T>
	struct AsItself: FetchOrder_base
	{
		template <map M> using Get = T;
	};

	template <typename KEY>
	struct At: FetchOrder_base
	{
		template <map M> using Get = typename M::template Get<KEY>;
	};

	template <template <typename...> typename TEMPLATE
		, typename... ARGS>
	struct AsTemplate: FetchOrder_base
	{
		template <map M> using Get = From
			<TEMPLATE<From<ARGS, M>...>, M>;
	};
	
} // Namespace.
