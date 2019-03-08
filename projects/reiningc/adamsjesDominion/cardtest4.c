/* -----------------------------------------------------------------------
 * great_hall function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	card = great_hall,
	choice1 = 0,
	choice2 = 0,
	choice3 = 0,
	handPos = 0,
	bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
    int oldHandCt, newHandCt, 
	oldActionCt, newActionCt;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // --------------------- TEST 1 -------------------------------------------
    // Play great hall and check if 1 card added to the hand
    // ------------------------------------------------------------------------

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    oldHandCt = testG.handCount[curPlayer];	// get original count of cards in hand
    oldActionCt = testG.numActions;		// get original count of actions
   
    rv = cardEffect(card, choice1, choice2, choice3, &testG, handPos, &bonus);  
    newHandCt = testG.handCount[curPlayer];	// get new count of cards in hand
    newActionCt = testG.numActions;		// get new count of actions
   
    // difference of newHandCt-oldHandCt should be 0 because you gain 1 card then discard the great_hall
    if(rv == 0 && newHandCt-oldHandCt == 0)
	    printf("great_hall() Test 1: %sPASS %s- 1 card added to hand\n", Color_Green, Color_end);
    else
	    printf("great_hall() Test 1: %sFAIL %s- %d cards added to hand (expected 0)\n", Color_Red, Color_end, newHandCt-oldHandCt);

    // ---------------------- TEST 2 ---------------------------------------
    // Play great hall and check if 1 action added
    // ---------------------------------------------------------------------

    if(rv == 0 && newActionCt-oldActionCt == 1)
	    printf("great_hall() Test 2: %sPASS %s- 1  action added\n", Color_Green, Color_end);
    else
	    printf("great_hall() Test 2: %sFAIL %s- %d actions added (expected 2)\n", Color_Red, Color_end, newActionCt-oldActionCt);

    return 0;

}
