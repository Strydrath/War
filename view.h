#ifndef view
#define view
typedef struct card {
	int power;
	int color;
	card* next;
} card;
typedef struct deck {
	card* first;
	card* pointer;
} deck;

void textcolor(int color, int bg);
void ChangePosition(int column, int line);
void Draw(card* Card, int x, int y);
void DrawBattle (card* A, card*B);
void DrawBack(int x, int y);
void DrawWar (card* A, card* B, int x, int y);
#endif