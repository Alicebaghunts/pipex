/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:42:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/04/10 18:40:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//0 invalid argument
//1 pipe faile
//2 fork faile
//3 open faile
//4 path error
#include "../includes/pipex.h"

int	chechking_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	ft_free_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error_handling(int num)
{
	if (num == 0)
		ft_putstr_fd("❌ \033[31mError: Invalid argument\e[0m\n", 2);
	else if (num == 1)
		ft_putstr_fd("❌ \033[31mError: Failed to create pipe\e[0m\n", 2);
	else if (num == 2)
		ft_putstr_fd("❌ \033[31mError: Failed to create child\e[0m\n", 2);
	else if (num == 3)
		ft_putstr_fd("❌ \033[31mError: Failed to open file\e[0m\n", 2);
	else if (num == 4)
		ft_putstr_fd("❌ \033[31mError: Invalid path\e[0m\n", 2);
	else if (num == 5)
		ft_putstr_fd("❌ \033[31mError: Failed to run command\e[0m\n", 2);
	else if (num == 6)
		 ft_putstr_fd("❌ \033[31mError: Invslid input\e[0m\n", 2);
	exit(num);
}

char	*find_executable_path(char *command, char **envp)
{
	char	**arr;
	char	*full_path;
	int		index;
	char	*path;

	index = 0;
	while (ft_strnstr(envp[index], "PATH", 4) == 0)
		index++;
	arr = ft_split(envp[index] + 5, ':');
	index = 0;
	while (arr[index])
	{
		path = ft_strjoin(arr[index], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		index++;
	}
	ft_free_matrix(arr);
	return (0);
}

void	run_command(char *str, char **envp)
{
	char	**command;
	char	*path;

	if (chechking_argument(str) == 0)
		error_handling(0);
	command = ft_split(str, ' ');
	path = find_executable_path(command[0], envp);
	if (!path)
	{
		ft_free_matrix(command);
		error_handling(4);
	}
	if (execve(path, command, envp) == -1)
	{
		free(path);
		ft_free_matrix(command);
		error_handling(5);
	}
}