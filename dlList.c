/// dlList.c
/// $Id: dlList.h,v 1.4 2014/04/15 17:06:07 csci243 Exp $
///
/// An implementation of a
/// doubly linked list with a cursor
/// that keeps track of position in the list.
///
/// @author: jxz5746 Jacob Zuber
///

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


/// Struct of the doubly linked list
/// Holds the cursor to keep track of position in list,
/// the length of the list,
/// the first Node in the list,
/// and the last Node int the list.
struct dlList
{
	int length;
	struct Node* first;
	struct Node* last;
	struct Node* cursor;
};

/// Define what a Node is
/// A Node holds data of a certain type,
/// the previous Node in the list,
/// and the next Node in the list.
typedef struct Node
{
	struct Node* prev;
	struct Node* next;
	void * data;
} Node;

typedef struct dlList *DlList_T;

#define _DLL_IMPL_
#include "dlList.h"

/// Creates an instance of an empty doubly linked list
DlList_T dll_create( void )
{
	DlList_T new;
	
	new = (DlList_T) malloc( sizeof(struct dlList) );
	if( new != NULL )
	{
		new->length = 0;
		new->first = NULL;
		new->last = NULL;
		new->cursor = NULL;
	}
	
	return new;
}

/// Clears and frees the passed doubly linked list
void dll_destroy( DlList_T lst )
{
	assert( lst != NULL );
	dll_clear( lst );
	free( lst );
}

/// Empties passed doubly linked list
void dll_clear( DlList_T lst )
{
	assert( lst != NULL );
	
	while( !dll_empty( lst ) )
	{
		void* data = dll_pop( lst, 0 );
		free( data );
	}
}

/// Moves cursor of passed list to passed index
/// if index is not in range, returns false and does nothing
bool dll_move_to( DlList_T lst, int indx )
{
	assert( lst != NULL );
	
	if( indx >= 0 && indx < lst->length )
	{
		lst->cursor = lst->first;
		int i;
		for( i = 0; i < indx; i++ )
		{
			lst->cursor = lst->cursor->next;
		}
		return true;
	}
	else return false;
}

/// Check if cursor points to a non-null value
int dll_has_next( DlList_T lst )
{
	if( lst->cursor != NULL ) return 1;
	else return 0;
}

/// Returns current cursor data and moves to next
void * dll_next( DlList_T lst )
{
	assert( lst != NULL );
	
	void* data = lst->cursor->data;
	//if( lst->cursor->next != NULL )	// Let dlList fall of edge
	lst->cursor = lst->cursor->next;
	return data;
}

/// Returns current cursor data and moves to previous if any
void * dll_prev( DlList_T lst )
{
	assert( lst != NULL );
	
	void* data = lst->cursor->data;
	//if( lst->cursor->prev != NULL )	// Let dlList fall of edge
	lst->cursor = lst->cursor->prev;
	return data;
}

/// Returns size of passed list
int dll_size( DlList_T lst )
{
	return lst->length;
}

/// Adds element to end of list
void dll_append( DlList_T lst, void *data )
{
	assert( lst != NULL );
	
	struct Node* new = (struct Node*) malloc( sizeof(struct Node) );
	new->data = data;
	new->next = NULL;
	
	// IF LIST IS EMPTY
	if( lst->last == NULL )
	{
		lst->first = new;
		lst->last = new;
	}
	else
	{
		lst->last->next = new;
		new->prev = lst->last;
		lst->last = new;
	}
	lst->cursor = new;
	lst->length++;
}

/// Inserts element to designated location based on passed index
void dll_insert_at( DlList_T lst, int indx, void *data )
{
	assert( lst != NULL );
	assert( indx >=0 && indx < lst->length );
	
	struct Node* new = (struct Node*) malloc( sizeof(struct Node) );
	new->data = data;
	
	if( dll_move_to( lst, indx ) )
	{
		// EMPTY LIST
		if( dll_empty( lst ) )
		{
			dll_append( lst, data );
		}
		// FIRST
		else if( indx == 0 )
		{
			lst->first->prev = new;
			new->next = lst->first;
			lst->first = new;
		}
		else
		{
			lst->cursor = lst->cursor->prev;
			
			new->next = lst->cursor->next;
			lst->cursor->next = new;
			new->prev = lst->cursor;
			new->next->prev = new;
		}
	}
	lst->cursor = new;
	lst->length++;
}

