/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:06:57 by alvega-g          #+#    #+#             */
/*   Updated: 2023/09/30 14:05:03 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*create_line(t_list *list)
{
	int		len;
	char	*next_str;

	len = len_to_newline(list);
	next_str = malloc(len + 1);
	if (!len)
		return (0);
	copy_to_buffer(list, next_str);
	return (next_str);
}

void	add_to_list(t_list **list, char *buffer)
{
	t_list	*new;
	t_list	*last;

	last = ft_lstlast(*list);
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*list = new;
	else
		last->next = new;
	new->content = buffer;
	new->next = 0;
}

int	search_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (i);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	char	*buffer;
	int		read_characters;

	while (!search_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		read_characters = read(fd, buffer, BUFFER_SIZE);
		if (!read_characters)
		{
			free(buffer);
			return ;
		}
		buffer[read_characters] = 0;
		add_to_list(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*buffer;

	list = 0;
	if (!fd || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (0);
	create_list(&list, fd);
	if (!list)
		return (0);
	buffer = create_line(list);
	return (buffer);
}
int main()
{
	int fd;
	char *file;

	system("leaks -q a.out");
	file = "test.txt";
	fd = open(file, O_RDONLY);
	printf("%s\n", get_next_line(fd));
}