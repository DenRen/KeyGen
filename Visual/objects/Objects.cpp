//
// Created by tester on 10.05.2020.
//

#include "Objects.hpp"

extern sf::RenderWindow window;

namespace objs {

    void background::Vis::draw () {
        window.draw (sprite);
    }

    background::Vis::Vis (sf::Texture &texture) :
        sprite (texture)
    {
        sf::Vector2u size_window = window.getSize ();
        sf::Vector2u size_sprite = sprite.getTexture()->getSize();

        sprite.setScale (size_window.x / size_sprite.x, size_window.y / size_sprite.y);
        sprite.setOrigin (0, 0);
        sprite.setPosition (0, 0);
    }

    background::background (sf::Texture *texture) :
        View (*texture)
    {

    }
}