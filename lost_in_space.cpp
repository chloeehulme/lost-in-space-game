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
 * Draws the heads up display in top left corner.
 */
void draw_hud(const player_data &player)
{
    // Draw the heads up display titled and background //
    fill_rectangle(COLOR_POWDER_BLUE, 0, 0, 370, 158, option_to_screen());
    fill_rectangle(rgb_color(0.098, 0.098, 0.439), 0, 0, 365, 153, option_to_screen());
    draw_text("SCORE: " + to_string(player.score), COLOR_WHITE, 0, 0, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(player.player_sprite)), COLOR_WHITE, 0, 30, option_to_screen());
    draw_text("FUEL: ", COLOR_WHITE, 0, 60, option_to_screen());
    draw_text("HEALTH: ", COLOR_WHITE, 0, 90, option_to_screen());
    draw_text("COINS: ", COLOR_WHITE, 0, 120, option_to_screen());
    draw_text("PRESS C FOR CONTROLS MENU", COLOR_WHITE, 0, 780, option_to_screen());
    draw_text("PRESS L FOR LEVEL GUIDE", COLOR_WHITE, 610, 780, option_to_screen());

    // Draws empty mini-map //
    draw_rectangle(COLOR_WHITE, 0, 165, 104, 104, option_to_screen());
    fill_rectangle(COLOR_BLACK, 2, 167, 100, 100, option_to_screen());  

    // Draws empty power up data //
    draw_bitmap("empty", 60, 45, option_to_screen());
    draw_bitmap("empty", 60, 75, option_to_screen());
    draw_bitmap("empty", 60, 105, option_to_screen());

    // Draws part-full power up data over empty bars drawn previously //
    draw_bitmap("full", 60, 45, option_part_bmp(0, 0, player.fuel_pct * bitmap_width("empty"), bitmap_height("empty"), option_to_screen()));
    draw_bitmap("red_bar", 60, 75, option_part_bmp(0, 0, player.health_bar * bitmap_width("empty"), bitmap_height("empty"), option_to_screen()));
    draw_bitmap("coin_bar", 60, 105, option_part_bmp(0, 0, player.coin_bar * bitmap_width("empty"), bitmap_height("empty"), option_to_screen()));
}

/**
 * Starts a new game.
 */
game_data new_game()
{
    game_data game;
    game.player = new_player();

    for (int i = 0; i < 6; i++)
    {
        game.power_ups.push_back(new_power_up(rnd(-1500, 1500), rnd(-1500, 1500), rnd(6)));
    }

    return game;
}

/**
 * Updates game data.
 */
void update_game(game_data &game)
{
    // Adjust player movement //
    process_events();

    // Perform movement and update the camera //
    update_player(game.player);
    
    // updates power ups and obstacles//
    for (int i = 0; i < game.power_ups.size(); i++ )
    {
        update_power_up(game.power_ups[i]);
    }

    for (int i = 0; i < game.obstacles.size(); i++ )
    {
        update_obstacle(game.obstacles[i]);
    }

    // randomly generates/removes power ups from game play //
    if (rnd() < 0.05)
    {
        add_power_up(game);
    }

    if (rnd() < 0.0005)
    {
        remove_power_up(game, rnd(game.power_ups.size()));
    }

    // randomly generates/removes obstacles from game play according to ship kind (game difficulty) //
    if (game.player.kind == AQUARII or game.player.kind == GLIESE)
    {
        if (game.player.score >= 1000)
        {
            if (rnd() < 0.03)
            {
                add_obstacle(game);
            }

            if (rnd() < 0.001)
            {
                remove_obstacle(game, rnd(game.obstacles.size()));
            }
        
            // applies damage and removes obstacle from screen if player hits it //
            check_damage(game);
        }
    }

    // applies power up and removes power up from screen if player collects it //
    check_collisions(game);

    // trades health or fuel for coins depending on user input //
    buy_extra(game.player);

    // generates a game over display when the user dies //
    if (game.player.health_bar == 0 or game.player.fuel_pct <= 0)
    {
        game_over(game.player);
    }
}

/**
 * Draws player, power up, and mini map data to screen.
 */
