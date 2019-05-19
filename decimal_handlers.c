/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:20:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/19 16:59:16 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pointer_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= HAS;
	*flags |= PTR;
	*flags |= (16 << 8);
	print_uns_dig(va_arg(*list, intptr_t), flags, wid, pre);
}

void	hexadecimal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'X' ? *flags |= BIG : 0;
	*flags |= (16 << 8);
	if (*flags & HH)
		print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre);
	else if (*flags & L)
		print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & J)
		print_uns_dig(va_arg(*list, uintmax_t), flags, wid, pre);
	else if (*flags & Z)
		print_uns_dig(va_arg(*list, size_t), flags, wid, pre);
	else
		print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre);
}

void	decimal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= (10 << 8);
	if (SPEC == 'D')
		print_sig_dig(va_arg(*list, long), flags, wid, pre);
	else if (*flags & HH)
		print_sig_dig((char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		print_sig_dig((short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		print_sig_dig(va_arg(*list, long long), flags, wid, pre);
	else if (*flags & L)
		print_sig_dig(va_arg(*list, long), flags, wid, pre);
	else if (*flags & J)
		print_sig_dig(va_arg(*list, intmax_t), flags, wid, pre);
	else if (*flags & Z)
		print_sig_dig(va_arg(*list, size_t), flags, wid, pre);
	else
		print_sig_dig(va_arg(*list, int), flags, wid, pre);
}

void	unsigned_decimal_handler(va_list *list, size_t *flags, int *wid,
		int *pre)
{
	(*flags & PLU) ? (*flags ^= PLU) : 0;
	(*flags & SPA) ? (*flags ^= SPA) : 0;
	*flags |= (10 << 8);
	if (SPEC == 'U')
		print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & HH)
		print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre);
	else if (*flags & L)
		print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & J)
		print_uns_dig(va_arg(*list, intmax_t), flags, wid, pre);
	else if (*flags & Z)
		print_uns_dig(va_arg(*list, size_t), flags, wid, pre);
	else
		print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre);
}

void	octal_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	*flags |= (8 << 8);
	if (SPEC == 'O')
		print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & HH)
		print_uns_dig((unsigned char)va_arg(*list, int), flags, wid, pre);
	else if (*flags & H)
		print_uns_dig((unsigned short)va_arg(*list, int), flags, wid, pre);
	else if (*flags & LL)
		print_uns_dig(va_arg(*list, unsigned long long), flags, wid, pre);
	else if (*flags & L)
		print_uns_dig(va_arg(*list, unsigned long), flags, wid, pre);
	else if (*flags & J)
		print_uns_dig(va_arg(*list, intmax_t), flags, wid, pre);
	else if (*flags & Z)
		print_uns_dig(va_arg(*list, size_t), flags, wid, pre);
	else
		print_uns_dig(va_arg(*list, unsigned int), flags, wid, pre);
}
