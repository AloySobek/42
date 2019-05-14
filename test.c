#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <limits.h>

int main(void)
{
	long double	e;
	size_t flags;

	e = 1234334234.532234322323234234234234;
	//wchar_t *hello;
	//hello = L"Я программирую на си";
	char *hello;
	hello = "hello from that";
	int test = 0;
	while (test++ < 100000)
		//ft_printf(">>>|%d%d%d|<<<", 42, 42, 42);
	//printf("    bytes = %d\n", test);
		printf(">>>|%d%d%d|<<<", 42, 42, 42);
	//printf("    bytes = %d\n", test);
	/*while (test++ < 100000)
		//ft_printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		 //hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);
		printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		 hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);*/
	return (0);
}
