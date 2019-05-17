/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/16 17:08:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'F' ? *flags |= BIG : 0; 
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	if (*flags & BL)
		print_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_double(va_arg(*list, double), flags, wid, pre);
}

void	expo_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'E' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	if (*flags & BL)
		print_expo_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_expo_double(va_arg(*list, double), flags, wid, pre);
}

void	g_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'G' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & FLO) ? (*flags |= 48) : 0;
	/*
	code...soon
	code...soon
	code...soon
	*/
}