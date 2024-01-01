export module aeostasis.map.fetch_order;
import <concepts>;
import aeostasis.map.conceptual;

namespace aeos
{
	export struct FetchOrder_base {};


	// Take advantage of template template parameter,
	// to offer requirement.

	template <template <typename> typename T> struct Checker {};

	export template <typename T>
	concept fetch_order = std::derived_from<T, FetchOrder_base>
		&& requires {
			typename Checker<T::template Get>;
	};


	// A set of fetch orders.
	

	export template <typename T>
	struct Fetch
	{
		template <map M, map M1 = M> using Get = T;
	};
	export template <fetch_order T>
	struct Fetch<T>
	{
		template <map M, map M1 = M> using Get = typename T::template Get<M>;
	};
	export template <typename T>
	struct Fetch<Fetch<T>>
	{
		template <map M, map M1 = M> using Get = typename Fetch<T>::template Get<M1>;
	};
	export template <typename T, map M, map M1 = M>
	using From = typename Fetch<T>::template Get<M, M1>;

	export template <typename T>
	struct AsItself: FetchOrder_base
	{
		template <map M> using Get = T;
	};

	export template <typename KEY>
	struct At: FetchOrder_base
	{
		template <map M> using Get = typename M::template Get<KEY>;
	};

	export template <template <typename...> typename TEMPLATE
		, typename... ARGS>
	struct AsTemplate: FetchOrder_base
	{
		template <map M> using Get = From
			<TEMPLATE<From<ARGS, M>...>, M>;
	};
	
} // Namespace.
