#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions 
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

char* cap(char* word){                  
    //helper function to make word all caps

    char* cap_word = word;
    for(int i = 0; i < bSize; i++){
        if(*(word+i) >= 97 && *(word+i) <= 122){
            *(cap_word+i) = *(word+i) - 32;
        }
    }
    return cap_word;
}

void append(char* arr, int index){                    
    //helper fucntion to put the path into the table array

    char ch = index + '0';
    int i = 0;
    while(*(arr+i) != '\0'){
        i++;
    }
    *(arr+i) = ch;
    *(arr+i+1) = '\0';
}


int wordFinder(char** arr, char* word, int char_index, int row, int col, char*** table){             
    //helper function to help decide if the word is the puzzle

    word = cap(word);

    if ((row < 0 || row >= bSize) || (col < 0 || col >= bSize)){
        return 0;
    }else if(*(word+char_index) == '\0'){
        return 1;
    }else if(*(*(arr+row)+col) != *(word+char_index)){
        return 0;
    }
    
    if(wordFinder(arr, word, char_index+1, row-1, col-1, table) || 
        wordFinder(arr, word, char_index+1, row-1, col, table)||
        wordFinder(arr, word, char_index+1, row-1, col+1, table) ||
        wordFinder(arr, word, char_index+1, row, col-1, table) ||
        wordFinder(arr, word, char_index+1, row, col+1, table) ||
        wordFinder(arr, word, char_index+1, row+1, col-1, table) ||
        wordFinder(arr, word, char_index+1, row+1, col, table) ||
        wordFinder(arr, word, char_index+1, row+1, col+1, table)){
        append(*(*(table+row)+col), char_index+1);
        return 1;
    }

    return 0;
}

void printPath(char*** table){                             
    //helper function to print pathing of word

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(*(*(*(table+i)+j)) == '\0'){
                *(*(*(table+i)+j)) = '0';
            }
        }
    }


    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%s\t", *(*(table+i)+j));
        }
        printf("\n");
    }
}




// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    for(int i = 0; i < bSize; i++){
        char* arr_i = *(arr+i);
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(arr_i+j));
        }
        printf("\n");
    }
    printf("\n");

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // If not found, it will print a different message.
    char*** table = (char***)malloc(bSize * sizeof(char**));

    for(int i = 0; i < bSize; i++){
        *(table+i) = (char**)malloc(bSize * sizeof(char*));
        for(int j = 0; j < bSize; j++){
            *(*(table+i)+j) = (char*)malloc(bSize * sizeof(char));
            *(*(*(table+i)+j)) = '\0';
        }
    }

    int tf = 0;
    word = cap(word);
    for(int row = 0; row < bSize; row ++){
        for(int col = 0; tf == 0 && col < bSize; col++){
            if(wordFinder(arr, word, 0, row, col, table) == 1){
                tf = 1;
            }
        }
    }

    if(tf == 1){
        printf("Word found!\n");
        printf("Printing the search path:\n");
        printPath(table);
    }else{
        printf("Word not found!\n");
    }
    




}
