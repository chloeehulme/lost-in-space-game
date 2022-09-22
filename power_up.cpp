#include "splashkit.h"
#include "power_up.h"
#include "terminal_user_input.h"
#include "player.h"
#include "obstacles.h"
#include <string>

/**
 * The ship bitmap function converts a power up kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power up you want the bitmap of
 * @return      The bitmap matching this power up kind
 */
bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case FUEL:
        return bitmap_named("fuel");
    case COIN:
        return bitmap_named("coin");
    case HEART:
        return bitmap_named("heart");
    case DIAMOND:
        return bitmap_named("diamond");
    case LEVEL:
        return bitmap_named("level");
    case POTION:
        return bitmap_named("potion");
    default:
        break;
    }
}

power_up_data new_power_up(double x, double y, int type)
{
    power_up_data result; 
    result.kind = static_cast<power_up_kind>(type);

    // Creates the power up sprite by selecting a random power up
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));

    // Positions the power up at the indicated (x,y) location
    sprite_set_x(result.power_up_sprite, (x));
    sprite_set_y(result.power_up_sprite, (y));

    // Gives power up a small velocity by changing its x value
    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2); 

    return result;
}

void draw_power_up(const power_up_data &power_up_to_draw)
{
    draw_sprite(power_up_to_draw.power_up_sprite);
}

void update_power_up(power_up_data &power_up_to_update)
{
    update_sprite(power_up_to_update.power_up_sprite);

    // gets power up position
    point_2d sprite_pos = sprite_position(power_up_to_update.power_up_sprite);

    // tests left/right game boundaries
    if (sprite_pos.x < MIN)
    {
        sprite_set_x(power_up_to_update.power_up_sprite, MIN);
    }
    else if (sprite_pos.x > MAX)
    {
        sprite_set_x(power_up_to_update.power_up_sprite, MAX);
    }

    // tests top/bottom game boundaries
    if (sprite_pos.y < MIN)
    {
        sprite_set_y(power_up_to_update.power_up_sprite, MIN);
    }
    else if (sprite_pos.y > MAX)
    {
        sprite_set_y(power_up_to_update.power_up_sprite, MAX);
    }
}