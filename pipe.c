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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipe.h"
#include "libft/libft.h"

static void	move(char **av)
{
		av += 3;
		printf("%s", *av);
}

int	main(int ac, char **av, char **envp)
{
	int	counter;
	int	fd[3];

	counter = 1;
	fd[0] = 0;
	fd[1] = 0;
	fd[2] = 0;
	if (ac > 4 && envp)
	{
		fd[0] = openfileRD(av[1]);
		fd[1] = openfileWR(av[ac - 1]);
		av[ac - 1] = NULL;
		move(av);
		// copyfile();
		// childloop2();
		// while (++counter < ac)
		// {

		// }
		//av[1] && av[ac] são paths para os arquivos de entrada e saída;
	}
}

void	childloop(int *fd, int ac, char **av)
{
	int			pipefd[2];
	pid_t		pid;
	static int	counter;

	pid = 0;
	pipe(pipefd);
	if (counter++ < (ac - 2))
		pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execve("/bin/sh", &av[counter + 2], NULL);
	}
	else if (pid > 0 && fd)
	{
		close(pipefd[1]);
		wait(NULL);
	}
}

char	*findshellpath(char *envp)
{
	int	f;
	char *path;

	f = 0;
	while (envp[f])
	{
		if (ft_strncmp(&envp[f], "SHELL=", 6))
			path = &envp[f];
		else
			f++;
	}
	path = path + 6;
	return (path);
}

