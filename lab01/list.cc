#include <stdio.h>
#include "List.h"
#include <stdlib.h>


void List::insertSorted(int val)
{
    ListNode *curr;
    curr = _head;
    
    ListNode *last;
    last = NULL;
    
    while (curr != NULL)
    {
        if (val <= curr->_value) {break;}     
        last = curr;        
        curr = curr->_next;
    }
    
    ListNode *n;
    n = (ListNode*)malloc(sizeof(ListNode));
    n->_value = val;
    n->_next = curr;
    
    if (last != NULL)
        last->_next = n;
    else
        _head = n;
}

// Inserts a new element with value "val" at end of list
void List::append(int val)
{
    ListNode *curr;
    curr = _head;
    
    while (curr != NULL) {curr = curr->_next;}
    
    ListNode *n;
    n = (ListNode*)malloc(sizeof(ListNode));
    n->_value = val;
    n->_next = NULL;
    
    if (curr != NULL)
        curr->_next = n;
    else
        _head = n;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend(int val)
{
    ListNode *n;
    n = (ListNode*)malloc(sizeof(ListNode));
    n->_value = val;
    n->_next = _head;
    
    _head = n;
}

// Removes an element with value "val" from List
int  List::remove(int val)
{
    ListNode *curr;
    curr = _head;
    
    ListNode *last;
    last = NULL;
    
    if (curr->_value == val)
    {
        _head = curr->_next;
        return 0;
    }
    
    while (curr != NULL)
    {
        if (curr->_value == val)
        {
            last->_next = curr->_next;  
            return 0;
        }
        
        last = curr;        
        curr = curr->_next;
    }
    
    return -1;
}

// Prints The elements in the list. 
void List::print()
{
    ListNode *curr;
    curr = _head;
    
    while (curr != NULL)
    {
        printf("%d\n", curr->_value); 
        curr = curr->_next;
    }
}

//
int List::lookup(int val)
{
    ListNode *curr;
    curr = _head;
    
    while (curr != NULL)
    {
        if (curr->_value == val)
        {
            return 0;
        }
        
        curr = curr->_next;
    }
    
    return -1;
}

//
// List constructor

List::List() {_head = NULL;}

//
// List destructor: 
List::~List() {
    ListNode* curr;
    curr = _head;
    
    while (curr != NULL)
    {
        ListNode* next;
        next = curr->_next;  
        free(curr);
        curr = next;
    }  
    _head = NULL;
}

