//
// Created by tester on 10.05.2020.
//

#ifndef KEYGEN_OBJECTS_HPP
#define KEYGEN_OBJECTS_HPP

#include "ClassCat.hpp"
#include "file_box.hpp"
#include "hack_box.hpp"
namespace objs {

    class background {
    public:
        struct Vis : public ve::Visobj {
            sf::Sprite sprite;

            void draw ();

            Vis (sf::Texture &texture);
        };

        Vis View;

        background (sf::Texture *texture);
    };

}
#endif //KEYGEN_OBJECTS_HPP
