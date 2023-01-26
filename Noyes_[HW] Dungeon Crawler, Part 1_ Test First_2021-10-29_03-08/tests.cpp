#include <iostream>
#include "logic.h"
#include <string>
#include <sstream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void testLoadLevel(const std::string& fileName, int& maxRow, int& maxCol, Player& player){
    try {
        char **map = loadLevel(fileName, maxRow, maxCol, player);
        deleteMap(map, maxRow);
    }
    catch (...){
        
    }
}

void testGetDirection(char input, int& nextRow, int& nextCol){
    try {
        getDirection(input, nextRow, nextCol);
    }
    catch (...) {

    }
}

void testDeleteMap(char**& map, int& maxRow) {
    try {
        deleteMap(map, maxRow);
    }
    catch (...) {

    }
}

void testResizeMap(char** map, int& maxRow, int& maxCol) {
    try {
        map = resizeMap(map, maxRow, maxCol);
        // need if statements to check if locations contain expected values
        deleteMap(map, maxRow);
    }
    catch (...) {

    }
}

void testDoPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    try {
        getDirection('a', nextRow, nextCol);
        doPlayerMove(map, maxRow, maxCol, player, nextRow, nextCol);
    }
    catch (...) {

    }
}

void testDoMonsterAttack(char** map, int maxRow, int maxCol, Player player) {
    try {
        doMonsterAttack(map, maxRow, maxCol, player);
    }
    catch (...) {

    }
}

