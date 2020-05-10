#include "UserCtrlMove.hpp"

namespace objmove {

	namespace smooth {

	#define _RC			ReqUserController
	#define KEY(key)	sf::Keyboard::isKeyPressed (sf::Keyboard:: key)
	#define ACT			_RC->action = smooth::action_manager::
	#define DIR			_RC->direction = smooth::direct_move::
	#define SEND		_RC->Processed_PE = false;

		void UserCtrl::get () {

			if (_RC->Processed_PE == false)
				return;

			if (KEY (LShift)) {					// SHIFT	

				if (KEY (Right)) {

					ACT ACC_RUN;
					DIR RIGHT;

				} else if (KEY (Left)) {

					ACT ACC_RUN;
					DIR LEFT;

				} else if (KEY (Down))
					ACT DOWN;
				else
					ACT NONE;

			}
			else {							// SIMPLE	

				if (KEY (Right)) {

					ACT ACC_WALK;
					DIR RIGHT;

				} else if (KEY (Left)) {

					ACT ACC_WALK;
					DIR LEFT;

				} else if (KEY (Down))
					ACT DOWN;
				else
					ACT NONE;
			}

			SEND
		}
		
	#undef KEY
#undef ACT
#undef DIR
#undef SEND
#undef _AM
	}

}