/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/03 19:34:50 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	directory_loop(t_command *c, DIR *d, char *target_file, char *cmd_path)
{
	struct dirent	*entry;

	while (d)
	{
		entry = readdir(d);
		if (!entry)
			break ;
		if (entry && !ft_strcmp(target_file, entry->d_name))
		{
			closedir(d);
			if (c->full_path != NULL)
				free(c->full_path);
			c->full_path = cmd_path;
			free(target_file);
			return (1);
		}
	}
	return (0);
}

int	is_builtin(t_command *c, t_shell *m)
{
	DIR		*directory;
	char	*target_file;
	char	*cmd_path;

	cmd_path = ft_strjoin(m->original_pwd, "/builtins");
	directory = opendir(cmd_path);
	target_file = ft_strjoin(c->cmd[0], ".c");
	if (directory_loop(c, directory, target_file, cmd_path))
		return (1);
	free(cmd_path);
	free(target_file);
	closedir(directory);
	return (0);
}

int	is_bin(t_shell *m, t_command *c)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	i = -1;
	while (m->envpath[++i])
	{
		directory = opendir(m->envpath[i]);
		while (directory)
		{
			entry = readdir(directory);
			if (!entry)
				break ;
			if (!ft_strcmp(c->cmd[0], entry->d_name))
			{
				c->full_path = ft_strdup(m->envpath[i]);
				closedir(directory);
				return (1);
			}
		}
		closedir(directory);
	}
	return (0);
}

int	parse_full_path(t_command *c, t_shell *m)
{
	char	*temp;

	is_builtin(c, m);
	if (!c->full_path)
		is_bin(m, c);
	if (c->full_path)
	{
		temp = ft_strjoin(c->full_path, "/");
		if (!temp)
			return (p_error(ALLOC_FAILURE, NULL));
		free(c->full_path);
		c->full_path = ft_strjoin(temp, c->cmd[0]);
		free(temp);
		if (!c->full_path)
			return (p_error(ALLOC_FAILURE, NULL));
	}
	return (0);
}

int	print_parser(t_shell *minihell)
{
	t_command	*test;
	t_shell		*m;
	int			i;

	m = minihell;
	i = 1;
	while ((t_command *)(m->parser))
	{
		test = (t_command *)(m->parser->content);
		while (*test->cmd)
		{
			printf("CMD %d: %s\n", i, *test->cmd);
			test->cmd++;
		}
		printf("CMD %d path: %s\n", i, test->full_path);
		if (test->cmd_splitter == PIPE)
			printf("CMD %d splitter: PIPE\n", i);
		else if (test->cmd_splitter == OR)
			printf("CMD %d splitter: OR\n", i);
		else if (test->cmd_splitter == AND)
			printf("CMD %d splitter: AND\n", i);
		m->parser = m->parser->next;
		i++;
	}
	return (0);
}
