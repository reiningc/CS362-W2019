/* -------------------------------------------------
 * smithy_card function random tests
 * ref: Lecture 11 testDrawCard.c
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 * 	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

int countPlayedSmithys(int p, struct gameState *g)
{
	int smithys = 0, i = -5;
	for(i = 0; i < g->playedCardCount; i++)
	{
		if(g->playedCards[i] == smithy)
			smithys = smithy + 1;
	}
	return smithys;
}

int cardInHand(int p, struct gameState *g, int card)
{
	int i, cardFound = 0;
	for(i = 0; i < g->handCount[p]; i++)
	{
		if(g->hand[p][i] == card)
			cardFound = 1;
	}
	return cardFound;
}

int checkSmithyCard(int p, struct gameState *post) {
  struct gameState pre;
  int i, r, 
      prePlayedSmithys = -5, postPlayedSmithys = -5,
      card = smithy,
      choice1 = 0, choice2 = 0, choice3 = 0,
      handPos = 0;

  // if smithy card is not in hand, add it to hand
  if(!cardInHand(p, post, card))
  {
	post->hand[p][post->handCount[p]] = smithy;
	post->handCount[p]++;
	handPos = post->handCount[p]-1;
  }
  else
  {
	 for(i = 0; i < post->handCount[p]; i++)
		 if(post->hand[p][i] == smithy)
			  handPos = i;
  }
  // copy post to pre
  memcpy (&pre, post, sizeof(struct gameState));
 
  // save initial counts of smithys in discard
  prePlayedSmithys = countPlayedSmithys(p, &pre);


  // play card and store result in r  
  r = playCard(handPos,choice1,choice2,choice3,post);

  postPlayedSmithys = countPlayedSmithys(p, post);

/* 
  printf("PRE. deck: %d, played: %d, hand: %d, playedSmithy's: %d\n", 
		  pre.deckCount[p], pre.playedCardCount, pre.handCount[p], prePlayedSmithys);
  printf("POST. deck: %d, played: %d, hand: %d, playedSmithy's: %d\n", 
		  post->deckCount[p], post->playedCardCount, post->handCount[p], postPlayedSmithys);
*/

  // ASSERTIONS
  assert(r == 0);
  // The difference in deck/played count should be 2 (3 cards drawn from deck - 1 smithy played)
  int change = (pre.deckCount[p] - post->deckCount[p]) - (post->playedCardCount - pre.playedCardCount);
//  assert(change == 0);
  if(change != 2)
	  printf("FAIL - deckCount/playedCardCount mismatch. expected: 2, actual: %d\n", change);
  
  // The hand should have change of 2 (3 cards added - 1 smithy played)
  //assert(postHandTreasures - preHandTreasures  == 2);
  change = post->handCount[p] - pre.handCount[p];
//  assert(change == 0);
  if(change != 2)
	  printf("FAIL - incorrect change in number of cards in hand. expected: 2, actual: %d\n", change);

  // The discard pile should have 1 more smithy
  change = postPlayedSmithys - prePlayedSmithys;
//  assert(change == 1);
  if(change != 1)
	  printf("FAIL - played card pile did not receive smithy card. expected: %d, actual: %d\n", prePlayedSmithys + 1, change);
  
  return 0;
}

int main () {

  int x, i, n, p;

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  srand(time(0));

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    printf("Random Test #%d\n", n+1);
    p = floor(Random() * 2);
    G.deckCount[p] = rand() % MAX_DECK;
    G.discardCount[p] = rand() % MAX_DECK;
    G.handCount[p] = rand() % MAX_HAND;
    // fill deck/discard/hand with actual card values
    for(x = 0; x < G.deckCount[p]; x++)
	    G.deck[p][x] = rand() % 27;
    for(x = 0; x < G.discardCount[p]; x++)
	    G.discard[p][x] = rand() % 27;
    for(x = 0; x < G.handCount[p]; x++)
	    G.hand[p][x] = rand() % 27;
    // set phase to 0 so we can play a card
    G.phase = 0;
    // set current player to p for handCard function to work
    G.whoseTurn = p;
    G.numActions = rand() % MAX_DECK + 1;
    G.playedCardCount = rand() % MAX_DECK;
    checkSmithyCard(p, &G);
  }

  printf ("RANDOM TESTS COMPLETED\n");

  return 0;
}
