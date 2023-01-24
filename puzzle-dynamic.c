/*  Crossword Puzzle Solver.
    Authors: Asela H Premawansha - e19300@eng.pdn.ac.lk
           : Janitha Dilshan     - e19295@eng.pdn.ac.lk
    Last Updated: Tue 01/17/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Creating Dynamic variable for grid, word
char **grid;
char **words;

// Creating Static variable for others
int ROWS, COLUMNS, numWords;
int filledCount = 0;
int wordCount;

// Function to checking if a given word fits in a given row or column of the grid
bool fitsInGrid(char word[], int indexi, int indexj, bool isRow, char **grid)
{
    int length = strlen(word) - 1;

    // Checking if the word fits in the given row or column
    if (isRow)
    {

        if (indexj + length > COLUMNS)
        {
            // Checking weather num of # in the row are lower than the length of the word. If so return false
            return false;
        }
        for (int i = indexj; i < indexj + length; i++)
        {
            if (grid[indexi][i] != '#' && grid[indexi][i] != word[i - indexj])
            {
                // Checking weather num of # in the row are greater than the length of the word. If so return false
                return false;
            }
        }

        if (indexj + length < COLUMNS)
        {
            if ((grid[indexi][indexj + length]) == '#')
            {
                // Checking weather there are # in the row before checking the index. If so return false
                return false;
            }
        }

        if (indexj > 0)
        {
            if (((grid[indexi][indexj - 1]) == '#'))
            {
                // Checking weather there are # in the row before checking the index. If so return false
                return false;
            }
        }
    }
    else
    {
        if (indexi + length > ROWS)
        {
            // Checking weather num of # in the column are lower than the length of the word. If so return false
            return false;
        }
        for (int i = indexi; i < indexi + length; i++)
        {
            if (grid[i][indexj] != '#' && grid[i][indexj] != word[i - indexi])
            {
                // Checking wheather num of # in the column are greater than the length of the word. If so return false
                return false;
            }
        }

        if (indexi + length < ROWS)
        {
            // Checking wheather there is a additional # in the column after the word length. If so return false
            // For fit the word, no of # should be same as the length of the word
            if ((grid[indexi + length][indexj] == '#'))
            {
                return false;
            }
        }

        if (indexi > 0)
        {
            // Checking wheather there is a additional # in the column before the word length. If so return false
            if ((grid[indexi - 1][indexj] == '#'))
            {
                return false;
            }
        }
    }

    // return true if a word fits in the given row or column
    return true;
}

// Function to count the no of Rows and Columns in the grid
void countRows_P(char **arr)
{
    int r = 0;
    while (arr[r][0] != '\0')
    {
        int c = 0;
        while (arr[r][c] != '\0')
        {
            c++;
        }
        COLUMNS = c - 1;
        r++;
    }
    ROWS = r;
}

// Function to count the no of words
void countRows_W(char **arr)
{
    int r = 0;
    while (arr[r][0] != '\0')
    {
        r++;
    }
    numWords = r - 1;
}

// Print the completed crossword puzzle
void printArr(char **arr)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // Creating grid array to store the crossword puzzel
    char buffer[256];
    grid = (char **)malloc(sizeof(char *) * 256);
    for (int i = 0; i < 256; i++)
    {
        grid[i] = (char *)malloc(sizeof(char) * 256);
    }

    // Get inputs and assign them into grid array
    int p = 0;
    while (fgets(buffer, sizeof(buffer), stdin))
    {
        if (buffer[0] == '\n')
            break;
        strcpy(grid[p], buffer);
        p++;
    }

    // Calling the funcion to count Rows and Columns
    countRows_P(grid);

    // Creating words array to store the words
    words = (char **)malloc(sizeof(char *) * 256);
    for (int i = 0; i < 256; i++)
    {
        words[i] = (char *)malloc(sizeof(char) * 256);
    }

    // Get inputs and assign them into words array
    int q = 0;
    while (fgets(buffer, sizeof(buffer), stdin))
    {
        strcpy(words[q], buffer);
        q++;
    }

    // Calling the function to count num of words
    countRows_W(words);

    // initialize the word count
    wordCount = numWords;

    // Iterate through the grid and try to place each word in each row and column
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            // Checking whether the grid has invalid inputs
            // Invalid inputs means inputs other than #,* and alpahabatic charaters
            int a = ((grid[i][j] == 42) | (grid[i][j] == 35) | ((grid[i][j] >= 65) & (grid[i][j] <= 90)) | ((grid[i][j] >= 97) & (grid[i][j] <= 122)));
            if (a == 0)
            {
                printf("%s", "INVALID INPUT\n");
                return 0;
            }

            //  Try to place the word horizontally
            for (int k = 0; k < numWords; k++)
            {
                if (fitsInGrid(words[k], i, j, true, grid))
                {
                    // Place the word in the grid
                    filledCount++;
                    for (int l = 0; l < strlen(words[k]) - 1; l++)
                    {
                        grid[i][j + l] = words[k][l];
                    }
                    // Remove the word from the list
                    for (int l = k; l < numWords - 1; l++)
                    {
                        strcpy(words[l], words[l + 1]);
                    }
                    numWords--;
                    k--; // Decrement the index to compensate for the removed word
                }
            }

            // Try to place the word vertically
            for (int k = 0; k < numWords; k++)
            {
                if (fitsInGrid(words[k], i, j, false, grid))
                {
                    // Place the word in the grid
                    filledCount++;
                    for (int l = 0; l < strlen(words[k]) - 1; l++)
                    {
                        grid[i + l][j] = words[k][l];
                    }
                    // Remove the word from the list
                    for (int l = k; l < numWords - 1; l++)
                    {
                        strcpy(words[l], words[l + 1]);
                    }
                    numWords--;
                    k--; // Decrement the index to compensate for the removed word
                }
            }
        }
    }

    // Print impossible if the words can not fit to the puzzel
    if (!(filledCount == wordCount))
    {
        printf("%s", "IMPOSSIBLE\n");
        return 0;
    }

    // Calling the print function
    printArr(grid);

    // Freeing memory which are allocated for grid and words arrays
    for (int i = 0; i < 256; i++)
    {
        free(grid[i]);
        free(words[i]);
    }
    free(grid);
    free(words);

    return 0;
}
