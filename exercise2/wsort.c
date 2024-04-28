#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 101
//DANACH DAS HIER DEAKTIVIEREN
/*
static void printWords(char **array, int amount) {
    for(int i=0; i<amount; i++) {
        printf("%s", array[i]);

        if(i < amount-1) {
            printf("\n");
        }
        free(array[i]);
    }
    free(array);
}
*/
//BIS HIER


static void printWords (char **array, int amount) {
    for (int i=0; i<amount; i++) {
        //Fehlerbehandlung "fputs"
        if(fputs(array[i], stdout) == EOF) {
            perror("fputs");
            exit(EXIT_FAILURE);
        }
        //Fehlerbehandlung "fputs"
        if(fputs("\n", stdout) == EOF) {
            perror("fputs");
            exit(EXIT_FAILURE);
        }
    }
    //Fehlerbehandlung "fflush"
    if(fflush(stdout) == EOF) {
        perror("fflush");
    }
}

static void findNextWord() {
    int c;
    while(true) {
        c = fgetc(stdin);
        if((c != EOF) && (c != '\n')) {
            continue;
        }
        break;
    }
    //Fehlerbehandlung "fgetc" - immer nach while-schleife
    if(ferror(stdin)) {
        perror("fgetc");
        exit(EXIT_FAILURE);
    }
}

static int charCompare(const void *a, const void *b) {
    char* const* ca = (char* const*) a;
    char* const* cb = (char* const*) b;

    return strcmp(*ca, *cb);
}

static void memoryFree(char **array, int amount) {
    for(int i=0; i<amount; i++) {
        free(array[i]);
    }
    free(array);
}

static void getWords() {
    char **wordList = NULL;
    int numberOfWords = 0;

    int lengthOfChar;
    char bufferWord[BUFFER_SIZE];
    while(fgets(bufferWord, BUFFER_SIZE, stdin)) {

        lengthOfChar = strlen(bufferWord);

        if(bufferWord[lengthOfChar-1] != '\n') {
            findNextWord();
            continue;
        }

        bufferWord[lengthOfChar-1] = '\0';
        wordList = realloc(wordList, (numberOfWords+3) * sizeof(char *));
        //Fehlerbehandlung "realloc" Hier würde auch !wordList, da NULL = 0 also false
        if(wordList == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        wordList[numberOfWords] = malloc(lengthOfChar *sizeof(char));
        //Fehlerbehandlung "malloc" - Hier würde auch !wordList[numberOfWords], da NULL = 0 also false
        if(wordList[numberOfWords] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(wordList[numberOfWords], bufferWord);
        numberOfWords++;
    }
    //Fehlerbehandlung "fgets" - immer nach while-schleife
    if(ferror(stdin)) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    qsort(wordList, numberOfWords, sizeof(wordList[0]), charCompare);
    printWords(wordList, numberOfWords);
    memoryFree(wordList, numberOfWords);
}

int main (int argc, char* argv[]) {
    getWords();
    exit(EXIT_SUCCESS);
}
