#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 4
int board[SIZE][SIZE] = {0};
int score = 0;
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void displayBoard(int isFirstTime) {
    if (isFirstTime) {
        printf("\033[1;31mPress \033[0m\033[1;31mEnter\033[0m to start the game...\n");
        while (getchar()!= '\n');
    }   
    clearScreen();
    if (isFirstTime){
        printf("\n     \033[1;33mWelcome To 2048 Game\033[0m\n\n");
        printf("     \033[1;31mThe game has started!\033[0m\n");
    }else{
        printf("\n         \033[1;33m  2048 Game\033[0m\n\n");
    }        
    printf("\033[1;34m+------+------+------+------+ \033[0m\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("\033[1;34m|\033[0m");
            if (board[i][j] == 0) {
                printf("      ");
            } else {
                int tile = board[i][j];
                switch (tile) {
                    case 2: printf("\033[1;33m%6d\033[0m", tile); break;
                    case 4: printf("\033[1;31m%6d\033[0m", tile); break;
                    case 8: printf("\033[1;33m%6d\033[0m", tile); break;
                    case 16: printf("\033[1;31m%6d\033[0m", tile); break;
                    case 32: printf("\033[1;33m%6d\033[0m", tile); break;
                    case 64: printf("\033[1;31m%6d\033[0m", tile); break;
                    case 128: printf("\033[1;33m%6d\033[0m", tile); break;
                    case 256: printf("\033[1;31m%6d\033[0m", tile); break;
                    case 512: printf("\033[1;33m%6d\033[0m", tile); break;
                    case 1024: printf("\033[1;31m%6d\033[0m", tile); break;
                    case 2048: printf("\033[1;33m%6d\033[0m", tile); break;
                    default: printf("\033[1;31m%6d\033[0m", tile);
                }
            }
        }
        printf("\033[1;34m|\033[0m\n");
        printf("\033[1;34m+------+------+------+------+\033[0m\n");
    }
    printf("\033[1;32mCurrent Score: %d\033[0m\n", score);
    printf("\n\033[1;31mUse W/A/S/D to move tiles, P to save, Q to quit.\033[0m\n");
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
            score += temp[i];
            temp[i + 1] = 0;
        }
    }
    k = 0;
    for (int i = 0; i < SIZE; i++) {
        if (temp[i] != 0) {
            row[k++] = temp[i];
        } else {
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
int hasWon() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) return 1;
        }
    }
    return 0;
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
int boardChanged(int prevBoard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != prevBoard[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}
void saveGame() {
    FILE *file = fopen("2048_save.txt", "w");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }
    fprintf(file, "%d\n", score);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%d ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Game saved automatically.\n");
}
int main() {
    char input;
    int inFirstTime = 1;
    srand(time(NULL));
    addRandomTile();
    addRandomTile();
    while (1) {
        displayBoard(inFirstTime);
        inFirstTime = 0;
        if (hasWon()) {
            printf("Congratulations! You've won!\n");
            saveGame(); 
            break;
        }
        if (isGameOver()) {
            printf("Game Over!\n");
            saveGame(); 
            break;
        }
        int prevBoard[SIZE][SIZE];
        memcpy(prevBoard, board, sizeof(board));
        printf("Enter move (w: up, s: down, a: left, d: right, q: quit): ");
        scanf(" %c", &input);
        switch (input) {
            case 'W': moveUp(); break;
            case 'w': moveUp(); break;
            case 'S': moveDown(); break;
            case 's': moveDown(); break;
            case 'A': moveLeft(); break;
            case 'a': moveLeft(); break;
            case 'D': moveRight(); break;
            case 'd': moveRight(); break;
            case 'q': exit(0); break;
            default: continue;
        }
        if (boardChanged(prevBoard)) {
            addRandomTile();
        }
    }
}





