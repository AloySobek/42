#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <limits.h>

int g_hello = 0;

int main(void)
{
	wchar_t he;
	int		pre;
	int 	wid;
	long double	e;
	size_t flags;

	e = 1234334234.532234322323234234234234;
	pre = 7;
	wid = 20;
	flags = 0;
	flags |= POI;
	flags |= BIA;
	//putfloat(e, &flags, &wid, &pre);
	//pre = 10;
	//expofloat(e, &flags, &wid, &pre);
	//printf("\n");
	//ft_putcharbase(he, &wid, &pre);
	//wchar_t *hello;
	//hello = L"Я программирую на си";
	int test = 0;
	test = ft_printf(">>>|%d|<<<", 50);
	printf("   bytes = %d\n", test);
	test = printf(">>>|%d|<<<", 50);
	printf("   bytes = %d\n", test);
	return (0);
}