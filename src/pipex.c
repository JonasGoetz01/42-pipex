/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:10:42 by jgotz             #+#    #+#             */
/*   Updated: 2023/11/14 11:03:10 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * Functions to use:
 * open -> open a file
 * close -> close file descriptor
 * read -> read from file descriptor
 * write -> write to file descriptor
 * malloc -> allocate memory
 * free -> free memory
 * perror -> print error message
 * strerror -> return error message
 * access -> check if file exists
 * dup -> duplicate file descriptor
 * dup2 -> duplicate file descriptor to custom file descriptor
 * execve -> execute program
 * exit -> exit program
 * fork -> create child process
 * pipe -> create pipe between two file descriptors
 * unlink -> delete file
 * wait -> wait for child process to finish
 * waitpid -> wait for child process to finish with pid
 */

/**
 * Usage: ./pipex file1 cmd1 cmd2 file2
 *  		./pipex infile "ls -l" "wc -l" outfile
 */
int	main(int argc, char **argv)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		outfilefd;
	int		infilefd;
	char	**cmd1;
	char	**cmd2;

	infilefd = 0;
	outfilefd = 0;
	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	infilefd = open(argv[1], O_RDONLY);
	if (infilefd == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
	{
		dup2(infilefd, STDIN_FILENO);
		close(infilefd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		cmd1 = ft_split(argv[2], ' ');
		execvp(cmd1[0], cmd1);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		outfilefd = open(argv[4], O_WRONLY | O_CREAT, 0755);
		if (outfilefd == -1)
			exit(1);
		dup2(outfilefd, STDOUT_FILENO);
		close(outfilefd);
		cmd2 = ft_split(argv[3], ' ');
		execvp(cmd2[0], cmd2);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
