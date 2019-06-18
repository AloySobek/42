/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <cnikia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:53:27 by cnikia            #+#    #+#             */
/*   Updated: 2019/04/29 18:34:49 by cnikia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"

# ifndef BUFF_SIZE
#  define BUFF_SIZE 5
# endif

void				free_tet(char ***tet);

typedef struct		s_lst
{
	int				**loc;
	int				index;
	struct s_lst	*next;
}					t_lst;

void				fillit_exit(int a, char ***tet, t_lst **list);
t_lst				*coords(int fd);
char				**tetrimino_read(int fd, t_lst **list);
char				**ft_fillit(t_lst *tet_list, int x);
void				fillit_list_exit(int a, t_lst **list);
void				new_cords_dlc(char ***str, int ***tet);

#endif
