#ifndef PIPE_H
# define PIPE_H

#include "libft/libft.h"

int	filechecker(char *file);

int	filecheckerWR(char *file);

int	openfileRD(char *file);

int	openfileWR(char *file);

void	childloop(int *fd, int ac, char **av, char **envp);

void	childloop2();

void	copyfile(int ac, char **av, char **envp);

char	*findshellpath(char **envp);

int		execute_command(int input_fd, char **av, char **envp);

void	loopend(int fdin, int fdout, char *command, char **envp);

char	*findcommand(char *command, char **envp);

void	freesplit(char **splited);

#endif
