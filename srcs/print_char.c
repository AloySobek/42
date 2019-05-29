/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:25:24 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/29 21:21:28 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			unistrlen(const wchar_t *s)
{
	int		size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

void	print_any_char(wchar_t c, size_t *flags, int *wid)
{
	(*wid)--;
	if (!(*flags & BIA))
		while ((*wid)-- > 0 && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = SIGN;
	EJECT(1);
	*flags & UNI && c > 127 ? uni(c) :
	(g_buff__.g_buff[g_buff__.g_count++] = c);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = SIGN;
}

void		print_uni_string(wchar_t *s, size_t *flags, int *wid, int *pre)
{
	if (!s)
		s = L"(null)";
	*wid -= (((unistrlen(s) > *pre && *flags & POI) ? (*pre) : unistrlen(s)));
	if (!(*flags & BIA))
		while (((*wid)-- > 0) && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = SIGN;
	if (*flags & POI)
		while (*s && (*pre)-- > 0 && EJECT(1))
			(*flags & UNI && *s > 127) ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	else
		while (*s && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = SIGN;
}

void		print_usual_string(char *s, size_t *flags, int *wid, int *pre)
{
	if (!s)
		s = "(null)";
	*wid -= (((ft_strlen(s) > (size_t)*pre && *flags & POI) ? (*pre) : ft_strlen(s)));
	if (!(*flags & BIA))
		while (((*wid)-- > 0) && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = SIGN;
	if (*flags & POI)
		while (*s && (*pre)-- > 0 && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	else
		while (*s && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = SIGN;
}

void	uni(wchar_t c)
{
	if (c <= 0x7FF && EJECT(3) && (g_buff__.g_count += 2))
	{
		g_buff__.g_buff[g_buff__.g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 2] = 0xC0 | (c & 0x1F);
	}
	else if (c <= 0xFFFF && EJECT(4) && (g_buff__.g_count += 3))
	{
		g_buff__.g_buff[g_buff__.g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 3] = 0xE0 | (c & 0xF);
	}
	else if (c <= 0x10FFFF && EJECT(5) && (g_buff__.g_count += 4))
	{
		g_buff__.g_buff[g_buff__.g_count - 1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 3] = 0x80 | (c & 0x3F);
		c = (c >> 6);
		g_buff__.g_buff[g_buff__.g_count - 4] = 0xF0 | (c & 0x7);
	}
}
