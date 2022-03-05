/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:50:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/05 23:03:51 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_access(char **div, t_cmd *args, t_join *jn)
{
	args->check = 1;
	args->j = 0;
	while (div[args->j])
	{
		jn->join2 = ft_strjoin("/", args->cmd2[0]);
		jn->post_join2 = ft_strjoin(div[args->j], jn->join2);
		if (access(jn->post_join2, F_OK) == 0)
		{
			args->flag = 1;
			args->com1 = jn->post_join1;
			free(jn->join1);
			args->com2 = jn->post_join2;
			free(jn->join2);
			break ;
		}
		free(jn->join2);
		free(jn->post_join2);
		args->j++;
	}
}

void	fork_end(t_cmd args, char **argv, char *env[])
{
	t_var	var;

	var.id = 0;
	if (args.flag == 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	fork_pipe(var, argv, args, env);
	waitpid(-1, NULL, 0);
}

void	init_check(t_cmd *args, char **argv)
{
	args->i = 0;
	args->j = 0;
	args->flag = 0;
	args->check = 0;
	int	i = 0;
	int	j = 0;
	int	flag = 0;
	while (argv[2][i])
	{
		if (isalnum(argv[2][i]))
		{
			flag = 1;
			break ;
		}
		i++;
		j++;
	}
	int flag1 = 0;
	while (argv[3][j])
	{
		if (isalnum(argv[3][j]))
		{
			flag1 = 1;
			break ;
		}
		j++;
	}
	if (flag == 0 || flag1 == 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (!argv[2][0])
		exit(EXIT_FAILURE);
	else
		args->cmd1 = ft_split(argv[2], ' ');
	if (!argv[3][0])
		exit(EXIT_FAILURE);
	else
		args->cmd2 = ft_split(argv[3], ' ');
}

void	pipex(char **div, char **argv, char *env[])
{
	t_cmd	args;
	t_join	jn;

	init_check(&args, argv);
	while (div[args.i])
	{
		jn.join1 = ft_strjoin("/", args.cmd1[0]);
		jn.post_join1 = ft_strjoin(div[args.i], jn.join1);
		if (access(jn.post_join1, F_OK) == 0)
			check_access(div, &args, &jn);
		if (args.flag == 1 || args.check == 1)
			break ;
		free(jn.join1);
		free(jn.post_join1);
		args.i++;
	}
	fork_end(args, argv, env);
}

int	main(int argc, char **argv, char *env[])
{
	int		i;
	char	*dest;
	char	**div;

	i = 0;
	if (argc == 5)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "PATH", 4) == 0)
			{
				dest = ft_strchr(env[i], '=');
				div = ft_split(dest, ':');
				pipex(div, argv, env);
				free_split(div);
				break ;
			}
			i++;
		}
	}
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}
