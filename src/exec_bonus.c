/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:12:08 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/12 15:48:12 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	execute_cmd(t_data *data, char **cmd, char **envp)
{
	int	exit_code;

	if (execve(data->exec_path, cmd, envp) == -1)
	{
		exit_code = execute_shell_cmd(data, cmd, envp);
		free_data(data);
		return (exit_code);
	}
	return (0);
}
