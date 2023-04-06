/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:18:58 by dcella-d          #+#    #+#             */
/*   Updated: 2023/03/26 10:18:58 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	main(int ac, char **av, char **envp)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 0;
	if (ac > 4 && envp)
	{
		fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			fd[0] = here_doc(av);
		else
			fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0 || fd[1] < 0)
			error_func("file");
		// av[ac - 1] = NULL;
		childloop(fd, ac, av, envp);
	}
	else
		ft_putendl_fd("try using:	infidel	cmd1	cmd2	outfile", 2);
}

void	childloop(int *fd, int ac, char **av, char **envp)
{
	int				pipefd[2];
	static pid_t	pid;
	static int		counter;

	if (pipe(pipefd) == -1)
		error_func("pipe");
	pid = fork();
	if (pid == -1)
		error_func("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		execve_func(av[2], envp);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		while (++counter + 2 < ac - 2)
			pipefd[0] = execute_command(pipefd[0], av, envp, counter + 2);
		loopend(pipefd[0], fd[1], av[ac - 2], envp);
	}
}

void	loopend(int fdin, int fdout, char *command, char **envp)
{
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	execve_func(command, envp);
}

char	*findcommand(char *command, char **envp)
{
	char	**splited;
	char	*joined;
	int		f;

	f = 0;
	splited = ft_split(findshellpath(envp), ':');
	command = ft_strjoin("/", command, 0);
	while (splited[f])
	{
		joined = ft_strjoin(splited[f], command, 0);
		if (access(joined, F_OK) == 0)
			break ;
		f++;
		free (joined);
	}
	freesplit(splited);
	free(command);
	return (joined);
}

int	execute_command(int input_fd, char **av, char **envp, int counter)
{
	int		output_fd[2];
	pid_t	pid;

	if (pipe(output_fd) == -1)
		error_func("pipe");
	pid = fork();
	if (pid == -1)
		error_func("fork");
	if (pid == 0)
	{
		close(output_fd[0]);
		dup2(output_fd[1], STDOUT_FILENO);
		dup2(input_fd, STDIN_FILENO);
		execve_func(av[counter], envp);
	}
	else
	{
		close(input_fd);
		close(output_fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (output_fd[0]);
}
