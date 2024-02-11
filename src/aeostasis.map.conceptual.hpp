// This file defines the concept map,
// which is used by other submodules.
# pragma once
# include "aeostasis.utility.value_container.hpp"

namespace aeos
{
	// Take advantage of template template parameters
	// to check requirements.
	namespace
	{
		template <template <typename...> typename T> struct Helper
		{
		};
	}
	template <typename T> concept map = requires {
		typename Helper<T::template Get>;
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
