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

int	main(int ac, char **av)
{
	int	counter;
	int	fd;

	counter = 1;
	fd = 0;
	if (ac > 4)
	{
		if (filechecker(av[1]) > 1)
			fd = open(av[1], O_RONLY, );
		while (++counter < ac)
		{

		}
		/*av[1] && av[ac] são paths para os arquivos de entrada e saída;
		*/
	}
}

int	filechecker(char **file)
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