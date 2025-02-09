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



char
randPull(int* pool, int numberOfUniques)
{
	int sum = 0;
	for(int i = 0; i < numberOfUniques; ++i) sum += pool[i];
	
	int a = randInt(0, sum);
	
	for(int i = 0; i < numberOfUniques; ++i)
	{
		if(a < pool[i]) return i;
		else a -= pool[i];
	}
	
	//Should never happen
	return -1;
}


void
fillCellConditionally(char* pos, int* walls, int* openings, ENUM_cellType true, ENUM_cellType false)
{
	if(randPull((int[2]){*walls, *openings}, 2))
	{
		*pos = true;
		(*openings)--;
	}
	else
	{
		*pos = false;
		(*walls)--;
	}
}


void
map_makeRoom(u8* map, int topLeftY, int topLeftX, int roomHeight, int roomWidth, int openings)
{
	if(roomHeight < 3|| roomWidth < 3) return;

	int nrWalls = 2*roomHeight + 2*(roomWidth-2) - openings;

	for(int i = topLeftY*MAP_WIDTH + topLeftX; 
			i < topLeftY*MAP_WIDTH + topLeftX + roomWidth; 
			++i)
	{
		fillCellConditionally(map + i,							  &nrWalls, &openings, EMPTY, WALL);
		fillCellConditionally(map + i + (roomHeight-1)*MAP_WIDTH, &nrWalls, &openings, EMPTY, WALL);
	}
	for(int i = (topLeftY+1)*MAP_WIDTH + topLeftX;
			i < (topLeftY+roomHeight-1)*MAP_WIDTH + topLeftX;
			i += MAP_WIDTH)
	{
		fillCellConditionally(map + i,				 &nrWalls, &openings, EMPTY, WALL);
		fillCellConditionally(map + i + roomWidth-1, &nrWalls, &openings, EMPTY, WALL);
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
		#if 0
		int y1 = randInt(0, MAP_HEIGHT);
		int y2 = randInt(0, MAP_HEIGHT);
		int x1 = randInt(0, MAP_WIDTH);
		int x2 = randInt(0, MAP_WIDTH);

		printf("%d %d %d %d\n",min(y1, y2), min(x1, x2), max(y1, y2)-min(y1,y2), max(x1, x2)-min(x1, x2)); 
		map_makeRoom(map, min(y1, y2), min(x1, x2), max(y1, y2)-min(y1,y2), max(x1, x2)-min(x1, x2), 0);
		#else
		int vertical = randInt(3, MAP_HEIGHT);
		int horizontal = randInt(3, MAP_WIDTH);
		int h = randInt(3, vertical+1);
		int w = randInt(3, horizontal+1);

		map_makeRoom(map, vertical-h, horizontal-w, h, w, 0);
		#endif	
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
	

	//map_makeRoom(map, 0, 0, MAP_HEIGHT, MAP_WIDTH, 1); 
	map_generateRooms(map, 15, 25);

	print_fillGameScreen(map, print_buffer);	
	printf("%s", print_buffer);
}

/*
 |
-+- 
 |  
	  

+

*/
