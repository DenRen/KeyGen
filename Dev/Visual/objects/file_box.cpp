//
// Created by tester on 10.05.2020.
//

#include "file_box.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../Engines/Engines.hpp"
#include "../Templates/ObjMoveTempl.hpp"

extern sf::RenderWindow window;
extern int StoryLine;

namespace objs {

    void file_box::view::draw () {

        sprite.setPosition (coord);

        window.draw (sprite);

    }

    file_box::view::view (sf::Vector2f coord, sf::Texture *texture) :
        coord (coord),
        sprite (*texture)
    {
        sprite.setOrigin ({0, sprite.getLocalBounds().height / 2});
        sprite .setScale (0.8, 0.8);
    }

    file_box::file_box (sf::Vector2f coord, sf::Texture *texture, int StoryLineReaction) :
        Model (StoryLineReaction),
        Visual (coord, texture)
    {
        Model.type = pe::objtype::BECON;
        Model.poligon = {{coord.x - 200, coord.y - 200}, {coord.x + 200, coord.y + 200}};
    }

    inline sf::Vector2f file_box::model::getLocate () {
       return coord;
    }

    void file_box::model::ActInterOutside (Physobj &physobj) {

        if (physobj.type == pe::objtype::USER) {
            if (physobj.getCurState () == objmove::smooth::state_move::SITTING) {
                sf::Vector2f coord_hero = physobj.getLocate ();

                if (coord_hero.x >= poligon.first.x && coord_hero.x <= poligon.second.x &&
                    coord_hero.y >= poligon.first.y && coord_hero.y <= poligon.second.y) {

                    printf("%d\n", StoryLineReaction);
                    StoryLine = StoryLineReaction;                                                          // 4:17 10.05.2020
                }
            }
        }
    }

    file_box::model::model(int StoryLineReaction) :
        StoryLineReaction (StoryLineReaction) {

    }

}