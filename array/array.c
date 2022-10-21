#include <stdio.h>
#define N 5
#define M 10

int main()
{
	
	printf("Task 1:\n");

	int matrix_one[N][N];
	int num = 1;
	for(int i=0;i<N;i++)
	{
		for(int j=0; j<N; j++)
		{
			matrix_one[i][j] = num++;
			printf("%d\t",matrix_one[i][j]);
		}
		printf("\n");
	}


	printf("\n\nTask 2:\n");
	int array[M] = {0,1,2,3,4,5,6,7,8,9};
	for(int i = 0; i < M; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
	for(int i = M-1; i >= 0; i--)
	{
		printf("%d ",array[i]);
	}

	printf("\n\nTask 3:\n");
	int matrix_two[N][N];
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			
			if(i < N-j-1)
			{
				matrix_two[i][j] = 0;
			}
			else
			{
				matrix_two[i][j] = 1;
			}
			printf("%d ",matrix_two[i][j]);
		}
		printf("\n");
	}

	printf("\n\nTask 4:\n");


	int matrix_three[N][N];
	int x = 0, y = 0, number = 1;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			matrix_three[i][j] = 0;
		}
	}
	
	
	for(int i = 0; i < N; i++)
	{

		for(; y < N; y++)
		{
			if(matrix_three[x][y] != 0) 
			{
				break;
			}
			matrix_three[x][y] = number++;
		}
		y--;
		x++;
		
		for(; x < N; x++)
		{
			if(matrix_three[x][y] != 0)
			{
				break;
			}
			matrix_three[x][y] = number++;	
		}
		x--;
		y--;
		for(; y > -1; y--)
		{
			if(matrix_three[x][y] != 0)
			{
				break;
			}
			matrix_three[x][y] = number++;	
		}
		y++;
		x--;
		for(; x > -1; x--)
		{
			if(matrix_three[x][y] != 0)
			{
				break;
			}
			matrix_three[x][y] = number++;	
		}
		x++;
		y++;
	}
	printf("\n\n");
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%d\t",matrix_three[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	return 0;
}
