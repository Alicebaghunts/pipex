/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:54:02 by gcollet           #+#    #+#             */
/*   Updated: 2025/04/10 18:32:43 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(char **argv, int *fd, char **envp)
{
	int		input_file_fd;

	close(fd[0]);
	input_file_fd = open(argv[1], O_RDONLY);
	if (input_file_fd == -1)
		error_handling(3);
	dup2(input_file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(input_file_fd);
	close(fd[1]);
	run_command(argv[2], envp);
}

void	second_child(char **argv, int *fd, char **envp)
{
	int		output_file_fd;

	close(fd[1]);
	output_file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file_fd == -1)
		error_handling(3);
	dup2(fd[0], STDIN_FILENO);
	dup2(output_file_fd, STDOUT_FILENO);
	close(fd[0]);
	close(output_file_fd);
	run_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		error_handling(6);
	if (pipe(fd) == -1)
		error_handling(1);
	pid1 = fork();
	if (pid1 == -1)
		error_handling(2);
	if (pid1 == 0)
		first_child(argv, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_handling(2);
	if (pid2 == 0)
		second_child(argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}