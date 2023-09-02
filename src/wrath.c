/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:53:09 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 17:57:24 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	mutex_destroy(t_program *prgm)
{
	int		i;

	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_destroy(&prgm->forks[i]);
		pthread_mutex_destroy(&(prgm->philos[i].meals_eaten_lock));
		i++;
	}
	pthread_mutex_destroy(&prgm->print_lock);
	ft_free(prgm->forks);
	return (1);
}

void	free_and_exit(t_program *prgm)
{
	mutex_destroy(prgm);
	ft_free(prgm->philos);
	ft_free(prgm);
}
