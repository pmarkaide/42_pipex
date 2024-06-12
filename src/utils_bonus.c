/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:27 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/12 10:18:44 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*allocate_result(const char *arg)
{
	int		len;
	char	*res;

	len = ft_strlen(arg);
	if (len == 0)
		return (ft_strdup(arg));
	res = (char *)malloc((len + 1) * sizeof(char));
	return (res);
}

void	get_executable_path(t_data *data)
{
	int		i;
	char	*exec_path;

	exec_path = data->cmd[0];
	i = 0;
	while (data->paths[i])
	{
		exec_path = ft_strjoin(data->paths[i], data->cmd[0], "/");
		if (!access(exec_path, F_OK))
		{
			free(data->exec_path);
			data->exec_path = exec_path;
			return (eval_executable_permissions(data));
		}
		free(exec_path);
		i++;
	}
	free_data_and_exit(data, data->cmd[0], COMMAND_NOT_FOUND);
}

char	**parse_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*parse_shell(char **envp)
{
	int		i;
	char	*shell;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "SHELL=", 6))
		{
			shell = ft_strdup(envp[i] + 6);
			return (shell);
		}
		i++;
	}
	shell = ft_strdup("/bin/sh");
	return (shell);
}

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_memset(data->pipe_fd, 0, sizeof(data->pipe_fd));
	data->infile = argv[1];
	data->outfile = argv[4];
	data->num_cmd = argc - 3;
	data->cmd1 = clean_arguments(argv[2]);
	data->cmd2 = clean_arguments(argv[3]);
	data->exec_path = NULL;
	data->cmd = NULL;
	data->paths = parse_paths(envp);
	data->shell = parse_shell(envp);
	if (data->cmd1 == NULL || data->cmd2 == NULL)
		free_data_and_exit(data, "malloc error", -1);
}

void open_infile(t_data *data)
{
	data->in_fd = open(data->infile, O_RDONLY);
	if (errno == ENOENT)
		free_data_and_exit(data, data->infile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->infile, PERMISSION_DENIED);
	if (errno == IS_DIRECTORY)
		free_data_and_exit(data, data->infile, IS_DIRECTORY);
}

void open_outfile(t_data *data)
{
	data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (errno == ENOENT)
		free_data_and_exit(data, data->outfile, NO_FILE);
	if (errno == EACCES)
		free_data_and_exit(data, data->outfile, PERMISSION_DENIED);
	if (errno == IS_DIRECTORY)
		free_data_and_exit(data, data->infile, IS_DIRECTORY);
}
