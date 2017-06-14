#include <cs50.h>
#include <stdio.h>

bool checkvalidity(long long cardnumber, int digits);
long long exponential(long long x, int number);
void checkflag(long long cardnumber, int digits);

int main(void)
{
    long long cardnumber = 0;
    int digits = 0;
    bool validity;

    // CARD MUST HAVE BETWEEN 13 AND 16 DIGITS     
    do
    {
    printf("Number: ");    
    cardnumber = get_long_long();
    }
    while (cardnumber < 1);
 
    // Verify how many digits in card number   
    if (cardnumber < 1000000000000)
    {
        digits = 1; // store 1 as an error
    }
    else if (cardnumber < 10000000000000)
    {
        digits = 13;
    }
    else if (cardnumber < 100000000000000)
    {
        digits = 1; // store 1 as an error, since there are no cc with 14 digits
    }
    else if (cardnumber < 1000000000000000)
    {
        digits = 15;
    }
    else if (cardnumber < 10000000000000000)
    {
        digits = 16;
    }
    else
    {
        digits = 1; // store 1 as an error
    }


    // VERIFY CARD VALIDITY USING LUHNs ALGORITHM    
    if (digits == 1)
    {
        printf("INVALID\n");    
    }
    else 
    {
        validity = checkvalidity(cardnumber,digits);
        if(validity)
        {
            checkflag(cardnumber, digits);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

bool checkvalidity(long long cardnumber, int digits)
{
    int cc_digits[digits];
    int sum = 0;
    for (int i = 0; i < digits; i++)
    {
        cc_digits[i] = (cardnumber / exponential(10,digits - 1 - i)) % 10;
        
        //different actions depending if # of digits is odd (13, 15) or even (16)
        if (digits % 2 == 1)
        {
            if (i % 2 == 1)
            {
                
                // if digit is < 5, multiply by 2 and sum, if it is > 5, then it will result in a 2 digits number after multiplying by 2, those digits should count each as a number
                if (cc_digits[i] < 5)
                {
                    sum = sum + (cc_digits[i] * 2);
                }
                else
                {
                    switch (cc_digits[i])
                    {
                        case 5: 
                            sum = sum + 1 + 0;
                            break;
                        case 6: 
                            sum = sum + 1 + 2;
                            break;
                        case 7: 
                            sum = sum + 1 + 4;
                            break;
                        case 8: 
                            sum = sum + 1 + 6;
                            break;
                        case 9: 
                            sum = sum + 1 + 8;
                            break;
                    }
                
                }
            }    
            else
            {
                sum = sum + cc_digits[i];
            }
        }
        else
        {
            if (i % 2 == 0)
            {
                if (cc_digits[i] < 5)
                {
                    sum = sum + (cc_digits[i] * 2);
                }
                else
                {
                    switch (cc_digits[i])
                    {
                        case 5: 
                            sum = sum + 1 + 0;
                            break;
                        case 6: 
                            sum = sum + 1 + 2;
                            break;
                        case 7: 
                            sum = sum + 1 + 4;
                            break;
                        case 8: 
                            sum = sum + 1 + 6;
                            break;
                        case 9: 
                            sum = sum + 1 + 8;
                            break;
                    }
                
                }
            }    
            else
            {
                sum = sum + cc_digits[i];
            }
        }
    /* printf("sum[%i]=%i\n",i,sum);     */ 
    }
    if (sum % 10 == 0) // if sum ends in zero, true!
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// function to calculate a number (x) exp number times.
long long exponential(long long x, int number)
{
    long long result = 1;
    if (number < 0)
    {
        return -1;    
    }
    else if (number == 0)
    {
        return 1;    
    }
    else
    {
        for (int i = 0; i < number; i++)
        {
            result = result * x;
        }
    return result;
    }
}

// function to verify the flag of a card
void checkflag(long long cardnumber, int digits)
{
    //get first 2 digits of card 
    int initial = (cardnumber / exponential(10,digits - 2)) % 100;
    
    
    if((initial/10) % 10 == 4 && (digits == 16 || digits == 13))
    {
        printf("VISA\n");
    }
    else if ((initial == 34 || initial == 37) && digits == 15)
    {
        printf("AMEX\n");
    }
    else if ((initial >= 51 && initial <= 55) && digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n"); 
    }
        
}