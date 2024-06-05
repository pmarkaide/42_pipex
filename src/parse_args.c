/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:47:49 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/05 11:54:05 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	count_args(char *arg)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (arg[i] != '\0')
		count = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] == ' ' && (i == 0 || arg[i - 1] != '\\'))
			count++;
		i++;
	}
	return (count);
}

char	**handle_empty_arg(char *arg)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		return (NULL);
	cmd[0] = ft_strdup(arg);
	if (cmd[0] == NULL)
	{
		free(cmd);
		return (NULL);
	}
	cmd[1] = NULL;
	return (cmd);
}

char	**handle_non_empty_arg(char *arg)
{
	char	**cmd;
	int		i;
	int		start;
	int		arg_count;

	i = 0;
	arg_count = 0;
	start = 0;
	cmd = malloc(sizeof(char *) * (count_args(arg) + 1));
	if (cmd == NULL)
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == ' ' && (i == 0 || arg[i - 1] != '\\'))
		{
			cmd[arg_count] = ft_substr(arg, start, i - start);
			start = i + 1;
			arg_count++;
		}
		i++;
	}
	cmd[arg_count] = ft_substr(arg, start, i - start);
	cmd[arg_count + 1] = NULL;
	return (cmd);
}

char	**parse_cmd_args(char *arg)
{
	char	**cmd;

	if (ft_str_empty(arg))
		cmd = handle_empty_arg(arg);
	else
		cmd = handle_non_empty_arg(arg);
	return (cmd);
}
