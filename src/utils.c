/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:19:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/18 16:10:46 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

	i = 0;
	while (data->paths[i])
	{
		data->executable = ft_strjoin(data->paths[i], data->cmd[0], "/");
		if (!access(data->executable, F_OK))
		{
			if (cmd_is_directory(data->executable))
				free_data_and_exit(data, data->cmd[0], COMMAND_NOT_FOUND);
			return (eval_executable_permissions(data));
		}
		free(data->executable);
		data->executable = NULL;
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

void	init_struct(t_data *data, char **argv, char **envp)
{
	data->infile = argv[1];
	data->outfile = argv[4];
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->cmd1 = clean_arguments(argv[2]);
	data->cmd2 = clean_arguments(argv[3]);
	data->executable = NULL;
	data->cmd = NULL;
	data->paths = parse_paths(envp);
	data->shell = parse_shell(envp);
	if (data->cmd1 == NULL || data->cmd2 == NULL)
		free_data_and_exit(data, "malloc error", -1);
}
