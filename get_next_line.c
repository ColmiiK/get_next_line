/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:30:02 by alvega-g          #+#    #+#             */
/*   Updated: 2023/10/11 17:44:25 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*prepare_for_next(char *text)
{
	int		i;
	int		j;
	char	*new_text;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (0);
	}
	new_text = (char *)malloc((ft_strlen(text) - i + 1) * sizeof(char));
	if (!new_text)
		return (0);
	i++;
	while (text[i])
		new_text[j++] = text[i++];
	free(text);
	return (new_text);
}

static char	*copy_up_to_newline(char *text)
{
	char	*result;
	char	*total;
	int		len;

	total = ft_strchr(text, '\n');
	len = (total - text) + 1;
	result = ft_substr(text, 0, len);
	return (result);
}

static char	*create_buffer(char *text, int fd)
{
	char	*buffer;
	int		chars_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	buffer[0] = 0;
	while (!ft_strchr(buffer, '\n') && chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read > 0)
		{
			buffer[chars_read] = 0;
			text = ft_strjoin(text, buffer);
		}
	}
	free(buffer);
	return (text);
}

// void	check_leaks(void)
// {
// 	system("leaks -q a.out");
// }

char	*get_next_line(int fd)
{
	static char	*text;
	char		*result;

	if (fd < 0)
		return (0);
	// atexit(check_leaks);
	text = create_buffer(text, fd);
	if (!text)
		return (0);
	result = copy_up_to_newline(text);
	text = prepare_for_next(text);
	return (result);
}
