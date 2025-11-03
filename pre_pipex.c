/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by esakgul           #+#    #+#             */
/*   Updated: 2025/11/04 02:43:20 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_infile(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Infile could not be opened");
		exit(1);
	}
	return (fd);
}

int	create_outfile(char **av)
{
	int	fd2;

	fd2 = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd2 == -1)
	{
		perror("Outfile could not be opened");
		exit(1);
	}
	return (fd2);
}

void	close_all(int fd, int fd2, int pip[2])
{
	close(fd);
	close(fd2);
	close(pip[0]);
	close(pip[1]);
}

void	free_full(char *cmd, char **cmd_arg)
{
	ft_free_split(cmd_arg);
	free(cmd);
}

void	check_arguments(int ac, char *av[])
{
	if (ac != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		exit(1);
	}
	null_check(av);
}
