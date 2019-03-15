#include <iostream>
#include <thread>
#include <chrono>
#include "RainDrop.h"
#include "DoubleBufferedConsole.h"

using namespace std::chrono_literals;
const auto refreshRate = 0.1s;
const auto resizeChance = 0.3;

static std::random_device rd;
static std::mt19937 mt(rd());


void initRainDrops(std::vector<matrix::RainDrop> & rainDrops, int width, int height)
{
	const std::uniform_int_distribution<int> disSize(0, height);
	const std::uniform_int_distribution<int> disDepth(height, height + height / 2);

	//init raindrops
	for (auto x = 0; x < width; ++x)
	{
		rainDrops.push_back({
			disSize(mt),
			x,
			disDepth(mt),
			0.2f });
	}
}

int main()
{
	DoubleBufferedConsole<wchar_t> myConsole(L"Matrix");
	const auto txtAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	const auto[width, height] = myConsole.getSize();
	myConsole.clear(' ', txtAttributes);

	std::vector<matrix::RainDrop> rainDrops;
	initRainDrops(rainDrops, width, height);

	const std::uniform_real_distribution<double> disD(0,1);

	//screensaver
	while (1)
	{
		for (auto & rainDrop : rainDrops)
		{
			rainDrop.fall();
			for (auto & element : rainDrop.get())
			{
				if (element.y < height)
				{
					myConsole.write(element.x, element.y, element.c, txtAttributes);
				}
			}

			//resize randomly
			if (disD(mt) <= resizeChance)
			{
				if (disD(mt) <= 0.5)
					++rainDrop;
				else
					--rainDrop;
			}
		}
		myConsole.flip();
		myConsole.clear(' ',txtAttributes);
		std::this_thread::sleep_for(refreshRate);
	}
}