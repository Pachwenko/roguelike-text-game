#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// For reference, spaces are rocks ' ', floors are periods '.', corridors are hashes '#',
// upward staircase are less than '<', downward stairs are greater than '>'

#define DUNGEONCOLS 80
#define DUNGEONROWS 21
#define NUMROOMS 6
#define MINROOMWIDTH 4
#define MINROOMHEIGHT 3

void printDungeon(char **dungeon);
char **initializeDungeon();
void freeDungeon(char **dungeon);
void createRooms(char **dungeon);
int isImmuteable(char value);
int isValid(char value);
int canPlaceRoom(char **dungeon, int x, int y, int width, int height);
void placeRoom(char **dungeon, int x, int y, int width, int height);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    char **dungeon = initializeDungeon();
    createRooms(dungeon);

    printDungeon(dungeon);
    freeDungeon(dungeon);
    return 0;
}

char **initializeDungeon()
{
    char **dungeon;
    //allocate pointers to the rows of our dungeon
    dungeon = malloc(DUNGEONROWS * sizeof(char *));

    if (dungeon == NULL)
    {
        fprintf(stderr, "Dungeon is null - out of memory\n");
        exit(0);
    }

    //now allocate enough columns for each row
    int i = 0;
    for (i = 0; i < DUNGEONROWS; i++)
    {
        dungeon[i] = malloc(DUNGEONCOLS * sizeof(char *));
        if (dungeon[i] == NULL)
        {
            fprintf(stderr, "Out of memory - allocating dungeolCols");
            exit(0);
        }
    }

    int row, col = 0;
    for (row = 0; row < DUNGEONROWS; row++)
    {
        for (col = 0; col < DUNGEONCOLS; col++)
        {
            dungeon[row][col] = ' ';
        }
    }
    for (row = 0; row < DUNGEONROWS; row++)
    {
        dungeon[row][0] = '|';
        dungeon[row][DUNGEONCOLS - 1] = '|';
    }
    for (col = 0; col < DUNGEONCOLS; col++)
    {
        dungeon[0][col] = '-';
        dungeon[DUNGEONROWS - 1][col] = '-';
    }
    return dungeon;
}

void printDungeon(char **dungeon)
{
    int row, col = 0;
    for (row = 0; row < DUNGEONROWS; row++)
    {
        for (col = 0; col < DUNGEONCOLS; col++)
        {
            printf("%c", dungeon[row][col]);
        }
        printf("\n");
    }
}

void freeDungeon(char **dungeon)
{
    int i = 0;
    for (i = 0; i < DUNGEONROWS; i++)
    {
        free(dungeon[i]);
    }
    free(dungeon);
}

int isImmuteable(char value)
{
    if (value == '-' || value == '|')
    {
        return 1;
    }
    return 0;
}

int isValid(char value)
{
    if (isImmuteable(value) || value == '.' || value == '#' || value == '<' || value == '>')
    {
        return 0;
    }
    return 1;
}

void createRooms(char **dungeon)
{
    int rooms = 0;
    while (rooms < NUMROOMS)
    {
        // TODO: replace width and height with random values

        int width = MINROOMWIDTH + (rand() % 7 + 1);
        int height = MINROOMHEIGHT + (rand() % 7 + 1);

        int x = (rand() % DUNGEONCOLS) + 1;
        int y = (rand() % DUNGEONROWS) + 1;
        // check if the room can be placed
        if (canPlaceRoom(dungeon, x, y, width, height))
        {
            rooms++;
            placeRoom(dungeon, x, y, width, height);
        }
    }
}

int canPlaceRoom(char **dungeon, int x, int y, int width, int height)
{
    if ((x + width + 1) > DUNGEONCOLS || (y + height + 1) > DUNGEONROWS)
    {
        return 0;
    }
    int row, col = 0;
    for (col = x; col < x + width; col++)
    {
        for (row = y; row < y + height; row++)
        {
            if (!(isValid(dungeon[row-1][col-1]) && isValid(dungeon[row][col-1])
                && isValid(dungeon[row-1][col]) && isValid(dungeon[row][col])
                && isValid(dungeon[row+1][col]) && isValid(dungeon[row][col+1])
                && isValid(dungeon[row+1][col+1])))
            {
                return 0;
            }
        }
    }
    return 1;
}

void placeRoom(char **dungeon, int x, int y, int width, int height)
{
    // Attempting to follow the column first standard
    int col, row = 0;
    for (col = x; col < x + width; col++)
    {
        for (row = y; row < y + height; row++)
        {
            dungeon[row][col] = '.';
        }
    }
}