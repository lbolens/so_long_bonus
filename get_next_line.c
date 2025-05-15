/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:22 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/08 16:52:18 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_stash(t_nod **stash)
{
	t_nod	*tmp;

	while (*stash)
	{
		tmp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = tmp;
	}
	*stash = NULL;
}

int	check_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_nod	*add_to_stash(t_nod *stash, char *buffer)
{
	t_nod	*new;
	t_nod	*last;

	new = malloc(sizeof(t_nod));
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	new->content = buffer;
	new->next = NULL;
	if (!stash)
		return (new);
	last = stash;
	while (last->next)
		last = last->next;
	last->next = new;
	return (stash);
}

char	*read_and_stash(int fd, t_nod **stash, int new_l, ssize_t bytes_read)
{
	char	*buffer;

	while (!new_l)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read < 0 || !(*stash))
			{
				free_stash(stash);
				return (NULL);
			}
			return (ft_split_the_stash(*stash, 0, 0, 0));
		}
		buffer[bytes_read] = '\0';
		*stash = add_to_stash(*stash, buffer);
		if (!(*stash))
			return (NULL);
		new_l = check_newline(buffer);
	}
	return (ft_split_the_stash(*stash, 0, 0, 0));
}

char	*get_next_line(int fd)
{
	static t_nod	*stash;
	char			*line;
	int				new_l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_l = 0;
	if (stash)
		new_l = check_newline(stash->content);
	line = read_and_stash(fd, &stash, new_l, 0);
	ft_clean_stash(&stash);
	return (line);
}