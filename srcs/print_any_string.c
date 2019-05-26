/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:25:24 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/26 13:19:54 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			unistrlen(const wchar_t *s)
{
	int		size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

void		print_uni_string(wchar_t *s, size_t *flags, int *wid, int *pre)
{
	if (!s)
		s = L"(null)";
	*wid -= (((unistrlen(s) > *pre && *flags & POI) ? (*pre) : unistrlen(s)));
	if (!(*flags & BIA))
		while (((*wid)-- > 0) && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
	if (*flags & POI)
		while (*s && (*pre)-- > 0 && EJECT(1))
			(*flags & UNI && *s > 127) ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	else
		while (*s && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}

void		print_usual_string(char *s, size_t *flags, int *wid, int *pre)
{
	if (!s)
		s = "(null)";
	*wid -= (((ft_strlen(s) > *pre && *flags & POI) ? (*pre) : ft_strlen(s)));
	if (!(*flags & BIA))
		while (((*wid)-- > 0) && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
	if (*flags & POI)
		while (*s && (*pre)-- > 0 && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	else
		while (*s && EJECT(1))
			*flags & UNI && *s > 127 ? uni(*s++) :
			(g_buff__.g_buff[g_buff__.g_count++] = *s++);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}
