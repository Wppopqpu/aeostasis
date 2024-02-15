# pragma once

namespace aeos
{
	namespace
	{
		template <bool BOOL, typename A, typename B>
		struct If_impl
		{
			using Type = A;
		};

		template <typename A, typename B>
			struct If_impl<false, A, B>
		{
			using Type = B;
		};
	}

	template <bool BOOL, typename A, typename B>
	using If = typename If_impl<BOOL, A, B>::Type;

} // namespace
