/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:33:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 23:11:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *g_buff;
int g_count;
int g_bytes;

int			eject(void)
{
	g_bytes += write(1, g_buff, g_count);
	g_count = 0;
	return (1);
}

void		everything_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	if ((*flags << 40) >> 56 == 'c' || (*flags << 40) >> 56 == 'C' || (*flags << 40) >> 56 == '%')
		char_handler(list, flags, wid);
	else if ((*flags << 40) >> 56 == 's' || (*flags << 40) >> 56 == 'S')
		string_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'd' || (*flags << 40) >> 56 == 'D' || (*flags << 40) >> 56 == 'i')
		decimal_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'u' || (*flags << 40) >> 56 == 'U')
		unsigned_decimal_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'f' || (*flags << 40) >> 56 == 'F')
		double_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'e' || (*flags << 40) >> 56 == 'E')
		expo_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'g' || (*flags << 40) >> 56 == 'G')
		;//return (double_or_expo_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'a' || (*flags << 40) >> 56 == 'A')
		;//return (hexafloat_handler(list, flags, wid, pre));
	else if ((*flags << 40) >> 56 == 'x' || (*flags << 40) >> 56 == 'X')
		hexadecimal_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'o' || (*flags << 40) >> 56 == 'O')
		octal_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'b' || (*flags << 40) >> 56 == 'B')
		binary_handler(list, flags, wid, pre);
	else if ((*flags << 40) >> 56 == 'p')
		pointer_handler(list, flags, wid, pre);
}

int			ft_printf(const char *format, ...)
{
	va_list	listv;
	size_t 	flags;
	int		pre;
	int		wid;

	va_start(listv, format);
	pre   = 0;
	wid   = 0;
	g_buff = malloc(BUFF_SIZE);
	g_count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			flags  = 0;
			flags |= 32;
			flags_collector(&format, &listv, &flags, &wid, &pre);
			if (*format && format++)
				everything_handler(&listv, &flags, &wid, &pre);
		}
		else
			g_buff[g_count++] = *format++;
	}
	va_end(listv);
	eject();
	return (g_bytes);
}
