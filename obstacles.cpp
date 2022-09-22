#include "splashkit.h"
#include "power_up.h"
#include "terminal_user_input.h"
#include "player.h"
#include "obstacles.h"
#include <string>

/**
 * The bitmap function converts an obstacle kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of obstacle you want the bitmap of
 * @return      The bitmap matching this obstacle kind
 */
bitmap obstacle_bitmap(obstacle_kind kind)
{
    switch (kind)
    {
    case ASTEROID:
        return bitmap_named("asteroid");
    case METEOR:
        return bitmap_named("meteor");
    case ALIEN:
        return bitmap_named("alien");
    case COMET:
        return bitmap_named("comet");
    default:
        break;
    }
}

obstacle_data new_obstacle(player_data &player, double x, double y)
{
    obstacle_data result;

    if (player.kind == GLIESE)
    {
        if (player.score >= 1000)
        {
            result.kind = static_cast<obstacle_kind>(0);
        }
    }

    if (player.kind == AQUARII)
    {
        if (player.score >= 1000 and player.score < 2000)
        {
            result.kind = static_cast<obstacle_kind>(0);
        }

        if (player.score >= 2000 and player.score < 3000)
        {
            result.kind = static_cast<obstacle_kind>(rnd(2));
        }

        if (player.score >= 3000 and player.score < 4000)
        {
            result.kind = static_cast<obstacle_kind>(rnd(3));
        }

        if (player.score >= 4000 and player.score < 5000)
        {
            result.kind = static_cast<obstacle_kind>(rnd(4));
        }
    }

    // Creates the obstacle sprite by selecting an obstacle based off the level of game play and game difficulty //
    result.obstacle_sprite = create_sprite(obstacle_bitmap(result.kind));

    // Positions the obstacle at the indicated (x,y) location //
    sprite_set_x(result.obstacle_sprite, (x));
    sprite_set_y(result.obstacle_sprite, (y));

    // Gives obstacle a velocity by changing its x, or x and y values //
    if (result.kind != COMET and result.kind != METEOR)
    {
        sprite_set_dx(result.obstacle_sprite, rnd() * 4 - 2); 
    }

    if (result.kind == METEOR)
    {
        sprite_set_dx(result.obstacle_sprite, rnd() * 10 - 1); 
    }

    if (result.kind == COMET)
    {
        sprite_set_dx(result.obstacle_sprite, -5); 
        sprite_set_dy(result.obstacle_sprite, 5); 
    }

    return result;
}

void draw_obstacle(const obstacle_data &obstacle_to_draw)
{
    draw_sprite(obstacle_to_draw.obstacle_sprite);
}


void update_obstacle(obstacle_data &obstacle_to_update)
{
    update_sprite(obstacle_to_update.obstacle_sprite);

    // gets obstacle position
    point_2d sprite_pos = sprite_position(obstacle_to_update.obstacle_sprite);

    // tests left/right game boundaries
    if (sprite_pos.x < MIN)
    {
        sprite_set_x(obstacle_to_update.obstacle_sprite, MIN);
    }
    else if (sprite_pos.x > MAX)
    {
        sprite_set_x(obstacle_to_update.obstacle_sprite, MAX);
    }

    // tests top/bottom game boundaries
    if (sprite_pos.y < MIN)
    {
        sprite_set_y(obstacle_to_update.obstacle_sprite, MIN);
    }
    else if (sprite_pos.y > MAX)
    {
        sprite_set_y(obstacle_to_update.obstacle_sprite, MAX);
    }
}