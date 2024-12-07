#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using namespace std;

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
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream inFS (fileName);
    if (!inFS.is_open()) {inFS.open("levels/" + fileName);}
    if (!inFS.is_open()) return nullptr;
    string rowCheck, colCheck, startRow, startCol;
    char inData = ' ';
    char allPossibleTiles[] = "-$@M+?!";
    inFS >> rowCheck >> colCheck >> startRow >> startCol;
    // FIXME: Instead of throwing error return nullptr
    if (rowCheck.find_first_not_of("0123456789") != string::npos
        || colCheck.find_first_not_of("0123456789") != string::npos)
            { return nullptr; }
    maxRow = stoi(rowCheck);
    maxCol = stoi(colCheck);
    if (startRow.find_first_not_of("0123456789") != string::npos
        || startCol.find_first_not_of("0123456789") != string::npos)
            { return nullptr; }
    player.row = stoi(startRow); player.col = stoi(startCol); 
    char** dungeonMap = createMap(maxRow, maxCol);
    for (int r = 0; r < maxRow; ++r){
        for (int c = 0; c <maxCol; ++c){
        inFS >> inData;
    
        if (inFS.eof()) return nullptr;
        bool goodTile = false;
        for (int i = 0; i < 8; ++i){
            if (inData == allPossibleTiles[i]) {
                goodTile = true; break;
            }
        }
        if (!goodTile) return nullptr;
        dungeonMap[r][c] = inData;
        }
    }
    if (dungeonMap[player.row][player.col] != TILE_OPEN) return nullptr;
    else dungeonMap[player.row][player.col] = TILE_PLAYER;
    if (inFS >> inData) return nullptr;      



    return dungeonMap;
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
void getDirection(char input, int& nextRow, int& nextCol) {
    switch (input){
        case MOVE_UP:
            nextRow -=1;
            break;
        case MOVE_DOWN:
            nextRow += 1;
            break;
        case MOVE_LEFT:
            nextCol -= 1;
            break;
        case MOVE_RIGHT:
            nextCol += 1;
            break;
        default: break;
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
char** createMap(int maxRow, int maxCol) {
    
    char** newMap = new char*[maxRow];
    for (int r = 0; r < maxRow; ++r){
        newMap[r] = new char[maxCol + 1];
        newMap[r][maxCol] = '\0';
        for (int c = 0; c < maxCol; ++c){
            newMap[r][c] = '-';
        }
    }
    
    return newMap;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr) return;
    
    for (int i = 0; i < maxRow; ++i){
        delete[] map[i];
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
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (maxRow <= 0 || maxCol <= 0
        || INT32_MAX / 2 < maxRow || INT32_MAX / 2 < maxCol) return nullptr;

    char** newMap = createMap(maxRow*2, maxCol*2);
    char oldTile = ' ';
    // subarray A
    for (int r = 0; r < maxRow; ++r){
        for (int c = 0; c < maxCol; ++c){
            oldTile = map[r][c];
            newMap[r][c] = oldTile;
        }
    }
    // subarray B, C, D
    for (int r = 0; r < maxRow; ++r){
        for (int c = 0; c < maxCol; ++c){
            oldTile = map[r][c];
            if (oldTile == TILE_PLAYER){
                oldTile = TILE_OPEN;
            }
            newMap[r][c + maxCol] = oldTile;
            newMap[r + maxRow][c] = oldTile;
            newMap[r + maxRow][c + maxCol] = oldTile;
        }
    }
    int tempRow = maxRow;
    deleteMap(map, maxRow);
    maxRow = tempRow * 2;
    maxCol *= 2;
    return newMap;
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
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if (nextRow >= maxRow || nextCol >=maxCol || nextRow < 0 || nextCol < 0
        || map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR)
        { return STATUS_STAY; } // Case going out of bounds or meeting monster/pillar
    else if (map[nextRow][nextCol] == TILE_EXIT && player.treasure == 0)
        { return STATUS_STAY; }
    
    int NEW_STATUS = 0;
    switch (map[nextRow][nextCol]){
        case TILE_TREASURE:
            player.treasure += 1;
            NEW_STATUS = STATUS_TREASURE;   break; // Just in case :)
        case TILE_AMULET:
            NEW_STATUS = STATUS_AMULET;     break;
        case TILE_DOOR:
            NEW_STATUS =  STATUS_LEAVE;     break;
        case TILE_EXIT:
            NEW_STATUS = STATUS_ESCAPE;     break;
        default:
            NEW_STATUS = STATUS_MOVE;       break;
    }

    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    player.row = nextRow; player.col = nextCol;
 
    return NEW_STATUS;
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
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    char tile = ' ';
    

    // Looking up for pillar, end of map, or monster
    for (int r = player.row - 1; r >=0; --r){
        tile = map[r][player.col];
        if (tile == TILE_MONSTER){
                map[r + 1][player.col] = TILE_MONSTER;
                map[r][player.col] = TILE_OPEN;
            }
        else if (tile == TILE_PILLAR){
            break;
        }
    }
        // Looking down for pillar, end of map, or monster
    for (int r = player.row + 1; r < maxRow; ++r){
        tile = map[r][player.col];
        if (tile == TILE_MONSTER){

                map[r - 1][player.col] = TILE_MONSTER;
                map[r][player.col] = TILE_OPEN;
                // if (map[player.row][player.col] == TILE_MONSTER){
                //     return true;
                // }
            }
        else if (tile == TILE_PILLAR){
            break;
        }
    }
    
        // Looking left for pillar, end of map, or monster
    for (int c = player.col + 1; c < maxCol; ++c){
        tile = map[player.row][c];
        if (tile == TILE_MONSTER){
                map[player.row][c - 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
                // if (map[player.row][player.col] == TILE_MONSTER){
                //     return true;
                // }
            }
        else if (tile == TILE_PILLAR){
            break;
        }
    }
    // Looking right for pillar, end of map, or monster
    for (int c = player.col - 1; c >= 0; --c){
        tile = map[player.row][c];
        if (tile == TILE_MONSTER){
                map[player.row][c + 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
                // if (map[player.row][player.col] == TILE_MONSTER){
                //     return true;
                // }
            }
        else if (tile == TILE_PILLAR){
            break;
        }
    }

    if (map[player.row][player.col] == TILE_MONSTER){
        return true;
        }    


    return false;
}
