/// testdlList.c
/// $Id: testdlList.h,v 1.2 2014/09/28 17:42:27 csci243 Exp $
///
/// Tests all methods in dlList.h that is
/// implemented by dlList.c
///
/// @author: jxz5746 Jacob Zuber
///

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include "dlList.h"

/// printIntList prints the current elements in the
/// passed list in int form
/// @param lst the linked list to print
/// @post lst is not changed
static void printIntList( DlList_T lst )
{
	printf("List of elements:\n");
	for( int i = 0; i < dll_size( lst ); i++ )
	{
		printf( "element #%d: %d\n",
				i, (unsigned int) dll_get( lst, i ) );
	}
}

/// Main method to test all methods in dlList
int main( void )
{
	DlList_T mydlList;
	mydlList = dll_create();
	
	// TEST APPEND
	printf("\nAppending 2\n");
	dll_append( mydlList, (int*) 2 );
	printf("Appending 6\n");
	dll_append( mydlList, (int*) 6 );
	printf("Appending 13\n");
	dll_append( mydlList, (int*) 13 );
	printf("Appending 3\n");
	dll_append( mydlList, (int*) 3 );
	printf("Appending 9\n");
	dll_append( mydlList, (int*) 9 );
	
	// TEST INSERT AND GET
	printf( "insert 57 at index 0\n");
			dll_insert_at( mydlList, 0, (int*) 57 );
	printf( "insert 19 at index 2\n");
			dll_insert_at( mydlList, 2, (int*) 19 );
	printf( "element at index 2: %d\n",
			(unsigned int) dll_get( mydlList, 2 ) );
	
	printf("Order should be 57, 2, 19, 6, 13, 3, 9\n\n");
	
	// DISPLAY LIST
	printIntList( mydlList );
	printf( "Size: %d\n\n", dll_size( mydlList ) );
	
	printf( "Remove element at index 0:\nRemoved element: %d\n\n",
				(unsigned int) dll_pop( mydlList, 0 ) );
				
	// DISPLAY LIST
	printIntList( mydlList );
	
	// TEST PREV AND NEXT AND HAS_NEXT
	printf( "\nmove to index 2\n" );
	dll_move_to( mydlList, 2 );
	printf( "Test prev- cursor should be at index 2 and move to index 1:"
				"\nelement at index 2: %d\n",
				(unsigned int) dll_prev( mydlList ) );
	printf( "Test has_next- Non-zero number: %d\n\n",
			dll_has_next( mydlList ) );
	printf( "Test next- cursor should be at index 1 and move to index 2:"
				"\nelement at index 1: %d\n",
				(unsigned int) dll_next( mydlList ) );
	printf( "Test has_next- Non-zero number: %d\n\n",
			dll_has_next( mydlList ) );
	printf( "Test prev- cursor should be at index 2 and move to index 1:"
				"\nelement at index 2: %d\n",
				(unsigned int) dll_prev( mydlList ) );
	printf( "Test has_next- Non-zero number: %d\n\n",
			dll_has_next( mydlList ) );
			
	
	// DISPLAY LIST
	printIntList( mydlList );
	
	// TEST MOVE_TO
	printf( "\nmove to index 19. int should be 0 to show fail: %d\n",
			dll_move_to( mydlList, 19 ) );
	printf( "move to index 4. int should be 1 to show move success: %d\n",
			dll_move_to( mydlList, 4 ) );
			
	// 	TEST NEXT MORE
	printf( "Test next- cursor should be at index 4 and move to index 5:"
				"\nelement at index 4: %d\n",
				(unsigned int) dll_next( mydlList ) );
	printf( "Test next- cursor should be at index 5 and stay at index 5:"
				"\nelement at index 5: %d\n",
				(unsigned int) dll_next( mydlList ) );
	printf( "Test next- cursor should be at index 5 and still stay at index 5:"
				"\nelement at index 5: %d\n",
				(unsigned int) dll_next( mydlList ) );
	printf( "Test has_next- Non-zero number: %d\n\n",
			dll_has_next( mydlList ) );
			
	// TEST MORE MOVE_TO
	printf( "move to index 0. int should be 1 to show move success: %d\n",
			dll_move_to( mydlList, 0 ) );
			
	// TEST PREV MORE
	printf( "Test prev- cursor should be at index 0 and stay at index 0:"
				"\nelement at index 0: %d\n",
				(unsigned int) dll_prev( mydlList ) );
	printf( "Test prev- cursor should be at index 0 and still stay at index 0:"
				"\nelement at index 0: %d\n",
				(unsigned int) dll_prev( mydlList ) );
	printf( "Test has_next- Non-zero number: %d\n\n",
			dll_has_next( mydlList ) );
	
	// DISPLAY LIST
	printIntList( mydlList );
	
	//	TEST SET
	printf( "\nTest Set- index 0 is now 7. Previous index 0: %d\n",
			(unsigned int) dll_set( mydlList, 0, (int*) 7 ) );
	printf( "First element: %d\n\n",
			(unsigned int) dll_get( mydlList, 0 ) );
	
	// DISPLAY LIST
	printIntList( mydlList );
	
	//TEST POP (REMOVAL)
	printf( "\nPop- first element: %d is gone\n",
			(unsigned int) dll_pop( mydlList, 0) );
	printf( "New first element: %d\n\n",
			(unsigned int) dll_get( mydlList, 0 ) );
			
	// DISPLAY LIST
	printIntList( mydlList );
	printf( "Pop- element at index 3: %d is gone\n",
			(unsigned int) dll_pop( mydlList, 3 ) );
	
	// DISPLAY LIST
	printIntList( mydlList );
	
	// TEST INDEX
	printf( "\nindex of 6 in list: %d\n",
			dll_index( mydlList, (int*) 6 ) );
	printf( "index of 77 in list (Should be not found: -1): %d\n\n",
			dll_index( mydlList, (int*) 77 ) );
	
	// DISPLAY LIST
	printIntList( mydlList );
	
	// TEST CLEAR
	printf( "Clearing list...\n");
	dll_clear( mydlList );
	
	// DISPLAY LIST
	printIntList( mydlList );
	printf( "Size: %d\n\n", dll_size( mydlList ) );
	
	printf( "append 2 and 7\n" );
	dll_append( mydlList, (int*) 2 );
	dll_append( mydlList, (int*) 7 );
	
	// DISPLAY LIST
	printIntList( mydlList );
	printf( "Size: %d\n\n", dll_size( mydlList ) );
	
	// TEST CASES OF POP:
	//		POP LAST ELEMENT
	//		POP WHEN ONE ELEMENT IN LIST
	printf( "Delete last element (index 1): %d is gone\n\n",
				(unsigned int) dll_pop( mydlList, 1 ) );
	printIntList( mydlList );
	printf( "\nDelete only element in list (index 0): %d is gone\n\n",
				(unsigned int) dll_pop( mydlList, 0 ) );
	
	// DISPLAY LIST
	printIntList( mydlList );
	printf( "Size: %d\n\n", dll_size( mydlList ) );
	
	// DESTROY
	dll_destroy( mydlList );
	
	return 0;
}