export module aeostasis.map;
export import aeostasis.map.conceptual;
export import aeostasis.map.fetch_order;
export import aeostasis.map.operation;
import aeostasis.utility.occasion;
import aeostasis.utility.value_container;

namespace aeos
{
	export struct EmptyMap
	{
		// Always invokes an error.
		template <typename T, map M1 = EmptyMap> using Get = Assert<false, T>;

		template <typename... ORDERS>
		using Applied = Apply<EmptyMap, ORDERS...>;

		template <typename K>
		using Contains = False;

		template <typename K>
		static constexpr bool contains = false;
	};
	static_assert(map<EmptyMap>);


} // Namespace.
