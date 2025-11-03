/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:07:19 by esakgul           #+#    #+#             */
/*   Updated: 2025/11/04 01:48:10 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_first_cmd(int *fds, int *pip, char **av, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	cmd_args = ft_split(av[2], ' ');
	cmd = final_path(cmd_args, envp);
	if (!cmd)
	{
		perror("Command not found");
		free_full(cmd, cmd_args);
		exit(127);
	}
	dup2(fds[0], STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close_all(fds[0], fds[1], pip);
	execve(cmd, cmd_args, envp);
	perror("Execve cmd1 failed");
	free_full(cmd, cmd_args);
	exit(1);
}

static void	execute_second_cmd(int *fds, int *pip, char **av, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	cmd_args = ft_split(av[3], ' ');
	cmd = final_path(cmd_args, envp);
	if (!cmd)
	{
		perror("Command not found");
		free_full(cmd, cmd_args);
		exit(127);
	}
	dup2(pip[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close_all(fds[0], fds[1], pip);
	execve(cmd, cmd_args, envp);
	perror("Execve cmd2 failed");
	free_full(cmd, cmd_args);
	exit(1);
}

static void	create_pipe_and_fork(int *fds, int *pip, char **av, char **envp)
{
	pid_t	p_id;
	pid_t	p_id2;

	if (pipe(pip) == -1)
	{
		perror("pipe");
		exit(1);
	}
	p_id = fork();
	if (p_id == 0)
		execute_first_cmd(fds, pip, av, envp);
	p_id2 = fork();
	if (p_id2 == 0)
		execute_second_cmd(fds, pip, av, envp);
	close_all(fds[0], fds[1], pip);
	waitpid(p_id, NULL, 0);
	waitpid(p_id2, NULL, 0);
}

int	main(int ac, char *av[], char **envp)
{
	int	pip[2];
	int	fds[2];

	check_arguments(ac, av);
	fds[0] = create_infile(av);
	fds[1] = create_outfile(av);
	create_pipe_and_fork(fds, pip, av, envp);
	return (0);
}
