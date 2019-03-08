/* -----------------------------------------------------------------------
 * gainCard function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int i, 
	rv, 
	cardAdded = 0, 
	player = 0,
	discard = 0,
	deck = 1,
	hand = 2;
    struct gameState G;
  
    // --------------------- TEST 1 -------------------------------------------
    // gainCard(): Player gains card in their discard pile (should add card to discard, not hand or deck)
    // ------------------------------------------------------------------------
 
    G.numPlayers = 2;
    G.supplyCount[gold] = 3;	// 3 gold cards available for gaining
    rv = gainCard(gold, &G, discard, player);	// attempt to gain the gold coin to the discard pile of player 1 and save return value in rv
    // check for gold coin in discard
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.discard[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if(rv == 0 && cardAdded)
	    printf("gainCard() Test 1: %sPASS %s- card gained and added to discard.\n", Color_Green, Color_end);
    else
	    printf("gainCard() Test 1: %sFAIL %s- card not bought and added to discard\n", Color_Red, Color_end);

 
    // --------------------- TEST 2 -------------------------------------------
    // gainCard(): Player gains card in their deck (should add card to deck, not hand or discard)
    // ------------------------------------------------------------------------
 

    cardAdded = 0; 				// reset cardAdded to false
    rv = gainCard(gold, &G, deck, player); 	// attempt to gain gold coin in deck of player 1
    // check for gold coin in deck
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.deck[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if(rv == 0 && cardAdded)
	    printf("gainCard() Test 2: %sPASS %s- card gained and added to deck\n", Color_Green, Color_end);
    else
	    printf("gainCard() Test 2: %sFAIL %s- card not gained and added to deck\n", Color_Red, Color_end);
 
    // --------------------- TEST 3 -------------------------------------------
    // gainCard(): Player gains card in their hand (should add card to hand, not deck or discard)
    // ------------------------------------------------------------------------

    cardAdded = 0;				// reset cardAdded to false
    rv = gainCard(gold, &G, hand, player);	// attempt to gain gold in hand
    // check for gold in hand
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.hand[0][i] == gold)
	    {
		cardAdded = 1;
		break;
	    }
    }
    if(rv == 0 && cardAdded)
	    printf("gainCard() Test 3: %sPASS %s- card gained and added to hand\n", Color_Green, Color_end);
    else
	    printf("gainCard() Test 3: %sFAIL %s- card not gained and added to hand\n", Color_Red, Color_end);

    // --------------------- TEST 4 -------------------------------------------
    // gainCard(): Player attempts to gain card when none is left in supply (should nto add card to hand)
    // ------------------------------------------------------------------------

    cardAdded = 0;				// reset cardAdded to false
    rv = gainCard(gold, &G, hand, player);	// attempt to gain gold in hand
    // check for gold in hand
    for(i = 0; i < MAX_HAND; i++)
    {
	    if(G.hand[0][i] == gold)
	    {
		cardAdded = cardAdded + 1;
	    }
    }
    if(rv == -1 && cardAdded == 1)
	    printf("gainCard() Test 4: %sPASS %s- card not added to hand when none available in supply\n", Color_Green, Color_end);
    else
	    printf("gainCard() Test 4: %sFAIL %s- card added to hand when none available in supply\n", Color_Red, Color_end);

    return 0;

}
