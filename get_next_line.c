/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:30:02 by alvega-g          #+#    #+#             */
/*   Updated: 2023/10/17 17:18:42 by alvega-g         ###   ########.fr       */
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
	new_text = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
		return (free(text), NULL);
	new_text = ft_calloc((ft_strlen(text) - i + 1), sizeof(char));
	if (!new_text)
		return (0);
	i++;
	while (text[i])
		new_text[j++] = text[i++];
	free(text);
	text = 0;
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

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	chars_read = 1;
	while (!ft_strchr(buffer, '\n') && chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(text);
			free(buffer);
			return (0);
		}
		if (chars_read > 0)
		{
			buffer[chars_read] = 0;
			text = ft_strjoin(text, buffer);
		}
	}
	free(buffer);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (free(text), NULL);
	text = create_buffer(text, fd);
	if (!text)
		return (free(text), NULL);
	result = copy_up_to_newline(text);
	text = prepare_for_next(text);
	if (*result == 0)
	{
		free(result);
		return (0);
	}
	return (result);
}
