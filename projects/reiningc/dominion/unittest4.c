/* -----------------------------------------------------------------------
 * isGameOver function unit tests
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	rv;
    struct gameState G;
    // prefill supplyCount with 1 of each card
    for(i = 0; i <= treasure_map; i++)
    {
	    G.supplyCount[i] = 1;
    }

    // --------------------- TEST 1 -------------------------------------------
    // isGameOver(): Check isGameOver when there are 1 of each card in supplyCount (game should not be over)
    // ------------------------------------------------------------------------

    rv = isGameOver(&G);	// check if game is over and save return value in rv
    if(rv == 0)
	    printf("isGameOver() Test 1: %sPASS %s- game is not over when 1 of each type of card in supply.\n", Color_Green, Color_end);
    else
	    printf("isGameOver() Test 1: %sFAIL %s- game is over when 1 of each type of card in supply\n", Color_Red, Color_end);

    // --------------------- TEST 2 -------------------------------------------
    // isGameOver(): Check isGameOver when province count is 0 (game should be over)
    // ------------------------------------------------------------------------

    G.supplyCount[province] = 0;
    rv = isGameOver(&G); 	// check if game is over
    if(rv == 1)
	    printf("isGameOver() Test 2: %sPASS %s- game is over when no provinces remain in supply\n", Color_Green, Color_end);
    else
	    printf("isGameOver() Test 2: %sFAIL %s- game is not over when no provinces remain in supply\n", Color_Red, Color_end);

    // --------------------- TEST 3 -------------------------------------------
    // isGameOver(): Check isGameOver when two supply piles at 0 (game should not be over)
    // ------------------------------------------------------------------------

    G.supplyCount[province] = 1;	// reset province supply
    G.supplyCount[gold] = 0;
    G.supplyCount[smithy] = 0;
    rv = isGameOver(&G);		// check if game is over
    if(rv == 0)
	    printf("isGameOver() Test 3: %sPASS %s- game is not over when two supply piles at 0\n", Color_Green, Color_end);
    else
	    printf("isGameOver() Test 3: %sFAIL %s- game is over when two supply piles at 0\n", Color_Red, Color_end);

    // --------------------- TEST 4 -------------------------------------------
    // isGameOver(): Check isGameOver when three supply piles at 0 (game should be over)
    // ------------------------------------------------------------------------

    G.supplyCount[gold] = 0;
    G.supplyCount[smithy] = 0;
    G.supplyCount[sea_hag] = 0;
    rv = isGameOver(&G);		// check if game is over
    if(rv == 1)
	    printf("isGameOver() Test 4: %sPASS %s- game is over when three supply piles at 0\n", Color_Green, Color_end);
    else
	    printf("isGameOver() Test 4: %sFAIL %s- game is not over when three supply piles at 0\n", Color_Red, Color_end);

    return 0;
}
