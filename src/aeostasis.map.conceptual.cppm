// This file defines the concept map,
// which is used by other submodules.
export module aeostasis.map.conceptual;
export import aeostasis.utility.value_container;

namespace aeos
{
	// You can only provide Get<> if you want to create your own map;
	// every map that aeos provides also has Applied<>, Contains<>, contains<>,
	// which along with Get<> can be accessed by class name.
	template <typename T> struct Helper
	{
		// Notice that Get<> may have several parameters.
		template <typename K> using Type = typename T::template Get<K>;
	};
	export template <typename T> concept map = requires {
		typename Helper<T>;
	};

	export template <map T, typename K>
	constexpr bool contains = requires { typename T::template Get<K>; };

	export template <map T, typename K>
	using Contains = Boolean<contains<T, K>>;

	export template <typename K, typename T>
	concept contained_by = map<K> && contains<T, K>;
	export template <typename K, typename T>
	concept not_contained_by = ! contained_by<K, T>;

} // Namespace.
