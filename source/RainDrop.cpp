#include "RainDrop.h"

void matrix::RainDrop::fall()
{
	for (auto &droplet : rainDropElements)
		droplet.changeRandomly(changeChance);

	rainDropElements.push_front({ x,y });

	while(rainDropElements.size() > size)
		rainDropElements.pop_back();

	// |--------| <- Top of screen
	// | x      |
	// | x      | <- Screen
	// |-x------| <- Bottom of screen
	// # x      # <- "Delay" Area
	if (++y >= maxDepthY)
		y = 0;
}

