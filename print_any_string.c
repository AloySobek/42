/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:25:24 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 23:03:22 by marvin           ###   ########.fr       */
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

int			print_any_string(wchar_t *s, size_t *flags, int *wid, int *pre)
{
	char	*h;
	int		size;

	if (!s)
		s = L"(null)";
	size = 0;
	(*flags * UNI) ? h = (char *)s : 0;
	*wid -= (((unistrlen(s) > *pre && *flags & POI) ? (*pre) : unistrlen(s)));
	if (!(*flags & BIA))
		while (((*wid)-- > 0) && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count] = (*flags << 56) >> 56;
	if (*flags & POI)
		while ((*flags & UNI ? *s : *h) && (*pre)-- > 0 && ((g_count + 1) ==
			BUFF_SIZE ? eject() : 1))
			*flags & UNI && (*flags & UNI ? *s : *h) > 127 ? uni((*flags & UNI ?
			*s++ : *h++)) : (g_buff[g_count++] = (*flags & UNI ? *s++ : *h++));
	else
		while ((*flags & UNI ? *s : *h) && ((g_count + 1) == BUFF_SIZE ? eject()
				: 1))
			*flags & UNI && (*flags & UNI ? *s : *h) > 127 ? uni((*flags & UNI ?
			*s++ : *h++)) : (g_buff[g_count++] = (*flags & UNI ? *s++ : *h++));
	while ((*wid)-- > 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = (*flags << 56) >> 56;
	return (size);
}
