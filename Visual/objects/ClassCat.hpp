#pragma once

#include "../Templates/ObjMoveTempl.hpp"
#include "../Templates/SpriteAnimation.hpp"
#include "../Engines/Engines.hpp"

namespace hero {

	class cat {
	public:

		struct Model_2_View {	// Inteface between Model and View
			sf::Vector2f coord;
			float speed;
			int direct;			// Move direction
			int state;			// 
		};

		struct Control_2_Model {
			bool Processed_PE;
			signed direction : 2;
			__int8_t action;
		};

		class Animation : 
			public ve::Visobj, public objmove::smooth::ViewFrame
		{
		public:

			// Interface getting Model Requests 
			Model_2_View ViewParam;

			void draw ();

			Animation (sf::Texture *texture_cat);
		};

		class Physic : 
			public pe::Physobj, public objmove::smooth::PhysSmoothMove
		{
		public:
			// Interface Model -> View
			Model_2_View *ViewParam;

			Physic (sf::Vector2f init_pos, pe::objtype type, Model_2_View *ViewParam, 
					int direct = objmove::smooth::direct_move::RIGHT);

			void ActCtrl ();
			void SetViewParam ();
			int getCurState ();

			sf::Vector2f getLocate ();
			void ActInterOutside (pe::Physobj &physobj);
		 };

		class ActKey : 
			public ue::UserCtrlobj, public objmove::smooth::UserCtrl
		{
		public:
			
			ActKey (objmove::smooth::AManager *ReqUserCtrl);

			void AKey ();
			
		};

		Animation	View;
		Physic		Model;
		ActKey		Control;

		cat (sf::Vector2f init_pos, sf::Texture *texture_cat, pe::objtype);
	};
}
