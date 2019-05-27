/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 16:42:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'F' || SPEC == 'E' || SPEC == 'G' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	*flags |= END;
	if (*flags & BL)
		print_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_double(va_arg(*list, double), flags, wid, pre);
}

void	hexadouble_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'A' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	*flags |= END;
	*flags |= HAS;
	*flags |= (16 << 8);
	(*wid)++;
	list = NULL;
	if (*flags & BL)
		;//print_hexadouble(va_arg(*list, long double), flags, wid, pre);
	else
		;//print_hexadouble(va_arg(*list, double), flags, wid, pre);
}