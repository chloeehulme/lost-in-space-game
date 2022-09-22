#include "splashkit.h"
#include "terminal_user_input.h"
#include "power_up.h"
#include "player.h"
#include "lost_in_space.h"
#include "obstacles.h"
#include <string>
#include <vector>

using namespace std;
using std::vector;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    // initialise window and load resources //
    open_window("Lost In Space", 800, 800);
    load_resources();

    // draws the intro screen at the beginning of game //
    clear_screen(COLOR_BLACK);
    draw_bitmap("intro_screen", 0, 0);
    refresh_screen(60);
    delay(3000);

    // initialise new game //
    game_data game;
    game = new_game();

    // begins game play //
    while ( not quit_requested() ) 
    {   
        if (not sound_effect_playing("backing_music"))
        {
            play_sound_effect("backing_music", 1, 0.2);
        }
        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }   

    return 0;
}