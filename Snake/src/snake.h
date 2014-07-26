// Gluttonous Snake '(zhangpengpeng 2013/09/08)
// rocflyhi(at)gmail.com

#define SNAKE_CORE
#include "sysLayer.h"

typedef struct _st_Node {
	int x;
	int y;
}Node;

typedef struct _st_Snake {
	Node bodys[SNAKE_MAX_LEN];
	int len;
	int drc;	// direction
	// enum { ALIVE, DIED }state;
}Snake;

typedef struct _st_Food {
	Node loc;
}Food;

typedef struct _st_World {
	int tile_type[WORLD_HEIGHT][WORLD_WIDTH];
	int lens[4];	// four tile type
}World;

int world_update(int x, int y, int type);
int node_movenext_by_drc(Node *nd, int drc);
int snake_try_eat_food(Snake *snk, Food **fd);	// return value: 1 eaten, 0 fail

int snake_check_before_move(Snake *snk);
int snake_move_drc(Snake *snk);					// return snake state
int food_create_one(Food *fd);

// for external to call
int snake_init_all();
int snake_one_step();							// return snake state
int snake_set_direction(int drc);