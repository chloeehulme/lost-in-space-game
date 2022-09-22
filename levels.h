#ifndef LOST_IN_SPACE_LEVELS
#define LOST_IN_SPACE_LEVELS

#include "splashkit.h"
#include "terminal_user_input.h"
#include "power_up.h"
#include "player.h"
#include "obstacles.h"
#include <vector>

using namespace std;
using std::vector;

/**
 * Different options for the level number.
 * Adjusts the image used.
 */
enum level_num
{
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE,
    LEVEL_FOUR,
    LEVEL_FIVE
};

/**
 * The level data keeps track of all of the information related to the level display.
 * 
 * @field   level      The level of game play. 
 */
struct level_data
{
    level_num   level;
    bitmap      level_bitmap;
};

/**
 * Generates a level display menu.
 * 
 * @returns     The level display menu
 */
bitmap display_level(const player_data &player);

/**
 * Generates a level up display when the user levels up.
 * 
 * @returns     The level up menu
 */
void level_up(const player_data &player);

#endif