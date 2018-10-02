//
// Created by hagitba on 11/5/17.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

/**
 *this function checks if two word are the same
 * @param token the word in the file
 * @param word the given word to search
 * @return 1 if the word found, and 1 else
 */
int isTheSameWords(char token[], char word[])
{
    int i = 0;
    if (strlen(token) != strlen(word))
    {
        return 0;
    }
    for(int j = 0; j<(int)strlen(word); j++)
    {
        if (token[i] == word[i] || token[i] == tolower(word[i]) || token[i] == toupper(word[i]))
        {
            i++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

/**
 *this function go line by line of every file and checks if the given word is in the files.
 * @param path of the file
 * @param word the given word to search
 * @param isSingleFile 1 if there is one file
 */
void searchInFile(char *path, char word[], int isSingleFile)
{
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        fprintf(stderr, "%s", "No such file or directory\n");
    }
    else
    {
        while ((fgets(line, MAX_LINE_LENGTH, file)) != NULL)
        {
            char *token;
            char *space = " \n";
            char originalLine[256];
            strcpy(originalLine, line);

            token = strtok(line, space);

            while (token != NULL)
            {
                int comparisionWord = isTheSameWords(token, word);

                if (comparisionWord && isSingleFile)
                {
                    printf("%s", originalLine);
                    break;
                }
                else if (comparisionWord && (!isSingleFile))
                {
                        printf("%s:%s", path, originalLine);
                    break;
                }
                token = strtok(NULL, space);
            }
        }
    }
    fclose(file);
}


/**
 * The main function that get the arguments from the user
 * @param argc the number of arguments
 * @param argv an array of the files' path
 * @return 0 if the code run smooth
 */
    int main(int argc, char *argv[])
{

        int isSingleFile = 0;

        if (argc < 3)
        {
            fprintf(stderr, "%s", "Wrong amount of arguments, you should insert at least 2 argument: word to find and"
                    " one or more paths of files \n");
            return 1;
        }
        // that's mean that there is more then one file
        if (argc == 3)
        {
            isSingleFile = 1;
        }
        for (int i = 2; i < argc; i++)
        {
            searchInFile(argv[i], argv[1], isSingleFile);
        }
        return 0;
}
