#include <iostream>
#include <vector>
#include "Project3.h"
#include <vector>
#include <random>
#include <string>
#include <fstream>
using namespace std;
using namespace sf;

int main(){
    // if you're reading my comments whenever i say bomb i meant mine, and whenever i say mine i meant tile //
    while(StartGame()) {
        StartGame();
    }

    return 0;
}
bool StartGame() {
        // Create the window
        RenderWindow window(VideoMode(800, 600), "Minesweeper");
        // Load the texture of one-eight
        Texture one;
        one.loadFromFile("images/number_1.png");
        Texture two;
        two.loadFromFile("images/number_2.png");
        Texture three;
        three.loadFromFile("images/number_3.png");
        Texture four;
        four.loadFromFile("images/number_4.png");
        Texture five;
        five.loadFromFile("images/number_5.png");
        Texture six;
        six.loadFromFile("images/number_6.png");
        Texture seven;
        seven.loadFromFile("images/number_7.png");
        Texture eight;
        eight.loadFromFile("images/number_8.png");

        // Create sprites for the bomb counter
        Sprite digitOne;
        Sprite digitTwo;
        Sprite digitThree;
        Sprite digitFour;
        vector<Sprite> digits;
        digitOne.setPosition(0, 512);
        digitTwo.setPosition(21, 512);
        digitThree.setPosition(42, 512);
        digitFour.setPosition(53, 512);
        digits.push_back(digitOne);
        digits.push_back(digitTwo);
        digits.push_back(digitThree);
        digits.push_back(digitFour);

        Texture smileyFace;
        smileyFace.loadFromFile("images/face_happy.png");
        // Create sprite for reset button
        Sprite resetButton;
        resetButton.setTexture(smileyFace);
        resetButton.setPosition(350, 512);


        //Load the texture for a bomb
        Texture bombTiles;
        bombTiles.loadFromFile("images/mine.png");

        // Load the texture for a revealed tile
        Texture revealedTiles;
        revealedTiles.loadFromFile("images/tile_revealed.png");

        // Load the texture for a hidden tile
        Texture hiddenTiles;
        hiddenTiles.loadFromFile("images/tile_hidden.png");
        hiddenTiles.setRepeated(true);
        Texture flag;
        flag.loadFromFile("images/flag.png");

        // Create debug sprite
        Texture debugPic;
        debugPic.loadFromFile("images/debug.png");
        Sprite debug;
        debug.setTexture(debugPic);
        debug.setPosition(480, 512);

        // Load test sprites
        Texture testOne;
        testOne.loadFromFile("images/test_1.png");
        Sprite test1;
        test1.setTexture(testOne);
        test1.setPosition(550, 512);
        Texture testTwo;
        testTwo.loadFromFile("images/test_2.png");
        Sprite test2;
        test2.setTexture(testTwo);
        test2.setPosition(620, 512);
        Texture testThree;
        testThree.loadFromFile("images/test_3.png");
        Sprite test3;
        test3.setTexture(testThree);
        test3.setPosition(690, 512);

        // Load textures for losses/wins respectively
        Texture takeL;
        takeL.loadFromFile("images/face_lose.png");

        Texture takeW;
        takeW.loadFromFile("images/face_win.png");


        // Create a sprite for the revealed tiles
        Sprite background;
        background.setTexture(hiddenTiles);
        // Set a texture rectangle for the sprite equal to the size of the mine field
        background.setTextureRect(sf::IntRect(0, 0, 800, 512));
        int actualBombCount = 0;
        vector<Tile> tiles = TileVector();
        int bombCount = 0;
        // Add in 50 bombs randomly
        random_device rd;
        mt19937 mt(rd()); // generate random seed every run
        uniform_int_distribution<int> dist(0,tiles.size()); // generates a random number from 0 to the amount of sprites
        for (int i = 0; i < 50; i++) {
            int randomInt = dist(mt);
            while (tiles[randomInt].isBomb) { // if there already is a bomb generates another random number
                randomInt = dist(mt);
            }
            tiles[randomInt].isBomb = true; // set isBomb at the random index equal to true 50 times
            bombCount++;
            actualBombCount ++;
        }
        // Add bomb count to each individual mine
        for (int i = 0; i < tiles.size(); i++) {
            int n = 0;

            if (((i + 1) % 16 != 0)) {
                if (tiles[i + 1].isBomb) n++;
            }
            if (i < tiles.size() - 16) {
                if (tiles[i + 16].isBomb) {
                    n++;

                }
            }
            if (i < tiles.size() - 17 && ((i + 1) % 16 != 0)) {
                if (tiles[i + 17].isBomb) {
                    n++;
                }

            }
            if (i % 16 != 0 && i < tiles.size() - 15) {
                if (tiles[i + 15].isBomb) {
                    n++;
                }
            }
            if (i % 16 != 0) {
                if (tiles[i - 1].isBomb) {
                    n++;
                }

            }
            if (i % 16 != 0) {
                if (tiles[i - 17].isBomb) {
                    n++;
                }

            }
            if (tiles[i - 16].isBomb) {
                n++;
            }
            if (((i + 1) % 16 != 0)) {
                if (tiles[i - 15].isBomb) {
                    n++;

                }

            }
            if (tiles[i].isBomb) n = -1;
            tiles[i].bombCount = n;

        }


        while (window.isOpen()) {
            Event e;
            // Closes the window on event e
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
                // Get mouse position in cordinates
                auto mouse_pos = sf::Mouse::getPosition(window);
                auto translated_pos = window.mapPixelToCoords(mouse_pos);
                // If resetButton is clicked on restart the game but restarting the while loop in main
                if (resetButton.getGlobalBounds().contains(translated_pos)) {
                    if (e.type == Event::MouseButtonPressed) {
                        if (e.key.code == Mouse::Left) {
                            return true;
                        }
                    }
                }
                // Only continue if the player has not won or lost
                if (tiles[0].iLost != true && tiles[0].iWin != true) {

                    if (test3.getGlobalBounds().contains(translated_pos)) {
                        if (e.type == Event::MouseButtonPressed) {
                            if (e.key.code == Mouse::Left) {
                                // clean bord
                                bombCount = 0; // keep track for bomb counter
                                actualBombCount = 0; // keep track for win condition
                                for (int i = 0; i < tiles.size(); i++) {
                                    tiles[i].sprite.setTexture(hiddenTiles);
                                    tiles[i].revealed = false;
                                    if (tiles[i].isBomb) {
                                        tiles[i].isBomb = false;
                                    }
                                }
                                string line;
                                fstream file;
                                int col = 0;
                                int row = 0;
                                file.open("boards/testboard3.brd");
                                while (getline(file, line)) {
                                    // Because i created my tile vector verticaly i had to get nifty with rows/collums
                                    row = 0;
                                    for (int i = 0; i < line.length(); i++) {
                                        if (line[i] == '1') {
                                            tiles[(row * 16) + col].isBomb = true; // she works like a beut
                                            bombCount++;
                                            actualBombCount++;
                                        }
                                        row++;
                                    }
                                    col++;
                                }
                                // Add bomb count to each mine
                                for (int i = 0; i < tiles.size(); i++) {
                                    int n = 0;

                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i + 1].isBomb) n++;
                                    }
                                    if (i < tiles.size() - 16) {
                                        if (tiles[i + 16].isBomb) {
                                            n++;

                                        }
                                    }
                                    if (i < tiles.size() - 17 && ((i + 1) % 16 != 0)) {
                                        if (tiles[i + 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0 && i < tiles.size() - 15) {
                                        if (tiles[i + 15].isBomb) {
                                            n++;
                                        }
                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 1].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (tiles[i - 16].isBomb) {
                                        n++;
                                    }
                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i - 15].isBomb) {
                                            n++;

                                        }

                                    }
                                    if (tiles[i].isBomb) n = -1;
                                    tiles[i].bombCount = n;

                                }

                            }
                        }
                    }
                    // Same as test 3
                    if (test2.getGlobalBounds().contains(translated_pos)) {
                        if (e.type == Event::MouseButtonPressed) {
                            if (e.key.code == Mouse::Left) {
                                // clean bord
                                bombCount = 0;
                                actualBombCount = 0;
                                for (int i = 0; i < tiles.size(); i++) {
                                    tiles[i].sprite.setTexture(hiddenTiles);
                                    tiles[i].revealed = false;
                                    if (tiles[i].isBomb) {
                                        tiles[i].isBomb = false;
                                    }
                                }
                                string line;
                                fstream file;
                                int col = 0;
                                int row = 0;
                                file.open("boards/testboard2.brd");
                                while (getline(file, line)) {
                                    row = 0;
                                    for (int i = 0; i < line.length(); i++) {
                                        if (line[i] == '1') {
                                            tiles[(row * 16) + col].isBomb = true;
                                            bombCount++;
                                            actualBombCount++;
                                        }
                                        row++;
                                    }
                                    col++;
                                }
                                for (int i = 0; i < tiles.size(); i++) {
                                    int n = 0;

                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i + 1].isBomb) n++;
                                    }
                                    if (i < tiles.size() - 16) {
                                        if (tiles[i + 16].isBomb) {
                                            n++;

                                        }
                                    }
                                    if (i < tiles.size() - 17 && ((i + 1) % 16 != 0)) {
                                        if (tiles[i + 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0 && i < tiles.size() - 15) {
                                        if (tiles[i + 15].isBomb) {
                                            n++;
                                        }
                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 1].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (tiles[i - 16].isBomb) {
                                        n++;
                                    }
                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i - 15].isBomb) {
                                            n++;

                                        }

                                    }
                                    if (tiles[i].isBomb) n = -1;
                                    tiles[i].bombCount = n;

                                }

                            }
                        }
                    }
                    // Same as test two
                    if (test1.getGlobalBounds().contains(translated_pos)) {
                        if (e.type == Event::MouseButtonPressed) {
                            if (e.key.code == Mouse::Left) {
                                // clean bord
                                bombCount = 0;
                                actualBombCount = 0;
                                for (int i = 0; i < tiles.size(); i++) {
                                    tiles[i].sprite.setTexture(hiddenTiles);
                                    tiles[i].revealed = false;
                                    if (tiles[i].isBomb) {
                                        tiles[i].isBomb = false;
                                    }
                                }
                                string line;
                                fstream file;
                                file.open("boards/testboard1.brd");
                                while (getline(file, line)) {
                                    for (int i = 0; i < line.length(); i++) {
                                        if (line[i] == '1') {
                                            tiles[i].isBomb = true;
                                            bombCount++;
                                            actualBombCount++;
                                        }
                                    }
                                }
                                // Add in tile numbers
                                for (int i = 0; i < tiles.size(); i++) {
                                    int n = 0;

                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i + 1].isBomb) n++;
                                    }
                                    if (i < tiles.size() - 16) {
                                        if (tiles[i + 16].isBomb) {
                                            n++;

                                        }
                                    }
                                    if (i < tiles.size() - 17 && ((i + 1) % 16 != 0)) {
                                        if (tiles[i + 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0 && i < tiles.size() - 15) {
                                        if (tiles[i + 15].isBomb) {
                                            n++;
                                        }
                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 1].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (i % 16 != 0) {
                                        if (tiles[i - 17].isBomb) {
                                            n++;
                                        }

                                    }
                                    if (tiles[i - 16].isBomb) {
                                        n++;
                                    }
                                    if (((i + 1) % 16 != 0)) {
                                        if (tiles[i - 15].isBomb) {
                                            n++;

                                        }

                                    }
                                    if (tiles[i].isBomb) n = -1;
                                    tiles[i].bombCount = n;

                                }

                            }
                        }
                    }
                    // Toggle Debug
                    if (debug.getGlobalBounds().contains(translated_pos) || tiles[0].keepDebug == true) {
                        if (e.type == Event::MouseButtonPressed || tiles[0].keepDebug == true) {
                            if (e.key.code == Mouse::Left) {
                                bool debugReset = false;
                                for (int i = 0; i < tiles.size(); i++) {
                                    if (tiles[i].debug == true) {
                                        debugReset = true;
                                        tiles[0].keepDebug = false; // Used to keep track of toggle
                                    }
                                }
                                if (debugReset == true) {
                                    for (int j = 0; j < tiles.size(); j++) {
                                        tiles[j].debug = false;
                                    }
                                    debugReset = false; // Used to clear toggle
                                }
                                for (int i = 0; i < tiles.size(); i++) {
                                    if (debugReset == false) {
                                        if (tiles[i].isBomb) {
                                            tiles[i].debug = true;
                                            tiles[0].keepDebug = true; // Toggle on
                                        }
                                    }
                                }
                            }
                        }
                    }


                    for (unsigned int i = 0; i < tiles.size(); i++) {
                        if (tiles[i].sprite.getGlobalBounds().contains(translated_pos))
                        {
                            // Left click events
                            if (e.type == Event::MouseButtonPressed) {
                                if (e.key.code == Mouse::Left) {
                                    if (!tiles[i].isFlag) {
                                        tiles[i].revealed = true;
                                    }
                                    if (tiles[i].isBomb) {
                                        for (int i = 0; i < tiles.size(); i++) {
                                            if (tiles[i].isBomb) {
                                                tiles[i].revealed = true;
                                                resetButton.setTexture(takeL);
                                                tiles[0].iLost = true;
                                            }
                                        }
                                    }
                                }
                                // Adds Flags
                                if (e.key.code == Mouse::Right) {
                                    if (tiles[i].revealed == false) { // dont add flags if revealed
                                        if (tiles[i].isFlag == false) {
                                            tiles[i].isFlag = true;
                                            tiles[i].revealed = false;
                                            bombCount--;
                                        } else if (tiles[i].isFlag == true) { // remove flag if already flag
                                            tiles[i].isFlag = false;
                                            tiles[i].sprite.setTexture(hiddenTiles);
                                            window.draw(tiles[i].sprite);
                                            bombCount++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
           window.clear(Color::White);
            // draws the sprite with the revealed texture
            DrawTiles(tiles, window);
            DrawBombCounter(digits, window, bombCount);
            int numRevealed = 0;
            // Check score
            for(int i = 0; i < tiles.size() ; i++){
                if(tiles[i].revealed){
                    numRevealed++;
                }
            }
            // Win condition
            if(numRevealed == 400 - actualBombCount){
                resetButton.setTexture(takeW);
                tiles[0].iWin = true;
                for(int i = 0; i < tiles.size() ; i++){
                    if(tiles[i].isBomb){
                        tiles[i].sprite.setTexture(flag);
                        window.draw(tiles[i].sprite);
                    }
                }

            }
            window.draw(resetButton);
            window.draw(debug);
            window.draw(test1);
            window.draw(test2);
            window.draw(test3);
            // display the window
            window.display();

        }
        return false;
    };

// Function that creates a vector of sprites
    vector<Tile> TileVector() {
        Tile tile;

        Texture hiddenTiles;
        hiddenTiles.loadFromFile("images/tile_hidden.png");

        tile.sprite.setTexture(hiddenTiles);
        vector<Tile> returnVector;
        int x, y = 0;
        // Adds the original sprite at the origin
        for (unsigned int i = 0; i < 25; i++) {
            // sets the position back to the top row moving one sprite to the right
            tile.sprite.setPosition(x, -32);
            x += 32;
            // goes through each x value and adds 16 sprites going down
            for (unsigned int j = 0; j < 16; j++) {
                y = 32;
                tile.sprite.move(0, y);
                returnVector.push_back(tile);
            }
        }
        return returnVector;
    }

    void DrawTiles(vector<Tile>& tiles, RenderWindow &window) {
        Texture one;
        one.loadFromFile("images/number_1.png");
        Texture two;
        two.loadFromFile("images/number_2.png");
        Texture three;
        three.loadFromFile("images/number_3.png");
        Texture four;
        four.loadFromFile("images/number_4.png");
        Texture five;
        five.loadFromFile("images/number_5.png");
        Texture six;
        six.loadFromFile("images/number_6.png");
        Texture seven;
        seven.loadFromFile("images/number_7.png");
        Texture eight;
        eight.loadFromFile("images/number_8.png");

        //Load the texture for a bomb
        Texture bombTiles;
        bombTiles.loadFromFile("images/mine.png");

        // Load the texture for a revealed tile
        Texture revealedTiles;
        revealedTiles.loadFromFile("images/tile_revealed.png");

        // Load the texture for a hidden tile
        Texture hiddenTiles;
        hiddenTiles.loadFromFile("images/tile_hidden.png");
        hiddenTiles.setRepeated(true);

        // Load the texture for a flag
        Texture flag;
        flag.loadFromFile("images/flag.png");

        for (unsigned int i = 0; i < tiles.size(); i++) {
            if (tiles[i].revealed == false && tiles[i].isFlag == false) {
                tiles[i].sprite.setTexture(hiddenTiles);
                window.draw(tiles[i].sprite);
            }
            if (tiles[i].isFlag) {
                tiles[i].sprite.setTexture(hiddenTiles);
                window.draw(tiles[i].sprite);
                tiles[i].sprite.setTexture(flag);
                tiles[i].revealed = false;
            }
            if (tiles[i].revealed) {
                tiles[i].sprite.setTexture(revealedTiles);
                window.draw(tiles[i].sprite);
            }
            if (tiles[i].isBomb && tiles[i].revealed == false && tiles[i].isFlag == false) {
                tiles[i].sprite.setTexture(hiddenTiles);

            }
            if (tiles[i].isBomb && tiles[i].revealed) {
                tiles[i].sprite.setTexture(bombTiles);

            }
            if (tiles[i].bombCount == 1 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(one);
            }
            if (tiles[i].bombCount == 2 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(two);
            }
            if (tiles[i].bombCount == 3 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(three);
            }
            if (tiles[i].bombCount == 4 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(four);
            }
            if (tiles[i].bombCount == 5 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(five);
            }
            if (tiles[i].bombCount == 6 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(six);
            }
            if (tiles[i].bombCount == 7 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(seven);
            }
            if (tiles[i].bombCount == 8 && tiles[i].revealed) {
                tiles[i].sprite.setTexture(eight);
            }
            if (tiles[i].bombCount == 0 && tiles[i].revealed) {
                int j = i;
                tiles[i].sprite.setTexture(revealedTiles);
                while (tiles[j].bombCount == 0) {
                    if ((j + 1) % 16 != 0) {
                        if (tiles[j + 1].bombCount != -1 && !tiles[j + 1].isFlag) {
                            tiles[j + 1].revealed = true;
                            SetRevealed(tiles, j);
                        }
                        j++;
                    } else {
                      break;
                    }
                }
                j = i;
                while (tiles[j].bombCount == 0) {
                    if ((j + 1) % 16 == 0) {
                        if (tiles[j + 16].bombCount != -1 && !tiles[j + 1].isFlag) {
                            tiles[j + 16].revealed = true;
                            SetRevealed(tiles, j);
                        }
                        j = j + 16;
                    } else {
                        break;
                    }
                }
                j = i;
                while (tiles[j].bombCount == 0) {
                    if ((j% 16 != 0)) {
                        if (tiles[j - 1 ].bombCount != -1 && !tiles[j - 1].isFlag) {
                            tiles[j - 1].revealed = true;
                            SetRevealed(tiles, j);
                        }
                        j = j - 1;
                    } else {
                        break;
                    }
                }
            }
            if (tiles[i].debug) {
                tiles[i].sprite.setTexture(bombTiles);
            }
            window.draw(tiles[i].sprite);
        }

    };
    void SetRevealed(vector<Tile> &tiles, int i) {
        if (tiles[i + 16].bombCount != -1 && !tiles[i+16].isFlag) {
            tiles[i + 16].revealed = true;
        }
        if (tiles[i - 16].bombCount != -1  && !tiles[i-16].isFlag) {
            tiles[i - 16].revealed = true;
        }
        if (tiles[i - 1].bombCount != -1 && (i % 16 != 0)  && !tiles[i-16].isFlag) {
            tiles[i - 1].revealed = true;
        }
        if (tiles[i + 17].bombCount != -1 && (i + 1) % 16 != 0 && !tiles[i+17].isFlag) {
            tiles[i + 17].revealed = true;
        }
        if (tiles[i - 17].bombCount != -1 && i % 16 != 0  && !tiles[i-17].isFlag) {
            tiles[i - 17].revealed = true;
        }
        if (tiles[i + 15].bombCount != -1 && i % 16 != 0 && i < tiles.size() - 15  && !tiles[i+15].isFlag) {
            {
                tiles[i + 15].revealed = true;
            }
        }
        if (tiles[i - 15].bombCount != -1 && ((i + 1) % 16 != 0) && !tiles[i-15].isFlag) {
            {
                tiles[i - 15].revealed = true;
            }
        }

    };



void DrawBombCounter(vector<Sprite>& digits, RenderWindow& window, int bombCount){
    Texture zeroCount;
    zeroCount.loadFromFile("images/digits.png",IntRect(0, 0, 21, 32));

    Texture oneCount;
    oneCount.loadFromFile("images/digits.png",IntRect(21, 0, 21, 32));

    Texture twoCount;
    twoCount.loadFromFile("images/digits.png",IntRect(42, 0, 21, 32));

    Texture threeCount;
    threeCount.loadFromFile("images/digits.png",IntRect(63, 0, 21, 32));

    Texture fourCount;
    fourCount.loadFromFile("images/digits.png",IntRect(84, 0, 21, 32));

    Texture fiveCount;
    fiveCount.loadFromFile("images/digits.png",IntRect(105, 0, 21, 32));

    Texture sixCount;
    sixCount.loadFromFile("images/digits.png",IntRect(126, 0, 21, 32));

    Texture sevenCount;
    sevenCount.loadFromFile("images/digits.png",IntRect(147, 0, 21, 32));

    Texture eightCount;
    eightCount.loadFromFile("images/digits.png",IntRect(168, 0, 21, 32));

    Texture nineCount;
    nineCount.loadFromFile("images/digits.png",IntRect(189, 0, 21, 32));

    Texture negCount;
    negCount.loadFromFile("images/digits.png",IntRect(210, 0, 21, 32));
    string bombNum = to_string(bombCount);
    for(int i = 0; i < bombNum.length() ; i++){
        if(bombNum[i] == '-'){
            digits[i].setTexture(negCount);
        }
        if(bombNum[i] == '0'){
            digits[i].setTexture(zeroCount);
        }
        if(bombNum[i] == '1'){
            digits[i].setTexture(oneCount);
        }
        if(bombNum[i] == '2'){
            digits[i].setTexture(twoCount);
        }
        if(bombNum[i] == '3'){
            digits[i].setTexture(threeCount);
        }
        if(bombNum[i] == '4'){
            digits[i].setTexture(fourCount);
        }
        if(bombNum[i] == '5'){
            digits[i].setTexture(fiveCount);
        }
        if(bombNum[i] == '6'){
            digits[i].setTexture(sixCount);
        }
        if(bombNum[i] == '7'){
            digits[i].setTexture(sevenCount);
        }
        if(bombNum[i] == '8'){
            digits[i].setTexture(eightCount);
        }
        if(bombNum[i] == '9'){
            digits[i].setTexture(nineCount);
        }
        window.draw(digits[i]);
    }

}


