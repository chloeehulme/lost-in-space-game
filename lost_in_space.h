#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "terminal_user_input.h"
#include "power_up.h"
#include "player.h"
#include "obstacles.h"
#include "levels.h"
#include <vector>

using namespace std;
using std::vector;

/**
 * The game data keeps track of all of the information related to the game itself.
 * 
 * @field   player       The data for the player.
 * @field   power_ups    The data for the power ups.
 * @field   obstacles    The data for the obstacles.
 */
struct game_data
{
   player_data player;
   vector<power_up_data> power_ups;
   vector<obstacle_data> obstacles;
};

/**
 * Creates a new game and loads a new player.
 * 
 * @returns     The new game data
 */
game_data new_game();

/**
 * Actions a step update of the game.
 * 
 * @param game      The game being updated
 */
void update_game(game_data &game);

/**
 * Draws the game to the screen. 
 * 
 * @param game    The game to draw to the screen
 */
void draw_game(const game_data &game);

/**
 * Adds a random power up to the screen. 
 * 
 * @param game    The game the power up is added to
 */
void add_power_up(game_data &game);

/**
 * Checks if player has hit power up. 
 * 
 * @param game    The game the the collision occured in
 */
void check_collisions(game_data &game);

/**
 * Removes power up from game. 
 * 
 * @param game    The game the power up is removed from
 * @param index   The index of power up in power up array
 */
void remove_power_up(game_data &game, int index);

/**
 * Applies power up collected to player. 
 * 
 * @param game    The game the power up is applied to
 * @param index   The index of power up in power up array
 */
void apply_power_up(game_data &game, int index);

/**
 * Adds an obstacle to the screen. 
 * 
 * @param game    The game the obstacle is added to
 */
void add_obstacle(game_data &game);

/**
 * Removes obstacle from game. 
 * 
 * @param game    The game the obstacle is removed from
 * @param index   The index of obstacle in obstacle array
 */
void remove_obstacle(game_data &game, int index);

/**
 * Checks if player has hit obstacle. 
 * 
 * @param game    The game the the collision occured in
 */
void check_damage(game_data &game);

/**
 * Applies damage to player. 
 * 
 * @param game    The game the obstacle is applied to
 * @param index   The index of obstacle in obstacle array
 */
void apply_damage(game_data &game, int index);

/**
 * Gets mini map coordinates of power up sprite. 
 * 
 * @param power_up    The power up coordinates are being found for
 */
point_2d mini_map_coordinate(const power_up_data &power_up);

/**
 * Gets mini map coordinates of obstacle sprite. 
 * s
 * @param obstacle    The obstacle coordinates are being found for
 */
point_2d mini_map_obstacle(const obstacle_data &obstacle);

/**
 * Draws pixel to scaled coordinates of power ups on mini map. 
 * 
 * @param power_ups    The power up being drawn
 */
void draw_mini_map(const vector<power_up_data> &power_ups);

/**
 * Gets mini map coordinates of player sprite. 
 * 
 * @param power_up    The player coordinates are being found for
 */
point_2d mini_map_player(const player_data &player);

/**
 * Draws pixel to scaled coordinates of player on mini map. 
 * 
 * @param player    The player being drawn
 */
void draw_mini_player(const player_data &player);

/**
 * Draws pixel to scaled coordinates of obstacle on mini map. 
 * 
 * @param obstacle    The obstacle being drawn
 */
void draw_mini_obstacle(const vector<obstacle_data> &obstacle);

/**
 * Draws a control menu on the screen that shows the user the game controls. 
 */
void control_menu();

void game_over(const player_data &player);

/**
 * Draws the current level menu on the screen that shows the user the level characteristics. 
 */
void level_menu(const player_data &player);

/**
 * Allows the user to trade coins for health or fuel. 
 * 
 * @param player    The player trading items.
 */
void buy_extra(player_data &player);

#endif