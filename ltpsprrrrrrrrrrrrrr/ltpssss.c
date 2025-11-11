#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <windows.h>  
#include <time.h>  
#define WIDTH 30  
#define HEIGHT 20  
#define MAX_BULLETS 5  
#define MAX_ENEMIES 5  
int shipX, shipY; int bulletsX[MAX_BULLETS], 
bulletsY[MAX_BULLETS]; int enemiesX[MAX_ENEMIES], 
enemiesY[MAX_ENEMIES];  
int score = 0; int gameOver = 0; int lives = 
20; int GAME_SPEED = 150;  // default 
medium  
void setup(); void 
draw(); void input(); 
void logic(); void 
selectDifficulty(); void 
resetGame();  
// Setup game void setup() {     srand(time(0));     
shipX = WIDTH / 2;     shipY = HEIGHT - 2;     for (int i 
= 0; i < MAX_BULLETS; i++) bulletsY[i] = -1;     for (int i 
= 0; i < MAX_ENEMIES; i++) {         
enemiesX[i] = 
rand() % (WIDTH - 2) + 1;         enemiesY[i] = rand() % 
5;  
    }  
    score = 0;     
lives = 3;  
    gameOver = 0;  
}  
  
// Draw frame void draw() {     system("cls");     
for (int i = 0; i < WIDTH + 2; i++) printf("#");     
printf("\n");  
  
   for (int y = 0; y < HEIGHT; y++) {     
for (int x = 0; x < WIDTH; x++) {  
        if (x == 0)             
printf("#");       int 
printed = 0;  
            // Draw ship             if (x == 
shipX && y == shipY) {                 
printf("^");                 printed = 1;  
            }  
  
            // Draw bullets             for (int b = 0; b < 
MAX_BULLETS; b++) {                 if (bulletsY[b] == 
y && bulletsX[b] == x) {  
                    printf("|");                     
printed = 1;  
                }  
            }  
  
            // Draw enemies             for (int e = 0; e < 
MAX_ENEMIES; e++) {                 if (enemiesY[e] == y 
&& enemiesX[e] == x) {  
                    printf("M");                     
printed = 1;  
                }  
            }  
        if (!printed)             
printf(" ");  
        if (x == WIDTH - 1)  
          printf("#");  
       }  
        printf("\n");  
    }  
  
    for (int i = 0; i < WIDTH + 2; i++) printf("#");     
printf("\nScore: %d\tLives: %d\n", score, lives);  
}  
  
// Handle player input void input() {     if (_kbhit()) {         int 
key = _getch();         if (key == 224) { // arrow keys             
key = _getch();             if (key == 75 && shipX > 0) shipX--;        
// Left             if (key == 77 && shipX < WIDTH - 1) shipX++; 
// Right  
        } else if (key == 32) { // Space = shoot             
for (int i = 0; i < MAX_BULLETS; i++) {                 
if (bulletsY[i] == -1) {                     bulletsX[i] 
= shipX;                     bulletsY[i] = shipY - 1;                     
break;  
               }  
        }  
    } else if (key == 'x' || key == 'X') {         
gameOver = 1;  
    }  
} 
} 
  
// Core game logic void 
logic() {     static int 
counter = 0;     
counter++;  
  
    // Move bullets     for (int i = 0; i < 
MAX_BULLETS; i++) {         if (bulletsY[i] 
>= 0) {             bulletsY[i]--;             if 
(bulletsY[i] < 0) bulletsY[i] = -1;  
        }  
    }  
  
    // Move enemies slower     if (counter % 3 == 
0) {         for (int i = 0; i < MAX_ENEMIES; i++) {             
enemiesY[i]++;             if (enemiesY[i] > HEIGHT) 
{                 enemiesY[i] = 0;                 enemiesX[i] 
= rand() % (WIDTH - 2) + 1;  
           }  
    }  
}  
// Bullet vs enemy  
for (int b = 0; b < MAX_BULLETS; b++) {        for (int e = 0; e < 
MAX_ENEMIES; e++) {             if (bulletsY[b] == enemiesY[e] && 
bulletsX[b] == enemiesX[e]) {  
                score += 10;                 bulletsY[b] = -1;                 
enemiesY[e] = 0;                 enemiesX[e] = rand() 
% (WIDTH - 2) + 1;  
            }  
        }  
    }  
  
    // Enemy hits ship     for (int e = 0; e < MAX_ENEMIES; 
e++) {         if (enemiesY[e] == shipY && enemiesX[e] == 
shipX) {  
            lives--;             enemiesY[e] = 0;             
enemiesX[e] = rand() % (WIDTH - 2) + 1;  
            if (lives <= 0) {                 
gameOver = 1;  
            }  
        }  
    }  
}  
  
// Difficulty selection menu void 
selectDifficulty() { system("cls"); printf("  
SPACE INVADER  \n\n"); printf("Select 
Difficulty:\n");    printf("1. Easy   
(Slow)\n");     printf("2. Medium 
(Normal)\n");     printf("3. Hard   
(Fast)\n\n");     printf("Enter choice: ");  
  
    int choice;     
scanf("%d", &choice);     
getchar();  
  
    switch (choice) {         case 1: 
GAME_SPEED = 200; break;         case 2: 
GAME_SPEED = 150; break;         case 3: 
GAME_SPEED = 100; break;         default: 
GAME_SPEED = 150; break;  
    }  
}  
  
// Reset game (for restart) 
void resetGame() {  
    setup();     selectDifficulty();     printf("\nControls:\n← → 
Move | SPACE Shoot | X Quit\n");     printf("\nPress any key to 
start...\n");  
    _getch();  
}  
  
int main() {  
start_game:     
resetGame();  
  
    while (!gameOver) {  
        draw();         
input();         logic();  
        Sleep(GAME_SPEED);  
    }  
  
    system("cls");  
    printf("  GAME OVER  \n");  
    printf("Final Score: %d\n", score);     
printf("Lives Remaining: %d\n", lives);     
printf("\nWould you like to play again? (Y/N): ");     
char choice = _getch();     if (choice == 'y' || 
choice == 'Y') {         
gameOver = 0;         
goto 
start_game;  // restart cleanly  
}  
printf("\nThanks for playing, Commander!\n");     
return 0;  
} 