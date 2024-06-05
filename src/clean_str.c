/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:34:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/05 12:01:36 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	is_non_escape_char(char c)
{
	if (c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\''
		|| c == '\"' || c == '0')
		return (0);
	else
		return (1);
}

char	*remove_str_quotes_and_escape_chars(const char *arg)
{
	int		i;
	int		j;
	int		in_double_quotes;
	char	*result;

	i = 0;
	j = 0;
	in_double_quotes = 0;
	result = allocate_result(arg);
	if (result == NULL)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\"')
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue ;
		}
		if (arg[i] == '\\' && (!in_double_quotes || (in_double_quotes
					&& !is_non_escape_char(arg[i + 1]))))
			i++;
		result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_array_quotes(char **array)
{
	int		i;
	char	*new_str;

	i = 0;
	while (array[i] != NULL)
	{
		new_str = remove_str_quotes_and_escape_chars(array[i]);
		if (new_str != NULL)
		{
			free(array[i]);
			array[i] = new_str;
		}
		i++;
	}
}

char	*remove_double_quotes(const char *arg)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '\"' && arg[i + 1] == '\"')
			i += 2;
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

char	**clean_arguments(char *arg)
{
	char	*clean;
	char	**args;

	clean = remove_double_quotes(arg);
	args = parse_cmd_args(clean);
	remove_array_quotes(args);
	free(clean);
	return (args);
}
