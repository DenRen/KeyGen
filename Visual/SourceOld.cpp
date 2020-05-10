#define OOOPPP
#ifndef OOOPPP

#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/System/String.hpp>
#include <thread>
#include <cmath>
//#include <Windows.h>

void game();

sf::RenderWindow window;
float delta_time;

#define _EPSILON_SPEED 1
void inline eps_speed(float* speed) {

	if (abs(*speed) < _EPSILON_SPEED)
		*speed = 0;

}
bool inline speed_is_zero(float speed) {
	return abs(speed) < _EPSILON_SPEED;
}
#undef _EPSILON_SPEED
template <typename T> int sign(T value) {
	return (T(0) < value) - (value < T(0));
}
float add_to_abs(float x, float delta_x) {
	if (x >= 0)
		return x + delta_x;
	else
		return x - delta_x;
}

struct Visobj {							// Visual object
	sf::Vector2i coord;
	sf::Vector2u sizeRect;
	virtual void draw() = 0;

	Visobj(sf::Vector2i coord, sf::Vector2u sizeRect) :
		coord(coord),
		sizeRect(sizeRect)
	{};

	Visobj(int x, int y, int width, int height) :
		coord(sf::Vector2i(x, y)),
		sizeRect(sf::Vector2u(width, height))
	{};
};

struct ActKey {
	virtual void AKeyboard(sf::Event::KeyEvent key_event, bool push) = 0;
};

#define _DIRECTION_MOVE_RIGHT 1
#define _DIRECTION_MOVE_LEFT  -1

struct ActKey__ {
	bool move;
	int direction;						// _DIRECTION_MOVE_RIGHT/LEFT
	bool running;

	ActKey__() :
		move(false), direction(0), running(false)
	{}

	void free() {
		move = running = false;
		direction = 0;
	}
};

struct Physobj {
	virtual void set_physic() = 0;
	sf::Vector2f fcoord;

	Physobj(sf::Vector2f physich_coord) :
		fcoord(physich_coord)
	{}
};

struct unit_anim {
	sf::Vector2u start;
	int size;
	int frame_before_wakeup;
	int direction;				// Up == -1, down == +1
	bool state = false;
	float time_frame;
};

struct cat :
	public Visobj, public ActKey, public Physobj
{
	float speed;						// If velocity more zero, that a cat see on the right
	const float walk_speed = 20 * 5 * 2;
	const float run_speed = 60 * 5 * 2;

	float accel;						// Dynamic
	const float accel_walk = 40 * 10 * 2;
	const float accel_run = 80 * 10 * 2;

	ActKey__ state_control_move;

	sf::Texture texture;
	sf::Sprite sprite;

	unit_anim sitting;
	unit_anim wakeup;
	unit_anim walking;
	unit_anim runup;
	unit_anim running;
	unit_anim* conds[5] = { &sitting, &wakeup, &walking, &runup, &running };

	cat(sf::Vector2i coord, sf::Vector2u size_rect_texture);
	void draw();
	void AKeyboard(sf::Event::KeyEvent key_event, bool push);
	void set_physic();
	//speed_up ();
};

cat::cat(sf::Vector2i coord, sf::Vector2u size_rect_texture) :
	Visobj(coord, size_rect_texture),
	Physobj(sf::Vector2f(coord)),
	speed(0),
	accel(0)
{
	if (texture.loadFromFile("sprites/cat.png") == false)
		throw ("Failed to load texture for cat");
	texture.setSmooth(true);

	sprite = sf::Sprite(texture);
	sprite.setOrigin(sizeRect.x / 4, sizeRect.y / 2);

#define _sizeX sizeRect.x
#define _sizeY sizeRect.y

	sitting.start = sf::Vector2u(_sizeX, _sizeY * 5 - 5);
	sitting.size = 5 + 1;
	sitting.frame_before_wakeup = 0;
	sitting.direction = -1;
	sitting.time_frame = 0;

	wakeup.start = sf::Vector2u(_sizeX, _sizeY * 5 - 5);
	wakeup.size = 5;
	wakeup.frame_before_wakeup = 0;
	wakeup.direction = -1;
	wakeup.time_frame = 0.1;

	walking.start = sf::Vector2u(0, 0);
	walking.size = 12;
	walking.frame_before_wakeup = 3;
	walking.direction = +1;
	walking.time_frame = 0.1;

	runup.start = sf::Vector2u(_sizeX * 2, 0);
	runup.size = 12;
	runup.frame_before_wakeup = 0;
	runup.direction = +1;
	runup.time_frame = 0.1;

	running.start = sf::Vector2u(_sizeX * 3, 0);
	running.size = 13;
	running.frame_before_wakeup = 0;
	running.direction = +1;
	running.time_frame = 0.1;

#undef _sizeX
#undef _sizeY

}
/*
#define _sizeX 400
#define _sizeY 200
#define _INIT_ANIMATION_OPT_CAT_											\
	unit_anim sitting = {};													\
	sitting.start = sf::Vector2u (_sizeX, _sizeY * 5 - 5);					\
	sitting.size = 5;														\
	sitting.frame_before_wakeup = 0;										\
	sitting.direction = -1;													\
	\
	unit_anim wakeup = {};													\
	wakeup.start = sf::Vector2u (_sizeX, _sizeY * 5 - 5);					\
	wakeup.size = 5;														\
	wakeup.frame_before_wakeup = 0;											\
	wakeup.direction = -1;													\
	\
	unit_anim walking = {};													\
	walking.start = sf::Vector2u (0, 0);									\
	walking.size = 12;														\
	walking.frame_before_wakeup = 3;										\
	walking.direction = +1;													\
	\
	unit_anim run_up = {};													\
	run_up.start = sf::Vector2u (_sizeX * 2, 0);							\
	run_up.size = 12;														\
	run_up.frame_before_wakeup = 0;											\
	run_up.direction = +1;													\
	\
	unit_anim running = {};													\
	running.start = sf::Vector2u (_sizeX * 3, 0);							\
	running.size = 13;														\
	running.frame_before_wakeup = 0;										\
	running.direction = +1;													\
	\
	unit_anim* conds[5] = { &sitting, &wakeup, &walking, &run_up, &running };

#undef _INIT_ANIMATION_OPT_CAT
#undef _sizeX
#undef _sizeY
*/

