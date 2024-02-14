// This file defines the basic concepts of map,
// which is used by other submodules.
# pragma once
# include "aeostasis.utility.value_container.hpp"
# include "aeostasis.utility.error.hpp"

namespace aeos
{
	// Take advantage of template template parameters
	// to check requirements.
	namespace
	{
		template <template <typename> typename T>
		struct Helper1
		{
		};
	}
	template <typename T> concept map = requires {
		typename Helper1<T::template At>;
	};

	// AppliedMap defines some interfaces help provide
	// the operations with lazy loading,
	// e.g.
	// fetch<At<int>>,
	// which can be applied to a map BEFORE the value of key int is set.
	// You can only use this feature via interface Apply;
	// defining an infinite map yourself will not work,
	// however, there is another way to do the same thing.
	// (See operation ApplyWith.)
	namespace
	{
		template <template <typename, map> typename T>
		struct Helper2
		{
		};
	}
	// applied_map implies map.
	template <typename T>
	concept applied_map = requires {
		typename Helper2<T::template Get>;
	} && map<T>;




	template <map T, typename K>
	constexpr bool contains = requires { typename T::template At<K>; };

	template <map T, typename K>
	using Contains = Boolean<contains<T, K>>;

	template <typename K, typename T>
	concept contained_by = map<K> && contains<T, K>;
	template <typename K, typename T>
	concept not_contained_by = ! contained_by<K, T>;

	
	// Null map (contains an error).
	// Derived fron this class and defines tyop error.
	struct NullMap: Null
	{
		template <typename K>
		using At = Null;

		template <typename K, map M2>
		using Get = Null;

		template <typename... ORDERS>
		using Applied = NullMap;

		template <typename K>
		inline static constexpr bool contains = false;

		template <typename K>
		using Contains = False;
	};
	static_assert(null<NullMap>);
	static_assert(applied_map<NullMap>);



} // Namespace.
