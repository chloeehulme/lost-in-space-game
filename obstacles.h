#ifndef LOST_IN_SPACE_OBSTACLES
#define LOST_IN_SPACE_OBSTACLES

#include "splashkit.h"
#include "player.h"
#include <vector>

using namespace std;

#define MIN -1500
#define MAX 1500

/**
 * Different options for the kind of obstacle.
 * Adjusts the image used.
 */
enum obstacle_kind
{
    ASTEROID,
    METEOR,
    ALIEN,
    COMET
};

/**
 * The obstacle data keeps track of all of the information related to the obstacles.
 * 
 * @field   obstacle_sprite   The obstacle's sprite - used to track position and movement
 * @field   kind              The kind of obstacle 
 */
struct obstacle_data
{
    sprite      obstacle_sprite;
    obstacle_kind   kind;
};

/**
 * Creates a new obstacle in a random location on the screen.
 * 
 * @returns     The new obstacle data
 */
obstacle_data new_obstacle(player_data &player, double x, double y);

/**
 * Draws the obstacke to the screen. 
 * 
 * @param obstacle_to_draw    The obstacle to draw to the screen
 */
void draw_obstacle(const obstacle_data &obstacle_to_draw);

/**
 * Actions a step update of the obstacle.
 * 
 * @param obstacle_to_update      The obstacle being updated
 */
void update_obstacle(obstacle_data &obstacle_to_update);

#endif