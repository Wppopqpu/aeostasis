# include "aeostasis.hpp"
# include "aeostasis.hpp"
# include <concepts>

using namespace aeos;


template <typename... T> struct Template {};

using Map1 = EmptyMap::Applied<AddAt<int, int>>;

static_assert(nonnull<Map1>);

static_assert(std::same_as<Map1::At<int>, int>);

//static_assert(false);

using MapA = EmptyMap::Applied 
	< SetAt<Index<0>, Index<1>>
	, AddAt<Index<2>, Index<3>>
	, AddAt<Index<10>, Index<2>>
	>;

static_assert(std::same_as<MapA::At<Index<10>>, Index<2>>);


using MapB = MapA::Applied
	< ModifyAt
		< At<Index<10>>
		, AsTemplate
			< Template
			, At<Index<0>>
		, At<Index<2>>
			>
		>
	>;

static_assert(std::same_as
	< MapB::At<Index<2>>
	, Template<Index<1>, Index<3>>
	>);


using MapC = EmptyMap::Applied
	< AddAt<int, Fetch<At<long>>>
	, SetAt<long, unsigned>
	, ModifyAt<long, short>
	>;
static_assert(std::same_as<short, MapC::At<long>>);
static_assert(std::same_as<short, MapC::At<int>>);