/// Returns element at passed index
void * dll_get( DlList_T lst, int indx )
{
	assert( lst != NULL );
	assert( indx >=0 && indx < lst->length );
	
	// GET FIRST
	if( indx == 0 )
	{
		return lst->first->data;
	}
	// GET LAST
	else if( indx == lst->length-1 )
	{
		return lst->last->data;
	}
	// ELSE SEARCH
	else
	{
		struct Node* temp;
		temp = lst->first;
		for( int i = 0; i < indx; i++ )
		{
			temp = temp->next;
		}
		return temp->data;
	}
}

/// Sets the element of the passed index to the new data
void * dll_set( DlList_T lst, int indx, void *data )
{
	assert( lst != NULL );
	assert( indx >=0 && indx < lst->length );
	
	dll_move_to( lst, indx );
	void* info = lst->cursor->data;
	lst->cursor->data = data;
	return info;
}

/// Removes element at passed index
void * dll_pop( DlList_T lst, int indx )
{
	assert( lst != NULL );
	assert( lst->length != 0 );
	assert( indx >=0 && indx < lst->length );
	
	dll_move_to( lst, indx );
	void* data = lst->cursor->data;
		
	// ONE ELEMENT IN LIST
	if( indx == lst->length-1 && indx == 0 )
	{
		free( lst->first );
		lst->first = NULL;
		lst->last = NULL;
		lst->cursor = NULL;
	}
	// LAST ELEMENT
	else if ( indx == lst->length-1 )
	{
		struct Node* tail = NULL;
		struct Node* newTail = NULL;
		
		tail = lst->last;
		newTail = tail->prev;
		lst->last = newTail;
		free( tail );
		lst->cursor = newTail;
	}
	// FIRST ELEMENT
	else if( indx == 0 )
	{	
		struct Node* head = NULL;
		struct Node* newHead = NULL;
		
		head = lst->first;
		newHead = head->next;
		newHead->prev = NULL;
		free( head );
		lst->first = newHead;
		lst->cursor = newHead;
	}
	// OTHER
	else
	{
		struct Node* deletee = NULL;
		struct Node* prev = NULL;
		struct Node* next = NULL;
		
		deletee = lst->cursor;
		prev = deletee->prev;
		next = deletee->next;
		
		prev->next = next;
		next->prev = prev;
		free( deletee );
		lst->cursor = next;
	}
	lst->length--;
	
	return data;
}

/// Returns index of passed data
/// If data not found, returns -1
int dll_index( DlList_T lst, void *data )
{
	assert( lst != NULL );
	
	int ans = -1;
	int currentIndex = 0;
	struct Node* temp = lst->first;
	
	while( temp != NULL )
	{
		if( data == temp->data )
		{
			ans = currentIndex;
			break;
		}
		temp = temp->next;
		currentIndex++;
	}
	
	return ans;
}

/// Check if list is empty
bool dll_empty( DlList_T lst )
{
	return ( lst->length == 0);
}


/// // // // // // // // // // // // // // // // // // // // // // // //
/// Revisions:
/// $Log: dlList.c,v $
/// Revision 1.4  2014/04/15 17:06:07  csci243
/// next and prev now are able to go off edge of list
///
/// Revision 1.3  2014/04/15 16:40:46  csci243
/// Now can insert when list is empty
///
/// Revision 1.2  2014/04/09 17:42:27  csci243
/// Fixed insert and pop
/// Commented all
///
/// Revision 1.1  2014/04/07 16:39:52  csci243
/// Initial revision
///









