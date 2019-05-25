#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>

int main(void)
{
	long double e;
	int test;

	test = 0;
	e = 99.8999999;
	test = ft_printf("%@{cyan}030Lf\n%S", e, L"Повар павел повар петр");
	printf("   bytes = %d\n", test);
	test = printf("%030Lf", e);
	printf("   bytes = %d\n", test);
	return (0);
}
