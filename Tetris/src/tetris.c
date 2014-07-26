// Tetris '(zhangpengpeng 2013/10/21)
// rocflyhi(at)gmail.com

#include "tetris.h"

extern const BlocksSharpType all_sharp_types[];
static Block theWorld[WORLD_HEIGHT][WORLD_WIDTH];
static int next_sharp = -1;
static int theScores = 0;
static BlocksSharp theSharp;

/*
		-> j y
	i x	|
		\/ 
	[i x height][j y width]
*/

int tetris_init_all()
{
	int i, j;
	for (i = 0; i < WORLD_HEIGHT; i++)
	{
		for (j = 0; j < WORLD_WIDTH; j++)
		{
			theWorld[i][j].color = COLOR_BLANK;
			theWorld[i][j].state = BLANK;
		}
	}

	theScores = 0;
	next_sharp = random(SHARP_NUM);
	tetris_new_drop();
	return 0;
}

void tetris_refresh_sharp(int action)
{
	int i, j;
	for (i = 0; i < SIDE_LEN; i++)
	{
		for (j = 0; j < SIDE_LEN; j++)
		{
			Block *bk = &(theWorld[theSharp.x + i][theSharp.y + j]);
			if (theSharp.type->form[i][j])
			{
				if (action == 0)		// erase sharp
				{
					bk->color = COLOR_BLANK;
					draw_one_block(theSharp.x + i, theSharp.y + j, COLOR_BLANK);
				}
				else if (action == 1)	// repaint sharp
				{
					bk->color = theSharp.type->color;
					draw_one_block(theSharp.x + i, theSharp.y + j, bk->color);
				}
				else if (action == 2)	// copy sharp to world
				{
					bk->state = FILLED;
				}
			}
		}
	}
}

int tetris_is_illegal(BlocksSharp *bs)
{
	int i, j;
	for (i = 0; i < SIDE_LEN; i++)
	{
		for (j = 0; j < SIDE_LEN; j++)
		{
			if (bs->type->form[i][j])
			{
				// is cross the border
				if (bs->x + i < 0 || bs->x + i >= WORLD_HEIGHT)
					return 1;
				if (bs->y + j < 0 || bs->y + j >= WORLD_WIDTH)
					return 1;

				// is overlap
				if (theWorld[bs->x + i][bs->y + j].state == FILLED)
					return 1;
			}
		}
	}
	return 0;
}

int tetris_new_drop()
{
	int is_over = 0;
	theSharp.type = &(all_sharp_types[next_sharp]);
	theSharp.y = WORLD_WIDTH / 2 - SIDE_LEN / 2;
	theSharp.x = 0;

	next_sharp = random(SHARP_NUM);
	is_over = tetris_is_illegal(&theSharp);
	tetris_refresh_sharp(1);

	if (is_over)
		return 2;
	return 0;
}

int tetris_try_vanish()
{
	int i, j, k;
	int is_vanish = 0;
	int vanished[SIDE_LEN] = {-1, -1, -1, -1};
	for (i = 0; i < SIDE_LEN; i++)
	{
		int is_full = 1;
		for (j = 0; j < WORLD_WIDTH; j++)
		{
			if (theWorld[theSharp.x + i][j].state != FILLED)
			{
				is_full = 0;
				break;
			}
		}

		if (is_full)	// vanish
		{
			is_vanish = 1;
			for (j = 0; j < WORLD_WIDTH; j++)
				draw_one_block(theSharp.x + i, j, COLOR_BLANK);
			vanished[i] = theSharp.x + i;
			theScores += WORLD_WIDTH;
		}
	}

	if (is_vanish == 0)
		return 0;

	// move upper blocks down
	for (i = 0; i < SIDE_LEN; i++)
	{
		if (vanished[i] == -1)
			continue;

		for (k = vanished[i]; k > 0; k--)
		{
			for (j = 0; j < WORLD_WIDTH; j++)
			{
				theWorld[k][j] = theWorld[k - 1][j];
				draw_one_block(k, j, theWorld[k][j].color);
			}
		}

		for (j = 0; j < WORLD_WIDTH; j++)
		{
			theWorld[0][j].color = COLOR_BLANK;
			theWorld[0][j].state = BLANK;
			draw_one_block(0, j, COLOR_BLANK);
		}
	}
				
	return is_vanish;
}

int tetris_rotate()
{
	BlocksSharp new_sharp = theSharp;
	new_sharp.type = &(all_sharp_types[theSharp.type->next]);

	if (tetris_is_illegal(&new_sharp) == 0)
	{
		tetris_refresh_sharp(0);
		theSharp.type = new_sharp.type;
		tetris_refresh_sharp(1);
		return 1;
	}
	return 0;
}

int tetris_h_move(int LR)
{
	BlocksSharp new_sharp = theSharp;
	if (LR == 0)	// left
		new_sharp.y--;
	else			// right
		new_sharp.y++;

	if (tetris_is_illegal(&new_sharp) == 0)
	{
		tetris_refresh_sharp(0);
		theSharp.y = new_sharp.y;
		tetris_refresh_sharp(1);
		return 1;
	}
	return 0;
}

int tetris_one_step()
{
	int ret = TETRIS_STATE_NORMAL;

	BlocksSharp new_sharp = theSharp;
	new_sharp.x++;
	if (tetris_is_illegal(&new_sharp))
	{
		tetris_refresh_sharp(2);
		ret |= TETRIS_STATE_DROPPEN;
		if (tetris_try_vanish())
			ret |= TETRIS_STATE_VANISH;
		if (tetris_new_drop() == 2)
			ret |= TETRIS_STATE_OVER;
	}
	else
	{
		// sharp move down
		tetris_refresh_sharp(0);
		theSharp.x++;
		tetris_refresh_sharp(1);
	}

	return ret;
}

int tetris_get_next_sharp(int *color, const int(**form)[SIDE_LEN][SIDE_LEN])
{
	if (color == 0 || form == 0)
		return -1;

	*color = all_sharp_types[next_sharp].color;
	*form = all_sharp_types[next_sharp].form;
	return 0;
}

int tetris_get_scores()
{
	return theScores;
}

const BlocksSharpType all_sharp_types[] = {
	{0, COLOR_RED, 0, {
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0} }},

	{1, COLOR_YELLOW, 2, {
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{2, COLOR_YELLOW, 1, {
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0} }},
			
	{3, COLOR_GREEN, 4, {
			{0, 1, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{4, COLOR_GREEN, 5, {
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0} }},
	{5, COLOR_GREEN, 6, {
			{1, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{6, COLOR_GREEN, 3, {
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0} }},

	{7, COLOR_BLUE, 8, {
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{8, COLOR_BLUE, 9, {
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0} }},
	{9, COLOR_BLUE, 10, {
			{0, 1, 1, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{10, COLOR_BLUE, 7, {
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0} }},

	{11, COLOR_RED, 12, {
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0} }},
	{12, COLOR_RED, 11, {
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 0} }},

	{13, COLOR_YELLOW, 14, {
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 0, 0} }},
	{14, COLOR_YELLOW, 13, {
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0} }},

	{15, COLOR_GREEN, 16, {
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0} }},
	{16, COLOR_GREEN, 17, {
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0} }},
	{17, COLOR_GREEN, 18, {
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0} }},
	{18, COLOR_GREEN, 15, {
			{0, 1, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 0, 0} }}
};
