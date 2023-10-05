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

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (c > 255)
		c -= 256;
	while (s[i])
	{
		if (c == s[i])
			return ((char *)&s[i]);
		else
			i++;
	}
	if (c == '\0')
		return ((char *)&s[i++]);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (0);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = 0;
	return (joined);
}

char	*join(char *text, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(text, buffer);
	free (buffer);
	return (text);
}

char	*get_lines(char *text, int fd)
{
	char	*buffer;
	int		i;
	int		read_chars;

	i = 0;
	if (!text)
		text = malloc(1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_chars = 1;
	while (read_chars > 0)
	{
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free (buffer);
			return (0);
		}
		buffer[read_chars] = 0;
		text = join(text, buffer);
		if (ft_strchr(text, '\n'))
			break ;
	}
	free (buffer);
	return (text);
}

char	*copy_text(char *text)
{
	char	*str;
	int		i;

	if (!text[i])
		return (0);
	while (text[i] && text[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		str[i] = text[i];
		i++;
	}
	if (text[i] && text[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	return (str);
}

char	*next(char *text)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free (text);
		return (0);
	}
	temp = malloc(sizeof(char) * (ft_strlen(text) - i + 1));
	i++;
	j = 0;
	while (text[i])
	{
		temp[j] = text[i];
		j++;
		i++;
	}
	free (text);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*result;

	text = get_lines(text, fd);
	if (!text)
		return (0);
	result = copy_text(text);
	text = next(text);
	return (result);
}

int	main(void)
{
	int fd;
	char *file;

	system("leaks -q a.out");
	file = "test.txt";
	fd = open(file, O_RDONLY);
	printf("%s\n", get_next_line(fd));
}
