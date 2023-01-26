#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "logic.h"
#include "helper.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{
    ifstream inFS;
    inFS.open(fileName);
    if (!inFS.is_open())
    {
        return nullptr;
    }

    string hold = "";
    getline(inFS, hold);
    stringstream ss = stringstream(hold);

    // test for invalid numRow data
    string hold_row = "";
    ss >> hold_row;
    try
    {
        maxRow = stoi(hold_row);
    }
    catch (...)
    {
        return nullptr;
    }
    if (ss.fail())
    {
        return nullptr;
    }
    if (maxRow <= 0)
    {
        return nullptr;
    }

    // test for invalid numCol data
    string hold_col = "";
    ss >> hold_col;
    try
    {
        maxCol = stoi(hold_col);
    }
    catch (...)
    {
        return nullptr;
    }
    if (ss.fail())
    {
        return nullptr;
    }
    if (maxCol <= 0)
    {
        return nullptr;
    }

    // test for good tile size
    if ((maxRow > INT32_MAX / maxCol) || (maxCol > INT32_MAX / maxRow))
    {
        return nullptr;
    }

    // test for invalid player row
    getline(inFS, hold);
    ss = stringstream(hold);
    string player_row = "";
    ss >> player_row;
    try
    {
        player.row = stoi(player_row);
    }
    catch (...)
    {
        return nullptr;
    }
    if (ss.fail())
    {
        return nullptr;
    }
    if (player.row < 0 || player.row >= maxRow)
    {
        return nullptr;
    }

    // test for invalid player column
    string player_col = "";
    ss >> player_col;
    try
    {
        player.col = stoi(player_col);
    }
    catch (...)
    {
        return nullptr;
    }
    if (ss.fail())
    {
        return nullptr;
    }
    if (player.col < 0 || player.col >= maxCol)
    {
        return nullptr;
    }

    // fill up map
    char **map = createMap(maxRow, maxCol);
    bool is_exit = false;
    bool is_door = false;
    for (int i = 0; i < maxRow; i++)
    {
        try
        {
            hold = "";
            getline(inFS, hold);
        }
        catch (...)
        {
            deleteMap(map, maxRow);
            return nullptr;
        }
        if (hold == "")
        {
            deleteMap(map, maxRow);
            return nullptr;
        }
        ss = stringstream(hold);
        for (int j = 0; j < maxCol; j++)
        {
            string map_tile = "";
            ss >> map_tile;
            // populate player tile
            if (i == player.row && j == player.col)
            {
                map[i][j] = 'o';
            }
            // invalid tiles or not enough tiles
            else if ((map_tile != "o") && (map_tile != "-") && (map_tile != "$") && (map_tile != "@") && (map_tile != "M") && (map_tile != "+") && (map_tile != "?") && (map_tile != "!"))
            {
                deleteMap(map, maxRow);
                return nullptr;
            }
            // populate other tiles
            else
            {
                if (map_tile == "o")
                {
                    map[i][j] = '-';
                }
                if (map_tile == "-")
                {
                    map[i][j] = '-';
                }
                else if (map_tile == "$")
                {
                    map[i][j] = '$';
                }
                else if (map_tile == "@")
                {
                    map[i][j] = '@';
                }
                else if (map_tile == "M")
                {
                    map[i][j] = 'M';
                }
                else if (map_tile == "+")
                {
                    map[i][j] = '+';
                }
                else if (map_tile == "?")
                {
                    map[i][j] = '?';
                    is_door = true;
                }
                else if (map_tile == "!")
                {
                    map[i][j] = '!';
                    is_exit = true;
                }
            }
        }
    }

    // no way out exists
    if (!is_exit && !is_door)
    {
        deleteMap(map, maxRow);
        return nullptr;
    }

    try
    {
        hold = "";
        getline(inFS, hold);
    }
    // catches if number of values is correct
    catch (...)
    {
        return map;
    }
    // if too many values
    if (hold != "")
    {
        deleteMap(map, maxRow);
        return nullptr;
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int &nextRow, int &nextCol)
{
    if (input == 'w')
    {
        nextRow -= 1;
    }
    if (input == 'a')
    {
        nextCol -= 1;
    }
    if (input == 's')
    {
        nextRow += 1;
    }
    if (input == 'd')
    {
        nextCol += 1;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char **createMap(int maxRow, int maxCol)
{
    // create empty map
    char **map = new char *[maxRow] {};
    for (int m = 0; m < maxRow; m++)
    {
        map[m] = new char[maxCol]{};
    }

    // create map of open tiles
    for (int k = 0; k < maxRow; k++)
    {
        for (int l = 0; l < maxCol; l++)
        {
            map[k][l] = '-';
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char **&map, int &maxRow)
{
    if (map == nullptr)
    {
        map = nullptr;
        maxRow = 0;
        return;
    }

    if (maxRow <= 0)
    {
        map = nullptr;
        maxRow = 0;
        return;
    }

    for (int m = 0; m < maxRow; m++)
    {
        delete[] map[m];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char **resizeMap(char **map, int &maxRow, int &maxCol)
{

    if (maxRow <= 0 || maxCol <= 0)
    {
        return nullptr;
    }

    if (maxRow > INT32_MAX / 2 || maxCol > INT32_MAX / 2)
    {
        return nullptr;
    }

    if (map == nullptr)
    {
        return nullptr;
    }

    // create new map
    char **hold_map = new char *[maxRow * 2] {};
    for (int m = 0; m < maxRow * 2; m++)
    {
        hold_map[m] = new char[maxCol * 2]{};
    }

    // copy top left
    for (int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            hold_map[i][j] = map[i][j];
        }
    }

    // copy to right
    for (int i = 0; i < maxRow; i++)
    {
        for (int j = maxCol; j < maxCol * 2; j++)
        {
            if (map[i][j - maxCol] == 'o')
            {
                hold_map[i][j] = '-';
            }
            else
            {
                hold_map[i][j] = map[i][j - maxCol];
            }
        }
    }

    // copy to below
    for (int i = maxRow; i < maxRow * 2; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            if (map[i - maxRow][j] == 'o')
            {
                hold_map[i][j] = '-';
            }
            else
            {
                hold_map[i][j] = map[i - maxRow][j];
            }
        }
    }

    // copy to bottom right
    for (int i = maxRow; i < maxRow * 2; i++)
    {
        for (int j = maxCol; j < maxCol * 2; j++)
        {
            if (map[i - maxRow][j - maxCol] == 'o')
            {
                hold_map[i][j] = '-';
            }
            else
            {
                hold_map[i][j] = map[i - maxRow][j - maxCol];
            }
        }
    }

    // delete old map
    for (int m = 0; m < maxRow; m++)
    {
        delete[] map[m];
    }
    delete[] map;
    map = nullptr;

    // resize map
    maxRow *= 2;
    maxCol *= 2;

    if (maxRow > INT32_MAX / maxCol)
    {
        deleteMap(hold_map, maxRow);
        return nullptr;
    }

    return hold_map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{
    // if moving out of bounds
    if ((nextRow >= maxRow) || (nextCol >= maxCol) || (nextRow < 0) || (nextCol < 0))
    {
        return STATUS_STAY;
    }

    // if moving onto invalid tile (monster, pillar, player(somehow?))
    if ((map[nextRow][nextCol] != TILE_OPEN) && (map[nextRow][nextCol] != TILE_TREASURE) && (map[nextRow][nextCol] != TILE_AMULET) && (map[nextRow][nextCol] != TILE_DOOR) && (map[nextRow][nextCol] != TILE_EXIT))
    {
        return STATUS_STAY;
    }

    // if pick up a treasure
    if (map[nextRow][nextCol] == TILE_TREASURE)
    {
        player.treasure += 1;
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_TREASURE;
    }

    // move to exit without a treasure
    if (map[nextRow][nextCol] == TILE_EXIT && player.treasure <= 0)
    {
        return STATUS_STAY;
    }

    // move to exit with a treasure
    if (map[nextRow][nextCol] == TILE_EXIT && player.treasure > 0)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_ESCAPE;
    }

    // move onto open tile
    if (map[nextRow][nextCol] == TILE_OPEN)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_MOVE;
    }

    // move onto amulet
    if (map[nextRow][nextCol] == TILE_AMULET)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_AMULET;
    }

    // move onto door
    if (map[nextRow][nextCol] == TILE_DOOR)
    {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_LEAVE;
    }

    return STATUS_STAY;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{

    // MONSTER TELEPORTING WHEN PLAYER IS AT LEFT AND RIGHT BORDERS
    // DOESN'T RECOGNIZE WHEN PLAYER IS ABOVE, TO THE LEFT, TO THE RIGHT (SEE ABOVE)
    // WHEN PLAYER IS BELOW, WORKS PERFECTLY

    // monster above
    for (int i = player.row - 1; i >= 0; i--)
    {
        // if line of sight blocked
        if (map[i][player.col] == TILE_PILLAR)
        {
            break;
        }
        // if monster found, move it down
        if (map[i][player.col] == TILE_MONSTER)
        {
            map[i + 1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    // monster below
    for (int i = player.row + 1; i < maxRow; i++)
    {
        // if line of sight blocked
        if (map[i][player.col] == TILE_PILLAR)
        {
            break;
        }
        // if monster found, move it up
        if (map[i][player.col] == TILE_MONSTER)
        {
            map[i - 1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    // monster left
    for (int i = player.col - 1; i >= 0; i--)
    {
        // if line of sight blocked
        if (map[player.row][i] == TILE_PILLAR)
        {
            break;
        }
        // if monster found, move it right
        if (map[player.row][i] == TILE_MONSTER)
        {
            map[player.row][i + 1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    // monster right
    for (int i = player.col + 1; i < maxCol; i++)
    {
        // if line of sight blocked
        if (map[player.row][i] == TILE_PILLAR)
        {
            break;
        }
        // if monster found, move it left
        if (map[player.row][i] == TILE_MONSTER)
        {
            map[player.row][i - 1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    // if monster hits player
    if (map[player.row][player.col] == TILE_MONSTER)
    {
        return true;
    }

    return false;
}