void draw_game(const game_data &game)
{
    // Redraw everything //
    clear_screen(COLOR_BLACK);
    draw_bitmap("star_background", 270, 150, option_scale_bmp(2.8, 2.8, option_to_screen()));

    // Draws the heads up display //
    draw_hud(game.player);
    draw_mini_map(game.power_ups);
    draw_mini_player(game.player);
    draw_mini_obstacle(game.obstacles);

    // brings up control/lebvel menu based on user input //
    if (key_down(C_KEY))
    {
        control_menu();
    }

    if (key_down(L_KEY))
    {
        level_menu(game.player);
    }

    // Redraw the player who can be moved by user, and power up that moves independently //
    draw_player(game.player);
    
    // draws power ups //
    for (int i = 0; i < game.power_ups.size(); i++ )
    {
        draw_power_up(game.power_ups[i]);
    }

    // draws obstacles based on ship kind (game difficulty) //
    if (game.player.kind == AQUARII or game.player.kind == GLIESE)
    {
        if (game.player.score >= 1000)
        {
            for (int i = 0; i < game.obstacles.size(); i++ )
            {
                draw_obstacle(game.obstacles[i]);
            }
        }
    }

    // draws a level up display when the user levels up //
    level_up(game.player);

    refresh_screen(60);
}

/**
 * Adds power up into game play.
 */
void add_power_up(game_data &game)
{
    game.power_ups.push_back(new_power_up(rnd(-1500, 1500), rnd(-1500, 1500), rnd(6)));
}

/**
 * Checks for sprite collisions between power up and player sprites.
 */
void check_collisions(game_data &game)
{
    for (int i = game.power_ups.size() - 1; i >= 0; i-- )
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[i].power_up_sprite))
        {
            apply_power_up(game, i);
            remove_power_up(game, i);
        }
    }
}

/**
 * Removes collected power up from game play.
 */
void remove_power_up(game_data &game, int index)
{
    for (int i = index; i < game.power_ups.size(); i++)
    {
        game.power_ups[i] = game.power_ups[i + 1];
        game.power_ups.pop_back();
    }
}

/**
 * Applies collected power up effects to player data.
 */
void apply_power_up(game_data &game, int index)
{  
    play_sound_effect("item_collect");
    if (game.power_ups[index].kind == FUEL)  // adds 25% to fuel bar //
    {
        if (game.player.fuel_pct + 0.25 < 1)
        {
            game.player.fuel_pct += 0.25;
        }
    }
    if (game.power_ups[index].kind == COIN)   // adds 10% to coin bar //
    {
        if (game.player.coin_bar + 0.1 < 1)
        {
            game.player.coin_bar += 0.1;
        }
    }
    if (game.power_ups[index].kind == HEART)  // adds 10% to health bar //
    {
        if (game.player.health_bar + 0.1 < 1)
        {
            game.player.health_bar += 0.1;
        }
    }
    if (game.power_ups[index].kind == DIAMOND)  // fills coin bar //
    {
        if (game.player.coin_bar < 1)
        {
            game.player.coin_bar = 1;
        }
    }
    if (game.power_ups[index].kind == LEVEL) // adds 100 to player score //
    {
        game.player.score += 100;
    }
    if (game.power_ups[index].kind == POTION) // fills health bar //
    {
        game.player.health_bar = 1;
    }
}

/**
 * Adds obstacle into game play.
 */
void add_obstacle(game_data &game)
{
    game.obstacles.push_back(new_obstacle(game.player, rnd(-1500, 1500), rnd(-1500, 1500)));
}

/**
 * Removes obstacle player has hit from game play.
 */
void remove_obstacle(game_data &game, int index)
{
    for (int i = index; i < game.obstacles.size(); i++)
    {
        game.obstacles[i] = game.obstacles[i + 1];
        game.obstacles.pop_back();
    }
}

/**
 * Checks for sprite collisions between obstacle and player sprites.
 */
void check_damage(game_data &game)
{
    for (int i = game.obstacles.size() - 1; i >= 0; i-- )
    {
        if (sprite_collision(game.player.player_sprite, game.obstacles[i].obstacle_sprite))
        {
            apply_damage(game, i);
            remove_obstacle(game, i);
        }
    }
}

/**
 * Applies pbstacle damage to player data.
 */
void apply_damage(game_data &game, int index)
{  
    if (game.obstacles[index].kind == ASTEROID or game.obstacles[index].kind == METEOR)  // - 10% from health bar //
    {
        game.player.health_bar -= 0.1;

        if (game.player.health_bar - 0.1 > 0)
        {
            play_sound_effect("ship_damage");
        }
    }

    if (game.obstacles[index].kind == ALIEN)  // stops ship movement for short time period and -15% fuel //
    {
        sprite_set_dx(game.player.player_sprite, 0);
        sprite_set_dy(game.player.player_sprite, 0);
        delay(1000);
        game.player.fuel_pct -= 0.15;

        if (game.player.fuel_pct - 0.15 > 0)
        {
            play_sound_effect("ship_damage");
        }
    }

    if (game.obstacles[index].kind == COMET)  // game over //
    {
        game.player.health_bar = 0;
    }
}

/**
 * Gets scaled down mini map coordinates of power up sprites.
 */
