#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "dlList.h"

int main( void )
{
	DlList_T mydlList;
	mydlList = dll_create();
	
	char el1[10];
	char el2[10];
	char el3[10];
	char el4[10];
	char el5[10];
	
	strcpy( el1, "hello" );
	//fgets( el1, 10, stdin );
	strcpy( el2, "work" );
	strcpy( el3, "please" );
	strcpy( el4, "plox" );
	strcpy( el5, "goodbye" );
	
	dll_append( mydlList, el1 );
	dll_append( mydlList, el2 );
	printf( "\nelement #0: %s\n", (char*) dll_get( mydlList, 0 ) );
	dll_append( mydlList, el3 );
	dll_append( mydlList, el4 );
	printf( "\nelement #0: %s\n", (char*) dll_get( mydlList, 0 ) );
	dll_append( mydlList, el5 );
	
	printf( "List of elements:\n" );
	for( int i = 0; i < dll_size( mydlList ); i++ )
	{
		printf( "element #%d: %s\n",
				i, (char*) dll_get( mydlList, i ) );
	}
	printf( "\nelement #0: %s\n", (char*) dll_get( mydlList, 0 ) );
	
	
	/*
	printf("Enter line to put into list(^D to exit):\n");
	char buff[80];
	while( fgets( buff, 80, stdin ) != NULL )
	{
		dll_append( mydlList, buff );
		char* first;
		first = (char*) dll_get( mydlList, 0 );
		printf( "List Size: %d\nData at index 0: %s\n",
			dll_size( mydlList ), first );
		printf("Enter line to put into list(^D to exit):\n");
	}
	*/
	
	/*
	printf("Enter int to put into list(^D to exit):\n");
	char buff[80];
	while( fgets( buff, 80, stdin ) != NULL )
	{
		int x = atoi( buff );
		dll_append( mydlList, (int*) x );
		int first;
		first = (int) dll_get( mydlList, 0 );
		printf( "List Size: %d\nData at index 0: %d\n",
			dll_size( mydlList ), first );
		printf("Enter line to put into list(^D to exit):\n");
	}
	*/
	
	return 0;
}