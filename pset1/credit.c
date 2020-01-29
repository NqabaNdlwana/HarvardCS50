#include <stdio.h>
#include <cs50.h>

int luhn_algo(unsigned long cred_num);
void cred_company(unsigned long cred_num);

int main(void)
{
    unsigned long cred_num = get_long_long("Number: ");
    int luhn_check = luhn_algo(cred_num);
    
    // check if given number is valid
    if ((luhn_check % 10) == 0)
    {
        // if given a valid number determine which company it's from
        cred_company(cred_num);
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhn_algo(unsigned long cred_num)
{
    // function implementing Luhn's algorithm
    unsigned long power_of_10 = 10;
    unsigned long second_power_of_10 = 100;
    int odd_sum = 0;
    int even_sum = 0;
    
    // loop while credit card number is greater than zero
    while (cred_num)
    {
        // get the current digit of the credit card number
        unsigned long cred_mod = cred_num % power_of_10;
        // subtract the current digit from the credit card number
        cred_num -= cred_mod;
        // scale the current digit to a single digit
        cred_mod /= (power_of_10 / 10);
        
        // condition for every second digit
        if (power_of_10 == second_power_of_10)
        {
            // multiply current digit by 2
            int times_2 = cred_mod * 2;
            // determine whether doubling created a double digit number
            int floor_div_10 = times_2 / 10;
            // increase scaling factor that determines even index digits
            second_power_of_10 *= 100;
            
            // sum the digits of every even index credit card number digit multiplied by 2
            if (floor_div_10)
            {
                even_sum += (times_2 % 10) + 1;
            }
            else
            {
                even_sum += times_2;
            }
        }
        // sum the digits of every odd index credit card number digit
        else
        {
            odd_sum += cred_mod;
        }
        power_of_10 *= 10;
    }
    // final sum for Luhn's algorithm
    int cred_sum = odd_sum + even_sum;
    
    return cred_sum;
}

void cred_company(unsigned long cred_num)
{
    // function to determine which credit card commpany a credit card is from
    
    // conditions for American Express:
    //     starts with either: 34 or 37
    //     is 15 digits long
    unsigned long ae_0_0 = 340000000000000;
    unsigned long ae_0_1 = cred_num - ae_0_0;
    unsigned long ae_1_0 = 370000000000000;
    unsigned long ae_1_1 = cred_num - ae_1_0;
    unsigned long ae_nines = 9999999999999;
    
    // conditions for Master Card:
    //     starts with either: 51, 52, 53, 54, 55
    //     is 16 digits long
    unsigned long mc_0_0 = 5100000000000000;
    unsigned long mc_0_1 = cred_num - mc_0_0;
    unsigned long mc_1_0 = 5200000000000000;
    unsigned long mc_1_1 = cred_num - mc_1_0;
    unsigned long mc_2_0 = 5300000000000000;
    unsigned long mc_2_1 = cred_num - mc_2_0;
    unsigned long mc_3_0 = 5400000000000000;
    unsigned long mc_3_1 = cred_num - mc_3_0;
    unsigned long mc_4_0 = 5500000000000000;
    unsigned long mc_4_1 = cred_num - mc_4_0;
    unsigned long mc_nines = 99999999999999;
    
    // conditions for Visa:
    //     starts with number 4
    //     is either 13 or 16 digits long
    unsigned long visa_0_0 = 4000000000000000;
    unsigned long visa_0_1 = cred_num - visa_0_0;
    unsigned long visa_1_0 = 4000000000000;
    unsigned long visa_1_1 = cred_num - visa_1_0;
    unsigned long visa_nines_0 = 999999999999999;
    unsigned long visa_nines_1 = 999999999999;
    
    // determine if it's an American Express card
    if (((ae_0_1 >= 0) && (ae_0_1 <= ae_nines)) ||
        ((ae_1_1 >= 0) && (ae_1_1 <= ae_nines)))
    {
        printf("AMEX\n");
    }
    // determine if it's a Master Card card
    else if (((mc_0_1 >= 0) && (mc_0_1 <= mc_nines)) || 
             ((mc_1_1 >= 0) && (mc_1_1 <= mc_nines)) || 
             ((mc_2_1 >= 0) && (mc_2_1 <= mc_nines)) || 
             ((mc_3_1 >= 0) && (mc_3_1 <= mc_nines)) || 
             ((mc_4_1 >= 0) && (mc_4_1 <= mc_nines)))
    {
        printf("MASTERCARD\n");
    }
    // determine if it's a Visa card
    else if (((visa_0_1 >= 0) && (visa_0_1 <= visa_nines_0)) ||
             ((visa_1_1 >= 0) && (visa_1_1 <= visa_nines_1)))
    {
        printf("VISA\n");
    }
    // determine if it's not from any of the above companies
    else
    {
        printf("INVALID\n");
    }
}
