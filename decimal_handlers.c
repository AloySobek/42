/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:20:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 14:34:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pointer_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= HAS;
	*flags |= PTR;
	*flags |= (16 << 8);
	return (print_uns_dig(va_arg(*list, intptr_t), flags, wid, pre));
}

int	hexadecimal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	((*flags << 40) >> 56) == 'X' ? *flags |= BIG : 0;
	*flags |= (16 << 8);
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

int	decimal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= (10 << 8);
	if ((*flags << 40) >> 56 == 'D')
		return (print_sig_dig(va_arg(*list, long), flags, wid, pre));
	else if (*flags & HH)
		return (print_sig_dig((char)va_arg(*list, int), flags, wid, pre));
	else if (*flags & H)
		return (print_sig_dig((short)va_arg(*list, int), flags, wid, pre));
	else if (*flags & LL)
		return (print_sig_dig(va_arg(*list, long long), flags, wid, pre));
	else if (*flags & L)
		return (print_sig_dig(va_arg(*list, long), flags, wid, pre));
	else if (*flags & J)
		return (print_sig_dig(va_arg(*list, intmax_t), flags, wid, pre));
	else if (*flags & Z)
		return (print_sig_dig(va_arg(*list, size_t), flags, wid, pre));
	else
		return (print_sig_dig(va_arg(*list, int), flags, wid, pre));
}

int	unsigned_decimal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(*flags & PLU) ? (*flags ^= PLU) : 0;
	(*flags & SPA) ? (*flags ^= SPA) : 0;
	*flags |= (10 << 8);
	if ((*flags << 40) >> 56 == 'U')
		return (print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre));
	else if (*flags & HH)
		return print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		return print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		return print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre);	
	else if (*flags & L)
		return print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & J)
		return (print_uns_dig(va_arg(*list, intmax_t), flags, wid, pre));
	else if (*flags & Z)
		return (print_uns_dig(va_arg(*list, size_t), flags, wid, pre));
	else 
		return print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre);
}

int	octal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= (8 << 8);
	if ((*flags << 40) >> 56 == 'O')
		return (print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre));
	else if (*flags & HH)
		return print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		return print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		return print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre);
	else if (*flags & L)
		return print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & J)
		return (print_uns_dig(va_arg(*list, intmax_t), flags, wid, pre));
	else if (*flags & Z)
		return (print_uns_dig(va_arg(*list, size_t), flags, wid, pre));
	else 
		return (print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre));
}
