/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:30:02 by alvega-g          #+#    #+#             */
/*   Updated: 2023/10/05 17:22:08 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *copy_up_to_newline(char *text)
{
	char *result;
	char *total;
	int len;

	total = ft_strchr(text, '\n');
	len = (total - text) + 1;
	result = ft_substr(text, 0, len);
	return (result);
}

char *create_buffer(char *text, int fd)
{
	char *buffer;
	int chars_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	buffer[0] = 0;
	while (!ft_strchr(buffer, '\n'))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read > 0)
		{
			buffer[chars_read] = 0;
			//printf("buffer: %s\ntext: %s\n", buffer, text);
			text = ft_strjoin(text, buffer);
		}
	}
	free (buffer);
	return (text);
}

char *get_next_line(int fd)
{
	static char *text;
	char *result;

	text = create_buffer(text, fd);
	result = copy_up_to_newline(text);
	
	return (result);
}

int	main(void)
{
	int fd;
	char *file;
	char *file2;

	file = "test.txt";
	fd = open(file, O_RDONLY);
	printf("%s", get_next_line(fd));
	
	close(fd);
}
