#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

namespace pe {
	enum PHYSIC_TYPE {
		MAT_POINT,
		CTRL_MAT_POINT,
		CTRL_POLIGON,
		MOTIONLESS
	};

	enum objtype {
		USER,
		NPC,
		BUTTON,
		BECON,
		WALL,
		COUNTER
	};

	struct Physobj {
		int BufNum = -1;	// -1 if it does not lie in any buffer
		int type = -1;
		virtual void ActCtrl () = 0;	// Action on the controller
		virtual sf::Vector2f getLocate () = 0;
		virtual void ActInterOutside (Physobj &physobj) = 0;
		virtual int getCurState () = 0;
	};

	struct PhysicEngine {
		Physobj **buf;
		int size;

		int sizeOn;
		int posOff;

		PhysicEngine ();
		PhysicEngine (int size);
        ~PhysicEngine ();

		void init (int size);
		void add (Physobj *physobj);
		void del (int number);

		void physOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void physOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void SetLocaleChanges ();		// Perform action on the controller
		void SetInteractionOutside ();

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
}
