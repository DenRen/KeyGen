#pragma once

#include <SFML/Graphics.hpp>

namespace ue {
	struct UserCtrlobj {
		int BufNum = -1;			// -1 if it does not lie in any buffer
		virtual void AKey () = 0;	// Action on key user pressed
	};

	struct UserControlEngine {
		UserCtrlobj **buf;
		//UserCtrlobj **buf_imm;		// For immadiatly reaction
		int size;

		int sizeOn;
		int posOff;

		UserControlEngine ();
		UserControlEngine (int size);
        ~UserControlEngine ();
		void init (int size);
		void add (UserCtrlobj *ctrlobj);
		void del (int number);

		void ControllOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void ControllOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void getCommandUsers ();

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
}
