#include <assert.h>
#include "PhysMove.hpp"

extern float delta_time;

namespace objmove {

	namespace smooth {

		void PhysSmoothMove::update_speed () {

        /*if (ReqController.Processed_PE)		// Невозможно)
            return;*/

		// This code have elements of optimization, because maybe therefore, 
		// it may seem that it is not structured. In fact, all is well.

		UpdateCurrentState ();

#define _WU speed += alpha.wu * delta_time
#define _RU speed += alpha.ru * delta_time

#define _SD speed += -alpha.sd * delta_time
#define _WRD speed += -alpha.wrd * delta_time
#define _WD speed += -alpha.wd * delta_time

#define _AM manager
#define CUR_STATE cur_state == state_move
#define CUR_STATE_NE cur_state != state_move

		UpdateCurrentState ();
		bool Accel = true;
		if (speed)
			Accel = _AM.direction == direct; // true - Accel, false - Braking
		else
			direct = _AM.direction;

		float accel = 0.0;

		if (Accel == false && CUR_STATE_NE::SITTING && _AM.action != action_manager::NONE) {
			_SD;
		
			if (speed < eps_speed)	speed = 0;
		}
		else
			switch (_AM.action) {

			case action_manager::NONE:

				if (CUR_STATE_NE::SITTING)
					if (CUR_STATE::D_WALK || CUR_STATE::WALKING)
						_WD;
					else
						_WRD;

				if (speed < eps_speed)
					speed = 0;
				break;

			case action_manager::ACC_WALK:

				if (CUR_STATE::SITTING || CUR_STATE::D_WALK) {
					_WU;

					if (speed > speed_state_move.walking - eps_speed)

						speed = speed_state_move.walking;
				}
				else if (CUR_STATE::D_RUN)
					_WRD;
				else if (CUR_STATE::RUNNING)
					_SD;
				
				break;

			case action_manager::ACC_RUN:

				if (CUR_STATE_NE::RUNNING) {
					_RU;

					if (speed > speed_state_move.running - eps_speed)

						speed = speed_state_move.running;
				}
				break;

			case action_manager::DOWN:

				if (Accel && CUR_STATE_NE::SITTING) {
					_SD;

					if (speed < eps_speed)
						speed = 0;
				}
				break;
			}

		//printf ("speed: %g\ncoord: %g\n", speed, coord.x);

		coord.x += direct * speed * delta_time;

		_AM.Processed_PE = true;

		UpdateCurrentState ();

	/*#define _WU accel = alpha.wu * (speed_state_move.walking + speed)
	#define _RU accel = alpha.ru * (speed_state_move.running - speed)

	#define _SD accel = -alpha.sd * (speed_state_move.running + speed)
	#define _WRD accel = -alpha.wrd * (speed_state_move.running + speed)
	#define _WD accel = -alpha.wd * (speed_state_move.walking + speed)

	#define _AM manager
	#define CUR_STATE cur_state == state_move
	#define CUR_STATE_NE cur_state != state_move

			UpdateCurrentState ();
			bool Accel = true;
			if (speed)
				Accel = _AM.direction == direct; // true - Accel, false - Braking
			else
				direct = _AM.direction;

			float accel = 0.0;

			if (Accel == false && CUR_STATE_NE::SITTING && _AM.action != action_manager::NONE)
				_SD;
			else
				switch (_AM.action) {

				case action_manager::NONE:

					if (CUR_STATE_NE::SITTING)
						if (CUR_STATE::D_WALK || CUR_STATE::WALKING)
							_WD;
						else
							_WRD;
					break;

				case action_manager::ACC_WALK:

					if (CUR_STATE::SITTING || CUR_STATE::D_WALK)
						_WU;
					else if (CUR_STATE::D_RUN)
						_WRD;
					else if (CUR_STATE::RUNNING)
						_SD;
					break;

				case action_manager::ACC_RUN:

					if (CUR_STATE_NE::RUNNING)
						_RU;

					break;

				case action_manager::DOWN:

					if (Accel && CUR_STATE_NE::SITTING)
						_SD;

					break;
				}

			SpeedChange (accel * delta_time);

			coord.x += direct * speed * delta_time;

			_AM.Processed_PE = true;

			UpdateCurrentState ();*/
	

		}

	#undef CUR_STATE_NE
	#undef CUR_STATE
	#undef _AM

	#undef _WU
	#undef _RU

	#undef _WD
	#undef _WRD
	#undef _SD
		void PhysSmoothMove::UpdateCurrentState () {
			if (speed == 0)
				cur_state = state_move::SITTING;

			else if (speed <= speed_state_move.walking)

				if (speed == speed_state_move.walking)
					cur_state = state_move::WALKING;
				else
					cur_state = state_move::D_WALK;
			else
				if (speed == speed_state_move.running)
					cur_state = state_move::RUNNING;
				else
					cur_state = state_move::D_RUN;
		}

	}

}