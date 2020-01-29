#include <cs50.h>
#include <stdio.h>

int get_height(void);
void make_pyramid(int height);

int main(void)
{
    int height = get_height();
    make_pyramid(height);
}

int get_height(void)
{
    // function to ask the user for a height between 1 to 8 (inclusive)
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));
    
    return height;
}

void make_pyramid(int height)
{
    // function to create a pyramid with a user defined height
    int outer_gap = height - 1;
    int width = height - outer_gap;
    
    for (int i = 0; i < height; i++)
    {
        // print left gap
        for (int j = 0; j < outer_gap; j++)
        {
            printf(" ");
        }
        // print right portion of pyramid
        for (int k = 0; k < width; k++)
        {
            printf("#");
        }
        
        // print middle gap
        printf("  ");
        
        //print right portion of pyramid
        for (int x = 0; x < width; x++)
        {
            printf("#");
        }
        // move to next row
        printf("\n");
        //reduce width of gap for next row
        outer_gap--;
        // increase width of pyramid for next row
        width++;
    }
}
