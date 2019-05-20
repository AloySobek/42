#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>

int main(void)
{
	double	e;
	size_t flags;

	e = 1.1;
	wchar_t *hello2;
	hello2 = L"Я программирую на си";
	char *hello;
	hello = "hello from that";
	int test = 0;
	int i;
	//while (test++ < 100400)
	test = ft_printf("%+80Lf", e);
	printf("    bytes = %d\n", test);
	test = printf("%+80LF", e);
	printf("    bytes = %d\n", test);
	
	/*while (test++ < 100000)
		//ft_printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		//hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);
		//printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		//hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);*/
	return (0);
}
