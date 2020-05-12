#pragma once
#include "ObjMoveTempl.hpp"

namespace objmove {

	namespace smooth {

		struct UserCtrl
		{
			// Interface User Control (Keyboard/Mouse) -> Model
			AManager *ReqUserController;

			void get ();
		};
	}

}

