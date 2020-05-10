#include "SpriteAnimation.hpp"

namespace spran {
	FrameAnimation::FrameAnimation (int size, sf::Sprite *sprite) :
		sprite (sprite),
		data ((DataAnim *) calloc (size, sizeof (DataAnim)))
	{
		//printf ("Generate:\t%p, %d\n", data, size);
		if (data == nullptr)
			throw "Failed to create data array for sprite animation";

	}

	void FrameAnimation::SetFrame (int state, int frame) {
#define _DA data[state]
		int sign = 1;

		//printf ("_DA.dir_spr: %d\n", _DA.dir_spr);
		if (_DA.dir_spr == spran::UP)
			sign = -1;

		if (_DA.arrang == HORIZONTAL)
			sprite->setTextureRect (sf::IntRect (_DA.locate.x - sign * _DA.Width * frame, _DA.locate.y,
									_DA.Width, _DA.Height));
		else {
			sprite->setTextureRect (sf::IntRect (_DA.locate.x, _DA.locate.y + sign * _DA.Height * frame,
									_DA.Width, _DA.Height));
			//printf ("\n\t\t\t\t\tsign: %d\n", sign);

		}
		
#undef _DA
	}
}
