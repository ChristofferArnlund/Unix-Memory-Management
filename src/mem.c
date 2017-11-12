/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author:
 * @date: 2015-11-20
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"

/* defines */

/* global variables */

int firstaddress;
int lastaddress;
//------------------------------------------------linkedlist -----------------------------------------------

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node {
	int size;
	struct Node* next;
	struct Node* previous;
};

int Enqueue(struct Node* p, int address, int size);


int Front() {
	if (front == NULL) {
		printf("Queue is empty\n");
		return -1;
	}
	return &front;
}
//Prints the linkelist with info about the nodes.
void Print() {
	struct Node* temp = front;
	int counter =0;
	printf("Nbr of Node:    First Address:     Final Address:     Size:");
	while (temp != NULL) {
        counter++;
		int relative_address = (int)temp - (int)firstaddress;
		int relative_end_address=(int)temp-(int)firstaddress+temp->size-1;
		int node_size=temp->size;
		printf("\n%d                    ",counter);
		printf("%d                  ",relative_address);
		printf("%d              ",relative_end_address);
		printf("%d",node_size);

		temp = temp->next;
	}
	printf("\n");
}
int isEmpty() {
	if (front == NULL) {
		return 1;
	}
	return 0;
}
//add a Node to correct place in linkedlist.
int Enqueue(struct Node* p, int address, int size) {
	struct Node* temp;
	int isempty = isEmpty();
	if (address == NULL && isempty == 1) { //list is empty add node at head of memory

		temp = firstaddress;
		temp->next = NULL;
		temp->previous = NULL;
		temp->size = size + sizeof(struct Node);
		front = temp;
		rear = temp;
		return firstaddress;

	} else if (address == NULL) {
		return -1; //LIST is FULL.
	}

//if we want to put a node before the first node

	if (address < front) {
		temp = address;

		temp->next = front;
		temp->previous = NULL;
		temp->size = size + sizeof(struct Node);
		front->previous = temp;
		front = temp;

		return address;

	}

	temp = address;
	temp->size = size + sizeof(struct Node);

	if (front == rear || p->next==NULL) {//inserting last
		p->next = temp;
		temp->next = NULL;
		temp->previous = p;
		rear = temp;
	} else {

		temp->next = p->next;

		temp->previous = p;
		(p->next)->previous = temp;
		p->next = temp;
		if (temp->next == NULL) {
			rear = temp;
		}
	}


	return address; //indicates success.
}