int main() {
    // unit tests for load level
    int row = 0;
    int col = 0;
    Player test;
    testLoadLevel("example.tst", row, col, test); // bad file name
    testLoadLevel("test1.txt", row, col, test); // bad file data
    testLoadLevel("test2.txt", row, col, test); // bad file data
    testLoadLevel("test3.txt", row, col, test); // bad file data
    testLoadLevel("test4.txt", row, col, test); // bad file data
    testLoadLevel("test5.txt", row, col, test); // bad file data
    testLoadLevel("test6.txt", row, col, test); // bad file data
    testLoadLevel("test7.txt", row, col, test); // bad file data
    testLoadLevel("test8.txt", row, col, test); // bad file data
    testLoadLevel("test9.txt", row, col, test); // bad file data
    testLoadLevel("test10.txt", row, col, test); // bad file data
    testLoadLevel("test11.txt", row, col, test); // bad file data
    testLoadLevel("test12.txt", row, col, test); // bad file data
    testLoadLevel("test13.txt", row, col, test); // bad file data
    testLoadLevel("test14.txt", row, col, test); // bad file data
    testLoadLevel("test15.txt", row, col, test); // bad file data
    testLoadLevel("test16.txt", row, col, test); // bad file data
    testLoadLevel("example.txt", row, col, test); // good file
    //*******************************************************

    // unit tests for delete map
    char **map; // good input
    map = loadLevel("example.txt", row, col, test);
    testDeleteMap(map, row);

    //*******************************************************

    // unit tests for get direction
    int nextRow;
    int nextCol;
    testGetDirection('e', nextRow, nextCol); // good input
    testGetDirection('w', nextRow, nextCol); // good input
    testGetDirection('a', nextRow, nextCol); // good input
    testGetDirection('s', nextRow, nextCol); // good input
    testGetDirection('d', nextRow, nextCol); // good input
    testGetDirection('q', nextRow, nextCol); // good input
    testGetDirection('x', nextRow, nextCol); // bad input
    // maybe check if nextRow and nextCol are equal to expected value? <-- MORE POSSIBLE POINTS
    //*******************************************************

    // unit tests for resize map
    char **map1;
    map1 = loadLevel("test23.txt", row, col, test);
    testResizeMap(map1, row, col);
    //*******************************************************

    // unit tests for do player move
    // treasure tile
    char **map2 = new char*[2]{};
    for (int i = 0; i < 2; i++) {
        map2[i] = new char[2]{};
    }
    map2[0][0] = TILE_TREASURE;
    map2[0][1] = TILE_EXIT;
    map2[1][0] = TILE_PLAYER;
    map2[1][1] = TILE_OPEN;
    if (doPlayerMove(map2, 2, 2, test, 0, 0) == 2) {
        cout << "treasure passed";
    }
    for (int j = 0; j < 2; j++) {
        delete[] map2[j];
    }
    delete[] map2;

    //amulet tile
    char **map18 = new char*[2]{};
    for (int i = 0; i < 2; i++) {
        map18[i] = new char[2]{};
    }
    map18[0][0] = TILE_AMULET;
    map18[0][1] = TILE_EXIT;
    map18[1][0] = TILE_PLAYER;
    map18[1][1] = TILE_OPEN;
    if (doPlayerMove(map18, 2, 2, test, 0, 0) == 3) {
        cout << "amulet passed";
    }
    for (int j = 0; j < 2; j++) {
        delete[] map18[j];
    }
    delete[] map18;

    // door tile
    char **map19 = new char*[2]{};
    for (int i = 0; i < 2; i++) {
        map19[i] = new char[2]{};
    }
    map19[0][0] = TILE_DOOR;
    map19[0][1] = TILE_EXIT;
    map19[1][0] = TILE_PLAYER;
    map19[1][1] = TILE_OPEN;
    if (doPlayerMove(map19, 2, 2, test, 0, 0) == 4) {
        cout << "door passed";
    }
    for (int j = 0; j < 2; j++) {
        delete[] map19[j];
    }
    delete[] map19;

    // exit tile
    char **map20 = new char*[2]{};
    for (int i = 0; i < 2; i++) {
        map20[i] = new char[2]{};
    }
    map20[0][0] = TILE_EXIT;
    map20[0][1] = TILE_DOOR;
    map20[1][0] = TILE_PLAYER;
    map20[1][1] = TILE_OPEN;
    if (doPlayerMove(map20, 2, 2, test, 0, 0) == 5) {
        cout << "exit passed";
    }
    for (int j = 0; j < 2; j++) {
        delete[] map20[j];
    }
    delete[] map20;

    // empty tile
    char **map21 = new char*[2]{};
    for (int i = 0; i < 2; i++) {
        map21[i] = new char[2]{};
    }
    map21[0][0] = TILE_OPEN;
    map21[0][1] = TILE_DOOR;
    map21[1][0] = TILE_PLAYER;
    map21[1][1] = TILE_EXIT;
    if (doPlayerMove(map21, 2, 2, test, 0, 0) == 1) {
        cout << "empty passed";
    }
    for (int j = 0; j < 2; j++) {
        delete[] map21[j];
    }
    delete[] map21;
    // check status, row, column, treasure, player location <--- POSSIBLE MORE POINTS

    //*******************************************************

    // unit tests for do monster attack
    char **map3; // down
    map3 = loadLevel("test17.txt", row, col, test);
    testDoPlayerMove(map3, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map3, row, col, test);
    deleteMap(map3, row);
    char **map4; // right
    map4 = loadLevel("test18.txt", row, col, test);
    testDoPlayerMove(map4, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map4, row, col, test);
    deleteMap(map4, row);
    char **map5; // up
    map5 = loadLevel("test19.txt", row, col, test);
    testDoPlayerMove(map5, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map5, row, col, test);
    deleteMap(map5, row);
    char **map6; // left
    map6 = loadLevel("test20.txt", row, col, test);
    testDoPlayerMove(map6, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map6, row, col, test);
    deleteMap(map6, row);
    char **map7; // hit player
    map7 = loadLevel("test21.txt", row, col, test);
    testDoPlayerMove(map7, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map7, row, col, test);
    deleteMap(map7, row);
    char **map8; // vision blocked
    map8 = loadLevel("test22.txt", row, col, test);
    testDoPlayerMove(map8, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map8, row, col, test);
    deleteMap(map8, row);
    char **map9; // no monster
    map9 = loadLevel("test23.txt", row, col, test);
    testDoPlayerMove(map9, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map9, row, col, test);
    deleteMap(map9, row);
    char **map10; // no vision, not blocked
    map10 = loadLevel("test25.txt", row, col, test);
    testDoPlayerMove(map10, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map10, row, col, test);
    deleteMap(map10, row);
    char **map11; // monster surrounded
    map11 = loadLevel("test26.txt", row, col, test);
    testDoPlayerMove(map11, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map11, row, col, test);
    deleteMap(map11, row);
    char **map12; // monster destroys amulet
    map12 = loadLevel("test27.txt", row, col, test);
    testDoPlayerMove(map12, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map12, row, col, test);
    deleteMap(map12, row);
    char **map13; // monster destroys door
    map13 = loadLevel("test28.txt", row, col, test);
    testDoPlayerMove(map13, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map13, row, col, test);
    deleteMap(map13, row);
    char **map14; // monster destroys treasure
    map14 = loadLevel("test29.txt", row, col, test);
    testDoPlayerMove(map14, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map14, row, col, test);
    deleteMap(map14, row);
    char **map15; // pillar down?
    map15 = loadLevel("test30.txt", row, col, test);
    testDoPlayerMove(map15, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map15, row, col, test);
    deleteMap(map15, row);
    char **map16; // spawn player on monster
    map16 = loadLevel("test31.txt", row, col, test);
    testDoPlayerMove(map16, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map16, row, col, test);
    deleteMap(map16, row);
    char **map17; // monsters collide
    map17 = loadLevel("test32.txt", row, col, test);
    testDoPlayerMove(map17, row, col, test, nextRow, nextCol);
    testDoMonsterAttack(map17, row, col, test);
    deleteMap(map17, row);
    //*******************************************************
    return 0;
}
