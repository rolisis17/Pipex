/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:02:20 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/06 20:06:05 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*findshellpath(char **envp)
{
	int		f;
	char	*path;

	f = 0;
	while (envp[f])
	{
		if (!(ft_strncmp(envp[f], "PATH", 4)))
			path = envp[f];
		f++;
	}
	return (path + 5);
}

void	error_func(char *msg)
{
	perror(msg);
	exit(-1);
}

void	freesplit(char **splited)
{
	int	counter;

	counter = 0;
	while (splited[counter])
	{
		free(splited[counter]);
		counter++;
	}
	free (splited);
}

void	execve_func(char *cmd, char **envp)
{
	char			**command;

	command = ft_split(cmd, ' ');
	execve(findcommand(command[0], envp), command, envp);
	error_func("execve");
}
