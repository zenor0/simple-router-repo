#include <stdio.h>
#include <stdbool.h>
#define EMPTY_VAL -1

enum DIRE
{
	NORTH, EAST, SOUTH, WEST
} direction;

typedef struct POSITION
{
	int x;
	int y;
} POS;


int row, col;
POS WalkAStep(int dir, POS pos);
int ReportVal(int mat[row + 2][col + 2], POS pos);


int main(void)
{
	//input
	scanf("%d %d", &row, &col);
	
	int mapMatrix[row + 2][col + 2];
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			mapMatrix[i][j] = EMPTY_VAL;
		}
	}
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			scanf("%d", &mapMatrix[i][j]);
		}
	}
	
	
	direction = EAST;
	POS pos = {1, 1};
	
	int ttlStep = row * col - 1;
	int DBCount = mapMatrix[pos.x][pos.y] * -1;
	for (int i = 0; i < ttlStep; i++)
	{
		mapMatrix[pos.x][pos.y] = EMPTY_VAL;
		
		if (ReportVal(mapMatrix, WalkAStep(direction, pos)) == EMPTY_VAL)
		{
			direction = (direction + 1) % 4;
		}
		
		pos = WalkAStep(direction, pos);
	}
	
	printf("%d", DBCount + mapMatrix[pos.x][pos.y]);
	
	return 0;
}

POS WalkAStep(int dir, POS pos)
{
	switch (dir)
	{
	case NORTH:
		pos.x--;
		break;
	case EAST:
		pos.y++;
		break;
	case SOUTH:
		pos.x++;
		break;
	case WEST:
		pos.y--;
		break;
	}
	
	return pos;
}

int ReportVal(int mat[row + 2][col + 2], POS pos)
{
	return mat[pos.x][pos.y];
}

