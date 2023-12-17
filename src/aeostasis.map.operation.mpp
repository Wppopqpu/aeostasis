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
	
	export template <map M, typename FIRST, typename... ORDERS>
	struct Apply: Apply<Apply<M, FIRST>, ORDERS...> {};

	export template <map M, typename KEY, typename VALUE>
	struct Apply<M, SetAt<KEY, VALUE>>
	{
	private:
		using This = Apply<M, SetAt<KEY, VALUE>>;

		template <bool BOOL, typename K>
		struct Get_impl
		{
			using Type = typename M::template Get<K>;
		};
		template <typename K>
		struct Get_impl<true, K>
		{
			using Type = FetchFrom<VALUE, M>;
		};

	public:
		
		template <typename K>
		using Get =
			typename Get_impl<std::same_as<FetchFrom<K, M>, FetchFrom<KEY, M>>
				, K>::Type;

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
	struct Apply<M, EraseAt<KEY>>
	{
	private:

		using This = Apply<M, EraseAt<KEY>>;

		template <bool BOOL, typename K>
		struct Get_impl {};

		template <typename K>
		struct Get_impl<true, K>
		{
			using Type = typename M::template Get<K>;
		};

	public:

		template <typename K>
		using Get = typename Get_impl
			< !std::same_as<FetchFrom<K, M>, FetchFrom<KEY, M>>
			, K>::Type;

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
