#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 236
#define SCREEN_HEIGHT 55

#define PRINT_WIDTH (SCREEN_WIDTH + 1)
#define PRINT_HEIGHT SCREEN_HEIGHT

#define MAP_WIDTH SCREEN_WIDTH
#define MAP_HEIGHT (SCREEN_HEIGHT - 5)
#define MAP_MAX_ROOMCOUNT ((SCREEN_WIDTH * SCREEN_HEIGHT)/9)

typedef unsigned __int8 u8;

typedef enum
ENUM_cellType
{
	EMPTY,
	WALL,
	FLOOR

} ENUM_cellType;

char sprites[] = {' ', '#', '.'};

//char sprites[] = {' ', '\u2551', '\u2550', '\u2554', '\u2557', '\u255D', '\u255A', '\0'};

void
fillWithRandomNumbers(int* arr, int count, int lower, int upper)
{
	for(int i = 0; i < count; i++)
	{
		arr[i] = randInt(lower, upper);
	}
}

int
randInt(int lower, int upper)
{
	//if(lower == upper) return lower;
	return ((rand() % (upper - lower)) + lower);
}




void
map_makeRoom(u8* map, int topLeftY, int topLeftX, int roomHeight, int roomWidth)
{
	for(int i = topLeftY*MAP_WIDTH + topLeftX; 
			i < topLeftY*MAP_WIDTH + topLeftX + roomWidth; 
			++i)
	{
		map[i] = WALL;
		map[i + (roomHeight-1)*MAP_WIDTH] = WALL;
	}
	for(int i = topLeftY*MAP_WIDTH + topLeftX;
			i < (topLeftY+roomHeight)*MAP_WIDTH + topLeftX;
			i += MAP_WIDTH)
	{
		map[i] = WALL;
		map[i+roomWidth-1] = WALL;
	}

	for(int i = (topLeftY+1)*MAP_WIDTH; i < (topLeftY+roomHeight-1)*MAP_WIDTH; i += MAP_WIDTH)
	{
		for(int j = topLeftX + 1; j < topLeftX + roomWidth - 1; ++j)
		{
			map[i+j] = EMPTY;
		}
	}
}


void
map_generateRooms(u8* map, int roomCountLower, int roomCountUpper)
{
	int roomCount = randInt(roomCountLower, roomCountUpper+1);
	
	for(int i = 0; i < roomCount*4; i += 4)
	{
		int vertical   =	randInt(3, MAP_HEIGHT);	
		int horizontal =	randInt(3, MAP_WIDTH);	
		int h =		randInt(3, vertical+1);
		int w =		randInt(3, horizontal+1);

		map_makeRoom(map, vertical-h, horizontal-w, h, w);
	}
}


void
print_bufferClear(u8* print_buffer)
{
	for(int i = 0; i < PRINT_HEIGHT; ++i)
	{
		for(int j = 0; j < PRINT_WIDTH-1; ++j)
		{
			print_buffer[i*PRINT_WIDTH + j] = sprites[EMPTY];
		}
	}
}


void
print_fillGameScreen(u8* map, u8* print_buffer)
{
	for(int i = 0; i < MAP_HEIGHT; ++i) 
	{
		for(int  j = 0; j < MAP_WIDTH; ++j) print_buffer[i*PRINT_WIDTH + j] = sprites[map[i*MAP_WIDTH + j]];
	}
}

int
main(int argc, int** argv)
{
	u8 print_buffer[PRINT_HEIGHT * PRINT_WIDTH + 1] = {0};
	u8 map[MAP_HEIGHT * MAP_WIDTH] = {0};

	print_bufferClear(print_buffer);
	for(int i = 0; i < PRINT_HEIGHT; ++i) print_buffer[i*PRINT_WIDTH + PRINT_WIDTH-1] = '\n';
	srand(time(NULL));
	


	map_makeRoom(map, 0, 0, MAP_HEIGHT, MAP_WIDTH); 
	map_generateRooms(map, 20, 50);

	print_fillGameScreen(map, print_buffer);	
	printf("%s", print_buffer);
}


