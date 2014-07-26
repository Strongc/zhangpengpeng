// Gluttonous Snake '(zhangpengpeng 2013/09/08)
// rocflyhi(at)gmail.com

#define WORLD_WIDTH		10
#define WORLD_HEIGHT	10
#define SNAKE_MAX_LEN	WORLD_WIDTH * WORLD_HEIGHT

#define SNAKE_DRC_UP	0x01
#define SNAKE_DRC_DOWN	0x02
#define SNAKE_DRC_RIGHT	0x11
#define SNAKE_DRC_LEFT	0x12

#define TILE_TYPE_EMPTY		0
#define TILE_TYPE_WALL		1
#define TILE_TYPE_SNAKE		2
#define TILE_TYPE_FOOD		3

#define SNAKE_STATE_NORMAL		0
#define SNAKE_STATE_ERROR		1
#define SNAKE_STATE_DIED		2
#define SNAKE_STATE_EATEN_FOOD	3
#define SNAKE_STATE_SUCCESS		4

#ifdef SNAKE_CORE	// snake call external
int draw_one_node(int x, int y, int type);
int random(int range);
#else // external call snake
int snake_init_all();
int snake_one_step();							// return snake state
int snake_set_direction(int drc);
#endif