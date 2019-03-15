#pragma once
#include <random>
#include <list>



namespace matrix
{
	constexpr static wchar_t allowedCharacters[]
	{
		'1','2','3','4','5','6', '7','8','9','0',' ',' ',' ',' ',
		'a','b','c','d','e','f','g','h','j','k','l',
		L'Ƣ',L'Ʃ',L'Ʊ',L'Ƹ',L'ǂ',L'ƽ',L'ǌ',L'Ȣ',L'Ⱦ',L'Ƚ',L'ɑ',L'ɤ',L'ʑ',
		L'ʫ',L'ʥ',L'ʮ',L'λ',L'ε',L'Ϡ',L'Ϟ',L'Ϡ',L'ϰ',L'Є'
	};
	static std::random_device rd;
	static std::mt19937 mt{ rd() };
	const static std::uniform_real<float> disF;
	const static std::uniform_int_distribution<size_t> disI(0,
		sizeof(allowedCharacters) / sizeof(allowedCharacters[0]));
	const size_t maxDepth = 50;

	struct RainDropElement
	{
		const int x, y;
		wchar_t c;

		inline void changeRandomly(const float chance)
		{
			if (chance >= disF(mt))
				c = allowedCharacters[disI(mt)];
		}

		inline RainDropElement(const int x, const int y)
			:x(x), y(y), c(L' ')
		{
			changeRandomly(1);
		}
	};

	class RainDrop
	{
	public:
		using raindrops_t = std::list<RainDropElement>;
	private:
		raindrops_t rainDropElements;
		const int maxSize;
		int size;
		const int x;
		const int maxDepthY;
		float changeChance{ 0.5 };
		int y{ 0 };

	public:
		RainDrop(int maxSize, int x, int maxDepthY, float changeChance)
			:maxSize(maxSize), x(x), y(0),
			size(maxSize / 2),
			maxDepthY(maxDepthY),
			changeChance(changeChance)
		{
		}

		void fall();

		inline const raindrops_t & get() const
		{
			return rainDropElements;
		}

		inline void operator++()
		{
			size = std::min(maxSize,size + 1);
		}
		inline void operator--()
		{
			size = std::max(0, size - 1);
		}
	};
}
