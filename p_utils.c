/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:26:11 by esakgul           #+#    #+#             */
/*   Updated: 2025/11/04 01:32:38 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*path2;

	tmp = ft_strjoin(path, "/");
	path2 = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path2);
}

char	*final_path(char **av, char **envp)
{
	int		i;
	char	*path;
	char	**path_sep;
	char	*path_f;

	path = find_path(envp);
	if (!path)
		return (NULL);
	path_sep = ft_split(path, ':');
	i = 0;
	while (path_sep[i])
	{
		path_f = join_path(path_sep[i], av[0]);
		if (access(path_f, F_OK | X_OK) == 0)
		{
			ft_free_split(path_sep);
			return (path_f);
		}
		free(path_f);
		i++;
	}
	ft_free_split(path_sep);
	return (NULL);
}
