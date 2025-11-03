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

static int	create_infile(char **av)
{
	int	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Infile could not be opened");
		exit(1);
	}
	return (fd);
}

static int	create_outfile(char **av)
{
	int	fd2 = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd2 == -1)
	{
		perror("Outfile could not be opened");
		exit(1);
	}
	return (fd2);
}

static void	null_check(char **av)
{
	int	i = 0;
	while (av[i])
	{
		if (av[i][0] == '\0' || av[i][0] == ' ')
		{
			perror("Null argument");
			exit(127);
		}
		i++;
	}
}
static void close_all(int fd, int fd2, int pip[2])
{
    close(fd);
	close(fd2);
	close(pip[0]);
	close(pip[1]);
}
static void free_full(char *cmd, char **cmd_arg)
{
    ft_free_split(cmd_arg);
    free(cmd);
}
int	main(int ac, char *av[], char **envp)
{
	int		pip[2];
	pid_t	p_id;
	pid_t	p_id2;
	int		fd;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	**cmd1_args;
	char	**cmd2_args;

	if (ac != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		exit(1);
	}
	null_check(av);
	fd = create_infile(av);
	fd2 = create_outfile(av);
	cmd1_args = ft_split(av[2], ' ');
	cmd2_args = ft_split(av[3], ' ');
    cmd1 = final_path(cmd1_args, envp);
    cmd2 = final_path(cmd2_args, envp);
    if (!cmd1 || !cmd2)
    {
        perror("Command not found");
        free_full(cmd1, cmd1_args);
        free_full(cmd2, cmd2_args);
        close_all(fd, fd2, pip);
        exit(127);
    }

	if (pipe(pip) == -1)
	{
		perror("pipe");
		exit(1);
	}

	p_id = fork();
	if (p_id == 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		close_all(fd,fd2, pip);
		execve(cmd1, cmd1_args, envp);
		perror("Execve cmd1 failed");
		free_full(cmd1, cmd1_args);
		exit(1);
	}
    
	p_id2 = fork();
	if (p_id2 == 0)
	{
        dup2(pip[0], STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		close_all(fd,fd2, pip);
		execve(cmd2, cmd2_args, envp);
		perror("Execve cmd2 failed");
		free_full(cmd2, cmd2_args);
		exit(1);
	}
    
	close_all(fd,fd2, pip);
	waitpid(p_id, NULL, 0);
	waitpid(p_id2, NULL, 0);
    
    free_full(cmd1, cmd1_args);
    free_full(cmd2, cmd2_args);
	return (0);
}
