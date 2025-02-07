#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
	/* your code here */
	    
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::InsertAfter(Node * p, const Block &ndata) {
	/* your code here */
	Node* newNode = new Node(ndata);

	if (p == nullptr) {
		head_ = newNode;
	} else {
		newNode->next = p->next;
		p->next = newNode;
	}

	return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::Swap(Node *p, Node *q) {
	/* your code here */

	if (p == nullptr || q == nullptr || p == q) {
		return;
	}
    
	if (head_ == p) {
		head_ = q;
	} else if (head_ == q) {
		head_ = p;
	}

	Node* pPrevious = p->prev;
	Node* pNext = p->next;
	Node* qPrevious = q->prev;
	Node* qNext = q->next;

	if (pPrevious != nullptr) {
		pPrevious->next = q;
	}
	if (pNext != nullptr) {
		pNext->prev = q;
	}
	if (qPrevious != nullptr) {
		qPrevious->next = p;
	}
	if (qNext != nullptr) {
		qNext->prev = p;
	}
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
	/* your code here */

    
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::Copy(Chain const &other) {
	/* your code here */
	
	
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::Render() {
    /* your code here */

	Node* current = head_;
	int x = 0;

	while (current != nullptr) {
		Block block = current->data;
		
		x += block.Width();
		current = current->next;
	}


    return PNG();
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::Unscramble() {
	/* your code here */

    
}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

