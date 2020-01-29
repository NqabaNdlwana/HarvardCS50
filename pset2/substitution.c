#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

void substituion(string pt, string k);

int main(int argc, string argv[])
{
    string key = argv[1];

    // check if 2 arguements were given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // check if the second arguement is 26 characters long
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // check if second arguement is strictly alphabetical
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (((key[i] >= 'a') && (key[i] <= 'z')) ||
            ((key[i] >= 'A') && (key[i] <= 'Z')))
        {
            continue;
        }
        else
        {
            printf("Key must be strictly alphabetical.");
            return 1;
        }
    }
    // check if second arguement contains duplicates
    for (int i = 0, n = strlen(key); i < (n - 1); i++)
    {
        printf("%c%c", key[i], key[i + 1]);

        if (key[i] == key[i + 1])
        {
            printf("Key must not complain duplicate characters.");
            return 1;
        }
    }
    string plaintext = get_string("plaintext: ");
    substituion(plaintext, key);
    return 0;
}

void substituion(string pt, string k)
{
    // function to convert plain text to cipher text using a key
    printf("ciphertext: ");

    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        // keep cipher text lower case if plain text lower case
        if ((pt[i] >= 'a') && (pt[i] <= 'z'))
        {
            int j = pt[i] - 97;
            printf("%c", tolower(k[j]));
        }
        // keep cipher text upper case if plain text upper case
        else if ((pt[i] >= 'A') && (pt[i] <= 'Z'))
        {
            int j = pt[i] - 65;
            printf("%c", toupper(k[j]));
        }
        // leave cipher text unchanged if plain text isn't a letter
        else
        {
            printf("%c", pt[i]);
        }
    }
    printf("\n");
}
