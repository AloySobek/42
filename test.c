#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf.h"
#include <limits.h>


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
	//hello = L"привет как дела";
	int test = 0;
	test = ft_printf(">>>|%30.20Lf|<<<", e);
	printf("   bytes = %d\n", test);
	test = printf(">>>|%30.20Lf|<<<", e);
	printf("   bytes = %d\n", test);
	//printf("\n%.10f\n", e);
	return (0);
}