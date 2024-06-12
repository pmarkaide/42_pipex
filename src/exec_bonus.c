/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:12:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/12 12:40:59 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	execute_shell_cmd(t_data *data, char **envp)
{
	char	*shell_cmd[4];

	shell_cmd[0] = data->shell;
	shell_cmd[1] = "-c";
	shell_cmd[2] = data->cmd[0];
	shell_cmd[3] = NULL;
	if (execve(data->shell, shell_cmd, envp) == -1)
	{
		ft_putstr_fd("execve failed\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	execute_cmd(t_data *data, char **envp)
{
	int	exit_code;

	if (execve(data->exec_path, data->cmd, envp) == -1)
	{
		exit_code = execute_shell_cmd(data, envp);
		return (exit_code);
	}
	return (0);
}
