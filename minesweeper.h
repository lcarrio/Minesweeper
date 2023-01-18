//
// Created by Lazaro Carrio on 2019-04-09.
//

#ifndef PROJECT3_PROJECT3_H
#define PROJECT3_PROJECT3_H

#endif //PROJECT3_PROJECT3_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;
bool StartGame();
struct Tile{

    Sprite sprite;
    bool revealed = false;
    bool isBomb = false;
    bool isFlag = false;
    bool debug = false;
    bool keepDebug = false;
    bool iLost = false;
    bool iWin = false;
    int bombCount;
};
vector<Tile> TileVector();
void DrawTiles(vector<Tile>& tiles, RenderWindow& window);
void SetRevealed(vector<Tile>& tiles, int tileNum);
void DrawBombCounter(vector<Sprite>& digits, RenderWindow& window, int bombCount);
