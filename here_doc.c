/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:13:29 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/06 21:10:15 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	here_doc(char **av)
{
	int		*fd;
	pid_t	pid;
	char	*str;

	if (pipe(fd) == -1)
		error_func("pipe");
	pid = fork();
	if (pid == -1)
		error_func("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		while(1)
		{
			ft_printf("%s", get_next_line(STDIN_FILENO));
			if (ft_strncmp(str, av[2], ft_strlen(av[2]) == 0))
				break ;
		}
	}
	else if (pid > 0)
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return fd[0];
	}
}