#include "chain.h"
#include <cmath>
#include <iostream>
#include <map>


// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
	// Assuming Clear() is done right
	Clear();
	    
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
		newNode->next = head_;
		head_ = newNode;
		if (newNode->next != nullptr) {
			newNode->next->prev = newNode;
		}
		newNode->prev = nullptr;
	} else {
		newNode->next = p->next;
		
		if (p->next != nullptr) {
			p->next->prev = newNode;
		}

		p->next = newNode;
		newNode->prev = p;
	}

	length_++;

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

	Node* pPrevious = p->prev;
	Node* pNext = p->next;
	Node* qPrevious = q->prev;
	Node* qNext = q->next;

	if (pNext == q) {
		if (pPrevious != nullptr) {
			pPrevious->next = q;
		}
		if (qNext != nullptr) {
			qNext->prev = p;
		}
		p->next = qNext;
		q->next = p;
		p->prev = q;
		q->prev = pPrevious;
	} else if (qNext == p) {
		if (qPrevious != nullptr) {
			qPrevious->next = p;
		}
		if (pNext != nullptr) {
			pNext->prev = q;
		}
		q->next = pNext;
		p->next = q;
		q->prev = p;
		p->prev = qPrevious;
	} else {
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

		p->prev = qPrevious;
		p->next = qNext;
		q->prev = pPrevious;
		q->next = pNext;
	}
    
	if (head_ == p) {
		head_ = q;
	} else if (head_ == q) {
		head_ = p;
	}
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
	// I think the only necessary thing to do here is to deallocate Node objects

	Node* cur = head_;

	while (cur != nullptr) {
		Node* temp = cur -> next;
		delete cur;
		cur = temp;
	}

	head_ = nullptr;
	length_ = 0;
    
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::Copy(Chain const &other) {
	// I think this is just making sure the linked list is the same

	if (other.head_ == nullptr) {
		head_ = nullptr;
		length_ = 0;
		return;
	}

	head_ = new Node(other.head_ -> data);
	Node* cur = head_;
	Node* toCopy = other.head_ -> next;

	while (toCopy != nullptr) {
		cur -> next = new Node(toCopy -> data);
		cur -> next -> prev = cur;
		cur = cur -> next;
		toCopy = toCopy -> next;
	}

	length_ = other.length_;
	
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
	int width = 0;
	int height = 0;

	while (current != nullptr) {
		Block block = current->data;
		width += block.Width();
		height = max(height, block.Height());
		current = current->next;
	}

	PNG image = PNG(width, height);
	current = head_;
	int x = 0;

	while (current != nullptr) {
		Block block = current->data;
		block.Render(image, x);
		x += block.Width();
		current = current->next;
	}

    return image;
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest. That is, the distance (using distanceTo) to this block
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
	
	
	if (head_ == nullptr || head_ -> next == nullptr) {
		return;
	}
	

	// step 1: find leftmost node
	

	Node* caller = head_;
	Node* callee = head_;
	
	map<Node*, double> distances = map<Node*, double>();

	while (callee != nullptr) {
		double minDistance = std::numeric_limits<double>::max();
		Block calleeBlock = callee->data;
		
		caller = head_;

		while (caller != nullptr) {
			Block callerBlock = caller->data;

			if (caller != callee) {
				double distance = callerBlock.DistanceTo(calleeBlock);
				minDistance = min(minDistance, distance);
			}
			
			caller = caller->next;
		}
		
		distances[callee] = minDistance;
		callee = callee->next;
	}

	double maxDistance = 0;
	Node* left_ = nullptr;

	for (auto iterator = distances.begin(); iterator != distances.end(); iterator++) {
		double distance = iterator->second;
		if (distance > maxDistance) {
			maxDistance = distance;
			left_ = iterator->first;
		}
	}

	left_ = nullptr;		
	


	// step 2: sort rest of the chain in terms of distance from leftmost node

	Node* curLeft = left_;
	Node* cand = curLeft -> next;
	Block leftBlock = curLeft -> data;

	double distance = leftBlock.DistanceTo(cand -> data);
	
	while (cand != nullptr) {
		
		double curDistance = leftBlock.DistanceTo(cand -> data);
		
		if (curDistance < distance) {
			
			Node* tempPrev = cand -> prev;
			Node* tempNext = cand -> next;

			cand -> prev = curLeft -> prev;
			cand -> next = curLeft -> next;

			curLeft -> prev = tempPrev;
			curLeft -> next = tempNext;
			
		}
		

	}

	// step 3: swap nodes to unscramble chain
}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

