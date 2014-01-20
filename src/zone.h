//
// zone.h
//

struct tile;
struct zone;

#ifndef ZONE_H
#define ZONE_H

#define TILE_MAX_WEIGHT 1000

#include "creature.h"
#include "inventory.h"

typedef struct tile {
	int impassible;//whether the tile is pasible or not
	struct creature * crtr;//creture that may be on the tile
	struct inventory * inv;//inventory of the tile
} tile;

typedef struct zone {//creates azone with a width and height
	int width, height;//width and height of zone
	tile ** tiles;//array of tiles in the zone
} zone;

zone * zone_new(int, int);//pointer to a new zone struct 
void zone_free(zone *);//deletes the zone
void zone_update(zone *, int, int);//updates the zones: re-adjust where the creatures and items are
void zone_draw(zone *);//redraws the updated zone
tile * zone_at(zone *, int, int);//returns the the thing at a particular tile
void zone_step(zone *, int);//moves creature to a different zone I think?

#define tileof(O) (&(O)->z->tiles[(O)->x][(O)->y])

#endif
