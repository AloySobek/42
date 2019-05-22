//#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>

typedef struct	s_bits
{
	long long	mantis: 64;
	int	expo: 15;
	long	sign: 1;
}				t_bits;


typedef union	u_union
{
	long double q;
	short		array[5];
}				t_union;

static void comb(char *power)
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

    ft_memset(power, 0, 5001);
	if (pwr != 0)
    	power[5000] = 1;
    pwr2neg(&power[0], pwr);
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

void add_power(char *summ, long long pwr)
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

long long  helloworld(long long one)
{
	long long  result = 1;

	while (one-- > 0)
		result *= 2;
	return (result);
}

int main(void)
{
	long double	e;
	size_t flags;
	t_union new;
	t_bits bits;

	new.q = 4578451237845612389.25;
	bits.mantis = new.q;
	bits.expo = new.array[4] - 16383;
	//ft_printf("%llb\n", bits.mantis);
	//ft_printf("%lld\n", bits.expo);
	//printf("%lld", bits.mantis);
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

	char summ[5002];
	int n = 5000;
	/*char result[129];
	int x = 4;
	int i = 0;
	int y = 0;
	while (x >= 0)
	{
		i = 15;
		while (i >= 0)
		{
			if (*(new.array + x) & (1 << i--))
				result[y++] = '1';
			else
				result[y++] = '0';
		}
		x--;
	}
	write(1, result, y);
	result[y] = '\0';
	ft_printf("\n%d\n", ft_strlen(result));*/
	long long bl = 64;
	summ[5001] = 0;
	char summ2[5002];
    ft_memset(summ, 0, n + 1);
    ft_memset(summ2, 0, 5001);
	bits.expo >= 0 ? add_power(&summ[0], (bits.expo)--) : add_power_neg(&summ2[0], (bits.expo)--);
	double zzz = 0;
    int n2;
    int m2;
	while (bl-- >= 0)
	{
		ft_printf("%d\n", bits.expo);
		ft_printf("|||%064llb|||\n", bits.mantis);
		ft_printf("\\\\\\%064llb///\n", bits.mantis << bl);
		ft_printf("\n|%lld|\n\n", bits.mantis & (1L << bl));
		//ft_printf("%s\n", &summ[0]);
		if (bits.mantis & (1L << bl))
			bits.expo >= 0 ? add_power(&summ[0], bits.expo) : add_power_neg(&summ2[0], bits.expo);
		else
			bits.expo < 0 ? add_power_neg(&summ2[0], 0) : 0;//add_power(&summ[0], 0);
		(bits.expo)--;
	}
	n2 = 0;
	while (!summ2[n2])
		++n2;
	m2 = n2;
	n2 = 0;
	while (n2 <= 5000)
    {
        summ2[n2] += '0';
        ++n2;
	}
	//printf("\n%s\n", &summ2[m2]);
    n = 0;
    while (!summ[n])
        ++n;
    int m = n;
    while (n <= 5000)
    {
        summ[n] += '0';
        ++n;
    }
    printf("\n%s.%s\n", &summ[m], &summ2[m2]);

	return (0);
}
