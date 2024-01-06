#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <fstream>


using namespace std;

class cargame {

private:
  bool exitGame;
  bool gameOver;
  bool isMoving;
  bool bombExplode;
  int width;
  int height;

  int life;
  bool dead;
  int speed;
  int score;
  int myCarX;
  int myCarY;

  int highScore;
  int highestScore[5];

  int enemyX[4];
  int enemyY[4] = {-8, -18, -28, -38};
  int enemyPositionX;
  int enemyPositionY;
  int enemyNum;

  string bombParticle1[4] = {"o   o", " ooo ", " ooo ", "o   o"};
  string bombParticle2[4] = {" ooo ", "o   o", "o   o", " ooo "};

  string myCar[4] = {" # ", "# #", " # ", "# #"};

public:
  void gotoxy(int x, int y) { // to print in any place you want
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  }

  void hideCursor() { // to hide cursor
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
  }

  void startUp() { // all values once the game starts
    srand(time(NULL));
    exitGame = false;
    isMoving = false;
    gameOver = false;
    dead = false;
    bombExplode = false;
    life = 5;
    height = 20;
    width = 19;
    myCarX = 8;
    myCarY = 16;
    speed = 1;
    enemyNum = 4;
    score = 0;

    for (int i = 0; i < enemyNum; i++) {
      enemyPositionX = rand() % 3;
      if (enemyPositionX == 0)
        enemyX[i] = 2;
      else if (enemyPositionX == 1)
        enemyX[i] = 8;
      else if (enemyPositionX == 2)
        enemyX[i] = 14;
    }
    enemyY[0] = -8;
    enemyY[1] = -18;
    enemyY[2] = -28;
    enemyY[3] = -38;
  }

  void reposition() {

    myCarX = 8;
    myCarY = 16;
    speed = 1;

    for (int i = 0; i < enemyNum; i++) {
      enemyPositionX = rand() % 3;
      if (enemyPositionX == 0)
        enemyX[i] = 2;
      else if (enemyPositionX == 1)
        enemyX[i] = 8;
      else if (enemyPositionX == 2)
        enemyX[i] = 14;
    }
    enemyY[0] = -8;
    enemyY[1] = -18;
    enemyY[2] = -28;
    enemyY[3] = -38;
  }

  void layout() { // to print the game layout
    for (int i = 0; i < height; i++) {
      gotoxy(0, i);
      cout << "#                 #";
      if (i % 2 == 0 && isMoving) {
        gotoxy(6, i);
        cout << "|     |";
      } else if (i % 2 != 0 && !isMoving) {
        gotoxy(6, i);
        cout << "|     |";
      }
    }
    gotoxy(5, 21);
    cout << "Life: " << life;
    gotoxy(5, 22);
    cout << "Score: " << score;
  }

  void drawMyCar() { // to print your car
    if (!dead) {
      for (int i = 0; i < 4; i++) {
        gotoxy(myCarX, myCarY + i);
        cout << myCar[i];
      }
      // gotoxy(myCarX, myCarY); cout << "888";
    } else {
      for (int i = 0; i < 4; i++) {
        gotoxy(myCarX, myCarY + i);
        cout << "    ";
      }
      // gotoxy(myCarX, myCarY); cout << "    ";
    }
  }

  void drawEnemyCar() { // to print enemy car
    for (int i = 0; i < enemyNum; i++) {
      if (enemyY[i] + 3 > 0) {
        gotoxy(enemyX[i], enemyY[i] + 3);
        cout << " # ";
      }
      if (enemyY[i] + 2 > 0) {
        gotoxy(enemyX[i], enemyY[i] + 2);
        cout << "# #";
      }
      if (enemyY[i] + 1 > 0) {
        gotoxy(enemyX[i], enemyY[i] + 1);
        cout << " # ";
      }
      if (enemyY[i] > 0) {
        gotoxy(enemyX[i], enemyY[i] + 3);
        cout << "# #";
      }
      if (enemyY[i] + 3 > height) {
        gotoxy(enemyX[i], enemyY[i] + 3);
        cout << "   ";
      }
      if (enemyY[i] + 2 > height) {
        gotoxy(enemyX[i], enemyY[i] + 2);
        cout << "   ";
      }
      if (enemyY[i] + 1 > height) {
        gotoxy(enemyX[i], enemyY[i] + 1);
        cout << "   ";
      }
      if (enemyY[i] > height) {
        gotoxy(enemyX[i], enemyY[i]);
        cout << "   ";
      }
    }
  }

