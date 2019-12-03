#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <unistd.h>
#include <wchar.h>
#include <fcntl.h>
#include "view.h"
#include "gamemechanics.h"

typedef int (*tactic)(char*,deck*, deck*,deck*, deck*, deck*, deck*, char);
void initTab(card* tab, int SIZE) {

	for (int i = 0; i < SIZE; i++) {
		tab[i].power = 12 -(i % (SIZE / 4));
		tab[i].color = i / (SIZE / 4);
	}
}
void init(deck* cards) {
	cards->first = NULL;
	cards->pointer = NULL;
}
void fill(deck* cards, card tab[], int start, int end) {
		cards->first = (card*)malloc(sizeof(card));
	cards->first->power = tab[start].power;
	cards->first->color = tab[start].color;
	cards->first->next = (card*)malloc(sizeof(card));
	cards->pointer = cards->first->next;

	for (int i = start + 1; i < end; i++) {
		cards->pointer->power = tab[i].power;
		cards->pointer->color = tab[i].color;
		cards->pointer->next = (card*)malloc(sizeof(card));
		cards->pointer = cards->pointer->next;
	}
	cards->pointer = cards->first;
	for (int i = start + 1; i < end; i++) {
		cards->pointer = cards->pointer->next;
	}
	cards->pointer->next = NULL;
}
int UltimatePower(deck* hand) {
	int pwr = 0;
	hand->pointer = hand->first;
	while (hand->pointer != NULL) {
		pwr += hand->pointer->power;
		hand->pointer = hand->pointer->next;
	}
	hand->pointer = hand->first;
	return pwr;
}
void Shuffle(card talia[], int SIZE) {
	int n;
	time_t t;
	int limit = SIZE;
	card temp;
	card temp2;
	for (int i = 0; i < SIZE; i++) {
		n = rand() % limit;
		temp2 = talia[n];
		temp = talia[limit - 1];
		talia[limit - 1] = temp2;
		talia[n] = temp;
		limit--;
	}
}
void ShuffleWin(card* talia[], int SIZE) {
	int n;
	time_t t;
	int limit = SIZE;
	card* temp;
	card* temp2;
	for (int i = 0; i < SIZE; i++) {
		n = rand() % limit;
		temp2 = talia[n];
		temp = talia[limit - 1];
		talia[limit - 1] = temp2;
		talia[n] = temp;
		limit--;
	}
}
void FreeHand(deck*Hand){
	while(Hand->first!=NULL){
		card* next = Hand->first->next;
		free(Hand->first);
		Hand->first = next;
	}
}
void addCard(card* item, deck* cards) {
	//card* tmp = cards->pointer;
	if (cards->first == NULL) {
		item->next = NULL;
		cards->first = item;
		cards->pointer = cards->first;
	}
	else {
		cards->pointer = cards->first;
		while (cards->pointer->next != NULL) {
			cards->pointer = cards->pointer->next;
		}
		item->next = NULL;
		cards->pointer->next = item;
		cards->pointer = cards->first;
	}
}
card* pullCard(deck* deck) {
	card* tmp;
	tmp = deck->first;
	deck->first = deck->first->next;
	tmp->next = NULL;
	return tmp;
}
void movePointer(deck* cards) {
	cards->pointer = cards->pointer->next;
}
void simpledraw(deck* deck) {
	card* tmp = deck->pointer;
	deck->pointer = deck->first;
	while (deck->pointer != NULL) {
		printf("%d %d,", deck->pointer->power, deck->pointer->color);
		movePointer(deck);
	}
	deck->pointer = tmp;
}
int trybB(int* testB, deck* giver, deck* taker, deck* tableTaker, char giverName, char* win, int limit){
    if ((*testB) < limit) {
            addCard(pullCard(giver), tableTaker);
            (*testB)++;
            if (giver->first == NULL) {
                (*win) = giverName;
                return 1;
            }
        }
        else {
            (*win) = giverName;
            return 1;
        }
        return 0;
}
char Battle(deck*TableA, deck*TableB){
    char winner= 'R';
    if (TableA->pointer->power > TableB->pointer->power) {
        winner= 'A';
    }
    else if (TableA->pointer->power < TableB->pointer->power) {
        winner= 'B';
    }
    return winner;
}
void Battlewin(deck* Winner, deck* TableWinner, deck* TableLooser){
    addCard(pullCard(TableWinner), Winner);
    addCard(pullCard(TableLooser), Winner);
}
void FindEnd(deck* Cards){
    while (Cards->pointer->next != NULL) {
					Cards->pointer = Cards->pointer->next;
            }
}
int Count(deck deck) {
	int Count = 0;
	deck.pointer = deck.first;
	while (deck.pointer != NULL) {
		Count++;
		movePointer(&deck);
	}
	return Count;
}
void WarWin(deck* Winner, deck* TableWinner, deck* TableLooser, int* test){
    while (TableWinner->first != NULL) {
        addCard(pullCard(TableWinner), Winner);
    }
    while (TableLooser->first != NULL) {
        addCard(pullCard(TableLooser), Winner);
    }
    *test = 1;
}
void SmartWarWin(deck* Winner, deck* TableWinner, deck* TableLooser, int* test){
    card* all [52];
	int i=0;
	while (TableWinner->first != NULL) {
        all[i]=pullCard(TableWinner);
		i++;
    }
    while (TableLooser->first != NULL) {
		all[i]=pullCard(TableLooser);
		i++;
	}
	ShuffleWin(all,i);
	for(int j=0; j<i;j++){
		addCard(all[j],Winner);
	}
    *test = 1;
}
char War(deck* HandA, deck* HandB, char tryb, float *moves,int show) {
	deck A;
	deck B;
	deck* TableA = &A;
	deck* TableB = &B;
	init(TableA);
	init(TableB);
	char win = 'Z';
	int x;
	int y;
	while (HandA->first != NULL && HandB->first != NULL) {
        textcolor(0,0);
        system("cls");
		addCard(pullCard(HandA), TableA);
		addCard(pullCard(HandB), TableB);
		(*moves)++;
		TableA->pointer = TableA->first;
		TableB->pointer = TableB->first;
		if(show==1){
            textcolor(7,0);
            ChangePosition(6,3);
            printf("Player 1: %d", Count(*HandA));
            ChangePosition(24,3);
            printf("Player 2: %d", Count(*HandB));
            DrawBattle(TableA->first,TableB->first);
            Sleep(900);
		}
		if (TableA->first->power != TableB->first->power) {
			if(Battle(TableA,TableB)=='A'){
                Battlewin(HandA,TableA, TableB);
			}
			else if(Battle(TableA,TableB)=='B'){
                Battlewin(HandB,TableB, TableA);
			}
		}
		else {
			int test = 0;
			int testBa = 0;
			int testBb = 0;
			int koniecA = 0;
			int koniecB = 0;
			x= 10;
			y=5;
			while (test == 0) {
				if (HandA->first == NULL && HandB->first == NULL) {
					win = 'R';
					break;
				}
				if (HandA->first != NULL) {
					addCard(pullCard(HandA), TableA);
				}
				else {
					if (tryb == 'A') {
						break;
					}
					else if (tryb == 'B') {
						if (testBa == 0) {
							koniecA = 1;
						}
						else {
							win = 'B';
							break;
						}
					}
				}
				if (HandB->first != NULL) {
					addCard(pullCard(HandB), TableB);
				}
				else {
					if (tryb == 'A') {
						break;
					}
					else if (tryb == 'B') {
						if (testBb == 0) {
							koniecB = 1;
						}
						else {
							win = 'A';
							break;
						}
					}
				}

				if (koniecA == 1) {
					addCard(pullCard(HandB), TableA);
					testBa++;
					if (HandB == NULL) {
						win = 'B';
						break;
					}
				}
				if (koniecB == 1) {
					addCard(pullCard(HandA), TableB);
					testBb++;
					if (HandA == NULL) {
						win = 'A';
						break;
					}
				}

				if (HandA->first != NULL) {
					addCard(pullCard(HandA), TableA);
				}

				if (HandB->first != NULL) {
					addCard(pullCard(HandB), TableB);
				}
				if (HandA == NULL && testBb > 0) {
					win = 'A';
					break;
				}
				if (HandB == NULL && testBa > 0) {
					win = 'B';
					break;
				}
				if (HandA->first == NULL && HandB->first == NULL) {
					win = 'R';
					break;
				}
				if (koniecA == 1&&testBa<2) {
					addCard(pullCard(HandB), TableA);
					testBa++;
				}
				if (testBa >= 2) {
					win =  'A';
					break;
				}
				if (koniecB == 1 && testBb < 2) {
					addCard(pullCard(HandA), TableB);
					testBb++;
				}
				if (testBb >= 2) {
					win = 'B';
					break;
				}
				FindEnd(TableA);
				FindEnd(TableB);


				if(show==1){
                    textcolor(7,0);
                    ChangePosition(6,3);
                    printf("Player 1: %d", Count(*HandA));
                    ChangePosition(24,3);
                    printf("Player 2: %d", Count(*HandB));
                    DrawWar(TableA->pointer,TableB->pointer,x,y);
                    Sleep(700);
                    x=x+4;
                    y=y+4;
                }
				(*moves)++;
				if (TableA->pointer->power != TableB->pointer->power){
                    if(Battle(TableA, TableB)=='A'){
                        WarWin(HandA, TableA, TableB,&test);
                    }
                    else if(Battle(TableA, TableB)=='B'){
                        WarWin(HandB, TableB, TableA,&test);
                    }
				}
				if ((*moves) > 10000) {
					win='K';
					break;
				}
			}

		}

	}

	if (((HandA->first == NULL) && (HandB->first == NULL))&& win=='Z') {
		win= 'R';
	}
	else if (HandA->first == NULL && win == 'Z') {
		win= 'B';
	}
	else if (HandB->first == NULL && win == 'Z') {
		win = 'A';
	}
	else if(win == 'Z'){
		win = 'K';
	}
	if(show==1){
        textcolor(0,0);
        system("cls");
        ChangePosition(20,10);
        textcolor(7,0);
        if(win=='A'){
            printf("PLAYER 1 WON!!!");
        }
        else if(win=='B'){
            printf("PLAYER 2 WON!!!");
        }
        else if(win=='R'){
            printf("THERE WAS A TIE");
        }
        ChangePosition(20,20);

	}
	return win;
}
void experiment1() {
	int SIZE = 20;
	int liczA = 0;
	int liczB = 0;
	int liczR = 0;
	int liczW = 0;
	int rangaA = 0;
	int rangaB = 0;
	char wynik;
	float moves = 0;
	float summoves = 0;
	deck HandA;
	deck HandB;
	card tab[52];
	for (int k = 20; k < 53; k = k + 4) {
		SIZE = k;
		initTab(tab, SIZE);
		liczA = 0;
		liczB = 0;
		liczR = 0;
		liczW = 0;
		summoves=0;
		for (int i = 0; i < 10000; i++) {
			Shuffle(tab, SIZE);
			fill(&HandA, tab, 0, SIZE / 2);
			fill(&HandB, tab, SIZE / 2, SIZE);
			moves = 0;
			wynik = War(&HandA, &HandB, 'B', &moves,0);
			if (wynik == 'R') {
				liczR++;
			}
			else if (wynik == 'A') {
				liczA++;
			}
			else if (wynik == 'B') {
				liczB++;
			}
			else if (wynik == 'K') {
				liczW++;
			}
			summoves += moves;
		}
		printf("%d\nA wygral: %d razy\nB wygral %d razy\nRemis byl %d razy\nSrednia ruchow: %f\npetla=%d\n",SIZE, liczA, liczB, liczR, summoves / 10000, liczW);

	}
}
int random(char* win, deck* Hand1, deck* Hand2, deck* Next1, deck* Next2, deck* Table1, deck* Table2, char player){
    if(Next2->first!=NULL){
        addCard(pullCard(Next2), Table2);
    }
    else{
        (*win)= player;
        return 1;
    }
    if(rand()%2==0){
        addCard(pullCard(Hand1), Table1);
        if(Hand1->first != NULL){
            addCard(pullCard(Hand1),Next1);
        }
    }
    else{
        if(Hand1->first->next != NULL){
            addCard(pullCard(Hand1),Next1);
            addCard(pullCard(Hand1), Table1);
        }
        else{
            addCard(pullCard(Hand1), Table1);
        }
    }
    return 0;
}
int furious(char* win, deck* Hand1, deck* Hand2, deck* Next1, deck* Next2, deck* Table1, deck* Table2, char player){
    if(Next2->first!=NULL){
        addCard(pullCard(Next2), Table2);
    }
    else{
        (*win)= player;
        return 1;
    }
	if(Hand1->first->next==NULL){
		addCard(pullCard(Hand1),Table1);
	}
	else{
		if(Hand1->first->power==Table2->first->power){
			addCard(pullCard(Hand1), Table1);
			addCard(pullCard(Hand1),Next1);
		}
		else if(Hand1->first->next->power==Table2->first->power){
			addCard(pullCard(Hand1),Next1);
			addCard(pullCard(Hand1), Table1);
		}
		else{
			if(Hand1->first->power<Hand1->first->next->power){
				addCard(pullCard(Hand1), Table1);
				addCard(pullCard(Hand1),Next1);
			}
			else{
				addCard(pullCard(Hand1),Next1);
				addCard(pullCard(Hand1), Table1);
			}
		}
	}
    return 0;
}
int peacefull(char* win, deck* Hand1, deck* Hand2, deck* Next1, deck* Next2, deck* Table1, deck* Table2, char player){
	if(Next2->first!=NULL){
        addCard(pullCard(Next2), Table2);
    }
    else{
        (*win)= player;
        return 1;
    }
	if(Hand1->first->next==NULL){
		addCard(pullCard(Hand1),Table1);
	}
	else{
		if(Hand1->first->power==Table2->first->power){
			addCard(pullCard(Hand1),Next1);
			addCard(pullCard(Hand1), Table1);
		}
		else if(Hand1->first->next->power==Table2->first->power){
			addCard(pullCard(Hand1), Table1);
			addCard(pullCard(Hand1),Next1);
		}
		else{
			if(Hand1->first->power<Hand1->first->next->power){
				addCard(pullCard(Hand1), Table1);
				addCard(pullCard(Hand1),Next1);
			}
			else{
				addCard(pullCard(Hand1),Next1);
				addCard(pullCard(Hand1), Table1);
			}
		}
	}
    return 0;
}
int chooseTactic(char* win, deck* Hand1, deck* Hand2, deck* Next1, deck* Next2, deck* Table1, deck* Table2, char player,char option ){
	if(option=='R'){
		return random(win,Hand1,Hand2,Next1,Next2, Table1,Table2, player);
	}
	else if(option=='F'){
		return furious(win,Hand1,Hand2,Next1,Next2, Table1,Table2, player);
	}
	else{
		return peacefull(win,Hand1,Hand2,Next1,Next2, Table1,Table2, player);
	}
}

