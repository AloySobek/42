/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:26:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/25 18:05:52 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_handler(va_list *list, size_t *flags, int *wid)
{
	SPEC == 'C' || *flags & L ? *flags |= UNI : 0;
	SIGN == 32 && *flags & POI ? *flags |= 48 : 0;
	if (SPEC == '%')
		print_any_char('%', flags, wid);
	else
		print_any_char(va_arg(*list, wchar_t), flags, wid);
}

void	string_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(*flags & BIA) ? (*flags >>= 8) && (*flags <<= 8) && (*flags |= 32) : 0;
	*flags & FLO && SIGN == 32 && !(*flags & BIA) ? *flags |= 48 : 0;
	if (SPEC == 'S' || *flags & L)
	{
		*flags |= UNI;
		print_uni_string(va_arg(*list, wchar_t *), flags, wid, pre);
	}
	else
		print_usual_string(va_arg(*list, char *), flags, wid, pre);
}

void	uni(wchar_t c)
{
	if (c <= 0x7FF && EJECT(3) && (g_count += 2))
	{
		g_buff[g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 2] = 0xC0 | (c & 0x1F);
	}
	else if (c <= 0xFFFF && EJECT(4) && (g_count += 3))
	{
		g_buff[g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff[g_count - 3] = 0xE0 | (c & 0xF);
	}
	else if (c <= 0x10FFFF && EJECT(5) && (g_count += 4))
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
