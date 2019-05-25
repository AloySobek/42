#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>

int main(void)
{
	double e;
	int test;

	test = 0;
	e = 0.0;
	test = ft_printf("%030f", e);
	printf("   bytes = %d\n", test);
	test = printf("%030f", e);
	printf("   bytes = %d\n", test);
	return (0);
}
