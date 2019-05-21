#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>

void power_of_two(char *power, int pwr)
{
    int n;
    int m;

    while (pwr)
    {
        n = 5000;
        while (n)
        {
            power[n] *= 2;
            --n;
        }
        n = 5000;
        while (n)
        {
            if (power[n] > 9)
            {
                power[n] -= 10;
                ++power[n - 1];
            }
            --n;
        }
        --pwr;
    }
}

void summ_powers(int pwr1, int pwr2)
{
    char power1[5002];
    char power2[5002];
    int n;
    int m;

    power1[5001] = 0;
    n = 5000;
    ft_memset(power1, 0, n);
    power1[n] = 1;
    power2[5001] = 0;
    n = 5000;
    ft_memset(power2, 0, n);
    power2[n] = 1;
    power_of_two(&power1[0], pwr1);
    power_of_two(&power2[0], pwr2);
    while (n)
    {
        power1[n] += power2[n];
        --n;
    }
    n = 5000;
    while (n)
    {
        if (power1[n] > 9)
        {
            power1[n] -= 10;
            ++power1[n - 1];
        }
        --n;
    }
    while (!power1[n])
        n++;
    m = n;
    while (n <= 5000)
    {
        power1[n] += '0';
        n++;
    }
    ft_printf("%s\n", &power1[m]);
}

int main(void)
{
	double	e;
	size_t flags;

	/*e = 65.54234234000001001;
	wchar_t *hello2;
	hello2 = L"Я программирую на си";
	char *hello;
	hello = "hello from that";
	int test = 0;
	int i;
	//while (test++ < 100400)
	test = ft_printf("\033[0;31m");

	ft_printf("    bytes = %d\n", test);
	test = printf("\033[0;31m");
	printf("    bytes = %d\n", test);*/
	e = 1234123411344654648463846534156465456546846879511234123333112351234.0;
	summ_powers(806, 0);
	int x = 53;
	int i = 1;
	long long int eee = *((long long *)&e);
	int expo = (*((long long *)&e) << 1) >> 53;
	ft_printf("%llb\n", eee);
	expo < 0 ? expo *= -1 : 0;
	printf("%d", expo);
	/*int sign = (*((long long *)&e) & (1L << 63));
	long long mant = (*((long long *)&e) << 12) >> 12;
	int expo2;
	expo > 53 ? (expo2 = (expo - 53)) : (expo2 = 0);

	while (x--)
	{
		if (mant & i)
			summ_powers(expo2, expo2 + 1);
		expo++;
		i <<= 1;
	}*/

	return (0);
}

void power_of_two(char *power, int pwr)
{
    int n;
    int m;

    while (pwr)
    {
        n = 5000;
        while (n)
        {
            power[n] *= 2;
            --n;
        }
        n = 5000;
        while (n)
        {
            if (power[n] > 9)
            {
                power[n] -= 10;
                ++power[n - 1];
            }
            --n;
        }
        --pwr;
    }
}

void add_power(char *summ, int pwr)
{
    char power[5002];
    int n;

    power[5001] = 0;
    n = 5000;
    ft_memset(power, 0, n);
    power[n] = 1;
    power_of_two(&power[0], pwr);
    while (n)
    {
        summ[n] += power[n];
        --n;
    }
    n = 5000;
    while (n)
    {
        if (summ[n] > 9)
        {
            summ[n] -= 10;
            ++summ[n - 1];
        }
        --n;
    }
}

void summ_powers(void)
{
    char summ[5002];
    int n;
    int m;

    summ[5001] = 0;
    n = 5000;
    ft_memset(summ, 0, n + 1);

    add_power(&summ[0], 2);
    add_power(&summ[0], 4);
    add_power(&summ[0], 4);
    add_power(&summ[0], 10);

    n = 0;
    while (!summ[n])
        ++n;
    m = n;
    while (n <= 5000)
    {
        summ[n] += '0';
        ++n;
    }
    ft_printf("%s\n", &summ[m]);
}
