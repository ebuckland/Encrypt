
// libraries to include
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// prototypes
int parseHexadecimal(char[], unsigned char[]);
int hextoDecimal(char, char);
int decimaltoHex(unsigned char[], int, unsigned char[]);

// acceptable hexadecimal chars
char hexChars[] = "0123456789abcdef";

int main(void)
{
    // the string for the text entering of the key, hexadecimal
    char keyString[512];
    
    printf("No spaces, Hexadecimal\n");
    printf("Key: ");
    scanf("%s",keyString);
    
    // creates the array for the key
    unsigned char key[strlen(keyString) / 2];
    
    // converts the hexadecimal string to the decimal array key
    // if the user enters in an invalid hex code, stop
    if (!parseHexadecimal(keyString, key)) 
    {
        printf("Unacceptable key\n");
        printf("Use hexadecimal with no spaces\n");
        return 0;
    }
    
    // creates the state array, and puts in incruments by one for each slot
    unsigned char state[256];
    for (int i = 0; i < sizeof(state); i++) 
    {
        state[i] = i;
    }
    
    // mixing loop for the state array
    unsigned char tempVar;
    unsigned char j = 0;
    for (int i = 0; i < 256; i++) 
    {
        j = (j + state[i] + key[i % sizeof(key)]);
        tempVar = state[i];
        state[i] = state[j];
        state[j] = tempVar;
    }
    j = 0;
    
    // prompts the user to enter in the string for encoding/decoding
    // if the user prefers, they can enter # to move to hexadecimal enter mode
    printf("Return # to move to Hex mode\n");
    printf("String: ");
    unsigned char string[128];
    scanf(" %[^\n]s",string);
    int stringLength = 0;
    
    // if the user wants to use hex enter mode
    if (string[0] == '#')
    {
        // gets the hexadecimal string from the user
        char hexString[128];
        printf("Hex String: ");
        scanf("%s",hexString);
        
        // converts hexadecimal string the user entered to the character string
        // if the user enters in an invalid hex code, the program stops
        if (!parseHexadecimal(hexString, string)) 
        {
            printf("Unacceptable hex\n");
            printf("Use hexadecimal with no spaces\n");
            return 0;
        }
        // gets the length of the string by dividing the hex by 2
        stringLength = strlen(hexString) / 2;
    } 
    else 
    // if the user enters in the string, search for the end value to find how long the string is
    {
        
        for (int i = 0; i < sizeof(string); i++) 
        {
            if (string[i] == '\0') 
            {
                stringLength = i;
                break;
            }
        } 
    }
    
    // ciphering, using state and repeating the length of the string
    unsigned char n;
    for (int i = 0; i < stringLength;i++)
    {
        j = j + state[i];
        tempVar = state[i];
        state[i] = state[j];
        state[j] = tempVar;
        n = state[i] + state[j];
        string[i] = (string[i] ^ state[n]);
    }
    
    // creates a temporary char array to print the hexadecimal string from decimal
    unsigned char hex[stringLength * 2];
    decimaltoHex(string,stringLength,hex);
    
    printf("Output Hex: %s\n",hex);
    printf("Output String: %s\n",string);
    
    return 1;
}

// returns the hex string in char form, from the user input
int parseHexadecimal(char hexString[], unsigned char string[])
{
    // if the user enters in a hex with a size that is uneven, stop
    if (strlen(hexString) % 2 != 0) 
    {
        return 0;
    }
    // if the user enters in characters that are not part of the allowed hexadecimal characters, stop
    for (int i = 0; i < strlen(hexString); i++) 
    {
        if (strchr(hexChars, tolower(hexString[i])) == NULL) 
        {
            return 0;
        }
    }
    
    // repeating for the length of the hex string / 2, convert hexadecimal to decimal
    for (int i = 0; i < strlen(hexString); i += 2) 
    {
        string[i / 2] = hextoDecimal(hexString[i],hexString[i + 1]);
    }
    return 1;
}

// returns the decimal value of a hexadecimal number ab
int hextoDecimal(char a, char b)
{
    int aNum = 0;
    int bNum = 0;
    
    // looks for the hexadecimal character in the hex char list, and sets the decimals to the place in the list
    // done for both hexadecimal 10's place and 1's place
    for (int i = 0; i < strlen(hexChars); i++)
    {
        if (tolower(a) == hexChars[i]) 
        {
            aNum = i;
            break;
        }
    }
    for (int i = 0; i < strlen(hexChars);i++)
    {
        if (tolower(b) == hexChars[i]) 
        {
            bNum = i;
            break;
        }
    }
    
    // returns the multiplied the value of 10's place by 16 and adds the value of 1's place
    return aNum * 16 + bNum;
}

// returns the hexadecimal char array from string array
int decimaltoHex(unsigned char string[], int stringLength, unsigned char hex[])
{
    // repeats for the length of the string, getting the char list value of the string in the 10's and 1's place
    // puts the output in the hexadecimal char array
    for (int i = 0; i < stringLength; i++)
    {
        hex[i * 2] = hexChars[string[i] / 16];
        hex[(i * 2) + 1] = hexChars[string[i] % 16];
    }
    
    hex[stringLength * 2] = '\0';
    return 1;
}

// oh hey!
