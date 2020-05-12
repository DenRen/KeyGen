#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Engines/Engines.hpp"
#include "objects/ClassCat.hpp"

struct ActKey {

};

unsigned int width = 1920;
unsigned int height = width * 9 / 16;

sf::RenderWindow window;
ve::VisualEngine VE;
pe::PhysicEngine PE;
ue::UserControlEngine UE;
float delta_time;

int main () {
#define TEXTURE_FILE_CAT "sprites/cat.png"

	window.create (sf::VideoMode (width, height, 8 * 8), "", sf::Style::Default &
															 ~sf::Style::Resize); //sf::Style::Titlebar & sf::Style::Close);
	window.setPosition (sf::Vector2i (1920 / 4 + width / 2, 0));
	window.setVerticalSyncEnabled (true);
	window.setKeyRepeatEnabled (false);

	VE.init (20);
	UE.init (3);
	PE.init (20);

	sf::Texture texture_cat;
	if (!texture_cat.loadFromFile (TEXTURE_FILE_CAT))
		printf ("Failed to load texture");

	hero::cat cat ({ 150, 330 }, &texture_cat, pe::objtype::USER);

	VE.add ((ve::Visobj		 *) &(cat.View));
	UE.add ((ue::UserCtrlobj *) &(cat.Control));
	PE.add ((pe::Physobj	 *) &(cat.Model));

	sf::Clock clock;
	__int64_t __time_old = clock.getElapsedTime ().asMicroseconds () - 1000000;
	__int64_t __curr_time = __time_old;

	while (window.isOpen ()) {
		// | Get delta_time | -------------------------------------
		__curr_time = clock.getElapsedTime ().asMicroseconds ();
		delta_time = (float) (__curr_time - __time_old) / 1000000;		// In seconds
		__time_old = __curr_time;
		//---------------------------------------------------------

		UE.getCommandUsers ();
		PE.SetLocaleChanges ();
		PE.SetInteractionOutside ();
		VE.draw ();

	}

	return 0;

#undef TEXTURE_FILE_CAT
}
