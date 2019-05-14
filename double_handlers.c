/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/13 19:57:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	//((*flags << 40) >> 56) == 'F' ? *flags |= 
	if (*flags & BL)
		return (print_double(va_arg(*list, long double), flags, wid, pre));
	else
		return (print_double(va_arg(*list, double), flags, wid, pre));
	return (1);
}

int		expo_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	((*flags << 40) >> 56) == 'E' ? *flags |= BIG : 0;
	if (*flags & BL)
		return (print_expo_double(va_arg(*list, long double), flags, wid, pre));
	else
		return (print_expo_double(va_arg(*list, double), flags, wid, pre));
	return (1);
}