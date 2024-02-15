# pragma once
# include <typeinfo>

namespace aeos
{
	template <typename T>
	constexpr auto type_name { typeid(T).name() };

	template <typename T1, typename T2>
	constexpr bool type_less { typeid(T1).before(typeid(T2)) };
}