void	execute_command(int input_fd, char **av, char **envp)
{
    int output_fd[2]; // file descriptor for pipe
    char **argv;
    pid_t pid;
    
	if (pipe(output_fd) == -1) { // create pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork(); // fork child process
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // child process
        close(output_fd[0]); // close read end of pipe

        // set up stdout to write to pipe
        dup2(output_fd[1], STDOUT_FILENO);

        // set up stdin to read from input_fd
        dup2(input_fd, STDIN_FILENO);

        // execute command
		argv = ft_split(av + counter, " ");
        execve(findshellpath(envp), argv, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else { // parent process
        close(input_fd); // close input file descriptor
        close(output_fd[1]); // close write end of pipe
        waitpid(pid, NULL, 0); // wait for child process to finish
		if (av + counter != NULL)
        	execute_command(output_fd[0], av, envp); // return read end of pipe as output file descriptor
    }
}

void	childloop2()
{
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process with PID %d\n", getpid());
    } else if (pid > 0) {
        // Parent process
        printf("Parent process with PID %d, child PID %d\n", getpid(), pid);
    } else {
        // Error
        printf("Error: failed to fork.\n");
    }
}

int	openfileRD(char *file)
{
	int	fd;

	fd = 0;
	if (filechecker(file) > 1)
		fd = open(file, O_RDONLY);
	else
	{
		ft_printf("File do not exist.\n");
		exit (-1);
	}
	if (fd > 0)
		return (fd);
	else
		exit (-1);
}

int	openfileWR(char *file)
{
	int	fd;

	if (filechecker(file) > 0)
	{
		if (filecheckerWR(file) == 1)
			fd = open(file, O_WRONLY);
		else
		{
			ft_printf("Permission Denied.\n");
			exit (-1);
		}
	}
	else
		fd = open(file, O_CREAT, 0644);
	if (fd > 0)
		return (fd);
	exit (-1);
}

void	closefile(int fd)
{
	close(fd);
}

int	filecheckerWR(char *file)
{
	int	f;

	f = 0;
	if (access(file, W_OK) == 0)
		f++;
	return (f);
}

int	filechecker(char *file)
{
	int	f;

	f = 0;
	if (access(file, F_OK) == 0)
		f++;
	else
		return (-1);
	if (access(file, R_OK) == 0)
		f++;
	if (access(file, W_OK) == 0)
		f++;
	return (f);
}

// void	copyfile(int ac, char **av, char **envp)
// {
//     int fd[2];
// 	int	fd2[2];
// 	static int counter;
//     pipe(fd); // create a pipe to redirect the output

//     pid_t pid = fork();
// 	counter += 2;
//     if (pid == 0) {
//         // Child process
//         dup2(fd[1], STDOUT_FILENO); // redirect the output to the write end of the pipe
//         close(fd[0]); // close the read end of the pipe

//         char *argv[] = {av[counter], NULL}; // command to execute
//         char *envp[] = {NULL}; // environment variables
//         int fd_in = open("README.md", O_RDONLY); // open the input file
// 		pipe(fd2);
//         // int fd_out = open(".readme", O_WRONLY | O_CREAT, 0644); // open the output file
//         dup2(fd_in, STDIN_FILENO); // redirect the input from the file
//         dup2(fd2[0], STDOUT_FILENO); // redirect the output to the file
//         close(fd_in); // close the input file descriptor
//         close(fd2[0]); // close the output file descriptor

//         execve("/bin/cat", argv, envp); // execute the command
//     } else if (pid > 0) {
//         // Parent process
//         close(fd[1]); // close the write end of the pipe
//         wait(NULL); // wait for the child process to complete

//         char buffer[1024];
//         ssize_t nread = read(fd[0], buffer, sizeof(buffer)); // read the output from the pipe
//         write(STDOUT_FILENO, buffer, nread); // write the output to the standard output
// 		counter++;
// 		if (counter < (ac - 1))
// 			copyfile(ac, av, envp);
//         //int fd_out = open(".readme", O_WRONLY | O_CREAT, 0644); // open the output file
//     } else {
//         // Error
//         printf("Error: failed to fork.\n");
//     }
//     return ;
// }

/*	numero de argumentos não definido (quantidade de pipes);
	primeiro e ultimo argumento precisam ser files/paths;
	se path não for definido, usar PWD para chamar o path local;
	se o file de saida (ultimo) não existir, criar um para colocar o output;
	todos os argumentos entre o primeiro e o ultimo precisam ser comandos validos no shell;
	guardar em um array de strings todos os comandos para usar em EXECVE();
	DUP() vai fazer uma cópia do FD(arquivo) que pode ser aberto em um novo processo para direcionar para outro pipe;
	FORK() vai ser usado para criar um segundo processo (child process);
	PIPE() vai ser usado para mandar data de um processo para o próximo;
	WAIT() e WAITPID() vão ser usados para esperar um ou algum child process específico terminar;
	ACCESS() vai checar se temos acesso ao arquivo passado como argumento;
	UNLINK() vai deletar arquivo criado/modificado.
	

perror() - This function is used to print an error message to the standard error output (stderr). It takes a string argument which is usually the name of the program, followed by a colon and a space, and then the error message itself. This function is often used in conjunction with system calls that can return an error code, such as open() or read().

strerror() - This function is used to convert an error code into a human-readable error message. It takes an integer error code as an argument and returns a pointer to a string containing the corresponding error message.

access() - This function is used to check whether the calling process has access to a particular file or directory. It takes two arguments: the first is a pointer to a string containing the path to the file or directory, and the second is an integer representing the type of access to check for (e.g. read, write, execute). It returns 0 if access is allowed, or -1 if an error occurs.

dup() - This function is used to create a copy of a file descriptor. It takes an integer file descriptor as an argument and returns a new file descriptor that refers to the same file or resource. This is often used in conjunction with fork() to create multiple processes that can read from or write to the same file or pipe.

dup2() - This function is similar to dup(), but allows the programmer to specify a specific file descriptor to use for the new descriptor. This is often used to redirect input or output to a specific file or pipe.

execve() - This function is used to replace the current process image with a new process image. It takes three arguments: the first is a pointer to a string containing the path to the new executable file, the second is an array of strings containing the command-line arguments to pass to the new process, and the third is an array of environment variables to set for the new process. If the function returns, an error has occurred.

exit() - This function is used to terminate the current process. It takes an integer argument which represents the exit status of the process.

fork() - This function is used to create a new process by duplicating the calling process. The new process (child process) is an exact copy of the calling process (parent process), but has a different process ID. The child process continues from the point where fork() was called, while the parent process continues executing after fork().

pipe() - This function is used to create a pipe, which is a unidirectional data channel between two processes. It takes an array of two integers as an argument, and returns 0 on success or -1 on error. The first element of the array is the read end of the pipe, while the second element is the write end of the pipe.

unlink() - This function is used to remove a file or directory from the file system. It takes a string argument which is the path to the file or directory to be removed. If the function succeeds, it returns 0, otherwise it returns -1.

wait() and waitpid() - These functions are used to wait for a child process to terminate. wait() waits for any child process to terminate, while waitpid() waits for a specific child process to terminate. They both take a pointer to an integer argument, which is used to store the exit status of the child process. They return the process ID of the terminated child process on success, or -1 on error.
*/