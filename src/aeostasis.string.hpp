# pragma once
# include <cstddef>
# include <algorithm>

namespace aeos
{
	static_assert(__cpp_nontype_template_args >= 201911L);

	template <std::size_t N>
	struct String
	{
		inline static constexpr auto size { N };

		constexpr String(char const (&text)[N]) {
			std::ranges::copy(text, this->text);
		}


		char text[N] {};
	};

	/*
	inline namespace literals
	{
		inline namespace string_literals
		{
			template <String S>
			constexpr String operator ""_s() {
				return S;
			}
		}
	}
	*/
}
