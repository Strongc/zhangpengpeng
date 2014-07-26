// Tetris '(zhangpengpeng 2013/10/21)
// rocflyhi(at)gmail.com

#define TETRIS_CORE
#include "sysLayer.h"

#define SHARP_NUM		19

typedef struct _st_Block {
	enum {BLANK, FILLED, SHARP} state;
	int color;
}Block;

typedef struct _st_BlocksSharpType {
	int id;		// sub-index
	int color;
	int next;
	int form[SIDE_LEN][SIDE_LEN];
}BlocksSharpType;

typedef struct _st_BlocksSharp{
	const BlocksSharpType *type;
	int x;
	int y;
}BlocksSharp;

void tetris_refresh_sharp(int action);	// action: 0 erase sharp, 1 repaint sharp, 2 copy charp to world
int tetris_is_illegal(BlocksSharp *bs);
int tetris_new_drop();
int tetris_try_vanish();

// for external calling
int tetris_init_all();
int tetris_rotate();
int tetris_h_move(int LR);		// LR:0 Left, 1 right
int tetris_one_step();			// ret:TETRIS_STATE_x
int tetris_get_next_sharp(int *color, const int(**form)[SIDE_LEN][SIDE_LEN]);
int tetris_get_scores();
