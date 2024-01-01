// This file enables you to modify maps.
// Generally, you write code like this:
//
// using Neomap = EmptyMap::Apply<SetAt<Key, Value>>;
export module aeostasis.map.operation;
import aeostasis.map.conceptual;
import aeostasis.map.fetch_order;
import aeostasis.utility.occasion;
import <concepts>;

namespace aeos
{
	// A set of operations.(Tags.)
	
	// AddAt<> requires that the key does NOT exist;
	// ModifyAt<> requires that the key does exist.
	export template <typename KEY, typename VALUE> struct SetAt {};
	export template <typename KEY, typename VALUE> struct AddAt {};
	export template <typename KEY, typename VALUE> struct ModifyAt {};

	// RemoveAt<> requires that the key does exist.
	export template <typename KEY> struct EraseAt {};
	export template <typename KEY> struct RemoveAt {};


	// The implementation.

	export struct AppliedMap_base {};
	export template <typename T>
	concept applied_map = std::derived_from<T, AppliedMap_base> || map<T>;
	
	export template <applied_map M, typename FIRST, typename... ORDERS>
	struct Apply: Apply<Apply<M, FIRST>, ORDERS...> {};

	template <map T>
	struct Wrapper: T, AppliedMap_base 
	{
		template <typename K, map M1>
		using Get = typename T::template Get<K>;
	};

	export template <map M,typename FIRST, typename...ORDERS> 
	struct Apply<M, FIRST, ORDERS...>: Apply<Apply<Wrapper<M, FIRST>, ORDERS...> {};

	export template <map M, typename KEY, typename VALUE>
	struct Apply<M, SetAt<KEY, VALUE>>: AppliedMap_base
	{
	private:
		using This = Apply<M, SetAt<KEY, VALUE>>;

		template <typename K, map M1>
		struct Get_impl
		{
			using Type = typename M::template Get<K, M1>;
		};
		template <typename K, map M1>
			requires std::same_as<From<K, M, M1>, From<KEY, M, M1>>
		struct Get_impl<K, M1>
		{
			using Type = From<VALUE, M, M1>;
		};

	public:
		
		template <typename K, map M1 = M>
		using Get = Get_impl<K, M1>::Type;

		template <typename... ORDERS>
		using Applied = aeos::Apply<This, ORDERS...>;

		template <typename K>
		static constexpr bool contains = aeos::contains<This, K>;

		template <typename K>
		using Contains = aeos::Contains<This, K>;
	};

	export template <map M, typename KEY, typename VALUE>
	struct Apply<M, AddAt<KEY, VALUE>>: Apply<M, SetAt<KEY, VALUE>>
	{
		Assert<!aeos::contains<M, KEY>>;
	};

	export template <map M, typename KEY, typename VALUE>
	struct Apply<M, ModifyAt<KEY, VALUE>>: Apply<M, SetAt<KEY, VALUE>>
	{
		Assert<aeos::contains<M, KEY>>;
	};

	export template <map M, typename KEY>
	struct Apply<M, EraseAt<KEY>>: AppliedMapBase
	{
	private:

		using This = Apply<M, EraseAt<KEY>>;

		template <typename K, map M1>
		struct Get_impl {};

		template <typename K, map M1>
			requires (!std::same_as<From<K, M, M1>, From<KEY, M, M1>>)
		struct Get_impl<K, M1>
		{
			using Type = typename M::template Get<K, M1>;
		};

	public:

		template <typename K, map M1 = M>
		using Get = typename Get_impl<K, M1>::Type;

		template <typename... ORDERS>
		using Applied = Apply<This, ORDERS...>;

		template <typename K>
		static constexpr bool contains = aeos::contains<This, K>;

		template <typename K>
		using Contains = aeos::Contains<This, K>;
	};

	export template<map M, typename KEY>
	struct Apply<M, RemoveAt<KEY>>: Apply<M, EraseAt<KEY>>
	{
		Assert<aeos::contains<M, KEY>>;
	};
	
} // Namespace.
