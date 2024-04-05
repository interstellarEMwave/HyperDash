#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define screenWidth 236
#define screenHeight 55
#define gameScreenHeight screenHeight - 5
#define mapWidth = screenWidth - 2
#define mapHeight = gameScreenHeight - 2

typedef unsigned __int8 u8;

char sprites[] = {' ', '\u2551', '\u2550', '\u2554', '\u2557', '\u255D', '\u255A'};

void
fillWithRandomNumbers(int* arr, int count, int lower, int upper)
{
	for(int i = 0; i < count; i++)
	{
		arr[i] = (rand() % (upper - lower + 1)) + lower;
	}
}

//Inlcudes upper
int
randint(int lower, int upper)
{
	return ((rand() % (upper - lower + 1)) + lower);
}




int
room_generateRandom(u8* map, int sizeMax, int attempts)
{
	int x = 0;
	int y = 0;
	int size[2] = {0};
	for(int i = 0; i < attempts; i++)
	{
		y = randint(0, mapHeight - 1);
		x = randint(0, mapWidth - 1);
		fillWithRandomNumbers(size, 2, 3, sizeMax);
		if(y + size[0] < mapHeight
		&& x + size[1] < mapWidth)
		{
			room_setInMap(map, y, x, size)
			


void
room_setInMap(u8* map, int y, int x, int[2] size)
{
	for(int i = y*mapWidth+x; i < y*width+x+size[1]; i++)
	{
		map[i] = 2;
		map[i + (size[0] - 1)*width] = 2;
	}
	for(int i = (y+1); i < y + size[0] - 1; i++)
	{
		map[i*mapWidth+x] = 2;
		map[i*mapWidth+x+size[1]-1] = 2;
		for(int j = i*width+x+1; j < i*width+x+size[1]-1; j++)
		{
			map[j] = 1;
		}
	}
}


void
drawRoom(u8* arr, int w, int y, int x, int roomHeight, int roomWidth)
{
	int width = w+1;
	for(int i = y*width+x; i < y*width+x+roomWidth; i++)
	{
		arr[i] = '#';
		arr[i + (roomHeight-1)*width] = '#';
	}
	for(int i = y*width+x; i < (y + roomHeight)*width; i += width)
	{
		arr[i] = '#';
		arr[i+roomWidth-1] = '#';
	}
}

void 
clearGamePrintBuffer(u8* gamePrintBuffer, int gamePrintBufferWidth)
{
	for(int i = 1; i < gameScreenHeight - 1; i++)
	{
		for(int j = 1; j < screenWidth - 1; j++)
		{
			gamePrintBuffer[i*gamePrintBufferWidth + j] = ' ';
		}
	}
}


int
main(int argc, int** argv)
{
	u8 gamePrintBuffer[(screenWidth+1)*gameScreenHeight] = {0};
	int gamePrintBufferWidth = screenWidth+1;
	clearGamePrintBuffer(gamePrintBuffer, gamePrintBufferWidth);	
	for(int i = 0; i < gamePrintBufferWidth; i++)
	{
		gamePrintBuffer[i] = '#';
		gamePrintBuffer[i + gamePrintBufferWidth*(gameScreenHeight-1)] = '#';
	}
	for(int i = 0; i < gameScreenHeight; i++)
	{
		gamePrintBuffer[i*gamePrintBufferWidth] = '#';
		gamePrintBuffer[i*gamePrintBufferWidth + screenWidth - 1] = '#';
		gamePrintBuffer[i*gamePrintBufferWidth + screenWidth] = '\n';
	}

	drawRoom(gamePrintBuffer, screenWidth, 1, 1, 5, 7);
	printf(gamePrintBuffer);

	return 0;
}


