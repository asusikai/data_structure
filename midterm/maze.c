// maze

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char maze[9][16];
	FILE *f;
	f = fopen("maze.txt", "r");
	int i, j;
	
	for(i=0; i<19; i++)
	{
		fscanf(f, "%s", maze[i]);
	}
	
	for(i = 0; i<9; i++)
	{
		//for(j=0; j<20; j++)
		{
			printf("%s", maze[i]);
		}
		printf("\n");
	}
}
