/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:ChunYu Chen
 * Email:chench6@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* stack_v;
  struct dynarray* stack_p;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->stack_p = dynarray_create();
  pq->stack_v = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->stack_p);
  dynarray_free(pq->stack_v);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(dynarray_size(pq->stack_p) == 0){
    return 1;
  }else{
    return 0;
  }
}

void swap(struct pq* pq, int down, int up){
  void* temp_pri = dynarray_get(pq->stack_p,down);
  void* temp_val = dynarray_get(pq->stack_v,down);
  
  dynarray_set(pq->stack_p,down,dynarray_get(pq->stack_p,up));
  dynarray_set(pq->stack_v,down,dynarray_get(pq->stack_v,up));

  dynarray_set(pq->stack_p,up,temp_pri);
  dynarray_set(pq->stack_v,up,temp_val);
}
/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  
  int parent = 0;//get the parent priority
  int size = 0;
  size = dynarray_size(pq->stack_p);

  dynarray_insert(pq->stack_p,priority);
  dynarray_insert(pq->stack_v,value);

  while(size > 0)
  {
    parent = (size-1)/2;
    //get the peiority value
    int get_parent = 0;
    get_parent = (int)dynarray_get(pq->stack_p,parent);
    if(get_parent > priority)
    {
      swap(pq,size,parent);
      // redefine the value of parent
      size = parent;
    }else{
      break;
    }
  }
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  return dynarray_get(pq->stack_v,0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  return (int)dynarray_get(pq->stack_p,0);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  int current = 0;//the first index
  int left = 0;
  int right = 0;

  int current_p = 0;
  int left_p = 0;
  int right_p = 0;

  int size = 0;
  void* get = dynarray_get(pq->stack_v,0);
  size = dynarray_size(pq->stack_p);
  //printf("remove is: %d\n",dynarray_get(pq->heap_p,0)); 
  swap(pq,0,size-1);
  dynarray_remove(pq->stack_p,(size-1));
  dynarray_remove(pq->stack_v,(size-1));
  //redefine size
  size--;
  
  while((current*2+1) < size)
  {
    //printf("进入循环\n");
    left = current*2+1;
    right = current*2+2;
    //printf("left is: %d, right is: %d\n",l,r);
    current_p = (int)dynarray_get(pq->stack_p,current);
    left_p = (int)dynarray_get(pq->stack_p,left);  
    //printf("current pri:%d, left pri:%d",curp,lp);
    if(left == size-1)
    {
      //printf("特殊情况\n");
      if(current_p > left_p)
      {
        swap(pq,current,left);
        //printf("跳出循环\n");
        break;
      }else{
        //printf("跳出循环\n");
        break;
      }
    }else{
      //printf("正常换位置\n");
      right_p = (int)dynarray_get(pq->stack_p,right);
      
      if((current_p >left_p) && (current_p > right_p)) 
      {
        //printf("root比左右都大\n");
        if(left_p < right_p)
        {
          //printf("左小\n");
          swap(pq,current,left);
          current = left;
        }else{
          //printf("右小\n");
          swap(pq,current,right);
          current = right;
        }
      }else if(current_p > left_p){
        //printf("root只比左大\n");
        swap(pq,current,left);
        current = left;
      }else if(current_p > right_p){
        //printf("root只比右大\n");
        swap(pq,current,right);
        current = right;
      }else{
        break;
      }
    }
  }
  return get;
}
