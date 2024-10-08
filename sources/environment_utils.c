/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:10 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/10 19:04:46 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_envp(t_shell *m)
{
	char	**v;

	v = m->envp;
	while (*v)
		printf("%s\n", *(v++));
}

// Custom function to swap two strings
void	ft_str_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Bubble sort function to sort array of strings
void	ft_str_bubble_sort(char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				ft_str_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

int	sizeof_2d_array(char **arr)
{
	int	n;

	n = 0;
	while (arr[n] != NULL)
		n++;
	return (n);
}
