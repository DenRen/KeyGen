//
// Created by tester on 10.05.2020.
//

#ifndef KEYGEN_FILE_BOX_HPP
#define KEYGEN_FILE_BOX_HPP

#include "../Engines/Engines.hpp"

namespace objs {

    class file_box {
    private:
        struct view : public ve::Visobj {

            sf::Vector2f coord;
            sf::Sprite sprite;

            void draw();

            view(sf::Vector2f coord, sf::Texture *texture);
        };

        struct model : public pe::Physobj {
            sf::Vector2f coord;
            std::pair<sf::Vector2f, sf::Vector2f> poligon;

            int StoryLineReaction;

            void ActCtrl() { return; };

            int getCurState() { return 0; }

            sf::Vector2f getLocate();

            void ActInterOutside(Physobj &physobj);

            model(int StoryLineReaction);
        };

    public:
        file_box(sf::Vector2f coord, sf::Texture *texture, int StoryLineReaction);

        view Visual;
        model Model;
    };
}


#endif //KEYGEN_FILE_BOX_HPP
