/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:36:00 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 18:02:24 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_string(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_array(char ***array)
{
	size_t	i;

	if (*array == NULL || **array == NULL)
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data == NULL)
		return ;
	close_open_fds(data);
	while (i < data->num_cmds)
	{
		if (data->cmds[i] != NULL)
		{
			free_array(&data->cmds[i]);
			data->cmds[i] = NULL;
		}
		i++;
	}
	free(data->cmds);
	data->cmds = NULL;
	free(data->pid);
	data->pid = NULL;
	free_array(&data->paths);
	free_string(&data->shell);
	if (data->executable != NULL)
		free_string(&data->executable);
}
