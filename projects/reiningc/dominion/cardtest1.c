/* -----------------------------------------------------------------------
 * smithy_card function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
// colors for test output
#define Color_Red "\x1b[31m"
#define Color_Green "\x1b[32m"
#define Color_end "\x1b[0m"	// resets color

int main() {
    int	rv,
	card = smithy,
	choice1 = 0,
	choice2 = 0,
	choice3 = 0,
	handPos = 0,
	bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
    int oldHandCt, newHandCt;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // test 1: play smithy with and check if 3 cards are drawn (should be 3 cards added to hand)
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    oldHandCt = testG.handCount[curPlayer];
    rv = cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);  // cardeffect will call smithy_card function
    newHandCt = testG.handCount[curPlayer];

    // difference of newHandCt-oldHandCt should be 2 because you gain 3 cards then discard the played smithy
    if(rv == 0 && newHandCt-oldHandCt == 2)
	    printf("smithy() Test 1: %sPASS %s- 3 cards added to hand when smithy played.\n", Color_Green, Color_end);
    else
	    printf("smithy() Test 1: %sFAIL %s- 3 cards not added to hand when smithy played\n", Color_Red, Color_end);


    return 0;

}
