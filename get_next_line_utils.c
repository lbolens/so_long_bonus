/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:49:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/05/27 15:34:15 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_str(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_strlen(t_nod *stash)
{
	int		i;
	int		len;
	t_nod	*temp;

	len = 0;
	temp = stash;
	if (!stash)
		return (0);
	while (temp != NULL)
	{
		if (temp->content)
		{
			i = 0;
			while (temp->content[i] != 0)
			{
				len++;
				if (temp->content[i] == '\n')
					return (len);
				i++;
			}
		}
		temp = temp->next;
	}
	return (len);
}

t_nod	*ft_create_new_stash(char *content, int index)
{
	t_nod	*new;
	int		i;
	int		j;
	char	*dest;

	dest = (char *)malloc((ft_strlen_str(content + index) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	j = index;
	while (content[j] != 0)
		dest[i++] = content[j++];
	dest[i] = '\0';
	new = malloc(sizeof(t_nod));
	if (!new)
	{
		free(dest);
		return (NULL);
	}
	new->content = dest;
	new->next = NULL;
	return (new);
}

void	ft_clean_stash(t_nod **stash)
{
	t_nod	*new;
	t_nod	*current;
	t_nod	*old_stash;
	int		i;

	if (((*stash) == NULL) || (stash == NULL))
		return ;
	new = NULL;
	current = (*stash);
	while (current && current->content)
	{
		i = 0;
		while (current->content[i] && current->content[i] != '\n')
			i++;
		if (current->content[i] == '\n' && current->content[i + 1])
			new = ft_create_new_stash(current->content, i + 1);
		current = current->next;
	}
	old_stash = *stash;
	free_stash(&old_stash);
	*stash = new;
}

char	*ft_split_the_stash(t_nod *stash, int i, int j, int size)
{
	char	*result;

	if (!stash)
		return (NULL);
	size = ft_strlen(stash);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (stash != NULL)
	{
		j = -1;
		while (stash->content[++j])
		{
			result[i] = stash->content[j];
			i++;
			if (stash->content[j] == '\n')
			{
				result[i] = '\0';
				return (result);
			}
		}
		stash = stash->next;
	}
	result[i] = '\0';
	return (result);
}