enum state_cat {
	SITTING,
	WAKE_UP,
	WALKING,
	RUN_UP,
	RUNNING
};

void cat::draw () {
	static float frame = 0;
	static int cur_cond = SITTING;
	static int direction = 1;			// Left
	static int dir_accel = 1;

	//printf ("_____: %f\n", accel);
	//printf ("ACCEL: %d\n", dir_accel);
	int nec_cond = SITTING;				// Neccesary to sitt {if (speed == 0) SITTING}

	bool need_comlete = false;

	if (accel != 0)
		dir_accel = sign(accel);

	for (int i = 0; i < 5; i++)
		if (conds[i]->state) {
			nec_cond = i;
			break;
		}

	if (speed != 0 && nec_cond == SITTING) {

		if (abs(speed) < walk_speed)
			nec_cond = WAKE_UP;
		else if (abs(speed) == walk_speed)
			nec_cond = WALKING;
		else if (abs(speed) <= run_speed)
			nec_cond = RUN_UP;
		else // if (abs (speed) == run_speed)
			nec_cond = RUNNING;

		speed < 0 ? direction = -1 : direction = 1;

	}

	float temp_frame = frame;
	switch (nec_cond) {

	case SITTING:
		printf("SITTING\n");
		sprite.setTextureRect(sf::IntRect(wakeup.start.x, wakeup.start.y,
			sizeRect.x, sizeRect.y));
		frame = 0;
		break;
	case WAKE_UP:
		wakeup.state = true;

		if (dir_accel * direction > 0) {
			frame += delta_time / wakeup.time_frame;
			if (frame >= wakeup.size) {
				wakeup.state = false;
				frame -= wakeup.size;
				break;
			}

			sprite.setTextureRect(sf::IntRect(wakeup.start.x,
											  wakeup.start.y + wakeup.direction * ((int)frame) * sizeRect.y,
											  sizeRect.x, sizeRect.y));
		}
		else {
			frame -= delta_time / wakeup.time_frame;
			if (frame <= 0) {
				wakeup.state = false;
				frame = abs(frame);
				break;
			}
			sprite.setTextureRect(sf::IntRect(wakeup.start.x,
				wakeup.start.y + wakeup.direction * ((int)temp_frame) * sizeRect.y,
				sizeRect.x, sizeRect.y));
		}
		printf("WAKE_UP (%d) \tdir: %d\n\t%f\n", (int)temp_frame, direction, dir_accel);

		break;

	case WALKING:
		walking.state = true;

		if (dir_accel * direction > 0) {
			frame += delta_time / walking.time_frame;
			if (frame >= walking.size) {
				walking.state = false;
				frame -= walking.size;
				break;
			}

			sprite.setTextureRect(sf::IntRect(walking.start.x,
				walking.start.y + walking.direction * ((int)frame) * sizeRect.y,
				sizeRect.x, sizeRect.y));
		}
		else {
			frame -= delta_time / walking.time_frame;
			if (frame <= 4 || frame >= walking.size - 4 - 1) {
				walking.state = false;
				frame = wakeup.size - 1;
				break;
			}
			sprite.setTextureRect(sf::IntRect(walking.start.x,
								  walking.start.y + walking.direction * ((int)temp_frame) * sizeRect.y,
								  sizeRect.x, sizeRect.y));
		}
		printf("WALKING (%d) \tdir: %d\n\t%f\n", (int)temp_frame, direction, dir_accel);

		break;

	case RUN_UP:
		runup.state = true;

		if (dir_accel * direction > 0) {
			frame += delta_time / runup.time_frame;
			if (frame >= runup.size) {
				runup.state = false;
				frame -= runup.size;
				break;
			}

			sprite.setTextureRect(sf::IntRect(runup.start.x,
				runup.start.y + runup.direction * ((int)frame) * sizeRect.y,
				sizeRect.x, sizeRect.y));
		}
		else {
			frame -= delta_time / runup.time_frame;
			if (frame <= 4 || frame >= runup.size - 4 - 1) {
				runup.state = false;
				frame = wakeup.size - 1;
				break;
			}
			sprite.setTextureRect(sf::IntRect(runup.start.x,
				runup.start.y + runup.direction * ((int)temp_frame) * sizeRect.y,
				sizeRect.x, sizeRect.y));
		}
		printf("RUN_UP (%d) \tdir: %d\n\t%f\n", (int)temp_frame, direction, dir_accel);
		break;
	default:
		printf("Other\n");
		frame = wakeup.size - 1;
	}

	//printf ("%f\t%d\n", frame, wakeup.start.y + wakeup.direction * (wakeup.size - 1) * sizeRect.y);

	//printf ("Direction: %d\n", direction); 
	if (direction < 0)	sprite.setScale(+1, 1);
	else if (direction > 0)	sprite.setScale(-1, 1);
	sprite.setPosition(coord.x, coord.y);

	window.draw(sprite);
}

