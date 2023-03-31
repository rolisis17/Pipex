#ifndef PIPE_H
# define PIPE_H

#include "libft/libft.h"

int	filechecker(char *file);

int	filecheckerWR(char *file);

int	openfileRD(char *file);

int	openfileWR(char *file);

void	childloop(int *fd, int ac, char **av);

void	childloop2();

void	copyfile(int ac, char **av, char **envp);

char	*findshellpath(char *envp);

#endif
