module aeostasis;
import aeostasis.map;
import aeostasis.utility;
import <concepts>;

namespace aeos
{
	Assert<true>;

	template <typename... T> struct Template {};

	using Map1 = EmptyMap::Applied<AddAt<int, int>>;

	Assert<std::same_as<Map1::Get<int>, int>>;

	//static_assert(false);

	using MapA = EmptyMap::Applied 
		< SetAt<Index<0>, Index<1>>
		, AddAt<Index<2>, Index<3>>
		, AddAt<Index<10>, Index<2>>
		>;
	using MapB = MapA::Applied
		< ModifyAt
			< FetchAt<Index<10>>
			, FetchAsTemplate
				< Template
				, FetchAt<Index<0>>
				, FetchAt<Index<2>>
				>
			>
		>;

	Assert<std::same_as
		< MapB::Get<Index<2>>
		, Template<Index<1>, Index<3>>
		>, MapB::Get<Index<2>>
	>;
}


