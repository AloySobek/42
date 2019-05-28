#include <stdlib.h>
#include <stdio.h>
#include "ft_printf.h"
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

int main(void)
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
	double e;
	int test;

	test = 0;
	e = 0.0000000002341234;
	test = ft_printf(">%#8e<\n", e);
	printf("   bytes = %d\n", test);
	test = printf(">%#8e<\n", e);
	printf("   bytes = %d\n", test);
	return (0);
}
