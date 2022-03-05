/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 02:54:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/01 15:10:04 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static	char	**boop(char const *s, char c, char	**mall, size_t k)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c && (int)j < ft_strlen(s))
		{
			j++;
			i++;
		}
		while (s[j] != c && (int)j < ft_strlen(s))
			j++;
		if (s[j] == c && (int)j < ft_strlen(s))
		{
			mall[k] = ft_substr(s, i, j - i);
			i = j;
			k++;
		}
	}
	if (s[i] && s[j - 1] != c)
		mall[k] = ft_substr(s, i, j - i);
	mall[++k] = 0;
	return (mall);
}

char	**ft_split(char const *s, char c)
{
	size_t	k;
	char	**mall;

	k = 0;
	if (!s)
		return (NULL);
	mall = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!mall)
		return (0);
	mall = boop(s, c, mall, k);
	return (mall);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (0);
	concat = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!concat)
		return (0);
	while (s1[i])
	{
		((char *)concat)[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j])
	{
		((char *)concat)[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	concat[i] = '\0';
	return (concat);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (str[i] == 0)
		return (0);
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (&((char *)str)[i + 1]);
		i++;
	}
	if (c == '\0')
		return (&((char *)str)[i]);
	return (0);
}
