# pragma once
# include <cstddef>
# include <algorithm>

namespace aeos
{
	namespace
	{
		template <std::size_t N>
		class String
		{
			constexpr String(char const (&text)[N]) {
				std::ranges::copy(text, m_text);
			}


			char m_text[N] {};
		};
	}

	inline namespace literals
	{
		inline namespace string_literals
		{
			template <String S>
			constexpr decltype(auto) operator ""_s() {
				return S.m_text;
			}
		}
	}
}
