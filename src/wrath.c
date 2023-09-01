/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:53:09 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 13:53:42 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	mutex_destroy(t_program *prgm)
{
	int		i;

	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_destroy(&prgm->forks[i]);
		pthread_mutex_destroy(&(prgm->philos[i].meal_lock));
		pthread_mutex_destroy(&(prgm->philos[i].dead_lock));
		pthread_mutex_destroy(&(prgm->philos[i].meals_eaten_lock));
		i++;
	}
	pthread_mutex_destroy(&prgm->print_lock);
	return (1);
}

void	free_and_exit(void *n, int exit_code)
{
	if (n)
	{
		free(n);
		n = NULL;
	}
	exit(exit_code);
}
