#pragma once
#include "ObjMoveTempl.hpp"

namespace objmove {
	
	namespace smooth {
		struct ViewFrame {
			void SetNextFrame (float speed, int direct, int state);

			int old_state		= 0;
			int old_speed		= 0;
			int old_type_anim	= 0;
			int old_num_state	= 0;

			float time_state	= 0;

			float walking_speed	= 0;							
			float running_speed	= 0;							
			float eps_speed		= 0;

			sf::Sprite sprite;		
			spran::FrameAnimation dataAnim;

			ViewFrame (sf::Texture *texture);
		};
	}

}