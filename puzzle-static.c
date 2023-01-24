/*  Crossword Puzzle Solver.
    Authors: Asela H Premawansha - e19300@eng.pdn.ac.lk
           : Janitha Dilshan     - e19295@eng.pdn.ac.lk
    Last Updated: Tue 01/10/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// Define initial size for the arrays
#define size 20

// Creating grid, word arrays and other variables
char grid[size][size], words[size][size];
int ROWS, COLUMNS, numWords;
int filledCount = 0;
int wordCount;
int p = 0, q = 0;

// Function to checking if a given word fits in a given row or column of the grid
bool fitsInGrid(char word[], int indexi, int indexj, bool isRow, char grid[size][size])
{
    int length = strlen(word);

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

        if (((grid[indexi][indexj + length]) == '#') || ((grid[indexi][indexj - 1]) == '#'))
        {
            // Checking weather there are # in the row before checking the index. If so return false
            return false;
        }
    }
    else
    {
        if (indexi + length > ROWS)
        {
            // checking weather num of # in the column are lower than the length of the word. If so return false
            return false;
        }
        for (int i = indexi; i < indexi + length; i++)
        {
            if (grid[i][indexj] != '#' && grid[i][indexj] != word[i - indexi])
            {
                // checking weather num of # in the column are greater than the length of the word. If so return false
                return false;
            }
        }
        if ((grid[indexi + length][indexj] == '#') || (grid[indexi - 1][indexj] == '#'))
        {
            // checking weather there are # in the column before checking the index. If so return false
            return false;
        }
    }

    // return true if a word fits in the given row or column
    return true;
}

// Function to count the num of Rows and Columns in the puzzel
int countRows_P(char arr[size][size])
{
    int rows = 0;
    int cls = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i][0] == 0)
        {
            break;
        }
        else
        {
            rows++;
            int cols = 0;
            for (int j = 0; j < size; j++)
            {
                if (arr[i][j] == '\0')
                {
                    cls = cols;
                    break;
                }
                else
                {
                    cols++;
                }
            }
        }
    }
    ROWS = rows;
    COLUMNS = cls;
    return 0;
}

// Function to count the num of words to be filled
int countRows_W(char arr[size][size])
{
    int rows = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i][0] == 0)
        {
            break;
        }
        else
        {
            rows++;
            for (int j = 0; j < size; j++)
            {
                if (arr[i][j] == '\n')
                {
                    break;
                }
                else
                {
                }
            }
        }
    }
    numWords = rows;
    return 0;
}

// Print the completed crossword puzzle
void printArr(char arr[size][size])
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

    // Get inputs and assign them into arrays
    char chr;
    while (scanf("%[^\n]%*c", grid[p]) == 1)
    {
        p++;
    }
    scanf("%c", &chr);
    while (scanf("%[^\n]%*c", words[q]) == 1)
    {
        q++;
    }

    // Calling the other functions
    countRows_P(grid);
    countRows_W(words);

    // initialize the word count
    wordCount = numWords;

    // Iterate through the grid and try to place each word in each row and column
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            // checking whether the grid has invalid inputs
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
                    for (int l = 0; l < strlen(words[k]); l++)
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
                    for (int l = 0; l < strlen(words[k]); l++)
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

    // Calling print function
    printArr(grid);

    return 0;
}