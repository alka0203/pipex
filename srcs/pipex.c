/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:54:36 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/02 14:13:12 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_error(t_var var)
{
	if (var.file2 < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(var.file2, STDIN_FILENO) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(var.fd[1], STDOUT_FILENO) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	id_child(t_var var, char **argv, t_cmd args, char *env[])
{
	char	*av[3];

	close(var.fd[0]);
	var.file2 = open(argv[1], O_RDWR);
	check_error(var);
	close(var.fd[1]);
	close(var.file2);
	if (args.cmd1[1])
	{
		av[0] = args.cmd1[0];
		av[1] = args.cmd1[1];
		av[2] = NULL;
		execve(args.com1, av, env);
	}
	else
	{
		av[0] = args.cmd1[0];
		av[1] = NULL;
		av[2] = NULL;
		execve(args.com1, av, env);
	}
}

void	check_error_2(t_var var)
{
	if (var.file < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(var.fd[0], STDIN_FILENO) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (dup2(var.file, STDOUT_FILENO) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	id2_child(t_var var, char **argv, t_cmd args, char *env[])
{
	char	*av[3];

	close(var.fd[1]);
	var.file = open(argv[4], O_TRUNC | O_RDWR | O_CREAT, 0666);
	check_error_2(var);
	close(var.fd[0]);
	close(var.file);
	if (args.cmd2[1])
	{
		av[0] = args.cmd2[0];
		av[1] = args.cmd2[1];
		av[2] = NULL;
		execve(args.com2, av, env);
	}
	else
	{
		av[0] = args.cmd2[0];
		av[1] = NULL;
		av[2] = NULL;
		execve(args.com2, av, env);
	}
}

void	fork_pipe(t_var var, char **argv, t_cmd args, char *env[])
{
	if (pipe(var.fd) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	var.id = fork();
	if (var.id < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (var.id == 0)
		id_child(var, argv, args, env);
	free(args.com1);
	free_split(args.cmd1);
	var.id2 = fork();
	if (var.id2 < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (var.id2 == 0)
		id2_child(var, argv, args, env);
	free(args.com2);
	free_split(args.cmd2);
}
