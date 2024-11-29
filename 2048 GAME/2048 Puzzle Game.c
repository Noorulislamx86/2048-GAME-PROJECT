#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4 
 
int board[SIZE][SIZE] = {0}; 
    
    void displayBoard(int isFirstTime) {
    if (isFirstTime) {
        printf("Press \033[1;31mEnter\033[0m to start the game...\n");
        while (getchar() != '\n');
        printf("   The game has started!\n");
    }
    printf("\n       2048 Game\n\n");
    printf("-------------------------\n");
    for (int i = 0; i < SIZE; i++) {
    printf("|");
    for (int j = 0; j < SIZE; j++) {
    if (board[i][j] == 0)
    printf("     |");  
    else
    printf("%5d|", board[i][j]); 
    }
    printf("\n-------------------------\n");
       }
    printf("\n");
}
    void addRandomTile() {
    int emptyCells[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
       if (board[i][j] == 0) {
       emptyCells[count][0] = i;
       emptyCells[count][1] = j;
       count++;
    }
        }
    }
    if (count > 0) {
        int index = rand() % count;
        int x = emptyCells[index][0];
        int y = emptyCells[index][1];
        board[x][y] = 2;  
    }
}
    void slideRow(int row[]) {
    int temp[SIZE] = {0}, k = 0;

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != 0) {
        temp[k++] = row[i];
}
    }

    for (int i = 0; i < SIZE - 1; i++) {
    if (temp[i] == temp[i + 1] && temp[i] != 0) {
        temp[i] *= 2;
        temp[i + 1] = 0;
        }
    }
    k = 0;
    for (int i = 0; i < SIZE; i++) {
        if (temp[i] != 0) {
        row[k++] = temp[i];
}else {
        row[k++] = 0;
        }
    }
}
void moveLeft() {
    for (int i = 0; i < SIZE; i++) {
        slideRow(board[i]);  
    }
}
void moveRight() {
    for (int i = 0; i < SIZE; i++) {
        int row[SIZE];
        for (int j = 0; j < SIZE; j++) {
            row[j] = board[i][SIZE - 1 - j]; 
        }
        slideRow(row);
        for (int j = 0; j < SIZE; j++) {
            board[i][SIZE - 1 - j] = row[j];  
        }
    }
}
void moveUp() {
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[i][j]; 
        }
        slideRow(column);
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = column[i];
        }
    }
}
void moveDown() {
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[SIZE - 1 - i][j];  
        }
        slideRow(column);
        for (int i = 0; i < SIZE; i++) {
            board[SIZE - 1 - i][j] = column[i]; 
        }
    }
}
int isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 0; 
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return 0;  
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return 0; 
        }
    }
    return 1; 
}

int main() {
    char input;
    int isFirstTime = 1; 

    srand(time(NULL));  
    addRandomTile();
    addRandomTile();

    while (1) {
        displayBoard(isFirstTime);
        isFirstTime = 0;
        if (isGameOver()) {
            printf("Game Over!\n");
            break;
        }
      printf("Enter move (w: up, s: down, a: left, d: right, q: quit): ");
      scanf(" %c", &input);
      switch (input) {
        case 'w': moveUp(); break;
        case 's': moveDown(); break;
        case 'a': moveLeft(); break;
        case 'd': moveRight(); break;
        case 'q': 
         printf("Game Over!\n");
        exit(0); 
        default: continue;
      }
      addRandomTile();  
    }
    return 0;
}
