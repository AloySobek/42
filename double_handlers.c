/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/18 20:17:54 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'F' ? *flags |= BIG : 0; 
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	if (*flags & BL)
		print_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_double(va_arg(*list, double), flags, wid, pre);
}

void	expo_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'E' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	if (*flags & BL)
		print_expo_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_expo_double(va_arg(*list, double), flags, wid, pre);
}

void	g_handler(va_list *list, size_t *flags, int *wid, int *pre)
{	
	long double src;
	long double cop;
	int			expo;

	(SPEC) == 'G' ? *flags |= BIG : 0;
	*flags |= GOF;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	src = va_arg(*list, long double);
	cop = src;
	if (cop >= 10)
	{
		while (cop >= 10)
		{
			cop /= 10;
			expo++;
		}
	}
	else if (cop < 1)
	{
		while (cop < 1)
		{
			cop *= 10;
			expo++;
		}
	}
	!(*flags & POI) ? *pre = 6 : 0;
	if (*flags & POI && *pre == 0)
		*pre = 1;
	if (expo < *pre && expo >= -4)
	{
		*pre = (expo + 1);
		print_double(src, flags, wid, pre);
	}
	else
	{
		*pre -= 1;
		print_expo_double(src, flags, wid, pre);
	}
}