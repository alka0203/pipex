/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 02:28:49 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/05 23:04:09 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <ctype.h>

typedef struct s_cmd
{
	char	**cmd1;
	char	**cmd2;
	char	*com1;
	char	*com2;
	int		flag;
	int		check;
	int		i;
	int		j;
}	t_cmd;

typedef struct s_join
{
	char	*join1;
	char	*join2;
	char	*post_join1;
	char	*post_join2;
}	t_join;

typedef struct s_var
{
	int	id;
	int	id2;
	int	fd[2];
	int	file;
	int	file2;
}	t_var;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(char const *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	pipex(char **div, char **argv, char *env[]);
void	fork_pipe(t_var var, char **argv, t_cmd args, char *env[]);
void	free_split(char **div);
#endif