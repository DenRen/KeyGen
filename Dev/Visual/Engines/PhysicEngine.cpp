#include "PhysicEngine.hpp"
#include <iostream>

extern sf::RenderWindow window;

namespace pe {
	PhysicEngine::PhysicEngine () :
		size (0),
		buf (nullptr)
	{}

	PhysicEngine::PhysicEngine (int size) {
		init (size);
	}

    PhysicEngine::~PhysicEngine() {
        free (buf);
    }

	void PhysicEngine::init (int _size) {
		this->size = _size;
		sizeOn = 0;
		posOff = size - 1;
		buf = (Physobj **) calloc (_size, sizeof (Physobj *));

		if (_size == 0 || buf == nullptr)
			throw "Failed to create VisualEngine";
	}

	//--------------------------------------
	//! Adds an item to the clipboard of visual objects.
	//! Sets its current buffer position in it.
	//! Turns on its visibility.
	//!
	//! @none
	//!
	//--------------------------------------

	void PhysicEngine::add (Physobj *physobj) {
		assert (verifier ());

		//if ((buf[sizeOn] = (Visobj *) calloc (1, sizeof (Visobj))) == nullptr)
		//	throw std::runtime_error ("Failed to create Visual Object in Graphic Engine");

		buf[sizeOn] = physobj;
		physobj->BufNum = sizeOn++;
	}

#define VERI_NUM(num)						\
	assert (num > -1);						\
	assert (num < size);					\
	assert (num < sizeOn || num >= posOff);

	// This function not call free or delete
	void PhysicEngine::del (int number) {
		VERI_NUM (number);

		//free (buf[number]);

		if (number < sizeOn)
			_swap (number, --sizeOn);
		else
			_swap (number, posOff++);
	}

	void PhysicEngine::_swap (int first, int second) {
		VERI_NUM (first);
		VERI_NUM (second);

		std::swap (buf[first]->BufNum, buf[second]->BufNum);
		std::swap (buf[first], buf[second]);
	}

	// Without realloc!
	bool PhysicEngine::verifier () {
		assert (size > 0);
		assert (sizeOn >= 0);
		assert (posOff >= 0);
		assert (posOff < size);
		assert (buf != nullptr);

		return sizeOn < posOff;		// So far without realloc
	}

	void PhysicEngine::physOn (int number) {
		VERI_NUM (number);

		if (number < sizeOn)
			return;

		if (sizeOn < posOff) {
			buf[sizeOn] = buf[number];
			buf[sizeOn]->BufNum = sizeOn++;


			if (++posOff != number) {
				buf[number] = buf[posOff];
				buf[number]->BufNum = number;
			} else
				buf[number] = nullptr;

		} else {						// else if (sizeOn == posOff)
			_swap (sizeOn++, number);
			posOff++;
		}
	}

	void PhysicEngine::physOff (int number) {
		VERI_NUM (number);

		if (number >= posOff)
			return;

		if (sizeOn < posOff) {

			buf[posOff] = buf[number];
			buf[posOff]->BufNum = posOff;
			posOff--;

			if (--sizeOn != number) {
				buf[sizeOn]->BufNum = number;
				buf[number] = buf[sizeOn];
			} else
				buf[number] = nullptr;

		} else {						// else if (sizeOn == posOff)
			_swap (sizeOn++, number);
			posOff++;
		}
	}

	void PhysicEngine::SetLocaleChanges () {

		for (int i = 0; i < sizeOn; i++)
			buf[i]->ActCtrl ();
	}

	void PhysicEngine::SetInteractionOutside () {
		Physobj *obj = nullptr;
		for (int i = 0; i < sizeOn; i++) {

			obj = buf[i];
			for (int j = 0; j < i; j++)
				obj->ActInterOutside (*buf[j]);

			for (int j = i + 1; j < sizeOn; j++)
				obj->ActInterOutside (*buf[j]);
		}
	}

	void PhysicEngine::DUMP () {

		/*printf ("╔════════════════════════════════════════════════════════╗\n"
				"║size:\t%2d\t|\tsizeOn:\t%2d\t|\tposOff:\t%2d║\n"
				"╠════════════════════════════════════════════════════════╣",
				 size,		   sizeOn,		   posOff);
	*/

		printf ("__________________________________________________________\n"
			"size:\t%2d\t|\tsizeOn:\t%2d\t|\tposOff:\t%2d|\n",
			size, sizeOn, posOff);
#define __LINE_DELIM for (int j = 0; j < num_in_line; j++)	\
						printf ("________");				\
						printf ("\n");

		int num_in_line = 10;
		__LINE_DELIM

			for (int i = 0; i < size / num_in_line; i++) {
				for (int j = 0; j < num_in_line && i * num_in_line + j < size; j++)
					printf ("|%4d\t", i * num_in_line + j);
				printf ("|\n");

				__LINE_DELIM


					for (int j = 0; j < num_in_line && i * num_in_line + j < size; j++)
						if (buf[i * num_in_line + j] != nullptr)
							printf ("|%4d\t", buf[i * num_in_line + j]->BufNum);
						else
							printf ("|%4d\t", -1);
				printf ("|\n");

				for (int j = 0; j < num_in_line && i * num_in_line + j < size; j++)
					if (buf[i * num_in_line + j] != nullptr)
						printf ("| %5ld\t", (long) buf[i * num_in_line + j] % 10000);
					else
						printf ("| %p", nullptr);
				printf ("|\n");

				__LINE_DELIM
			}
	}

}