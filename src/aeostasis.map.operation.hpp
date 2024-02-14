// This file enables you to modify maps.
// Generally, you write code like this:
//
// using Neomap = EmptyMap::Apply<SetAt<Key, Value>>;
# pragma once
# include "aeostasis.map.conceptual.hpp"
# include "aeostasis.map.fetch_order.hpp"
# include "aeostasis.utility.occasion.hpp"
# include "aeostasis.utility.error.hpp"
# include "aeostasis.utility.oo.hpp"
# include <concepts>
# include <string>

namespace aeos
{
	// A set of operations.(Tags.)
	
	// AddAt<> requires that the key does NOT exist;
	// ModifyAt<> requires that the key does exist.
	template <typename KEY, typename VALUE> struct SetAt {};
	template <typename KEY, typename VALUE> struct AddAt {};
	template <typename KEY, typename VALUE> struct ModifyAt {};

	// RemoveAt<> requires that the key does exist.
	template <typename KEY> struct EraseAt {};
	template <typename KEY> struct RemoveAt {};
	
	// Apply with an particular key.
	template <typename KEY> struct ApplyWith {};


	// The implementation.
	


	// Turn non-applied maps into applied ones.
	// (See the wrapper defined below.)
	template <map M, typename... ORDERS>
	struct Apply: Apply<Apply<M>, ORDERS...>
	{
	};


	// Wrapper to provide interfaces for lazy loading.
	template <map M>
	struct Apply<M>: M
	{
		template <typename K,typename M2>
		using Get = typename M::template At<K>;
	};


	// Wrapper to provide more interfaces for convenience.
	namespace
	{
		template <map M>
		struct Complement: M
		{
			template <typename ... ORDERS>
			using Applied = aeos::Apply<M, ORDERS...>;
			
			template <typename K>
			inline static constexpr bool contains = aeos::contains<M, K>;

			template <typename K>
			using Contains = aeos::Contains<M, K>;
		};
	}

	// Apply the operation one by one.
	template <applied_map M, typename FIRST, typename... ORDERS>
	struct Apply<M, FIRST, ORDERS...>
		: Complement<Apply<Apply<M, FIRST>, ORDERS...>>
	{
	};

	template <applied_map M, typename KEY, typename VALUE>
	struct Apply<M, SetAt<KEY, VALUE>>
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
	};

	template <applied_map M, typename KEY, typename VALUE>
	struct Apply<M, AddAt<KEY, VALUE>>
		: If
			< !contains<M, KEY>
			, Apply<M, SetAt<KEY, VALUE>>
			, CommonChild
				< NullMap
				, WithError
					< Apply<M, AddAt<KEY, VALUE>>
					, "aeos::AddAt: Key already exists."
					>
				>
			>
	{
	};

	template <applied_map M, typename KEY, typename VALUE>
	struct Apply<M, ModifyAt<KEY, VALUE>>
		: If
			< contains<M, KEY>
			, Apply<M, SetAt<KEY, VALUE>>
			, CommonChild
				< NullMap
				, WithError
					<Apply<M, ModifyAt<KEY, VALUE>>
					, "aeos::ModifyAt: Key does NOT exists."
					>
				>
			>
	{
	};

	template <map M, typename KEY>
	struct Apply<M, EraseAt<KEY>>
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
	};

	template<map M, typename KEY>
	struct Apply<M, RemoveAt<KEY>>
		: If
			< contains<M, KEY>
			, Apply<M, EraseAt<KEY>>
			, CommonChild
				< NullMap
				, WithError
					< Apply<M, RemoveAt<KEY>>
					, "aeos::RemoveAt: Key does not exists."
					>
				>
			>
	{
	};
	
} // Namespace.
