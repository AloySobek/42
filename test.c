#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <limits.h>
#include <math.h>

int main(void)
{
	double	e;
	size_t flags;

	e = 2341324534523453245.234187744567;
	wchar_t *hello2;
	hello2 = L"Я программирую на си";
	char *hello;
	hello = "hello from that";
	int test = 0;
	//while (test++ < 100400)
	test = ft_printf("%f", e);
	printf("    bytes = %d\n", test);
	test = printf("%f", e);
	printf("    bytes = %d\n", test);
	/*while (test++ < 100000)
		//ft_printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		 //hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);
		printf(">>>|%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s|<<<", hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
		 hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello, hello);
	//printf("   bytes = %d\n", test);*/
	return (0);
}