  void input() { // to control your car using keyboard input
    if (_kbhit()) {
      switch (_getch()) {
      case 72:
        if (myCarY > 0 && !dead)
          myCarY -= speed;
        break;
      case 75:
        if (myCarX > 2 && !dead)
          myCarX -= 6;
        break;
      case 77:
        if (myCarX < 14 && !dead)
          myCarX += 6;
        break;
      case 80:
        if (myCarY < 16 && !dead)
          myCarY += speed;
        break;
      case 163:
      	  ofstream outFile("player.txt");
      	 if(outFile.is_open())
      	 {
      	 	
      	 	outFile << score <<endl;
      	 	outFile << life <<endl;
      	 	outFile << speed <<endl;
      	 	outFile << myCarX <<endl;
      	 	outFile << myCarY<<endl;
      	 	outFile << dead<<endl;
      	 	outFile.close();
      	 	cout<<endl
      	 	<<"player data has been saved to file " << endl;
      	 	
		   }
		   else
		   {
		   	cerr << "Unable to open file for writing" << endl;
		   	return;
		   }
		   game_saved();
		   break;
      }
    }
  }
  
  void game_saved(){
  	cout<< "Game saved sucessfully"<<endl;
  }
  
  LoadstartUp()
{ 
    ifstream inFile("player.txt");
    if (inFile.is_open())
    {
        inFile >> score;
        inFile >> life;
        inFile >> speed;
        inFile >> myCarX;
        inFile >> myCarY;
        inFile >> dead;
        inFile.close();
    }
    else
    {
        cerr << "Unable to open file for reading." << endl;
    }

    srand(time(NULL));
    exitGame = false;
    isMoving = false;
    gameOver = false;
    dead = false;
    bombExplode = false;
    height = 20;
    width = 20;
    enemyNum = 2;
    for (int i = 0; i < enemyNum; i++)
    {
        enemyPositionX = rand() % 3;
        if (enemyPositionX == 0)
            enemyX[i] = 2;
        else if (enemyPositionX == 1)
            enemyX[i] = 8;
        else if (enemyPositionX == 2)
            enemyX[i] = 14;
    }
    enemyY[0] = -8;
    enemyY[1] = -18;
    enemyY[2] = -28;
    enemyY[3] = -38;
}

  void bombExplosion() { // to print bomb explosion effect
    if (bombExplode) {
      for (int i = 0; i < 4; i++) {
        gotoxy(myCarX - 1, myCarY - 1 + i);
        cout << bombParticle1[i] << endl;
      }
      bombExplode = false;
    } else {
      for (int i = 0; i < 4; i++) {
        gotoxy(myCarX - 1, myCarY - 1 + i);
        cout << bombParticle2[i] << endl;
      }
      bombExplode = true;
    }
    Sleep(100);
  }

  void died() { // logic when your character crash
                // if (dead) {
    dead = true;
    life -= 1;
    int count = 0;
    while (count != 10) {
      input();
      bombExplosion();
      gotoxy(2, 22);
      cout << "You got " << score << " Score!";
      count++;
    }
    gotoxy(2, 22);
    cout << "                    ";
    highestScore[life] = score;
    reposition();
    dead = false;
    // startUp();
    // }
  }

  void mecha() { // all mechanics, rules and logics
    srand(time(NULL));

    // isMoving = !isMoving;  // it toggles 'isMoving' property

    for (int i = 0; i < enemyNum; i++) {
      enemyY[i] += 1;
    }

    for (int i = 0; i < enemyNum; i++) { // setting new enemy positions
      if (enemyY[i] > 21) {
        enemyPositionX = rand() % 3;
        if (enemyPositionX == 0)
          enemyX[i] = 2;
        else if (enemyPositionX == 1)
          enemyX[i] = 8;
        else if (enemyPositionX == 2)
          enemyX[i] = 14;
        enemyY[i] = -8;
        score += 1;
      }
    }
    for (int i = 0; i < enemyNum;
         i++) { // checking collisions between 'myCar' and 'enemies'
      if (((myCarY <= enemyY[i] + 3 && myCarY >= enemyY[i])) &&
          myCarX == enemyX[i]) {
        // dead = true;
        died();
      }
    }
  }

