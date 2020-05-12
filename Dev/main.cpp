#include <cstdio>
#include <stdexcept>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <unistd.h>

#include "Visual/Engines/Engines.hpp"
#include "Visual/objects/Objects.hpp"
#include "hack_lib.h"

sf::RenderWindow window;
ve::VisualEngine VE;
pe::PhysicEngine PE;
ue::UserControlEngine UE;

float delta_time;
int StoryLine = 0;

#define WIDTH 1920 / 2
#define HEIGHT WIDTH * 9 / 16

int main() {

    char path[] = "../crack/THIS.COM";
    char path_out[] = "../crack/CRACK.COM";

#define _HASH_SUM               7217
#define TEXTURE_FILE_CAT        "../Visual/sprites/cat.png"
#define TEXTURE_FILE_LCAT       "../media/catL1_new.png"
#define TEXTURE_FILE_ART        "../media/Art.png"
#define TEXTURE_FILE_WART       "../media/WhiteBackGraund.png"
#define TEXTURE_OPEN_FILE       "../media/open_file.png"
#define TEXTURE_BLUE_SCREEN     "../media/BlueScreenDeath.png"
#define TEXTURE_FILE_HACK       "../media/Hack.png"
#define TEXTURE_FILE_END_ART    "../media/End.png"

#define AUDIO_BLUE_SCREEN   "../media/Blue_screen_of_death.wav"
#define AUDIO_MIAU          "../media/Miau.wav"
#define AUDIO_X_FILES       "../media/MarkSnowXFiles.wav"
#define AUDIO_CLASSIC_8_BIT "../media/Classical Music in Keygen Version - 8 bit.wav"

    window.create(sf::VideoMode(WIDTH, HEIGHT, 8 * 8), "", sf::Style::Default &
                                                           ~sf::Style::Resize); //sf::Style::Titlebar & sf::Style::Close);
    window.setPosition(sf::Vector2i(1920 / 4 + WIDTH / 2, 0));
    window.setFramerateLimit (30);
    window.setKeyRepeatEnabled(false);

    window.clear (sf::Color::Black);
    window.display ();

    VE.init (20);
    UE.init (3);
    PE.init (20);

    sf::Texture texture_cat,       texture_art,     texture_open_file,
                texture_lcat,      texture_wart,    texture_blue_screen,
                texture_icon_hack, texture_end_art;

    if (!texture_cat.loadFromFile         (TEXTURE_FILE_CAT)    ||
        !texture_lcat.loadFromFile        (TEXTURE_FILE_LCAT)   ||
        !texture_art.loadFromFile         (TEXTURE_FILE_ART)    ||
        !texture_wart.loadFromFile        (TEXTURE_FILE_WART)   ||
        !texture_open_file.loadFromFile   (TEXTURE_OPEN_FILE)   ||
        !texture_blue_screen.loadFromFile (TEXTURE_BLUE_SCREEN) ||
        !texture_icon_hack.loadFromFile   (TEXTURE_FILE_HACK)||
        !texture_end_art.loadFromFile     (TEXTURE_FILE_END_ART)) {

        printf("Failed to load texture");

        return 0;
    }

    hero::cat cat({WIDTH * 25 / 100, (float) HEIGHT * 762 / 1000}, &texture_cat, pe::objtype::USER);
    objs::file_box box ({WIDTH * 70 / 100, (float) HEIGHT * 750 / 1000}, &texture_open_file, 1);
    objs::hack_box shield ({WIDTH * 5 / 100, (float) HEIGHT * 750 / 1000}, &texture_icon_hack, 2);
    objs::background background (&texture_wart);


    VE.add ((ve::Visobj *) &(background.View));
    VE.add ((ve::Visobj *) &(cat.View));
    VE.add ((ve::Visobj *) &(box.Visual));

    UE.add ((ue::UserCtrlobj *) &(cat.Control));

    PE.add ((pe::Physobj *) &(cat.Model));
    PE.add ((pe::Physobj *) &(box.Model));

    sf::SoundBuffer SoundBBS,               // BlueScreen
                    SoundBMiau,
                    SoundBBG_find_file,     // BackGround when finding file
                    SoundBBG_crack_file;    // BackGround when cracking file

    if (!SoundBBS.loadFromFile            (AUDIO_BLUE_SCREEN)   ||
        !SoundBBG_find_file.loadFromFile  (AUDIO_X_FILES)       ||
        !SoundBBG_crack_file.loadFromFile (AUDIO_CLASSIC_8_BIT) ||
        !SoundBMiau.loadFromFile          (AUDIO_MIAU)) {

        printf ("Failedto open audio files\n");

        return 0;
    }

    sf::Sound sound;
    sf::Sound sound_miau;

    sound.setBuffer (SoundBBG_find_file);
    sound.setVolume (40);
    sound.setLoop (true);
    sound.play ();

    long size = 0;
    char *content = nullptr;

    sf::Clock clock;
    __int64_t __time_old = clock.getElapsedTime().asMicroseconds() - 1000000;
    __int64_t __curr_time = __time_old;

    while (window.isOpen()) {
        // | Get delta_time | -------------------------------------
        __curr_time = clock.getElapsedTime().asMicroseconds();
        delta_time = (float) (__curr_time - __time_old) / 1000000;        // In seconds
        __time_old = __curr_time;
        //---------------------------------------------------------

        UE.getCommandUsers ();
        PE.SetLocaleChanges ();
        PE.SetInteractionOutside ();
        VE.draw ();

        if (StoryLine) {
            printf ("STORYLINE: %d\n", StoryLine);
            if (StoryLine == 1) {
                //PE.DUMP ();
                size = 0;
                content = readfile (path, &size);
                long sum = get_hash_sum (content, size);

                if (content == nullptr || sum != _HASH_SUM) {   // Blue screen of death
                    background.View.sprite = sf::Sprite (texture_blue_screen);
                    background.View.sprite.setScale ((float) WIDTH  / texture_blue_screen.getSize().x,
                                                     (float) HEIGHT / texture_blue_screen.getSize().y);
                    sound.resetBuffer ();
                    sound.setBuffer (SoundBBS);

                    VE.visOff (box.Visual.BufNum);
                    VE.visOff (cat.View.BufNum);

                    sound.setLoop (false);
                    sound.play ();
                    VE.draw ();

                    sleep (2);

                    break;

                } else {
                    StoryLine = 0;

                    sound.resetBuffer ();
                    sound.setBuffer (SoundBBG_crack_file);
                    sound.setVolume (35);
                    sound.play ();

                    cat.View.sprite.setTexture(texture_lcat);
                    background.View.sprite.setTexture(texture_art);
                    background.View.sprite.setPosition(0, 0);

                    background.View.sprite.setScale((float) WIDTH / texture_art.getSize().x,
                                                    (float) HEIGHT / texture_art.getSize().y);

                    PE.physOff (box.Model.BufNum);
                    VE.visOff(box.Visual.BufNum);

                    PE.add ((pe::Physobj *) &(shield.Model));
                    VE.add ((ve::Visobj  *) &(shield.Visual));

                }
            } else if (StoryLine == 2) {
                StoryLine = 0;
                if (crackSerg(content, size))
                    printf("Crack!\n");

                writefile(path_out, content, size);

                free(content);

                VE.visOff  (shield.Visual.BufNum);
                PE.physOff (shield.Model.BufNum);

                background.View.sprite.setTexture (texture_end_art);
                background.View.sprite.setPosition (0, 0);

                background.View.sprite.setScale ((float) WIDTH / texture_art.getSize().x,
                                                (float) HEIGHT / texture_art.getSize().y);

                sound_miau.setBuffer (SoundBMiau);
                sound_miau.setLoop (false);
                sound_miau.play ();
            }

        }
    }

    return 0;
}

#undef AUDIO_BLUE_SCREEN
#undef TEXTURE_FILE_CAT
#undef TEXTURE_FILE_LCAT
#undef TEXTURE_FILE_ART
#undef TEXTURE_OPEN_FILE
#undef _HASH_SUM

/*printf("Program started\n");
    char path[] = "../crack/THIS.COM";
    char path_out[] = "../crack/CRACK.COM";

    long size = 0;
    char *content = readfile(path, &size);
    long sum = get_hash_sum(content, size);

    printf("content: \t%p\nsize:\t\t%ld\nsum:\t\t%ld\n",
           content, size, sum);

    if (crackSerg(content, size))
        printf("Crack!\n");

    writefile(path_out, content, size);

    free(content);*/