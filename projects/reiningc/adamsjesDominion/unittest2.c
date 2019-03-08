/* -----------------------------------------------------------------------
 * buyCard function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
#define Color_end "\x1b[0m"

int main() {
    int i, rv, cardAdded = 0;
    struct gameState G;
   
    // --------------------- TEST 1 -------------------------------------------
    // buyCard(): Player has exact match of # of coins to card cost (should add card to discard)
    // ------------------------------------------------------------------------
 
    G.numPlayers = 2;
    G.whoseTurn = 0;
    G.coins = 6; 	// gold coin card costs 6 coins 
    G.numBuys = 3;
    G.supplyCount[gold] = 2;
    rv = buyCard(gold, &G);  // attempt to buy the gold coin and save return value in rv
    // check for gold coin in discard
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.discard[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if((rv == 0 && cardAdded) && G.coins == 0)
	    printf("buyCard() Test 1: %sPASS %s- card bought and added to discard. remaining coins changed to 0\n", Color_Green, Color_end);
    else
	    printf("buyCard() Test 1: %sFAIL %s- card not bought and added to discard\n", Color_Red, Color_end);
   
    // --------------------- TEST 2 -------------------------------------------
    // buyCard(): Player cannot afford card cost - one coin short (should not add card to discard)
    // ------------------------------------------------------------------------
 
    G.coins = 5;		// reset coins to 5 - one short of the cost for a gold
    cardAdded = 0;		// reset cardAdded to false
    G.discard[0][i] = 0;	// reset discard pile
    rv = buyCard(gold, &G); 	// attempt to buy gold coin
    // check for gold coin in discard
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.discard[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if(rv == -1 && !cardAdded)
	    printf("buyCard() Test 2: %sPASS %s- card not bought if not enough coins\n", Color_Green, Color_end);
    else
	    printf("buyCard() Test 2: %sFAIL %s- card bought with too few coins\n", Color_Red, Color_end);
   
    // --------------------- TEST 3 -------------------------------------------
    // buyCard(): Player has more coins than needed to buy card - one coin over (should add card to discard)
    // ------------------------------------------------------------------------
 
    G.coins = 7;		// reset coins to 7 - one over the cost of a gold
    cardAdded = 0;		// reset cardAdded to false
    G.discard[0][i] = 0;	// reset discard pile
    rv = buyCard(gold, &G);	// attempt to buy gold
    // check for gold in discard
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.discard[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if((rv == 0 && cardAdded) && G.coins == 1)
	    printf("buyCard() Test 3: %sPASS %s- card bought with excess coins and added to discard. remaining coins changed to 1\n", Color_Green, Color_end);
    else
	    printf("buyCard() Test 3: %sFAIL %s- card not bought with excess coins\n", Color_Red, Color_end);

    return 0;

}
