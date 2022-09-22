#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

#define MIN -1500
#define MAX 1500

/**
 * Different options for the kind of power up.
 * Adjusts the image used.
 */
enum power_up_kind
{
    FUEL,
    COIN,
    HEART,
    DIAMOND,
    LEVEL,
    POTION
};

/**
 * The power up data keeps track of all of the information related to the power ups.
 * 
 * @field   power_up_sprite   The power up's sprite - used to track position and movement
 * @field   kind              The kind of power up 
 */
struct power_up_data
{
    sprite      power_up_sprite;
    power_up_kind   kind;
};

/**
 * Creates a new random power up in a random location on the screen.
 * 
 * @returns     The new power up data
 */
power_up_data new_power_up(double x, double y, int kind);

/**
 * Draws the power up to the screen. 
 * 
 * @param power_up_to_draw    The power up to draw to the screen
 */
void draw_power_up(const power_up_data &power_up_to_draw);

/**
 * Actions a step update of the power up - moving them and adjusting the camera.
 * 
 * @param power_up_to_update      The power up being updated
 */
void update_power_up(power_up_data &power_up_to_update);

#endif