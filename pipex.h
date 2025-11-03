/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:32:55 by esakgul           #+#    #+#             */
/*   Updated: 2025/11/04 01:33:53 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"

char	*find_path(char **envp);
char	*final_path(char **av, char **envp);
void	ft_free_split(char **arr);
int		create_infile(char **av);
int		create_outfile(char **av);
void	null_check(char **av);
void	close_all(int fd, int fd2, int pip[2]);
void	free_full(char *cmd, char **cmd_arg);
void	check_arguments(int ac, char *av[]);

#endif
