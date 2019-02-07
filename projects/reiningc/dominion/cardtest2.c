/* -----------------------------------------------------------------------
 * adventurer_card function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
    int	i, rv,
	card = adventurer,
	choice1 = 0,
	choice2 = 0,
	choice3 = 0,
	handPos = 0,
	bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
    int oldHandCt, newHandCt, 
	oldTreasureCt = 0, newTreasureCt = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // --------------------- TEST 1 -------------------------------------------
    // Play adventurer and check if only 2 treasure cards are added to the hand
    // ------------------------------------------------------------------------

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    oldHandCt = testG.handCount[curPlayer]; 		// get original count of cards in hand
    for(i = 0; i < testG.handCount[curPlayer]; i++)	// get original count of treasures in hand
    {
	    if(testG.hand[curPlayer][i] == copper ||
	       testG.hand[curPlayer][i] == silver ||
	       testG.hand[curPlayer][i] == gold)
		    oldTreasureCt = oldTreasureCt + 1;
    }
    rv = cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);  // cardeffect will call adventurer_card function
    newHandCt = testG.handCount[curPlayer];		// get new count of cards in hand
    for(i = 0; i < testG.handCount[curPlayer]; i++)	// get new count of treasures in hand
    {
	    if(testG.hand[curPlayer][i] == copper ||
	       testG.hand[curPlayer][i] == silver ||
	       testG.hand[curPlayer][i] == gold)
		    newTreasureCt = newTreasureCt + 1;
    }
    if(rv == 0 && newTreasureCt-oldTreasureCt == 2)
	    printf("adventurer() Test 1: %sPASS %s- 2 treasure cards added to hand\n", Color_Green, Color_end);
    else
	    printf("adventurer() Test 1: %sFAIL %s- 2 treasure cards not added to hand\n", Color_Red, Color_end);

    // ---------------------- TEST 2 ---------------------------------------
    // Play adventurer and check if only 2 cards are added to the hand
    // ---------------------------------------------------------------------

    // difference of newHandCt-oldHandCt should be 1 because you gain 2 cards then discard the adventurer
    if(rv == 0 && newHandCt-oldHandCt == 1)
	    printf("adventurer() Test 2: %sPASS %s- 2 cards total added to hand\n", Color_Green, Color_end);
    else
	    printf("adventurer() Test 2: %sFAIL %s- %d cards added to hand (expected 1)\n", Color_Red, Color_end, newHandCt-oldHandCt);


    return 0;

}
