// Gluttonous Snake '(zhangpengpeng 2013/09/08)
// rocflyhi(at)gmail.com

#include "snake.h"
#include <stdio.h>

Snake theSnake;
Food theFood;
World theWorld;

int snake_init_all()
{
	int x, y;
	for (y = 0; y < WORLD_HEIGHT; y++)
		for (x = 0; x < WORLD_WIDTH; x++)
			theWorld.tile_type[x][y] = TILE_TYPE_EMPTY;
	theWorld.lens[TILE_TYPE_EMPTY] = WORLD_HEIGHT * WORLD_WIDTH;
	theWorld.lens[TILE_TYPE_WALL] = 0;
	theWorld.lens[TILE_TYPE_SNAKE] = 0;
	theWorld.lens[TILE_TYPE_FOOD] = 0;

	theSnake.bodys[0].x = WORLD_WIDTH / 2;
	theSnake.bodys[0].y = WORLD_HEIGHT / 2;
	theSnake.len = 1;
	theSnake.drc = SNAKE_DRC_UP;
	world_update(theSnake.bodys[0].x, theSnake.bodys[0].y, TILE_TYPE_SNAKE);

	food_create_one(&theFood);

	return 1;
}

int world_update( int x, int y, int type )
{
	theWorld.lens[theWorld.tile_type[x][y]]--;
	theWorld.lens[type]++;
	theWorld.tile_type[x][y] = type;
	draw_one_node(x, y, type);
	return 1;
}

int node_movenext_by_drc(Node *nd, int drc)
{
	switch (drc)
	{
	case SNAKE_DRC_UP:
		nd->y--;
		break;
	case SNAKE_DRC_DOWN:
		nd->y++;
		break;
	case SNAKE_DRC_RIGHT:
		nd->x++;
		break;
	case SNAKE_DRC_LEFT:
		nd->x--;
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

int snake_try_eat_food(Snake *snk, Food **fd)
{
	int ret = 0;
	Node next_node = snk->bodys[0];
	if (node_movenext_by_drc(&next_node, snk->drc))		// get next node loc
	{
		if (next_node.x == theFood.loc.x && next_node.y == theFood.loc.y)
		{
			*fd = &theFood;
			return 1;
		}
	}
	return 0;
}

int snake_check_before_move(Snake *snk)
{
	int i = 0;
	Node next_node = snk->bodys[0];

	// get next head loc
	if (node_movenext_by_drc(&next_node, snk->drc) == 0)
		return 0;

	// whether hit the wall
	if (next_node.x >= WORLD_WIDTH || next_node.y >= WORLD_HEIGHT \
		|| next_node.x < 0 || next_node.y < 0)
		return 0;

	// whether hit itself
	for (i = 0; i < snk->len - 2; i++)
	{
		if (next_node.x == snk->bodys[i].x && next_node.y == snk->bodys[i].y)
			return 0;
	}
	return 1;
}

int snake_move_drc(Snake *snk)
{
	int i = 0;
	Node redraw_node;

	// try to eat food first
	Food *eaten_food = NULL;	// for several food
	if (snake_try_eat_food(snk, &eaten_food) == 1)
	{
		snk->len++;
		for (i = snk->len - 1; i > 0; i--)	// move bodys
			snk->bodys[i] = snk->bodys[i - 1];
		snk->bodys[0] = eaten_food->loc;
		redraw_node = eaten_food->loc;
		world_update(redraw_node.x, redraw_node.y, TILE_TYPE_SNAKE);
		return SNAKE_STATE_EATEN_FOOD;
	}

	// redraw the tail 
	redraw_node = snk->bodys[snk->len - 1];
	world_update(redraw_node.x, redraw_node.y, TILE_TYPE_EMPTY);

	// move bodys
	for (i = snk->len - 1; i > 0; i--)
		snk->bodys[i] = snk->bodys[i - 1];

	// move head
	if (node_movenext_by_drc(&(snk->bodys[0]), snk->drc) == 0)
		return SNAKE_STATE_ERROR;

	// redraw the head
	redraw_node = snk->bodys[0];
	world_update(redraw_node.x, redraw_node.y, TILE_TYPE_SNAKE);

	return SNAKE_STATE_NORMAL;
}

int food_create_one(Food *fd)
{
	// get random loc
	int x, y;
	int empty_left = 0;
	int rd = 0;
	empty_left = theWorld.lens[TILE_TYPE_EMPTY];
	if (empty_left == 0)
		return 2;

	rd = random(empty_left);
	for (y = 0; y < WORLD_HEIGHT; y++)
	{
		for (x = 0; x < WORLD_WIDTH; x++)
		{
			if (theWorld.tile_type[x][y] != TILE_TYPE_EMPTY)
				continue;

			if (rd == 0)
			{
				fd->loc.x = x;
				fd->loc.y = y;
				world_update(x, y, TILE_TYPE_FOOD);
				return 1;
			}
			else
			{
				rd--;
			}
		}
	}

	return 0;
}

int snake_one_step()
{
	int ret = SNAKE_STATE_NORMAL;
	// check alive
	if (snake_check_before_move(&theSnake) == 0)
		return SNAKE_STATE_DIED;

	// move snake
	ret = snake_move_drc(&theSnake);
	if (ret == SNAKE_STATE_EATEN_FOOD)
	{
		if (food_create_one(&theFood) == 2)
			return SNAKE_STATE_SUCCESS;
	}

	return ret;
}

int snake_set_direction(int drc )
{
	if (theSnake.drc == drc)
		return 1;
	if (((theSnake.drc ^ drc ) & 0xF0) == 0x00)
		return 0;

	theSnake.drc = drc;
	return 1;
}
