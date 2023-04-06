/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:46:01 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/06 17:46:01 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

void	error_func(char *msg);

void	childloop(int *fd, int ac, char **av, char **envp);

char	*findshellpath(char **envp);

int		execute_command(int input_fd, char **av, char **envp, int counter);

void	loopend(int fdin, int fdout, char *command, char **envp);

char	*findcommand(char *command, char **envp);

void	freesplit(char **splited);

void	execve_func(char *cmd, char **envp);

void	here_doc(char **av);

#endif
