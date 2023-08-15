#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define PUZZLE_SIZE 15
#define MAX_WORD_LENGTH 20

typedef struct {
    char word[MAX_WORD_LENGTH];
    int row;
    int col;
    bool direction; // true for horizontal, false for vertical
} Word;

void initializePuzzle(char puzzle[PUZZLE_SIZE][PUZZLE_SIZE]) {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        for (int j = 0; j < PUZZLE_SIZE; j++) {
            puzzle[i][j] = '.';
        }
    }
}

void printPuzzle(char puzzle[PUZZLE_SIZE][PUZZLE_SIZE]) {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        for (int j = 0; j < PUZZLE_SIZE; j++) {
            printf("%c ", puzzle[i][j]);
        }
        printf("\n");
    }
}

bool canPlaceWord(char puzzle[PUZZLE_SIZE][PUZZLE_SIZE], Word word) {
    int len = strlen(word.word);
    if (word.direction) {
        if (word.col + len > PUZZLE_SIZE) {
            return false;
        }
        for (int j = 0; j < len; j++) {
            if (puzzle[word.row][word.col + j] != '.' && puzzle[word.row][word.col + j] != word.word[j]) {
                return false;
            }
        }
    } else {
        if (word.row + len > PUZZLE_SIZE) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (puzzle[word.row + i][word.col] != '.' && puzzle[word.row + i][word.col] != word.word[i]) {
                return false;
            }
        }
    }
    return true;
}

void placeWord(char puzzle[PUZZLE_SIZE][PUZZLE_SIZE], Word word) {
    int len = strlen(word.word);
    if (word.direction) {
        for (int j = 0; j < len; j++) {
            puzzle[word.row][word.col + j] = word.word[j];
        }
    } else {
        for (int i = 0; i < len; i++) {
            puzzle[word.row + i][word.col] = word.word[i];
        }
    }
}

int main() {
    srand(time(NULL));

    char puzzle[PUZZLE_SIZE][PUZZLE_SIZE];
    initializePuzzle(puzzle);

    int wordsCount;
    printf("Enter the number of words: ");
    scanf("%d", &wordsCount);

    Word words[wordsCount];

    for (int i = 0; i < wordsCount; i++) {
        printf("Enter word %d: ", i + 1);
        scanf("%s", words[i].word);
        printf("Enter row, column, and direction (0 for vertical, 1 for horizontal): ");
        scanf("%d %d %d", &words[i].row, &words[i].col, &words[i].direction);

        while (!canPlaceWord(puzzle, words[i])) {
            printf("Invalid placement. Enter row, column, and direction again: ");
            scanf("%d %d %d", &words[i].row, &words[i].col, &words[i].direction);
        }

        placeWord(puzzle, words[i]);
    }

    printf("\nCrossword Puzzle:\n");
    printPuzzle(puzzle);

    return 0;
}
