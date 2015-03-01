/// mrEd.c
/// $Id: mrEd.h,v 1.3 2014/04/15 16:40:46 csci243 Exp $
///
/// A line-based editor maintains the concept
/// of the current line within a buffer that holds
/// the text. The ed editor stores the text line-by-line
/// as a sequence of text strings, and the
/// user can move the current line forward or back
/// one or more lines up to the limit of the
/// start and end of the buffer.
///
/// @author: jxz5746 Jacob Zuber
///

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "dlList.h"


/// Gets the data at the cursor in the passed list
/// @param lst list to get data from
/// @param data char array to put the data at cursor in
/// @post: data contains the element the cursor is pointing to
///				or NULL if the list is empty
static char* getCursor( DlList_T lst )
{
	assert( lst != NULL );
	
	if( dll_empty( lst ) )
	{
		return NULL;
	}

	char* data = (char*) dll_next( lst );
	int index = dll_index( lst, data );
	if( index == -1 )
	{
		printf( "Something messed up!\n" );
	}
	dll_move_to( lst, index );
	return data;
}

/// Gets the next element in the passed list
/// @param lst list to get data from
/// @param data char array to put next data in
/// @post: data is NULL if there is no next element
///			else it is element next in the list
static char* getNext( DlList_T lst )
{
	assert( lst != NULL );
	
	if( dll_empty( lst ) )
	{
		return NULL;
	}
	
	char* prevData = (char*) dll_next( lst );
	if( dll_has_next( lst ) == 0 )
	{
		int index = dll_index( lst, prevData );
		dll_move_to( lst, index );
		return NULL;
	}
	//char* nextData = (char*) malloc( 80 );
	//nextData = getCursor( lst );
	return getCursor( lst );
}

/// Gets the previous element in the passed list
/// @param lst list to get data from
/// @param data char array to put previous data in
/// @post: data is NULL if there is no previous element
///			else it is the element previous in the list
static char* getPrev( DlList_T lst )
{
	assert( lst != NULL );
	
	if( dll_empty( lst ) )
	{
		return NULL;
	}
	
	char* nextData = (char*) dll_prev( lst );
	if( dll_has_next( lst ) == 0 )
	{
		int index = dll_index( lst, nextData );
		dll_move_to( lst, index );
		return NULL;
	}
	//char* prevData = (char*) malloc( 80 );
	//prevData = getCursor( lst );
	return getCursor( lst );
}

