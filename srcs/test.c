#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>

/*int main(void)
{
    long double e = 1234.1234;
	wchar_t *hello2;
	int test = 0;

	hello2 = L"Я программирую на си";
	//while (test++ < 100400)
	test = ft_printf("%Lf", e);
	printf("    bytes = %d\n", test);
	test = printf("%Lf", e);
	printf("    bytes = %d\n", test);

	return (0);
}*/

	/*long long n = 5000;
	char summ[5002];
	long long test = 0;
	char result[129];
	int x = 3;
	int i = 0;
	int test1 = 63;
	while (x >= 0)
	{
		i = 15;
		while (i >= 0)
		{
			if (*(new.array + x) & (1L << i--))
				test |= (1L << test1);
			else
				test |= (0L << test1);
			test1--;
		}
		x--;
	}*/

/*static void comb(char *power)
{
    int n;

    n = 5000;
    while (n)
    {
        while (power[n] > 9)
        {
	        power[n] -= 10;
    	    ++power[n - 1];
        }
        --n;
    }
}

void pwr2neg(char *power, int pwr)
{
    int n;

    pwr *= -1;
    while (pwr)
    {
        n = 5000;
        while (n)
        {
            power[n] *= 5;
            --n;
        }
        comb(&power[0]);
        --pwr;
    }
}

void add_power_neg(char *summ, int pwr)
{
    char power[5002];
    int n;
    int s;

    n = 0;
    while (!summ[n])
        ++n;
    while (n <= 5000)
    {
        summ[n - 1] = summ[n];
        ++n;
    }
    summ[5000] = 0;
    n = 5000;
    while (n)
    {
        summ[n] += power[n];
        --n;
    }
    comb(summ);
}*/

/*void	add_power_neg(char *summ, int pwr)
{
	char power[5002] = {0};
	int n;
	int m;

	pwr *= -1;
	pwr != 0 ? (power[pwr - 1] = 1) : 0;
	m = pwr;
	while (pwr-- && (n = m))
	{
		while (n--)
			power[n] *= 5;
		n = m;
		while (n--)
			while (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
	}
	n = m;
	while (n--)
	   summ[n] += power[n];
	n = m;
	while (n--)
		while (summ[n] > 9)
		{
			summ[n] -= 10;
			++summ[n - 1];
		}
}

void		add_power(char *summ, int pwr)
{
    char	power[5002] = {0};
    int		n;

    n = 5000;
    power[n] = 1;
	while (pwr-- && (n = 5001))
    {
        while (--n)
            power[n] *= 2;
        n = 5001;
        while (--n)
            if (power[n] > 9)
            {
                power[n] -= 10;
				++power[n - 1];
            }
    }
	n = 5001;
    while (--n)
        summ[n] += power[n];
    n = 5001;
    while (--n)
        if (summ[n] > 9)
        {
            summ[n] -= 10;
            ++summ[n - 1];
        }
}*/

int main(void)
{
	long double e;
	int test;

	test = 0;
	e = 12123456.30000000;
	test = ft_printf("%-0100Lg", e);
	printf("   bytes = %d\n", test);
	test = printf("%-0100Lg", e);
	printf("   bytes = %d\n", test);
	return (0);
}
/*
static void comb(char *power)
{
    int n;

    n = 0;
    while (n <= 5000)
    {
        while (power[n] > 9)
        {
            power[n] -= 10;
            ++power[n - 1];
        }
        ++n;
    }
}

void pwr2neg(char *power, int pwr)
{
   int n;

   pwr *= -1;
   while (pwr)
   {
       n = 0;
       while (n <= 5000)
       {
           power[n] *= 5;
           ++n;
       }
       comb(&power[0]);
       --pwr;
   }
}

void add_power_neg(char *summ, int pwr)
{
   char power[5002] = {0};
   int n;
   int s;

    if (pwr != 0)
       power[-pwr - 1] = 1;
   pwr2neg(&power[0], pwr);
   n = 0;
   while (n <= 5000)
   {
       summ[n] += power[n];
       ++n;
   }
   comb(summ);
}*/
