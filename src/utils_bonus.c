/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:27 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 17:14:59 by pmarkaid         ###   ########.fr       */
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

void	init_cmds_and_pid(t_data *data, char **argv)
{
	int	i;
	int	offset;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * data->num_cmds);
	data->cmds = malloc(sizeof(char **) * (data->num_cmds + 1));
	if (data->cmds == NULL || data->pid == NULL)
		command_error_exit(data, "malloc error", -1);
	if (data->here_doc == 1)
		offset = 3;
	else
		offset = 2;
	while (i < data->num_cmds)
	{
		data->cmds[i] = clean_arguments(argv[i + offset]);
		if (data->cmds[i] == NULL)
			command_error_exit(data, "malloc error", -1);
		i++;
	}
	data->cmds[i] = NULL;
}

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->read_end = -1;
	data->in_fd = -1;
	data->out_fd = -1;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data->here_doc = 1;
		data->delimiter = argv[2];
		data->infile = "/tmp/here_doc";
		data->num_cmds = argc - 4;
	}
	else
	{
		data->delimiter = NULL;
		data->infile = argv[1];
		data->num_cmds = argc - 3;
	}
	data->outfile = argv[argc - 1];
	data->executable = NULL;
	data->envp = envp;
	data->shell = parse_shell(envp);
	data->paths = parse_paths(envp);
	init_cmds_and_pid(data, argv);
}
