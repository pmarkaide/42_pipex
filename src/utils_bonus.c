/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:27 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/14 11:52:12 by pmarkaid         ###   ########.fr       */
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
	int i;

	i = 0;
	data->pipe_fd[0] = -1;
    data->pipe_fd[1] = -1;
    data->in_fd = -1;
    data->out_fd = -1;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->num_cmds = argc - 3;
	data->cmds = malloc(sizeof(char **) * data->num_cmds);
	if (data->cmds == NULL)
		free_data_and_exit(data, "malloc error", -1);
	while (i < data->num_cmds)
	{
		data->cmds[i] = clean_arguments(argv[i + 2]);
		if (data->cmds[i] == NULL)
			free_data_and_exit(data, "malloc error", -1);
		i++;
	}
	data->exec_path = NULL;
	data->paths = parse_paths(envp);
	data->shell = parse_shell(envp);
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
