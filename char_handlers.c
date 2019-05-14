/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:26:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 16:45:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		char_handler(va_list *list, size_t *flags, int *wid)
{
	(*flags << 40) >> 56 == 'C' || *flags & L ? *flags |= UNI : 0;
	if ((*flags << 40) >> 56 == '%')
		return (print_any_char('%', flags, wid));
	return (print_any_char(va_arg(*list, wchar_t), flags, wid));
}

int		string_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(*flags & BIA) ? 0 : (*flags |= 48);
	(*flags << 40) >> 56 == 'S' || *flags & L ? *flags |= UNI : 0;
	return (print_any_string(va_arg(*list, wchar_t *), flags, wid, pre));
}

void	uni(wchar_t c)
{
	if (c <= 0x7FF && (g_count += 2))
	{
		g_buff[g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 2] = 0xC0 | (c & 0x1F);
	}
	else if (c <= 0xFFFF && (g_count += 3))
	{
		g_buff[g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 3] = 0xE0 | (c & 0xF);
	}
	else if (c <= 0x10FFFF && (g_count += 4))
	{
		g_buff[g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 3] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 4] = 0xF0 | (c & 0x7);
	}
}
