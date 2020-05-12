#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

namespace ve {
	struct Visobj {
		int BufNum = -1;	// -1 if it does not lie in any buffer
		virtual void draw () = 0;
	};

	struct VisualEngine {
		Visobj **buf;
		int size;

		int sizeOn;
		int posOff;

		VisualEngine ();
		VisualEngine (int size);
        ~VisualEngine();

		void init (int size);
		void add (Visobj *visobj);
		void del (int number);

		void visOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void visOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void draw ();

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
}