void cat::AKeyboard(sf::Event::KeyEvent key_event, bool push) {
#define _STATE state_control_move
#define _CODE  key_event.code

	if (_CODE == sf::Keyboard::D) {

		_STATE.move = push;
		_STATE.direction = _DIRECTION_MOVE_RIGHT;

	}
	else if (_CODE == sf::Keyboard::A) {

		_STATE.move = push;
		_STATE.direction = _DIRECTION_MOVE_LEFT;

	}
	else if (_CODE == sf::Keyboard::LShift) {
		_STATE.running = push;
	}

#undef _STATE
#undef _CODE
}

void cat::set_physic() {
#define _STATE state_control_move
#define _ACCEL_SLID_FICT 80 * (walk_speed - abs (speed))
	accel = 0;

	if (_STATE.move)
		accel = (accel_walk + accel_run * _STATE.running) * _STATE.direction;

	speed += accel * delta_time;

	if (!speed_is_zero(speed)) {							//Sliding fiction
		speed = add_to_abs(speed, -_ACCEL_SLID_FICT * delta_time);
		if (accel != 0)
			accel = add_to_abs(accel, -_ACCEL_SLID_FICT);
		else
			accel = -sign(speed) * _ACCEL_SLID_FICT;
	}
	printf("Sp: %f\n", speed);
	eps_speed(&speed);
	if (_STATE.running && abs(speed) > run_speed)
		speed = sign(speed) * run_speed;
	else if (!_STATE.running && abs(speed) > walk_speed)
		speed = sign(speed) * walk_speed;

	fcoord.x += speed * delta_time;
	coord.x = fcoord.x;

	printf("\nm, d, r: %d %2d %d\n\n", _STATE.move, _STATE.direction, _STATE.running);
	printf("accel: %3.2f, speed: %3.2f, location: %3.2f, dtime: %1.3f\n\n", accel, speed, fcoord.x, delta_time);

#undef _ACCEL_SLID_FICT
#undef _STATE
}

int main() {

	game();

	return 0;
}

void game() {
	const int height = 1080 / 2, width = 1920 / 2;

	window.create(sf::VideoMode(width, height), "", sf::Style::Default & ~sf::Style::Resize);	// (sf::VideoMode::getDesktopMode (), "", sf::Style::Fullscreen);
	window.setPosition(sf::Vector2i(width, 0));

	//window.create (sf::VideoMode (width, height), "", sf::Style::Default & ~sf::Style::Resize);	// (sf::VideoMode::getDesktopMode (), "", sf::Style::Fullscreen);
	//window.create (sf::VideoMode::getDesktopMode (), "", sf::Style::Fullscreen);

	window.setVerticalSyncEnabled(true);						// window.setFramerateLimit (25);
	window.setKeyRepeatEnabled(false);

	sf::Texture texture_cat;
	
	if (texture_cat.loadFromFile("sprites/cat.png") == false)
		return;

	texture_cat.setSmooth(true);
	sf::Sprite sprite(texture_cat);

	int frame = 25, size_y = 199, size_x = 400, num = 12;
	int frame_rate = 1000 / frame;

	//sprite.setPosition ((width - size_x / 2) / 2, height - size_y / 2);
	//sprite.setOrigin (size_x / 2, size_y / 2);

	sf::Event event;
	cat meow(sf::Vector2i(size_x / 2, size_y / 2), { 400, 200 });

	sf::Clock clock;
	__int64 __time_old = clock.getElapsedTime().asMicroseconds() - 1000000;
	__int64 __curr_time = __time_old;

	while (window.isOpen()) {
		__curr_time = clock.getElapsedTime().asMicroseconds();
		delta_time = (float)(__curr_time - __time_old) / 1000000;			// In seconds
		//printf ("DELTA: %f\n", delta_time);
		__time_old = __curr_time;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				meow.AKeyboard(event.key, event.type == sf::Event::KeyPressed);
				break;

			case sf::Event::MouseMoved:
				//printf ("x: %3d, y: %3d\n", event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				printf("Mouse pressed\n");
				break;
			}
		}

		meow.set_physic();

		window.clear(sf::Color::White);
		meow.draw();
		window.display();
	}
}

#endif