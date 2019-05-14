/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_handlers_addit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:31:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 11:10:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int binary_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= (2 << 8);
	if (*flags & HH)
		return (print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre));
	else if (*flags & H)
		return (print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre));
	else if (*flags & LL)
		return (print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre));
	else if (*flags & L)
		return (print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre));
	else if (*flags & J)
		return (print_uns_dig(va_arg(*list, uintmax_t), flags, wid, pre));
	else if (*flags & Z)
		return (print_uns_dig(va_arg(*list, size_t), flags, wid, pre));
	else 
		return (print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre));	
}