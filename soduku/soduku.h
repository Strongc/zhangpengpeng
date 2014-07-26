/* header file for soduku
   someting base
   '(zhangpengpeng 2011-1-20)
   include following:
   node structure
   */

enum enum_state{
	NONE,	/*do nothing */
	CAND, 	/*candidate*/
	ORIGIN,	/*origin value*/
	FIX		/*get it*/
};

typedef struct struct_sdkNode {
	int answer;		/* the answer */
	int cand[9];	/*1 to 9 who is candidate, 0 is not while 1 is.*/

	enum enum_state state;	/*state for this node*/
}SDKNODE;

/* base operations */
void initSoduku(SDKNODE soduku[9][9]);
void showSoduku(SDKNODE soduku[9][9]);
void copySoduku(SDKNODE soduku[9][9], int sdk[9][9]);

/* rules */
int checkRules(SDKNODE soduku[9][9]);
int rule1(SDKNODE soduku[9][9]);
int rule2(SDKNODE soduku[9][9]);
int rule3(SDKNODE soduku[9][9]);

/* ways to solve */
int wayViolent(SDKNODE soduku[9][9]);

