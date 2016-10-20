// Alphabetizer by Eric Buckland

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int checklines(FILE* file);

int main(int argc, string argv[])
{
    // checks to see if the user entered in the invalid paramemters
    if (argc != 2)
    {
        printf("Usage: ./alphabetize <text file name>\n");
        printf("Make sure the text file is in the same folder, and has .txt\n");
        return 1;
    }
    int sleeptime = 70000;
    // check to see if the file exits - code from: https://goo.gl/voojpZ
    FILE* file = fopen(argv[1],"rw");
    if (file == NULL)
    {
        printf("That file does not exist, how blue.\n");
        printf("Make sure the text file is in the same folder, and has .txt\n");
        return 1;
    }
    usleep(sleeptime);
    printf("That file exists! Parsing...\n");
    usleep(2000000);
    // initializing, opening the file, and setting the file pointer 
    int lines = checklines(file);
    file = fopen(argv[1],"r");
    printf("Lines: %i\n",lines);
    int j = 0;
    // recieve the strings from the text file - structure from http://cs50.tv/
    char line[128];
    char strings[lines][sizeof(line)];
    for (int i = 0; i < lines; i++)
    {
        // recives the new line from file
        fgets(line,sizeof(line),file);
        // chops off the \n
        j = 0;
        while (line[j] != '\n' && j < sizeof(line))
            j++;
        if (j != sizeof(line))
            line[j] = 0;
        // adds the newline to the array of strings
        strcpy(strings[i],line);
        printf("Line %d: %s\n", i + 1, strings[i]);
        usleep(sleeptime);
    }
    printf("Parsing Complete! Sorting...\n");
    usleep(2000000);
    // sorting all of the strings using bubble sorting
    char strtemp[128];
    for (int i = 0; i < lines - 1; i++) 
    {
        for (j = 0; j < lines - 1; j++) 
        {
            // words are switch alphabetically
            if (strcmp(strings[j],strings[j + 1]) > 0) 
            {
                strcpy(strtemp, strings[j]);
                strcpy(strings[j], strings[j + 1]);
                strcpy(strings[j + 1],strtemp);
            }
        }
    }
    for (int i = 0; i < lines; i++) 
    {
        printf("Line %d: %s\n", i + 1, strings[i]);
        usleep(sleeptime);
    }
    printf("Sorting Complete! Saving...\n");
    usleep(2000000);
    // wipes the file, and then saves each word to a new line
    file = fopen(argv[1],"w");
    for (int i = 0; i < lines; i++) 
    {
        fprintf (file, "%s" , strings[i]);
        if (i != lines - 1) 
            fprintf (file, "\n");
    }
    printf("Saving Complete!\n");
    usleep(2000000);
    printf("Now that your file is alphabetized ");
    printf("you don't have to be so blue!\n");
    fclose(file);
}

// check to see the length of file - structure from https://goo.gl/XtI0EJ
int checklines(FILE* file)
{
    int lines = 0;
    while(true)
    {
        // scans through the chars and counts all of the newlines
        char c = fgetc(file);
        if (feof(file))
        {
            lines++;
            break;
        }
        else
        {
            if (c == '\n')
                lines++;
        }
    }
    return lines;
}