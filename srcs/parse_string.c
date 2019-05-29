/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:11:36 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/29 21:17:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		shift(size_t *flags, int howmuch, char direction)
{
	if (direction == 'l')
	{
		*flags <<= howmuch;
		*flags >>= howmuch;
	}
	else if (direction == 'r')
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
	else if (**str >= '0' && **str <= '9')
		g_buff__.g_fd = ft_atoi(*str);
	else if (**str == 'f')
	{
		;/*
		open file name feature
		i can't use the "open" function
		so here no this feature;
		*/	
	}
	while (**str && *(*str - 1) != '}')
		(*str)++;
}

void	color_chooser(const char **str)
{
	char	*color;
	int		size;

	size = 32;
	if (!((char *)malloc(sizeof(char) * size)) && (g_buff__.g_error = -1))
		return ;
	while (**str && **str != '}' && size-- > 0)
		*color++ = *(*str)++;
	if (size == 0 && (g_buff__.g_error = -1))	
		return ;
	*color = 0;
	if (ft_strcmp(color, "red") == 0)
		g_buff__.g_bytes += write(1, "\033[0;31m", 7);
	else if (ft_strcmp(color, "bold red") == 0)
		g_buff__.g_bytes += write(1, "\033[1;31m", 7);
	else if (ft_strcmp(color, "green") == 0)
		g_buff__.g_bytes += write(1, "\033[0;32m", 7);
	else if (ft_strcmp(color, "bold green") == 0)
		g_buff__.g_bytes += write(1, "\033[1;32m", 7);
	else if (ft_strcmp(color, "yellow") == 0)
		g_buff__.g_bytes += write(1, "\033[0;33m", 7);
	else if (ft_strcmp(color, "bold yellow") == 0)
		g_buff__.g_bytes += write(1, "\033[1;33m", 7);
	else if (ft_strcmp(color, "blue") == 0)
		g_buff__.g_bytes += write(1, "\033[0;34m", 7);
	else if (ft_strcmp(color, "bold blue") == 0)
		g_buff__.g_bytes += write(1, "\033[1;34m", 7);
	else if (ft_strcmp(color, "magenta") == 0)
		g_buff__.g_bytes += write(1, "\033[0;35m", 7);
	else if (ft_strcmp(color, "bold magenta") == 0)
		g_buff__.g_bytes += write(1, "\033[1;35m", 7);
	else if (ft_strcmp(color, "cyan") == 0)
		g_buff__.g_bytes += write(1, "\033[0;36m", 7);
	else if (ft_strcmp(color, "bold cyan") == 0)
		g_buff__.g_bytes += write(1, "\033[1;36m", 7);
	else if (ft_strcmp(color, "eoc") == 0)
		g_buff__.g_bytes += write(1, "\033[0m", 4);
}
