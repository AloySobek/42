/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/25 20:13:27 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'F' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	*flags |= END;
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
	*flags |= END;
	if (*flags & BL)
		print_expo_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_expo_double(va_arg(*list, double), flags, wid, pre);
}

void	g_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	long double src;
	long double cop;
	double		sec;
	int			expo;

	(SPEC) == 'G' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	*flags |= END;
	*flags & BL ? src = va_arg(*list, long double) : 0;
	!(*flags & BL) ? sec = va_arg(*list, double) : 0;
	expo = 0;
	cop = src;
	calculation_expo(&cop, &expo);
	*flags & POI && *pre == 0 ? *pre = 0 : 0;
	if (expo < *pre && expo >= -4)
	{
		*pre -= (expo + 1);
		print_double(*flags & BL ? src : sec, flags, wid, pre);
	}
	else
	{
		*pre -= 1;
		print_expo_double(*flags & BL ? src : sec, flags, wid, pre);
	}
}