char SmartWar (deck* HandA, deck* HandB,float *moves, char tryb,char Tactic1, char Tactic2, int show){
	deck A;
	deck B;
	deck NA;
	deck NB;
	deck* TableA = &A;
	deck* TableB = &B;
	deck* NextA =&NA;
	deck* NextB =&NB;
	init(TableA);
	init(TableB);
	init(NextA);
	init(NextB);
	char win = 'Z';
    char choice;
    int turn = 0;
    int x;
	int y;
    addCard(pullCard(HandB),NextB);
	while (HandA->first != NULL && HandB->first != NULL) {
        if(turn%2==0){
            if(tryb=='R'){
                if(chooseTactic(&win,HandA,HandB,NextA,NextB,TableA,TableB,'A',Tactic1)==1){
                break;
                }
            }
            else if( tryb=='P'){
				addCard(pullCard(NextB),TableB);
				if(HandA->first->next!=NULL){
					if(show==1){
						textcolor(0,0);
						system("cls");
						textcolor(7,0);
						ChangePosition(6,3);
						printf("Player 1: %d", Count(*HandA));
						ChangePosition(24,3);
						printf("Player 2: %d", Count(*HandB));
						ChangePosition(10,5);
						printf("CHOOSE YOUR CARD L or R");
						Draw(HandA->first,3,6);
						Draw(HandA->first->next,15,6);
						Draw(TableB->first,35,5);
						
					}
					choice=getch();
					
					if (choice=='L'){
						addCard(pullCard(HandA),TableA);
						addCard(pullCard(HandA),NextA);
					}
					else if(choice=='R'){
						addCard(pullCard(HandA),NextA);
						addCard(pullCard(HandA),TableA);
					}
					
				}
				else{
					addCard(pullCard(HandA),TableA);
				}
            }
        }
        else{
            if(tryb=='R'){
                if(chooseTactic(&win,HandB,HandA,NextB,NextA,TableB,TableA,'B',Tactic2)==1){
                    break;
                }
            }
            else if( tryb=='P'){
                if(chooseTactic(&win,HandB,HandA,NextB,NextA,TableB,TableA,'B', Tactic2)==1){
                    break;
                }
            }
        }

		(*moves)++;
		TableA->pointer = TableA->first;
		TableB->pointer = TableB->first;
		if(show==1){
			textcolor(0,0);
			system("cls");
			textcolor(7,0);
			ChangePosition(6,3);
			printf("Player 1: %d", Count(*HandA));
			ChangePosition(24,3);
			printf("Player 2: %d", Count(*HandB));
            DrawBattle(TableA->first,TableB->first);
			if(turn%2==0&&NextA->first!=NULL){
				Draw(NextA->first,1,5);
			}
			else if(NextB->first!=NULL){
				Draw(NextB->first,32,5);
			}
			//sleep(2);
		}
		turn++;
		if (TableA->first->power != TableB->first->power) {
			if(Battle(TableA,TableB)=='A'){
                Battlewin(HandA,TableA, TableB);
			}
			else if(Battle(TableA,TableB)=='B'){
                Battlewin(HandB,TableB, TableA);
			}
		}
		else {
			int test = 0;
			int testB = 0;
            x= 10;
			y=5;
            while (test == 0) {
				if(turn%2==1){
					if(NextA->first!=NULL){
						addCard(pullCard(NextA),TableA);
					}
					else{
						break;
					}
					if (HandB->first != NULL) {
						addCard(pullCard(HandB), TableB);
					}
					else {
						break;
					}
					if (HandB->first != NULL) {
						addCard(pullCard(HandB), TableB);
					}
					else {
						break;
					}
					if (HandA->first != NULL) {
						addCard(pullCard(HandA), TableA);
					}
					else {
						break;
					}
					if(HandA->first!=NULL){
						addCard(pullCard(HandA),NextA);
					}
					else{
						break;
					}
				}
				else{
						if(NextB->first!=NULL){
							addCard(pullCard(NextB),TableB);
						}
						else{
							break;
						}
						if (HandA->first != NULL) {
							addCard(pullCard(HandA), TableA);
						}
						else {
							break;
						}
						if (HandA->first != NULL) {
							addCard(pullCard(HandA), TableA);
						}
						else {
							break;
						}
						if (HandB->first != NULL) {
							addCard(pullCard(HandB), TableB);
						}
						else {
							break;
						}	
						if(HandB->first!=NULL){
							addCard(pullCard(HandB),NextB);
						}
						else{
							break;
						}
					}
					FindEnd(TableA);
					FindEnd(TableB);
					if(show==1){
						textcolor(7,0);
						ChangePosition(6,3);
						printf("Player 1: %d", Count(*HandA)+Count(*NextA));
						ChangePosition(24,3);
						printf("Player 2: %d", Count(*HandB)+Count(*NextB));
						DrawWar(TableA->pointer,TableB->pointer,x,y);
						//Sleep(300);
						x=x+4;
						y=y+4;
					}
					if (TableA->pointer->power != TableB->pointer->power){
						if(Battle(TableA, TableB)=='A'){
							SmartWarWin(HandA, TableA, TableB,&test);
						}
						else if(Battle(TableA, TableB)=='B'){
							SmartWarWin(HandB, TableB, TableA,&test);
						}                  
					}
				    if ((*moves) > 10000) {
					win='K';
					break;
				}
			}
		}

	}

	if (((HandA->first == NULL) && (HandB->first == NULL))&& win=='Z') {
		win= 'R';
	}
	else if (HandA->first == NULL && win == 'Z') {
		win= 'B';
	}
	else if (HandB->first == NULL && win == 'Z') {
		win = 'A';
	}
	else if(win == 'Z'){
		win =  'K';
	}
	if(show==1){
        textcolor(0,0);
        system("cls");
        ChangePosition(20,10);
        textcolor(7,0);
        if(win=='A'){
            printf("PLAYER 1 WON!!!");
        }
        else if(win=='B'){
            printf("PLAYER 2 WON!!!");
        }
        else if(win=='R'){
            printf("THERE WAS A TIE");
        }
        ChangePosition(20,20);
		sleep(5);

	}
	return win;
}
void SmartExperiment1() {
	int SIZE = 20;
	int liczA = 0;
	int liczB = 0;
	int liczR = 0;
	int liczW = 0;
	int rangaA = 0;
	int rangaB = 0;
	char wynik;
	float moves = 0;
	float summoves = 0;
	deck HandA;
	deck HandB;
	card tab[52];
	for (int k = 20; k < 53; k = k + 4) {
		SIZE = k;
		initTab(tab, SIZE);
		liczA = 0;
		liczB = 0;
		liczR = 0;
		liczW = 0;
		summoves=0;
		for (int i = 0; i < 10000; i++) {
			Shuffle(tab, SIZE);
			fill(&HandA, tab, 0, SIZE / 2);
			fill(&HandB, tab, SIZE / 2, SIZE);
			moves = 0;
			wynik = SmartWar(&HandA, &HandB,&moves,'R','F','R',0);
			if (wynik == 'R') {
				liczR++;
			}
			else if (wynik == 'A') {
				liczA++;
			}
			else if (wynik == 'B') {
				liczB++;
			}
			else if (wynik == 'K') {
				liczW++;
			}
			summoves += moves;
		}
		printf("%d\nA wygral: %d razy\nB wygral %d razy\nRemis byl %d razy\nSrednia ruchow: %f\npetla=%d\n",SIZE, liczA, liczB, liczR, summoves / 10000, liczW);
		FreeHand(&HandA);
		FreeHand(&HandB);
	}
}
void SmartExperiment2() {
	int SIZE = 52;
	int liczA = 0;
	int liczB = 0;
	int liczR = 0;
	int liczW = 0;
	int rangaA = 0;
	int rangaB = 0;
	char wynik;
	float moves = 0;
	float summoves = 0;
	deck HandA;
	deck HandB;
	card tab[52];
	for (int i = 0; i < 1000; i++) {
		Shuffle(tab, SIZE);
		fill(&HandA, tab, 0, SIZE / 2);
		fill(&HandB, tab, SIZE / 2, SIZE);
		moves = 0;
		wynik = SmartWar(&HandA, &HandB,&moves,'R','P','F',0);
		if (wynik == 'R') {
			liczR++;
		}
		else if (wynik == 'A') {
			liczA++;
		}
		else if (wynik == 'B') {
			liczB++;
		}
		else if (wynik == 'K') {
			liczW++;
		}
		summoves += moves;
	}
	printf("%d\nA wygral: %d razy\nB wygral %d razy\nRemis byl %d razy\nSrednia ruchow: %f\npetla=%d\n",SIZE, liczA, liczB, liczR, summoves / 1000, liczW);
	FreeHand(&HandA);
	FreeHand(&HandB);
}