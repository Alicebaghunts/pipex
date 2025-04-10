/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:58:35 by gcollet           #+#    #+#             */
/*   Updated: 2025/04/10 19:26:29 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define INVALID_ARGUMENT 0
# define PIPE_ERROR 1
# define FORK_ERROR 2
# define OPEN_FILE_ERROR 3
# define INVALID_PATH 4
# define EXECVE_ERROR 5
# define INVALID_INPUT 6

void	error_handling(int num);
void	ft_free_matrix(char **arr);
char	*find_executable_path(char *command, char **envp);
void	run_command(char *str, char **envp);
void	first_child(char **argv, int *fd, char **envp);
void	second_child(char **argv, int *fd, char **envp);
int		chechking_argument(char *str);
void	handle_here_doc(char *limiter, int *fd);
void	execute_command(char *cmd, char **envp);
void	create_pipes_and_fork(int argc, char **argv, char **envp, int is_here_doc);
char	*get_next_line(int fd);
void	ft_get_line(int fd, char **line);
char	*ft_cut_str(char *line);
char	*future_next_line(char *line);

#endif
