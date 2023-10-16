/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:30:24 by alvega-g          #+#    #+#             */
/*   Updated: 2023/10/16 11:54:57 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t n, size_t size)
{
	void			*memory;
	unsigned int	i;
	unsigned int	total;
	char			*temp;

	memory = (void *)malloc(n * size);
	if (!memory)
		return (0);
	i = 0;
	total = n * size;
	temp = memory;
	while (i != total)
	{
		temp[i] = 0;
		i++;
	}
	return (memory);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*subs;

	i = 0;
	j = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	subs = (char *)malloc(sizeof(char) * len + 1);
	if (!subs)
		return (0);
	while (s[i] && i < start)
		i++;
	while (s[i] && j < len)
	{
		subs[j] = s[i];
		i++;
		j++;
	}
	subs[j] = 0;
	return (subs);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joined;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) + 1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (0);
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = 0;
	free (s1);
	return (joined);
}

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
