/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:33:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/21 15:33:28 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char g_buff[BUFF_SIZE];
int g_count;
int g_bytes;

int			eject(void)
{
	g_bytes += write(1, g_buff, g_count);
	g_count = 0;
	return (1);
}

void		ever_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	if (SPEC == 'c' || SPEC == 'C' || SPEC == '%')
		char_handler(list, flags, wid);
	else if (SPEC == 's' || SPEC == 'S')
		string_handler(list, flags, wid, pre);
	else if (SPEC == 'd' || SPEC == 'D' || SPEC == 'i')
		decimal_handler(list, flags, wid, pre);
	else if (SPEC == 'u' || SPEC == 'U')
		unsigned_decimal_handler(list, flags, wid, pre);
	else if (SPEC == 'f' || SPEC == 'F')
		double_handler(list, flags, wid, pre);
	else if (SPEC == 'e' || SPEC == 'E')
		expo_handler(list, flags, wid, pre);
	else if (SPEC == 'g' || SPEC == 'G')
		g_handler(list, flags, wid, pre);
	else if (SPEC == 'x' || SPEC == 'X')
		hexadecimal_handler(list, flags, wid, pre);
	else if (SPEC == 'o' || SPEC == 'O')
		octal_handler(list, flags, wid, pre);
	else if (SPEC == 'b' || SPEC == 'B')
		binary_handler(list, flags, wid, pre);
	else if (SPEC == 'r' || SPEC == 'k')
		;
	else if (SPEC == 'p')
		pointer_handler(list, flags, wid, pre);
}

int			ft_printf(const char *format, ...)
{
	va_list	listv;
	size_t	flags;
	int		pre;
	int		wid;

	va_start(listv, format);
	g_count = 0;
	g_bytes = 0;
	pre = 0;
	wid = 0;
	while (*format)
	{
		if (*format == '%' && !(flags = 0) && format++ && (flags |= 32))
		{
			flags_collector(&format, &listv, &flags, &wid, &pre);
			if (flags & UND)
				continue;
			*format && format++ ? ever_handler(&listv, &flags, &wid, &pre) : 0;
		}
		else if (EJECT(1))
			g_buff[g_count++] = *format++;
	}
	va_end(listv);
	eject();
	return (g_bytes);
}
