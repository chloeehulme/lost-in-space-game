#include "splashkit.h"
#include "terminal_user_input.h"
#include "power_up.h"
#include "player.h"
#include "lost_in_space.h"
#include "obstacles.h"
#include "levels.h"
#include <string>
#include <vector>

using namespace std;
using std::vector;

/** 
* Global variables acting as a switch to display level up screen once only.
* If true, level up screen will display, if false, level up screen wont display.
*/
bool l_1 = true;
bool l_2 = true;
bool l_3 = true;
bool l_4 = true;
bool l_5 = true;

/**
 * The bitmap function converts an level into a 
 * bitmap that can be used as the level display.
 * 
 * Not exposed by the header.
 * 
 * @param level  The level of game play you want the bitmap of
 * @return       The bitmap matching this level number
 */
bitmap level_bitmap(level_num level)
{
    switch (level)
    {
    case LEVEL_ONE:
        return bitmap_named("level_one");
    case LEVEL_TWO:
        return bitmap_named("level_two");
    case LEVEL_THREE:
        return bitmap_named("level_three");
    case LEVEL_FOUR:
        return bitmap_named("level_four");
    case LEVEL_FIVE:
        return bitmap_named("level_five");
    default:
        break;
    }
}

bitmap display_level(const player_data &player)
{
    level_data display;

    // sets parameters so correct level displays according to player score/game difficulty //
    if (player.score < 1000 or player.kind == PEGASI)
    {
        display.level = static_cast<level_num>(0);
    }

    if (player.kind == GLIESE)
    {
        if (player.score >= 1000)
        {
            display.level = static_cast<level_num>(1);
        }
    }

    if (player.kind == AQUARII)
    {
        if (player.score >= 1000 and player.score < 2000)
        {
            display.level = static_cast<level_num>(1);
        }

        if (player.score >= 2000 and player.score < 3000)
        {
            display.level = static_cast<level_num>(2);
        }

        if (player.score >= 3000 and player.score < 4000)
        {
            display.level = static_cast<level_num>(3);
        }

        if (player.score >= 4000 and player.score < 5000)
        {
            display.level = static_cast<level_num>(4);
        }
    }
    
    // generates bitmap to draw as level display //
    display.level_bitmap = level_bitmap(display.level);

    return display.level_bitmap;
}

void level_up(const player_data &player)
{
    // sets parameters so the new level screen displays at correct time //
    if (player.score == 0)
    {
        // we use global variable as parameter so once it has been used once we can set it ot false and essentially //
        // 'turn off' this function after level screen displays //
        if (l_1)
        {
            clear_screen(COLOR_BLACK);
            draw_text("------- LEVEL 1 -------", COLOR_WHITE, 300, 350, option_to_screen());
            refresh_screen(60);
            delay(1500);
            draw_bitmap("level_one", 150, 150, option_to_screen());
            refresh_screen(60);
            delay(4000);
            l_1 = false;
        }
        draw_text("LEVEL 1", COLOR_WHITE, 730, 3, option_to_screen());
    }

// displays run according to player score and game difficulty //
    if (player.kind == AQUARII or player.kind == GLIESE)
    {
        if (player.score == 1000)
        {
            if (l_2)
            {
                clear_screen(COLOR_BLACK);
                play_sound_effect("level_up");
                draw_text("------- LEVEL 2 -------", COLOR_WHITE, 300, 350, option_to_screen());
                refresh_screen(60);
                delay(1500);
                draw_bitmap("level_two", 150, 150, option_to_screen());
                refresh_screen(60);
                delay(3000);
                l_2 = false;
            }
            draw_text("LEVEL 2", COLOR_WHITE, 730, 3, option_to_screen());
        }
    }

    if (player.kind == AQUARII)
    {
        if (player.score == 2000)
        {
            if (l_3)
            {
                clear_screen(COLOR_BLACK);
                play_sound_effect("level_up");
                draw_text("------- LEVEL 3 -------", COLOR_WHITE, 300, 350, option_to_screen());
                refresh_screen(60);
                delay(1500);
                draw_bitmap("level_three", 150, 150, option_to_screen());
                refresh_screen(60);
                delay(3000);
                l_3 = false;
            }
            draw_text("LEVEL 3", COLOR_WHITE, 730, 3, option_to_screen());
        }

        if (player.score == 3000)
        {
            if (l_4)
            {
                clear_screen(COLOR_BLACK);
                play_sound_effect("level_up");
                draw_text("------- LEVEL 4 -------", COLOR_WHITE, 300, 350, option_to_screen());
                refresh_screen(60);
                delay(1500);
                draw_bitmap("level_four", 150, 150, option_to_screen());
                refresh_screen(60);
                delay(3000);
                l_4 = false;
            }
            draw_text("LEVEL 4", COLOR_WHITE, 730, 3, option_to_screen());
        }

        if (player.score == 4000)
        {
            if (l_5)
            {
                clear_screen(COLOR_BLACK);
                play_sound_effect("level_up");
                draw_text("------- LEVEL 5 -------", COLOR_WHITE, 300, 350, option_to_screen());
                refresh_screen(60);
                delay(1500);
                draw_bitmap("level_five", 150, 150, option_to_screen());
                refresh_screen(60);
                delay(3000);
                l_5 = false;
            }
            draw_text("LEVEL 5", COLOR_WHITE, 730, 3, option_to_screen());
        }
    }
}