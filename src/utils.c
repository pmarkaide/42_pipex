/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:19:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/04/23 18:22:08 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// typedef struct s_data
// {
// 	int pipe_fd[2];
// 	char **cmd1;
// 	char **cmd2;
// 	char **env;
// }				t_data;

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || *array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_array(data->cmd1);
	free_array(data->cmd2);
	free_array(data->paths);
}


char	**parse_cmd_args(char *arg)
{
	char **cmd;

	if (ft_str_empty(arg))
	{
		cmd = malloc(sizeof(char *) * 2);
		if (cmd == NULL)
			return NULL;
		cmd[0] = ft_strdup(arg);
		if (cmd[0] == NULL)
		{
			free(cmd);
			return NULL;
		}
		cmd[1] = NULL;
	}
	else
	{
		cmd = ft_split(arg, ' ');
		if (cmd == NULL)
			return NULL;
	}
	return cmd;
}


void eval_executable(t_data *data)
{
	int local;
	local = 0;

	data->exec_path = data->cmd[0];
	if(ft_str_empty(data->exec_path))
		free_data_and_exit(data, data->exec_path, COMMAND_NOT_FOUND);
	if(ft_strncmp(data->cmd[0], "/", 1) == 0)
		local = 1;
	if(ft_strncmp(data->cmd[0], "./", 2) == 0)
		local = 1;
	if(ft_strncmp(data->cmd[0], "../", 3) == 0)
		local = 1;
	if(local || data->paths == NULL)
	{
		if (access(data->exec_path, F_OK))
			free_data_and_exit(data, data->exec_path, NO_FILE);
		else
			return(eval_executable_permissions(data));
	}
	else
		get_executable_path(data);
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
			data->exec_path = exec_path;
			return(eval_executable_permissions(data));
		}
		free(exec_path);
		i++;
	}
	free_data_and_exit(data, data->cmd[0], COMMAND_NOT_FOUND);
}

void eval_executable_permissions(t_data *data)
{
	if (!access(data->exec_path, X_OK))
		return;
	free_data_and_exit(data, data->exec_path, PERMISSION_DENIED);
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

void	init_struct(t_data *data, char **argv, char **envp)
{
	data->infile = argv[1];
	data->outfile = argv[4];
	data->cmd1 = parse_cmd_args(argv[2]);
	data->cmd2 = parse_cmd_args(argv[3]);
	data->paths = parse_paths(envp);
	data->exec_path = NULL;
	if(data->cmd1 == NULL || data->cmd2 == NULL)
		free_data_and_exit(data, "malloc error", -1);
}
