//
// main.c
//

#include <lua.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "log.h"
#include "item.h"
#include "input.h"
#include "world.h"
#include "config.h"
#include "player.h"
#include "display.h"
#include "creature.h"
#include "inventory.h"
#include "lua/lua.h"
#include "commands.h"
#include "net/net.h"

extern command_t * command_list;
extern int num_commands;


static void sig_handler(int rc)
{
	end_disp();
	fprintf(stderr, "\nSignal %d caught.\n", rc);
	exit(rc);
}


int main(int argc, char ** argv)
{

	int step;
	int stall;

	init_config(argc, argv);
	init_lua();

	srandom(time(NULL));

	signal(SIGSEGV, sig_handler);
	signal(SIGINT,  sig_handler);

	//for the moment this is needed to make walls render properly
	//may be removed/fixed in the next major update.
	//this also seems to affect logging
	init_disp();
	init_world();


	step_world();
	setup_listener(config.port);

	for (;;) {
		start_timer();
		server_update_clients();
		step = world.tm.steps;

		while(abs(world.tm.steps - step) < 140){
			stall = world.tm.steps;
			step_world();
			if(stall == world.tm.steps) break;
			debug("Step %i %i", world.tm.steps, step);
		}

		try_accept();
		server_listen(server_sockets);
		end_timer("Step length");
		usleep(250000);

	}

	return 0;
}