point_2d mini_map_coordinate(const power_up_data &power_up)
{
    float power_up_x = sprite_x(power_up.power_up_sprite);
    float power_up_y = sprite_y(power_up.power_up_sprite);

    double mini_map_x = ((power_up_x + 1500) / 3000 * 100 + 2);
    double mini_map_y = ((power_up_y + 1500) / 3000 * 100 + 167);

    point_2d mini_map_xy = point_at(mini_map_x, mini_map_y);

    return mini_map_xy;
}

/**
 * Gets scaled down mini map coordinates of obstacle sprites.
 */
point_2d mini_map_obstacle(const obstacle_data &obstacle)
{
    float obstacle_x = sprite_x(obstacle.obstacle_sprite);
    float obstacle_y = sprite_y(obstacle.obstacle_sprite);

    double mini_map_x = ((obstacle_x + 1500) / 3000 * 100 + 2);
    double mini_map_y = ((obstacle_y + 1500) / 3000 * 100 + 167);

    point_2d obstacle_xy = point_at(mini_map_x, mini_map_y);

    return obstacle_xy;
}

/**
 * Gets scaled down mini map coordinates of player sprite.
 */
point_2d mini_map_player(const player_data &player)
{
    float player_x = sprite_x(player.player_sprite);
    float player_y = sprite_y(player.player_sprite);

    double mini_player_x = ((player_x + 1500) / 3000 * 100 + 2);
    double mini_player_y = ((player_y + 1500) / 3000 * 100 + 167);

    point_2d mini_player_xy = point_at(mini_player_x, mini_player_y);

    return mini_player_xy;
}

/**
 * Draws player position on mini map.
 */
void draw_mini_player(const player_data &player)
{
    draw_pixel(COLOR_WHITE, mini_map_player(player), option_to_screen());
}

/**
 * Draws obstacle position on mini map.
 */
void draw_mini_obstacle(const vector<obstacle_data> &obstacle)
{
    for (int i = 0; i < obstacle.size(); i++)
    {
        draw_pixel(COLOR_GREEN, mini_map_obstacle(obstacle[i]), option_to_screen());
    }
}

/**
 * Draws power up position on mini map.
 */
void draw_mini_map(const vector<power_up_data> &power_ups)
{
    for (int i = 0; i < power_ups.size(); i++)
    {
        if (power_ups[i].kind == FUEL)
        {
            draw_pixel(rgba_color(0.999, 0.0001, 0.0001, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());
        }
        if (power_ups[i].kind == COIN)
        {
            draw_pixel(rgba_color(0.999, 0.999, 0.0001, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());  
        }
        if (power_ups[i].kind == HEART)
        {
            draw_pixel(rgba_color(0.999, 0.0001, 0.999, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());
        }
        if (power_ups[i].kind == DIAMOND)
        {
            draw_pixel(rgba_color(0.0001, 0.999, 0.999, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());
        }
        if (power_ups[i].kind == LEVEL)
        {
            draw_pixel(rgba_color(0.153, 0.05, 0.204, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());
        }
        if (power_ups[i].kind == POTION)
        {
            draw_pixel(rgba_color(0.098, 0.098, 0.439, 0.8), mini_map_coordinate(power_ups[i]), option_to_screen());
        }
    }
}

/**
 * Draws control menu.
 */
void control_menu()
{
    draw_bitmap("control_menu", 150, 150, option_to_screen());
}

/**
 * Draws level menu.
 */
void level_menu(const player_data &player)
{
    draw_bitmap(display_level(player), 150, 150, option_to_screen());
}

/**
 * Draws game over display.
 */
void game_over(const player_data &player)
{
    play_sound_effect("game_over");
    clear_screen(COLOR_BLACK);
    draw_bitmap("game_over", 0, 0, option_to_screen());
    draw_text("FINAL SCORE: " + to_string(player.score), COLOR_WHITE, 333, 375, option_to_screen());
    refresh_screen(60);
    delay(10000);
}

/**
 * Allows the user to trade a full coin bar for half health or half fuel bar according to user input.
 */
void buy_extra(player_data &player)
{
    if (key_typed(H_KEY) and player.coin_bar == 1)
    {
        if (player.health_bar + 0.5 <= 1)
        {
            player.health_bar += 0.5;
            player.coin_bar = 0;
        }
        else 
        {
            player.health_bar = 1;
            player.coin_bar = 0;
        }
    }
    if (key_typed(F_KEY) and player.coin_bar == 1)
    {
        if (player.fuel_pct + 0.5 <= 1)
        {
            player.fuel_pct += 0.5;
            player.coin_bar = 0;
        }
        else 
        {
            player.fuel_pct = 1;
            player.coin_bar = 0;
        }
    }
}