/// Main method that runs the mrEd program
int main( int argc, char * argv[] )
{
	DlList_T mydlList = dll_create();
	FILE* file = NULL;
	char* fileName = NULL;
	
	// Get file if there is one
	if( argc == 2 )
	{
		fileName = argv[1];
		file = fopen( fileName, "r" );
		
		if( !file )
		{
			perror( fileName );
		}
		if( file != NULL )
		{
			char* addTo = (char*) malloc( 80 );
			while( fgets( addTo, 80, file ) != NULL )
			{
				dll_append( mydlList, addTo );
				addTo = (char*) malloc( 80 );
			}
			free( addTo );
			fclose( file );
		}
		else
		{
			printf( "could not read \'%s\'\n", fileName );
		}
	}
	
	char* wCheck = NULL;
	char* wqCheck = NULL;
	char* str = NULL;
	int isSaved = true;
	
	while( true )
	{
		str = (char*) malloc( 80 );
		str = fgets( str, 80, stdin );
		
		wCheck = (char*) malloc( 5 );
		wCheck = strncpy( wCheck, str, 3 );
		
		wqCheck = (char*) malloc( 5 );
		wqCheck = strncpy( wqCheck, str, 4 );
		
		// APPEND
		if( strcmp( str, "a\n" ) == 0 )
		{
			// GET NEXT AND INSERT BEFORE IT
			char* insBefore = getNext( mydlList );
			char* apnd = (char*) malloc( 80 );
			
			while( strcmp( fgets( apnd, 80, stdin ), ".\n" ) != 0 )
			{
				// IF THERE ISN'T A NEXT
				if( insBefore == NULL )
				{
					dll_append( mydlList, apnd );
				}
				else
				{
					int i = dll_index( mydlList, insBefore );
					dll_insert_at( mydlList, i, apnd );
				}
				
				apnd = (char*) malloc( 80 );
			}
			free( apnd );
			isSaved = false;
		}
		
		// PRINT CURRENT
		else if( strcmp( str, ".\n" ) == 0 )
		{
			char* current = getCursor( mydlList );
			if( current == NULL )
				printf( "?\n" );
			else
				printf( "%s", current );
		}
		
		// PRINT NEXT
		else if( strcmp( str, "+\n" ) == 0 || strcmp( str, "\n" ) == 0 )
		{
			char* next = getNext( mydlList );
			if( next == NULL )
				printf( "?\n" );
			else
				printf( "%s", next );
		}
		
		// PRINT PREV
		else if( strcmp( str, "-\n" ) == 0 )
		{
			char* prev = getPrev( mydlList );
			if( prev == NULL )
				printf( "?\n" );
			else
				printf( "%s", prev );
		}
		
		// MOVE TO LAST AND PRINT
		else if( strcmp( str, "$\n" ) == 0 )
		{
			if( dll_empty( mydlList ) )
				printf( "?\n" );
			else
			{
				dll_move_to( mydlList, dll_size( mydlList ) - 1 );
				printf( "%s", getCursor( mydlList ) );
			}
		}
		
		// DELETE CURRENT
		else if( strcmp( str, "d\n" ) == 0 )
		{
			if( dll_empty( mydlList ) )
				printf( "?\n" );
			else
			{
				// Pop element at index of cursor data
				char* data = dll_pop( mydlList, dll_index( 
										mydlList, getCursor( mydlList ) ) );
				free( data );
				isSaved = false;
			}
		}
		
		// INSERT
		else if( strcmp( str, "i\n" ) == 0 )
		{
				char* ins = (char*) malloc( sizeof( 80 ) );
				char* beforeCurrent = (char*) getCursor( mydlList );
				int startSize = dll_size( mydlList );
				while( strcmp( fgets( ins, 80, stdin ), ".\n" ) != 0 )
				{
					if( startSize == 0 && beforeCurrent == NULL )
					{
						dll_append( mydlList, ins );
					}
					else
					{
						// get index of data to insert before.
						int i = dll_index( mydlList, beforeCurrent );
						dll_insert_at( mydlList, i, ins );
					}
					ins = (char*) malloc( sizeof( 80 ) );
				}
				free( ins );
				isSaved = false;
			
		}
		
		// PRINT CURRENT LINE NUMBER- 0 IF EMPTY
		else if( strcmp( str, ".=\n" ) == 0 )
		{
			if( dll_empty( mydlList ) )
				printf( "%d\n", 0 );
			else
			{
				int index = dll_index( mydlList, getCursor( mydlList ) );
				if( index == -1 )
					printf( "Something messed up\n" );
				else
					printf( "%d\n", index + 1 );
			}
		}
		
		// PRINT NUMBER OF LAST LINE
		else if( strcmp( str, "$=\n" ) == 0 )
		{
			if( dll_empty( mydlList ) )
				printf( "?\n" );
			else
				printf( "%d\n", dll_size( mydlList ) );
		}
		
		// PRINT ALL ELEMENTS
		else if( strcmp( str, "P\n" ) == 0 )
		{
			for( int i = 0; i < dll_size( mydlList ); i++ )
			{
				printf( "%s", (char*) dll_get( mydlList, i ) );
			}
			dll_move_to( mydlList, dll_size( mydlList ) - 1 );
		}
		
		// SAVE TO ORIGINAL FILE AND QUIT
		else if( strcmp( wqCheck, "wq\n" ) == 0 )
		{
			if( fileName != NULL )
			{
				file = fopen( fileName, "w" );
				for( int i = 0; i < dll_size( mydlList ); i++ )
				{
					fputs( dll_get( mydlList, i ), file );
				}
				printf( "file name: \'%s\'\n", fileName );
				isSaved = true;
				fclose( file );
				break;
			}
			else
			{
				printf( "?\n" );
			}
		}
		// SAVE TO GIVEN FILE AND QUIT
		else if( strncmp( wqCheck, "wq ", 3 ) == 0 )
		{
			strcpy( fileName, str + 3 );
			strtok(fileName, "\n");
			file = fopen( fileName, "w" );
			for( int i = 0; i < dll_size( mydlList ); i++ )
			{
				fputs( dll_get( mydlList, i ), file );
			}
			printf( "file name: \'%s\'\n", fileName );
			isSaved = true;
			fclose( file );
			break;
		}
		
		// SAVE TO ORIGINAL FILE
		else if( strcmp( wCheck, "w\n" ) == 0 )
		{
			if( fileName != NULL )
			{
				file = fopen( fileName, "w" );
				for( int i = 0; i < dll_size( mydlList ); i++ )
				{
					fputs( dll_get( mydlList, i ), file );
				}
				printf( "file name: \'%s\'\n", fileName );
				isSaved = true;
				fclose( file );
			}
			else
			{
				printf( "?\n" );
			}
		}
		
		// SAVE TO GIVEN FILE
		else if( strncmp( wCheck, "w ", 2 ) == 0 )
		{
			strcpy( fileName, str + 2 );
			strtok(fileName, "\n");
			file = fopen( fileName, "w" );
			for( int i = 0; i < dll_size( mydlList ); i++ )
			{
				fputs( dll_get( mydlList, i ), file );
			}
			printf( "file name: \'%s\'\n", fileName );
			isSaved = true;
			fclose( file );
		}
		
		// QUIT BUFFER IF IT HAS SAVED WITH A W COMMAND
		else if( strcmp( str, "q\n" ) == 0 )
		{
			if( isSaved )
				break;
			else
				printf( "? buffer dirty.\n" );
		}
		
		// QUIT REGARDLESS OF SAVE
		else if( strcmp( str, "Q\n" ) == 0 )
		{
			break;
		}
		
		// NUMBERS
		else if( atoi( str ) >= 1 && atoi( str ) <= dll_size( mydlList ) )
		{
			int moveTo = atoi( str );
			dll_move_to( mydlList, moveTo - 1 );
			
			printf( "%s", getCursor( mydlList ) );
		}
		else
		{
			printf( "?\n" );
		}
		
		free( str );
		free ( wCheck );
		free( wqCheck );
	}
	
	free( str );
	free( wCheck );
	free( wqCheck );
	dll_destroy( mydlList );
	printf( "Bye\n" );
	
	return 0;
}

/// // // // // // // // // // // // // // // // // // // // // // // //
/// Revisions:
/// $Log: mrEd.c,v $
/// Revision 1.4 2014/04/15 19:52:36  csci243
/// Closed all files. Added readfile checks
///
/// Revision 1.3 2014/04/15 16:40:46  csci243
/// Fixed insert and append:
///  insert can insert into an empty list
///  append now adds item after cursor instead of end of list
///
/// Revision 1.2  2014/04/14 17:19:17  csci243
/// Made it so any file given is valid
/// program will not end
///
/// Revision 1.1  2014/04/12 18:38:45  csci243
/// Initial revision
///






