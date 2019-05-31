#include <stdlib.h>
#include <stdio.h>
#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>

/*void		add_power_neg(char *med, int pwr)
{
	char	power[102] = {0};
	int		n;
	int		m;
	int		z;

	pwr *= -1;
	power[100] = 1;
	while (pwr-- && (n = 101))
	{
		while (n--)
			power[n] *= 5;
		n = 101;
		while (n--)
			while (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
	}
	n = 101;
	while (n--)
		med[n] += power[n];
	n = 101;
	while (n--)
		while (med[n] > 15)
		{
			med[n] -= 16;
			++med[n - 1];
		}
	n = 101;
	while (n--)
	{
		if (med[n] >= 10)
			med[n] += 55;
		else
			med[n] += 48;
	}
}*/

# define TEST 18446744073709551615U

void 	test_car(char **str1, char **str2, char **result)
{
	
}

/*void	 caratsuba_multiply(char **str, int pwr)
{
	if (pwr > 64)
		caratsuba_multiply(str, pwr / 2);
	else
	{
		multiply(char **str);
	}
	
}*/

int main(int argc, char **argv)
{
	/*char str[102] = {0};
	int i;

	i = -7;
	while (i >= -50)	
		add_power_neg(&str[0], i--);
	i = 0;
	while (!str[i])
		i++;
	while (str[i])
		printf("%c", str[i++]);
	printf("5d");
	*/
	char str[21] = {49, 56, 52, 52, 54, 55, 52, 52, 48, 55, 51, 55, 48, 57, 53, 53, 49, 54, 49, 53};
	double e;
	int test;
	char hello[129];

	int i = 0;
	while (++i <= 127)
		hello[i - 1] = i;
	hello[i] = 0;
	test = 0;
	e = 2.51;
	int count = 0;
	test = ft_printf("{%.f}", e);
	printf("      >>>>>      bytes = %d\n", test);
	//printf("%d\n", count);
	test = printf("{%.f}", e);
	printf("      >>>>>      bytes = %d\n", test);
	//printf("%d\n", count);
	return (0);
}
