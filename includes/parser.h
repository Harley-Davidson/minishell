/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:31 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/26 17:45:39 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
**	**cmd 		= command name and parameters if any
	*full_path 	= if not builtin, path for executable, from $PATH var
	fd_in		= file descriptor to read from (defaults to stdin)
**	fd_out		= file descriptor to write to (defaults to stdout)
*/

typedef struct s_command
{
	char		**cmd;
	char		*full_path;
	int			infile;
	int			outfile;
	t_token		cmd_splitter;
	t_token		last_splitter_token;
}				t_command;

#endif
