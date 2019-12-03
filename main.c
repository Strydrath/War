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
#include <winbase.h>
/***
 *    ╦ ╦╔═╗╦═╗
 *    ║║║╠═╣╠╦╝
 *    ╚╩╝╩ ╩╩╚═
 */
int main()
{
	deck all;
	deck HandA;
	deck HandB;
	deck Table;
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
	char tryb;

	card tab[52];
	/*printf("choose size:\n");
	scanf("%d", &SIZE);
	while (SIZE % 4 != 0 || SIZE<20 || SIZE>52) {
		printf("SIZE must be dividable by 4 and between 20 and 52\n");
		scanf("%d", &SIZE);
	}
	printf("thanks\n");
	printf("choose mode:\n");
	scanf(" %c", &tryb);
	printf("thanks\n");*/

	srand(time(NULL));
	initTab(tab, SIZE);
	init(&all);
	init(&HandA);
	init(&HandB);
	fill(&all, tab, 0, SIZE);
    Shuffle(tab, SIZE);

    fill(&HandA, tab, 0, SIZE / 2);
    fill(&HandB, tab, SIZE / 2, SIZE);
    //DrawBattle(HandA.first,HandB.first);
    //DrawWar(HandA.first,HandB.first, 10,5);
    //SmartWar(&HandA,&HandB,&moves,'R','F','P',1);
	SmartExperiment1();
    //SmartWar(&HandA, &HandB, &moves,'A',1);
    //printf("%c",War(&HandA, &HandB, tryb, &moves));*/
    //experiment1();
	FreeHand(&HandA);
	FreeHand(&HandB);
    scanf("%d",liczB);
    return 0;
}
