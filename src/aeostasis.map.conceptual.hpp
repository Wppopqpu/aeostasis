// This file defines the concept map,
// which is used by other submodules.
# pragma once
# include "aeostasis.utility.value_container.hpp"

namespace aeos
{
	// You can only provide Get<> if you want to create your own map;
	// every map that aeos provides also has Applied<>, Contains<>, contains<>,
	// which along with Get<> can be accessed by class name.
	namespace
	{
		template <typename T> struct Helper
		{
			// Notice that Get<> may have several parameters.
			template <typename K> using Type = typename T::template Get<K>;
		};
	}
	template <typename T> concept map = requires {
		typename Helper<T>;
	};

	template <map T, typename K>
	constexpr bool contains = requires { typename T::template Get<K>; };

	template <map T, typename K>
	using Contains = Boolean<contains<T, K>>;

	template <typename K, typename T>
	concept contained_by = map<K> && contains<T, K>;
	template <typename K, typename T>
	concept not_contained_by = ! contained_by<K, T>;

} // Namespace.
