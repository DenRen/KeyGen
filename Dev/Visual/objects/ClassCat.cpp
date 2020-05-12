#include "../Engines/Engines.hpp"
#include "ClassCat.hpp"

extern sf::RenderWindow window;
extern float delta_time;

namespace hero {

	/*cat::cat (sf::Vector2f init_pos) :
		View (),
		Model (init_pos, &View.ViewParam),
		Control (&Model.ReqController)
	{
		printf ("%g %g\n", Model.coord.x, Model.coord.y);
	}*/

	cat::cat (sf::Vector2f init_pos, sf::Texture *texture_cat, pe::objtype type) :
		View (texture_cat),
		Model (init_pos, type, &View.ViewParam),
		Control (&Model.manager)
	{
		View.walking_speed = Model.speed_state_move.walking;
		View.running_speed = Model.speed_state_move.running;
	}
	
	//| Animation |------------------------------------------------------------------

	cat::Animation::Animation (sf::Texture *texture_cat) :
		ViewFrame (texture_cat)
	{

#define __DATA(_name) dataAnim.data[objmove::smooth::state_move:: _name]
#define FRAMES(name, V_H, U_D, _cycle, sizeX, sizeY, quant, x_0, y_0)	\
	__DATA (name).arrang	= spran:: V_H;								\
	__DATA (name).dir_spr	= spran:: U_D;								\
	__DATA (name).Width		= sizeX;									\
	__DATA (name).Height	= sizeY;									\
	__DATA (name).size		= quant;									\
	__DATA (name).cycle		= _cycle;									\
	__DATA (name).locate	= sf::Vector2i (x_0, y_0);
#define FRAME_DURATION(name, duration)									\
		__DATA (name).dur = duration;										
		
		// Base sizes
		int sizeX = 400;
		int sizeY = 199;

		FRAMES (SITTING, VERTICAL, UP,		true,  sizeX, sizeY, 1,  sizeX * 1,	sizeY * 5 + 2);
		FRAMES (D_WALK,  VERTICAL, UP,		false, sizeX, sizeY, 6,  sizeX * 1,	sizeY * 5 + 2);
		FRAMES (WALKING, VERTICAL, DOWN,	true,  sizeX, sizeY, 12, sizeX * 0, 0);
		FRAMES (D_RUN,	 VERTICAL, DOWN,	false, sizeX, sizeY, 12, sizeX * 2, 0);
		FRAMES (RUNNING, VERTICAL, DOWN,	true,  sizeX, sizeY, 13, sizeX * 3, 0);

		FRAME_DURATION (SITTING,	0);
		FRAME_DURATION (D_WALK,		0);
		FRAME_DURATION (WALKING,	0.10);
		FRAME_DURATION (D_RUN,		0);
		FRAME_DURATION (RUNNING,	0.05);

		sprite.setOrigin (sizeX / 2, sizeY / 2);

#undef FRAMES
#undef DATA
	}

	void cat::Animation::draw () {
		//printf ("\n");
		SetNextFrame (ViewParam.speed, ViewParam.direct, ViewParam.state);

		//printf ("direct: %d\n", ViewParam.direct);

		sprite.setScale (-ViewParam.direct, 1);

		sprite.setPosition (ViewParam.coord.x - ViewParam.direct * 100, ViewParam.coord.y);

		window.draw (sprite);
	}

	//|	Physics |--------------------------------------------------------------------

	cat::Physic::Physic (sf::Vector2f init_pos, pe::objtype type, 
						 Model_2_View *ViewParam, int direct) :
		ViewParam (ViewParam)		
	{
		this->type = type;
		
		alpha.wu  = 400;
		alpha.wd  = 500;
		alpha.ru  = 1000;
		alpha.wrd = 600;
		alpha.sd  = 2300;

		speed_state_move.walking = 250;
		speed_state_move.running = 700;

		coord = init_pos;
		speed = 0;
		this->direct = direct;

		UpdateCurrentState ();

		manager.Processed_PE = true;
		manager.direction = objmove::smooth::direct_move::RIGHT;
		manager.action = objmove::smooth::action_manager::NONE;

		eps_speed = 0.01;
	}

	void cat::Physic::ActInterOutside (pe::Physobj &physobj)
	{
	}

	inline void cat::Physic::SetViewParam () {
		ViewParam->coord = coord;
		ViewParam->direct = direct;
		ViewParam->speed = speed;
		ViewParam->state = cur_state;
	}

	void cat::Physic::ActCtrl () {	// Action on monipulats user

		update_speed ();
		SetViewParam ();

	}

	inline sf::Vector2f cat::Physic::getLocate ()
	{
		return coord;
	}

	inline int cat::Physic::getCurState () {
	    return cur_state;
	}
	
	// | Keyboard |------------------------------------------------------------------
	
	void cat::ActKey::AKey () {
		this->get ();
	}

	cat::ActKey::ActKey (objmove::smooth::AManager *ReqUserCtrl)
	{
		ReqUserController = ReqUserCtrl;
	}
}