// To Dequeue an integer.
void Dequeue(struct Node* p) {

	if (front == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	else if (front->next == NULL) {
		front = NULL;
		rear=NULL;
	}
	else if(p==front){
		front = p->next;
		(p->next)->previous = NULL;
	}
	else if(p->next == NULL){
		(p->previous)-> next = NULL;
		rear = p->previous;
	}

	else if(p->previous == NULL){
		(p->next)->previous = NULL;
		front = p->next;
	}
	else {
		(p->previous)->next = p->next;
		(p->next)->previous = p->previous;
	}
	p=NULL;
}

//__ Linkedlist ---

void * find_bestfitnode(size_t size){
      //case: if list is empty or full return null.
      size_t total_size = size + sizeof(struct Node); // size for wanted size+header


      int best_spacesize = NULL;
      struct Node* chosen_node = NULL;

      //If list is empty return null;
      if(isEmpty()){
            return NULL;
      }

      //check to the top
      int address_space = (int) front - firstaddress;


      if(address_space >= total_size){ //checks if hole is big enough
            if(best_spacesize > address_space || best_spacesize == NULL){
                chosen_node = NULL;
            	best_spacesize = address_space;


            }
      }


      struct Node* node = front;
      while(node->next != NULL){
            address_space = (int) (node->next) - (int) ((int) node + (int) node->size);
            if(address_space >= total_size){
                  if(best_spacesize > address_space || best_spacesize == NULL){
                        best_spacesize = address_space;
                        chosen_node = node;
                  }
            }
            node = node->next;
      }


      //check to the bottom
      address_space = (int) lastaddress - (int) ((int) node + (int) node->size);
      if(address_space >= total_size){ //checks if hole is big enough
            if(best_spacesize > address_space || best_spacesize == NULL){ //check if the last space is the best
                   best_spacesize = address_space; // is unnecessary
                   chosen_node = node;
            }
      }

      return chosen_node;
}


void* find_worstfitnode(size_t size) {
	 //case: if list is empty or full return null.
	      size_t total_size = size + sizeof(struct Node); // size for wanted size+header


	      int best_spacesize = NULL;
	      struct Node* chosen_node = NULL;

	      //If list is empty return null;
	      if(isEmpty()){
	            return NULL;
	      }

	      //checks the top
	      int address_space = (int) front - firstaddress;


	      if(address_space >= total_size){ //checks if hole is big enough
	            if(best_spacesize < address_space || best_spacesize == NULL){
	            	/*chosen_node = firstaddress;
	            	front->previous=chosen_node;
	                chosen_node->next=front;
	                front->previous = NULL;
	                */
	                chosen_node = NULL;
	            	best_spacesize = address_space;


	            }
	      }


	      struct Node* node = front;
	      while(node->next != NULL){
	            address_space = (int) (node->next) - (int) ((int) node + (int) node->size);
	            if(address_space >= total_size){ // if it fits
	                  if(best_spacesize < address_space || best_spacesize == NULL){
	                        best_spacesize = address_space;
	                        chosen_node = node;
	                  }
	            }
	            node = node->next;
	      }


	      //Checks to the bottom
	      address_space = (int) lastaddress - (int) ((int) node + (int) node->size);
	      if(address_space >= total_size){ //checks if hole is big enough
	            if(best_spacesize < address_space || best_spacesize == NULL){ //check if the last space is the best
	                   best_spacesize = address_space; // is unnecessary
	                   chosen_node = node;
	            }
	      }

	      return chosen_node;
}


/* memory initializer */
int best_fit_memory_init(size_t size) {
	front = NULL;
	rear = NULL;

	firstaddress = malloc(size);
	lastaddress = firstaddress + size - 1;

	return 0;
}

int worst_fit_memory_init(size_t size) {
	int res = best_fit_memory_init(size);
	return res;
}

/* memory allocators */
void *best_fit_alloc(size_t size) {
    if((size + sizeof(struct Node)) > (lastaddress - firstaddress) || ((int) size) <= 0) {
          return -1; // size too large/small
    }
    struct Node* node = find_bestfitnode(size); //returns the node above best fit
    int address = NULL;
    int empty =isEmpty();
    if((empty==0) && ((int) front - firstaddress) >= (size + sizeof(struct Node))){ // check size from firstaddress to first node
    	address=firstaddress;
    }

    if(node != NULL){ //either there are no objects in the list, or no space
          address = (int) node + (int) node->size; //get the correct address from node
   }
   //if address is NULL we pass it along
   address = Enqueue(node, address, size);
   if(address == -1) {
	   return -1;
   }else {
	   return address + sizeof(struct Node);
   }
}

void *worst_fit_alloc(size_t size) {
	 if((size + sizeof(struct Node)) > (lastaddress - firstaddress) || ((int) size) <= 0) {
	          return -1; // size too large/small
	    }
	    struct Node* node = find_worstfitnode(size); //returns the node above best fit
	    int address = NULL;
	    int empty =isEmpty();
	    if((empty==0) && ((int) front - firstaddress) >= (size + sizeof(struct Node))){ // check size from firstaddress to first node
	    	address=firstaddress;
	    }

	    if(node != NULL){ //either there are no objects in the list, or no space
	          address = (int) node + (int) node->size; //get the correct address from node
	   }
	   //if address is NULL we pass it along
	   address = Enqueue(node, address, size);
	   if(address == -1) {
		   return -1;
	   }else {
		   return address + sizeof(struct Node);
	   }
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) {
	 int address = ptr - sizeof(struct Node);
	 struct Node* temp = address;
	 Dequeue(temp);
	 return;
}

void worst_fit_dealloc(void *ptr) {
	best_fit_dealloc(ptr);
	return;
}


/* count how many free blocks are LESS than the input size */
int best_fit_count_extfrag(size_t size) {
	int result = 0;
	 //case: if list is empty or full return null.
	      size_t total_size = size + sizeof(struct Node); // size for wanted size+header


	      int best_spacesize = NULL;
	      struct Node* chosen_node = NULL;

	      //If list is empty return null;
	      if(isEmpty()){
	    	  if((lastaddress-firstaddress)<total_size){ // checks if total memory is less than the size
	    	      return 1; //if it is then the whole memory is fragmented.
	    	    }else{
	    	     return 0;
	    	     }
	      }

	      //check from first node to top
	      int address_space = (int) front - firstaddress;


	      if((address_space < total_size) && (address_space > 0)){ //checks if hole is big enough
	    	  result++;
	      }

          //checks between nodes
	      struct Node* node = front;
	      while(node->next != NULL){
	            address_space = (int) (node->next) - (int) ((int) node + (int) node->size);
	            if((address_space < total_size) && (address_space > 0)){
	                  result++;
	            }
	            node = node->next;
	      }


	      //check from last node to bottom
	      address_space = (int) lastaddress - (int) ((int) node + (int) node->size);
	      if((address_space < total_size) && (address_space > 0)){
	    	  result++;
	      }

	      return result;
}

int worst_fit_count_extfrag(size_t size) {
	int res = best_fit_count_extfrag(size);
	return res;
}








//----------------------------------------------TESTS------------------------------------------

void randomWorstAlloc() {
		int adr1 = worst_fit_alloc(32*2);
		int adr2 = worst_fit_alloc(32*2);
		int adr3 = worst_fit_alloc(32);
		int adr4 = worst_fit_alloc(32);
		int adr5 = worst_fit_alloc(32*4);
		int adr6 = worst_fit_alloc(32*2);
		int adr7 = worst_fit_alloc(32);
		int adr8 = worst_fit_alloc(32);
		int adr9 = worst_fit_alloc(32*2);

		Print();

		worst_fit_dealloc(adr1);
		worst_fit_dealloc(adr3);
		worst_fit_dealloc(adr5);
		worst_fit_dealloc(adr6);
		worst_fit_dealloc(adr7);

		Print();
		int res = worst_fit_count_extfrag(32*2+1);
		printf("fragmentation: %d \n", res);

		int adr10 = worst_fit_alloc(32);
		int adr11 = worst_fit_alloc(32*2);
		int adr12 = worst_fit_alloc(32*4);
		int adr13 = worst_fit_alloc(32);
		int adr14 = worst_fit_alloc(32*2);
		int adr15 = worst_fit_alloc(32);

		Print();
		res = worst_fit_count_extfrag(32*2+1);
				printf("fragmentation: %d \n", res);
}

void randomBestAlloc() {
		int adr1 = best_fit_alloc(32*2);
		int adr2 = best_fit_alloc(32*2);
		int adr3 = best_fit_alloc(32);
		int adr4 = best_fit_alloc(32);
		int adr5 = best_fit_alloc(32*4);
		int adr6 = best_fit_alloc(32*2);
		int adr7 = best_fit_alloc(32);
		int adr8 = best_fit_alloc(32);
		int adr9 = best_fit_alloc(32*2);

		Print();

		best_fit_dealloc(adr1);
		best_fit_dealloc(adr3);
		best_fit_dealloc(adr5);
		best_fit_dealloc(adr6);
		best_fit_dealloc(adr7);

		Print();
		int res = best_fit_count_extfrag(32*2+1);
		printf("fragmentation: %d \n", res);

		int adr10 = best_fit_alloc(32);
		int adr11 = best_fit_alloc(32*2);
		int adr12 = best_fit_alloc(32*4);
		int adr13 = best_fit_alloc(32);
		int adr14 = best_fit_alloc(32*2);
		int adr15 = best_fit_alloc(32);

		Print();
		res = best_fit_count_extfrag(32*2+1);
				printf("fragmentation: %d \n", res);
}
void testWorst() {

	////allocates 3 memoryslots
	int adr1 = worst_fit_alloc(10);
	int adr2 = worst_fit_alloc(20);
	int adr3 = worst_fit_alloc(30);
	Print();

	////deallocates and then allocates again
	worst_fit_dealloc(adr2);
	Print();
	int adr4 = worst_fit_alloc(20);
	Print();

	worst_fit_dealloc(adr1);
	Print();
	int adr5 = worst_fit_alloc(10);
	Print();

	///fill the remaining spots.
	int adrx = 0;
	int count=0;
	while(adrx != -1) {

		adrx = (int) worst_fit_alloc(1);
		if((adrx != -1) && (count%2 == 0)) {
			worst_fit_dealloc(adrx);
		}
		count++;
	}

	Print();

	//check fragmentation
	// fragmentation == 2
	int res = worst_fit_count_extfrag(25);
	printf("x: %d \n", res);
	Print();
	//remove first item, fragmentation == 3
	worst_fit_dealloc(firstaddress + 12);
	res = worst_fit_count_extfrag(25);
	printf("x: %d \n", res);
	Print();
}

void testFragmentation() {
	testFull();
	int x = best_fit_count_extfrag(205);
	printf("x: %d \n", x);
	if (x == 2) {
		printf("SUCCESS\n");
	}

}

void testFull() {
	int adr1 = best_fit_alloc(10);
	Print();
	int adr2 = best_fit_alloc(20);
	Print();
	int adr3 = best_fit_alloc(20);
	Print();
	best_fit_dealloc(adr2);
	Print();
	best_fit_alloc(20);
	Print();
	best_fit_dealloc(adr1);
	Print();
	int adr4 = best_fit_alloc(800);
	Print();
	best_fit_alloc(8);
	Print();
	best_fit_dealloc(adr4);
	Print();
	best_fit_alloc(800);
	Print();
	best_fit_dealloc(adr2);
	best_fit_dealloc(adr3);
	Print();
	int adr5 = best_fit_alloc(30);
	Print();
//
//	int adrx = 0;
//	while(adrx != -1) {
//		adrx = (int) best_fit_alloc(1);
//
//	}
//	front=rear=NULL;
//
//	Print();


}

void testlinkedlist() {
	int y = Enqueue(NULL, NULL, 10);
	int adr = (int) front + front->size;
	int x = Enqueue(front, adr, 20);
	int adr2 = (int) front + front->size + (front->next)->size;
	int z = Enqueue(front->next, adr2, 20);
	Print();
	Dequeue(front);
	Print();
	int a = Enqueue(NULL, firstaddress, 10);
	Print();
	Dequeue(front->next);
	Print();
	int b = Enqueue(front, adr, 10);
	Print();
	Dequeue((front->next)->next);
	Print();
	int c = Enqueue(front->next, adr2, 10);
	Print();


}

