#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_MAX_WIDTH 236
#define SCREEN_MAX_HEIGHT 55

#define PRINT_MAX_WIDTH (SCREEN_MAX_WIDTH + 1)
#define PRINT_MAX_HEIGHT SCREEN_MAX_HEIGHT

#define MAP_MAX_WIDTH SCREEN_MAX_WIDTH
#define MAP_MAX_HEIGHT (SCREEN_MAX_HEIGHT - 5)
#define MAP_MAX_ROOMCOUNT ((SCREEN_MAX_WIDTH * SCREEN_MAX_HEIGHT)/9)

typedef unsigned __int8 u8;

//a

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
map_makeRoom(u8* map, int map_width, int topLeftY, int topLeftX, int roomHeight, int roomWidth, int openings)
{
	if(roomHeight < 3|| roomWidth < 3) return;

	int nrWalls = 2*roomHeight + 2*(roomWidth-2) - openings;

	for(int i = topLeftY*map_width + topLeftX; 
			i < topLeftY*map_width + topLeftX + roomWidth; 
			++i)
	{
		fillCellConditionally(map + i,							  &nrWalls, &openings, EMPTY, WALL);
		fillCellConditionally(map + i + (roomHeight-1)*map_width, &nrWalls, &openings, EMPTY, WALL);
	}
	for(int i = (topLeftY+1)*map_width + topLeftX;
			i < (topLeftY+roomHeight-1)*map_width + topLeftX;
			i += map_width)
	{
		fillCellConditionally(map + i,				 &nrWalls, &openings, EMPTY, WALL);
		fillCellConditionally(map + i + roomWidth-1, &nrWalls, &openings, EMPTY, WALL);
	}

	for(int i = (topLeftY+1)*map_width; i < (topLeftY+roomHeight-1)*map_width; i += map_width)
	{
		for(int j = topLeftX + 1; j < topLeftX + roomWidth - 1; ++j)
		{
			map[i+j] = EMPTY;
		}
	}
}


void
map_generateRooms(u8* map, int map_height, int map_width, int roomCountLower, int roomCountUpper)
{
	int roomCount = randInt(roomCountLower, roomCountUpper+1);
	
	for(int i = 0; i < roomCount*4; i += 4)
	{
		#if 0
		int y1 = randInt(0, map_height);
		int y2 = randInt(0, map_height);
		int x1 = randInt(0, map_width);
		int x2 = randInt(0, map_width);

		printf("%d %d %d %d\n",min(y1, y2), min(x1, x2), max(y1, y2)-min(y1,y2), max(x1, x2)-min(x1, x2)); 
		map_makeRoom(map, min(y1, y2), min(x1, x2), max(y1, y2)-min(y1,y2), max(x1, x2)-min(x1, x2), 0);
		#else
		int vertical = randInt(3, map_height);
		int horizontal = randInt(3, map_width);
		int h = randInt(3, vertical+1);
		int w = randInt(3, horizontal+1);

		map_makeRoom(map, map_width, vertical-h, horizontal-w, h, w, 0);
		#endif	
	}
}


void
print_bufferClear(u8* print_buffer)
{
	for(int i = 0; i < PRINT_MAX_HEIGHT; ++i)
	{
		for(int j = 0; j < PRINT_MAX_WIDTH; ++j)
		{
			print_buffer[i*PRINT_MAX_WIDTH + j] = sprites[EMPTY];
		}
	}
}


void
print_fillGameScreen(u8* map, u8* print_buffer, int map_height, int map_width)
{
	for(int i = 0; i < map_height; ++i) 
	{
		for(int  j = 0; j < map_width; ++j) print_buffer[i*PRINT_MAX_WIDTH + j] = sprites[map[i*map_width + j]];
	}
}

int
main(int argc, int** argv)
{
	int map_height = MAP_MAX_HEIGHT/2;
	int map_width = MAP_MAX_WIDTH/2;
	int print_height = map_height;
	int print_width = map_width + 1;
	
	
	u8 print_buffer[PRINT_MAX_HEIGHT * PRINT_MAX_WIDTH + 1] = {0};
	u8 map[MAP_MAX_HEIGHT * MAP_MAX_WIDTH] = {0};

	print_bufferClear(print_buffer);
	for(int i = 0; i < PRINT_MAX_HEIGHT; ++i) print_buffer[i*PRINT_MAX_WIDTH + PRINT_MAX_WIDTH-1] = '\n';
	srand(time(NULL));
	

	//map_makeRoom(map, 0, 0, MAP_HEIGHT, MAP_WIDTH, 1); 
	map_generateRooms(map, map_height, map_width, 7, 15);

	print_fillGameScreen(map, print_buffer, map_height, map_width);	
	printf("%s", print_buffer);
}

/*
 |
-+- 
 |  
	  

+

*/
