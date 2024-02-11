# pragma once
# include "aeostasis.map.conceptual.hpp"
# include "aeostasis.map.fetch_order.hpp"
# include "aeostasis.map.operation.hpp"
# include "aeostasis.utility.occasion.hpp"
# include "aeostasis.utility.value_container.hpp"

namespace aeos
{
	struct EmptyMap
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
