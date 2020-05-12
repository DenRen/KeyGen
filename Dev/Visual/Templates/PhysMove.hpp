#pragma once
#include <SFML/Graphics.hpp>

namespace objmove {

	namespace smooth {

		struct AManager {
			bool Processed_PE;
			signed direction : 2;
			__int8_t action;
		};

		enum state_move {
			SITTING,
			D_WALK,		// Delta walk
			WALKING,
			D_RUN,		// Delta run
			RUNNING
		};

		enum direct_move {
			RIGHT = 1,
			LEFT = -1,
			FRONT = 0
		};
		enum action_manager {
			NONE,
			ACC_WALK,
			ACC_RUN,
			DOWN
		};

		struct _alpha {
			float wu;
			float wd;
			float ru;
			float wrd;
			float sd;
		};
		struct _speed_state_move {
			float walking;
			float running;
		};
		struct PhysSmoothMove
		{
			_alpha alpha;
			_speed_state_move speed_state_move;

			sf::Vector2f coord;
			float speed;		// Always above or equal by zero

			int cur_state;
			int direct;			// Right: 1; Left: -1

			AManager manager;

			void update_speed ();

			float eps_speed;

			void UpdateCurrentState ();
		};
	}
}