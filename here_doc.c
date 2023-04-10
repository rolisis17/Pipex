/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:13:29 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/10 21:28:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	here_doc(int fdout, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		counter;

	counter = 2;
	if (pipe(fd) == -1)
		error_func("pipe");
	pid = fork();
	if (pid == -1)
		error_func("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		here_child(av[2]);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		while (av[++counter + 2] != NULL)
			fd[0] = execute_command(fd[0], av, envp, counter);
		loopend(fd[0], fdout, av[counter], envp);
	}
	exit (0);
}

void	here_child(char *av2)
{
	char	*str;
	char	*limiter;
	char	*fileadd;

	fileadd = NULL;
	limiter = ft_strjoin(av2, "\n", 0);
	while(1)
	{
		ft_putstr_fd("Pipex here_doc ", 2);
		str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		fileadd = ft_strjoin(fileadd, str, -2);
		if (str)
			free (str);
	}
	ft_printf("%s", fileadd);
	exit (0);
}