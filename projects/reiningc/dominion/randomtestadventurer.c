/* -------------------------------------------------
 * adventurer_card function random tests
 * ref: Lecture 11 testDrawCard.c
 *
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 * 	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

int countHandTreasures(int p, struct gameState *g)
{
	int treasures = 0, i = -5;
	for(i = 0; i < g->handCount[p]; i++)
	{
		if(g->hand[p][i] == copper ||
		   g->hand[p][i] == silver ||
		   g->hand[p][i] == gold)
			treasures = treasures + 1;
	}
	return treasures;
}

int countDeckTreasures(int p, struct gameState *g)
{
	int treasures = 0, i = -5;
	for(i = 0; i < g->deckCount[p]; i++)
	{
		if(g->deck[p][i] == copper ||
		   g->deck[p][i] == silver ||
		   g->deck[p][i] == gold)
			treasures = treasures + 1;
	}
	return treasures;
}

int countDiscardTreasures(int p, struct gameState *g)
{
	int treasures = 0, i = -5;
	for(i = 0; i < g->discardCount[p]; i++)
	{
		if(g->discard[p][i] == copper ||
		   g->discard[p][i] == silver ||
		   g->discard[p][i] == gold)
			treasures = treasures + 1;
	}
	return treasures;
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

int checkAdventurerCard(int p, struct gameState *post) {
  struct gameState pre;
  int i, r, 
      preHandTreasures = -5, preDeckTreasures = -5,// preDiscardTreasures = -5,
      postHandTreasures = -5, postDeckTreasures = -5,// postDiscardTreasures = -5,
      card = adventurer,
      choice1 = 0, choice2 = 0, choice3 = 0,
      handPos = 0;

  // if adventurer card is not in hand, add it to hand
  if(!cardInHand(p, post, card))
  {
	post->hand[p][post->handCount[p]] = adventurer;
	post->handCount[p]++;
	handPos = post->handCount[p]-1;
  }
  else
  {
	 for(i = 0; i < post->handCount[p]; i++)
		 if(post->hand[p][i] == adventurer)
			  handPos = i;
  }
  // copy post to pre
  memcpy (&pre, post, sizeof(struct gameState));
 
  // save initial counts of treasures in hand, deck, and discard
  preHandTreasures = countHandTreasures(p, &pre);
  preDeckTreasures = countDeckTreasures(p, &pre);
  //preDiscardTreasures = countDiscardTreasures(p, &pre);
  
  // play card and store result in r  
  r = playCard(handPos,choice1,choice2,choice3,post);

  postHandTreasures = countHandTreasures(p,post);
  postDeckTreasures = countDeckTreasures(p,post);
  //postDiscardTreasures = countDiscardTreasures(p,post);
  
  // ASSERTIONS
  assert(r == 0);
  // The difference in deck counts should be 2 more than the difference in discard counts
  //assert((pre.deckCount[p] - post->deckCount[p]) - (post->discardCount[p] - pre.discardCount[p]) == 2);
  int change = (pre.deckCount[p] - post->deckCount[p]) - (post->discardCount[p] - pre.discardCount[p]);
  if(change != 2)
	  printf("FAIL - deckCount/discardCount mismatch. expected: 2, actual: %d\n", change);
		
  // The hand should have 2 treasures added
  //assert(postHandTreasures - preHandTreasures  == 2);
  change = postHandTreasures - preHandTreasures;
  if(change != 2)
	  printf("FAIL - incorrect number of treasures added to hand. expected: 2, actual: %d\n", change);

  // The deck should have 2 less treasures
  change = preDeckTreasures - postDeckTreasures;
  if(change != 2)
	  printf("FAIL - incorrect number of treasures removed from deck. expected: 2, actual: %d\n", change);
/*
  // The discard pile should have the same amount of treasures
  change = preDiscardTreasures - postDiscardTreasures;
  if(change != 0)
	  printf("FAIL - discard pile treasures changed. expected: 0, actual: %d\n", change);
*/
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
    checkAdventurerCard(p, &G);
  }

  printf ("RANDOM TESTS COMPLETED\n");

  return 0;
}
