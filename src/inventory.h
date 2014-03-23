//
// inventory.h
//

struct inventory;

#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include "creature.h"

#define INFINITE (-1)
#define INVALID  (-1)

typedef struct inventory {
	int size;
	int weight;
	int max_weight;
	struct item ** itms;
} inventory;

//
// Allocates a new, empty inventory
// Takes the max weight (can be INFINITE)
// Should be freed with inv_free
//
inventory * inv_new(int);

//
// Frees an inventory created with inv_new
//
void inv_free(inventory *);

//
// Adds an item to an inventory
// Returns index on success, INVALID on failure
//
int inv_add(inventory *, struct item *);

//
// Sees if an item will fit in inventory
// Returns 1 on success, 0 on failure
//
int inv_try(inventory *, struct item *);

//
// Removes an item at a given index from an inventory
//
struct item * inv_rm(inventory *, int);

//
// Will display the inventory an prompt, and return the item selected by the user
//
int inv_prompt(const char *, inventory *, struct creature *);

//
// These 2 functions convert between indicies and character representations of
//   said integers.
//
// Mappings:
//   a-z <-> 0-25
//   A-Z <-> 26-51
//   0-9 <-> 52-61
//
char ind2ch(int);
int  ch2ind(char);

#endif
