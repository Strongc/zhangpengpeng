// Tetris '(zhangpengpeng 2013/10/21)
// rocflyhi(at)gmail.com

#define WORLD_HEIGHT	15
#define WORLD_WIDTH		10
#define SIDE_LEN		4

#define COLOR_BLANK		0
#define COLOR_RED		1
#define COLOR_YELLOW	2
#define COLOR_GREEN		3
#define COLOR_BLUE		4

#define TETRIS_STATE_NORMAL		0x0000
#define TETRIS_STATE_DROPPEN	0x0001
#define TETRIS_STATE_VANISH		0x0010
#define TETRIS_STATE_OVER		0x0100

#ifdef TETRIS_CORE		// tetris core call externel
int draw_one_block(int x, int y, int color);
int random(int range);
#else		// external call tetris core
int tetris_init_all();
int tetris_rotate();
int tetris_h_move(int LR);
int tetris_one_step();
int tetris_get_next_sharp(int *color, const int(**form)[SIDE_LEN][SIDE_LEN]);
int tetris_get_scores();
#endif
