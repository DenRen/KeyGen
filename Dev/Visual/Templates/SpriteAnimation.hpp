#pragma once
#include <SFML/Graphics.hpp>

namespace spran {

	enum {
		HORIZONTAL, 
		VERTICAL,		// Arrangement direction locate of sprites	
		UP = 0,			// Right 
		DOWN,			// Left	
	};

	struct DataAnim {
		unsigned arrang : 1;
		unsigned dir_spr : 1;
		unsigned Width;
		unsigned Height;
		unsigned size = -1;
		float dur;				// Frane duration
		sf::Vector2i locate;
		bool cycle;
	};

	struct FrameAnimation
	{
		DataAnim *data = nullptr;
		sf::Sprite *sprite = nullptr;

		FrameAnimation (int size, sf::Sprite *sprite);
		void SetFrame (int state, int frame);
	};


}