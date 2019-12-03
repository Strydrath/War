#ifndef gamemechanics
#define gamemechanics
#include "view.h"


void initTab(card* tab, int SIZE);
void init(deck* cards);
void fill(deck* cards, card tab[], int start, int end);
int UltimatePower(deck* hand) ;
void addCard(card* item, deck* cards);
card* pullCard(deck* deck);
void movePointer(deck* cards);
void simpledraw(deck* deck);
int trybB(int* testB, deck* giver, deck* taker, deck* tableTaker, char giverName, char* win, int limit);
int random(char* win, deck* Hand1, deck* Hand2, deck* Next1, deck* Next2, deck* Table1, deck* Table2, char player);
void Shuffle(card talia[], int SIZE);
char Battle(deck*TableA, deck*TableB);
void Battlewin(deck* Winner, deck* TableWinner, deck* TableLooser);
void FindEnd(deck* Cards);
int Count(deck deck);
void WarWin(deck* Winner, deck* TableWinner, deck* TableLooser, int* test);
char War(deck* HandA, deck* HandB, char tryb, float *moves,int show);
void experiment1();
char SmartWar (deck* HandA, deck* HandB,float *moves, char tryb,char Tactic1, char Tactic2, int show);
void SmartExperiment1();
void FreeHand(deck*Hand);
#endif