  void transition() { // to print transition
    for (int i = 19; i >= 0; i--) {
      gotoxy(1, i);
      cout << "##################";
      Sleep(15);
    }
    for (int i = 1; i < 20; i++) {
      gotoxy(1, i);
      cout << "                  ";
      Sleep(15);
    }
  }

  void spiral(){};
  void splash(){};

  void games() {
      gotoxy(0, 0);
      cout << "###################";
      gotoxy(0, 1);
      cout << "#                 #";
      gotoxy(0, 2);
      cout << "#                 #";
      gotoxy(0, 3);
      cout << "#    CAR  GAME    #";
      gotoxy(0, 4);
      cout << "#                 #";
      gotoxy(0, 4);
      cout << "#                 #";
      gotoxy(0, 5);
      cout << "#                 #";
      gotoxy(0, 6);
      cout << "#    #   |   #    #";
      gotoxy(0, 7);
      cout << "#    #       #    #";
      gotoxy(0, 8);
      cout << "#    #   |   #    #";
      gotoxy(0, 9);
      cout << "#    #       #    #";
      gotoxy(0, 10);
      cout << "#    #   |   #    #";
      gotoxy(0, 11);
      cout << "#    #       #    #";
      gotoxy(0, 12);
      cout << "#    #   |   #    #";
      gotoxy(0, 13);
      cout << "#                 #";
      gotoxy(0, 13);
      cout << "#                 #";
      gotoxy(0, 14);
      cout << "#  PRESS 'SPACE'  #";
      gotoxy(0, 15);
      cout << "#    TO START     #";
      gotoxy(0, 16);
      cout << "#    PRESS 'L'    #";
      gotoxy(0, 17);
      cout << "#    TO LOAD      #";
      gotoxy(0, 18);
      cout << "###################";
      switch (getch()){
      	case 32:
      		getch();
      	break;
      	case 154:
      		LoadstartUp();
        break;
	  }
  }

  void game_Over() { // when player's life == 0
    for (int i = 0; i < life; i++) {
      if (highestScore[i + 1] >= highestScore[i]) {
        highScore = highestScore[i + 1];
      } else if (highestScore[i + 1] <= highestScore[i]) {
        highScore = highestScore[i];
      }
    }

    if (life == 0) {
      gameOver = true;
      do {
        gotoxy(0, 0);
        cout << "###################";
        gotoxy(0, 1);
        cout << "#                 #";
        gotoxy(0, 2);
        cout << "#                 #";
        gotoxy(0, 3);
        cout << "#                 #";
        gotoxy(0, 4);
        cout << "#                 #";
        gotoxy(0, 5);
        cout << "#                 #";
        gotoxy(0, 6);
        cout << "#    GAME OVER!!  #";
        gotoxy(0, 7);
        cout << "#                 #";
        gotoxy(0, 8);
        cout << "#    HIGHSCORE    #";
        gotoxy(0, 9);
        cout << "#                 #";
        gotoxy(0, 10);
        cout << "#       " << highScore << "       ";
        gotoxy(0, 11);
        cout << "#                 #";
        gotoxy(0, 12);
        cout << "#                 #";
        gotoxy(0, 13);
        cout << "#                 #";
        gotoxy(0, 14);
        cout << "#                 #";
        gotoxy(0, 15);
        cout << "#                 #";
        gotoxy(0, 16);
        cout << "#    PRESS   'X'  #";
        gotoxy(0, 17);
        cout << "#     TO EXIT     #";
        gotoxy(0, 18);
        cout << "#                 #";
        gotoxy(0, 19);
        cout << "###################";
        gotoxy(0, 20);
        cout << "#                 #";
        gotoxy(0, 21);
        cout << "#                 #";
      } while (getch() != 'x');
      exit(1);
    }
  }
  void play() {
    hideCursor();
    startUp();
    transition();
    games();
    while (!dead) {
      layout();
      input();
      mecha();
      drawMyCar();
      drawEnemyCar();
      // died();
      game_Over();
      Sleep(50);
    }
    system("cls");
    cout << "\n\n\n\n\tThank You for playing!!";
  }
};

int main() {

  cargame game;
  game.play();

  return 0;
}
