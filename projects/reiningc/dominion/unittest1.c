/* -----------------------------------------------------------------------
 * Shuffle function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int i, j, sameCards, shuffleFound;
    int numCardsInDeck = 5;
    struct gameState G;
    G.deckCount[0] = 5;
    // set gameState hand to have 5 cards: adventurer, council_room, feast, gardens, mine
    int testcards[5] = {adventurer, council_room, feast, gardens, mine};

    for(i = 0; i < numCardsInDeck; i++)
    {
	G.deck[0][i] = testcards[i];
    }
    
    // shuffle hand
    shuffle(0,&G);
    
    // test 1: compare number of cards (should be 5 after shuffle)
    if(G.deckCount[0] == numCardsInDeck)
	    printf("shuffle() Test 1: %sPASS %s- same number of cards in deck\n", Color_Green, Color_end);
    else
	    printf("shuffle() Test 1: %sFAIL %s- different number of cards in deck\n", Color_Red, Color_end);

    // test 2: compare cards in hand vs original cards (should match)
    for(i = 0; i < numCardsInDeck; i++)
    {
	sameCards = 0; // Set to false for each check
	for(j = 0; j < numCardsInDeck; j++)
	{
		if(testcards[i] == G.deck[0][j])
		{
			sameCards = 1; // Set to true if found
			break;
		}
	}
	if(!sameCards)
		break;
    }
    if(sameCards)
	    printf("shuffle() Test 2: %sPASS %s- same cards in deck\n", Color_Green, Color_end);
    else
	    printf("shuffle() Test 2: %sFAIL %s- not the same cards in deck\n", Color_Red, Color_end);


    // test 3: compare card locations vs original cards (should have at least one difference)
    for(i = 0; i < numCardsInDeck; i++)
    {
	shuffleFound = 0; // Set to false for each check
	for(j = 0; j < numCardsInDeck; j++)
	{
		if(testcards[i] == G.deck[0][j])
		{
			if(i != j)
				shuffleFound = 1; // Set to true if card was shuffled

		}
	}
	if(shuffleFound)
		break;
    }
    if(shuffleFound)
	    printf("shuffle() Test 3: %sPASS %s- cards shuffled to new locations in deck\n", Color_Green, Color_end);
    else
	    printf("shuffle() Test 3: %sFAIL %s- cards not shuffled to new locations in deck\n", Color_Red, Color_end);

    return 0;

}
