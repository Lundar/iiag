#ifndef PACKET_H
#define PACKET_H
#include "../creature.h"
#include "../zone.h"
#include "../world.h"
#include "net.h"
#include "../item.h"

typedef struct packet_header packet_header;
typedef struct spawn_packet spawn_packet;
typedef struct command_packet command_packet;
typedef struct tile_packet tile_packet;
typedef struct creature_subpacket creature_subpacket;
typedef struct item_subpacket item_subpacket;

struct packet_header{
	short type;
	short length;
};

struct spawn_packet{
	//arbitrary data for now, class data later?
	char data[32];
};

extern int net_inv_prompt_data;
extern short net_dir_prompt;
struct command_packet{
	int c;
	int i;
	short d;
};

struct item_subpacket{

	int iclass;
	int mat;
	int quality;
	int tile;
	short type;

	int weight; // in 1/100ths of pounds
	int spikiness;

	// consumable-specific data
	int restore_health;
	int restore_stamina;

	// equipable-specific data
	int modify_attack;
	int modify_ac;
	int durability;
	int slot;

	//id for serialization
	//int gen_id;

};

struct creature_subpacket{

	//id for serialization
	int gen_id;
	int x,y;
	int ai;

	// item fields
	int item_num;
	//inventory * inv;
	//item * slots[MAX_SLOTS];
	int slots[MAX_SLOTS];

	// level/xp
	int level;
	int xp, need_xp;

	// skills and stats
	int health, stamina;
	int max_health, max_stamina;
	int attack;
	int ac;
	int sight;
	int reflex;
	int throw;
	int speed;
	int stance;

};

struct tile_packet{
	int tile, show_tile;
	int itemnum;
	short crtr;
	int impassible;
	int object_type;
	int x,y;
};


short encode_dir(int x,int y);
void  decode_dir(short d,int*x,int*y);

creature_subpacket* make_crtr_subpacket(creature* c);
item_subpacket* make_item_subpacket(item* c);

void write_spawn_packet(int sock);
void write_command_packet(int sock, int c);
void write_tile_packet(int sock, tile* t, int x, int y);
void write_player_packet(int sock, creature* c);
void write_time_packet(int sock, world_time_t* t);
void write_zone_packet(int sock, char * c);
void write_memo_packet(int sock, char * c);

void handle_spawn(socket_node* s,void* pack, int len);
void handle_command(socket_node* s,void* pack, int len);
void handle_tile(socket_node* s,void* pack, int len);
void handle_player(socket_node* s,void* pack, int len);
void handle_time(socket_node* s,void* pack, int len);
void handle_zone(socket_node* s,void* pack, int len);
void handle_memo(socket_node* s,void* pack, int len);

#define PACKET_HANDLERS_SIZE 7
void (*packet_handlers[PACKET_HANDLERS_SIZE])(socket_node* s, void* pack, int len);

#endif
