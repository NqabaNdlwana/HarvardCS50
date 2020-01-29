#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

void caesar(string pt, int k);

int main(int argc, string argv[])
{
    // check that 2 arguements were given
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // check that second arguement is strictly numerical
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if ((argv[1][i] >= '0') && (argv[1][i] <= '9'))
        {
            continue;
        }
        else
        {
            printf("Key must be strictly numerical.\n");
            return 1;
        }
    }
    int key = 0;

    // convert string to number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        int factor = pow(10, (n - i - 1));
        int digit = (argv[1][i] - 48);
        key += digit * factor;
    }
    string plaintext = get_string("plaintext: ");
    caesar(plaintext, key);
    return 0;
}

void caesar(string pt, int k)
{
    // function to encrypt text using Caesar's cipher

    printf("ciphertext: ");

    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        // lower case remains lower case
        if ((pt[i] >= 'a') && (pt[i] <= 'z'))
        {
            int c = (((pt[i] - 96) + k) % 26) + 96;
            printf("%c", c);
        }
        // upper case remains upper case
        else if ((pt[i] >= 'A') && (pt[i] <= 'Z'))
        {
            int c = (((pt[i] - 64) + k) % 26) + 64;
            printf("%c", c);
        }
        // non-alphabetical characters remain the same
        else
        {
            printf("%c", pt[i]);
        }
    }
    printf("\n");
}
