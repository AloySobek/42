/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:13:25 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/29 18:22:49 by cnikia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fillit.h"

static int		search(char **obj, int x, int y)
{
	if (x < 0 || x >= 4 || y < 0 || y >= 4 || obj[x][y] != '#')
		return (0);
	obj[x][y] = '*';
	return (search(obj, x + 1, y) + search(obj, x - 1, y) +
		search(obj, x, y + 1) + search(obj, x, y - 1) + 1);
}

static int		validator(char **line, int x, int y)
{
	int result;

	result = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (line[x][y] == '#')
			{
				result = search(line, x, y);
				if (result == 4)
					return (1);
				else
					return (0);
			}
			y++;
		}
		x++;
	}
	return (0);
}

static void		some_tet_tests(char **tet, t_lst **list)
{
	size_t		a;
	size_t		b;
	size_t		count;

	b = 0;
	a = 0;
	count = 0;
	while (a < 4)
	{
		b = 0;
		while (b < 4)
		{
			if (tet[a][b] != '.' && tet[a][b] != '#')
			{
				fillit_exit(4, &tet, list);
			}
			if (tet[a][b] == '#')
				count++;
			b++;
		}
		a++;
	}
	if (count != 4)
		fillit_exit(4, &tet, list);
}

static char		**read_one(int fd, char **tet, int *end, t_lst **list)
{
	int			a;
	int			ret;
	char		buf[BUFF_SIZE];

	if (*end == 1)
		return (NULL);
	a = 0;
	while (a < 4)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if ((buf[4] != '\n') || ret == 0)
			fillit_exit(2, &tet, list);
		buf[4] = '\0';
		if (!(tet[a] = ft_strdup(buf)))
			fillit_exit(2, &tet, list);
		a++;
	}
	if ((ret = read(fd, buf, 1)) == 0)
	{
		*end = 1;
		return (tet);
	}
	if (buf[0] != '\n')
		fillit_exit(2, &tet, list);
	return (tet);
}

char			**tetrimino_read(int fd, t_lst **list)
{
	static int	end = 0;
	char		**tet;
	char		**wst;

	if (!(tet = (char **)malloc(sizeof(char **) * 4)))
		fillit_exit(3, &tet, list);
	tet[0] = NULL;
	tet[1] = NULL;
	tet[2] = NULL;
	tet[3] = NULL;
	wst = tet;
	tet = read_one(fd, tet, &end, list);
	if (tet)
	{
		some_tet_tests(tet, list);
		if (validator(tet, 0, 0) == 0)
			fillit_exit(4, &tet, list);
	}
	if (!tet)
		free_tet(&wst);
	return (tet);
}
