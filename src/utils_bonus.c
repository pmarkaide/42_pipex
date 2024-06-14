/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:27 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/14 16:52:57 by pmarkaid         ###   ########.fr       */
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

	i = 0;
	data->pid = malloc(sizeof(pid_t) * data->num_cmds);
	data->cmds = malloc(sizeof(char **) * (data->num_cmds + 1));
	if (data->cmds == NULL || data->pid == NULL)
		free_data_and_exit(data, "malloc error", -1);
	while (i < data->num_cmds)
	{
		data->cmds[i] = clean_arguments(argv[i + 2]);
		if (data->cmds[i] == NULL)
			free_data_and_exit(data, "malloc error", -1);
		i++;
	}
	data->cmds[i] = NULL;
}

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->in_fd = -1;
	data->out_fd = -1;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->num_cmds = argc - 3;
	init_cmds_and_pid(data, argv);
	data->exec_path = NULL;
	data->envp = envp;
	data->paths = parse_paths(envp);
	data->shell = parse_shell(envp);
}
