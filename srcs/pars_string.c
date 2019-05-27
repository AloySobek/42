/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:11:36 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 17:42:04 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		bi(size_t *flags, int howmuch, int left)
{
	if (left)
	{
		*flags <<= howmuch;
		*flags >>= howmuch;
	}
	else
	{
		*flags >>= howmuch;
		*flags <<= howmuch;
	}
	return (1);
}

int		width_collector(const char **str, va_list *list, size_t *flags,
		int *wid)
{
	int check;

	if (**str == '*')
	{
		*wid = va_arg(*list, int);
		if (*wid < 0)
		{
			*wid *= -1;
			!(*flags & BIA) ? (*flags |= BIA) : 0;
		}
		(*str)++;
	}
	else
	{
		if ((check = ft_atoi(*str)) > 0)
			*wid = check;
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

int		precision_collector(const char **str, va_list *list, size_t *flags,
		int *pre)
{
	*flags |= POI;
	(*str)++;
	if (**str == '*')
	{
		*pre = va_arg(*list, int);
		*pre < 0 ? *flags ^= POI : 0;
		(*str)++;
	}
	else
	{
		*pre = ft_atoi(*str);
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

void	file_descriptor(const char **str, va_list *list)
{
	*str += 3;
	if (**str == '*')
		g_buff__.g_fd = va_arg(*list, int);
	else
		g_buff__.g_fd = ft_atoi(*str);
	while (**str && **str != '}')
		(*str)++;
}

void	color_chooser(const char **str)
{
	char	*str2;
	int		count;

	*str += 2;
	str2 = (char *)malloc(20);
	count = 0;
	while (**str && **str != '}' && count >= 0)
		str2[count++] = *(*str)++;
	str2[count] = '\0';
	if (ft_strcmp(str2, "red") == 0)
		g_buff__.g_bytes += write(1, "\033[0;31m", 7);
	else if (ft_strcmp(str2, "bold red") == 0)
		g_buff__.g_bytes += write(1, "\033[1;31m", 7);
	else if (ft_strcmp(str2, "green") == 0)
		g_buff__.g_bytes += write(1, "\033[0;32m", 7);
	else if (ft_strcmp(str2, "bold green") == 0)
		g_buff__.g_bytes += write(1, "\033[1;32m", 7);
	else if (ft_strcmp(str2, "yellow") == 0)
		g_buff__.g_bytes += write(1, "\033[0;33m", 7);
	else if (ft_strcmp(str2, "bold yellow") == 0)
		g_buff__.g_bytes += write(1, "\033[1;33m", 7);
	else if (ft_strcmp(str2, "blue") == 0)
		g_buff__.g_bytes += write(1, "\033[0;34m", 7);
	else if (ft_strcmp(str2, "bold blue") == 0)
		g_buff__.g_bytes += write(1, "\033[1;34m", 7);
	else if (ft_strcmp(str2, "magenta") == 0)
		g_buff__.g_bytes += write(1, "\033[0;35m", 7);
	else if (ft_strcmp(str2, "bold magenta") == 0)
		g_buff__.g_bytes += write(1, "\033[1;35m", 7);
	else if (ft_strcmp(str2, "cyan") == 0)
		g_buff__.g_bytes += write(1, "\033[0;36m", 7);
	else if (ft_strcmp(str2, "bold cyan") == 0)
		g_buff__.g_bytes += write(1, "\033[1;36m", 7);
	else if (ft_strcmp(str2, "reset") == 0)
		g_buff__.g_bytes += write(1, "\033[0m", 4);
}
