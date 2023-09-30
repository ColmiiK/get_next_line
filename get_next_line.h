/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:06:51 by alvega-g          #+#    #+#             */
/*   Updated: 2023/09/30 13:46:15 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				create_list(t_list **list, int fd);
int					search_newline(t_list *list);
void				add_to_list(t_list **list, char *buffer);
char				*get_line(t_list *list);

t_list				*ft_lstlast(t_list *lst);
int					len_to_newline(t_list *list);
void				copy_to_buffer(t_list *list, char *str);

#endif