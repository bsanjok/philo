/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   despair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:58:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/03 18:25:38 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	last_ate_at(t_program *prgm, t_philo *philos)
{
	size_t	result;

	pthread_mutex_lock(&philos->meals_eaten_lock);
	pthread_mutex_lock(&prgm->meals_eaten_lock);
	result = philos->last_meal;
	pthread_mutex_unlock(&prgm->meals_eaten_lock);
	pthread_mutex_unlock(&philos->meals_eaten_lock);
	return (result);
}

void	check_need_of_eat_count(t_program *prgm, int argc)
{
	if (argc == 6)
		prgm->need_eat_count = 1;
	else
		prgm->need_eat_count = 0;
}

void	*monitor_end(void *holder)
{
	t_program	*prgm;
	int			i;

	prgm = holder;
	i = 0;
	while (!if_end(prgm))
	{
		i = 0;
		while (i < prgm->number_of_philosophers)
		{
			if (prgm->time_to_die < ft_gettime() - \
			last_ate_at(prgm, &prgm->philos[i]))
			{
				pthread_mutex_lock(&prgm->death_lock);
				prgm->end = 1;
				pthread_mutex_unlock(&prgm->death_lock);
				print_dead(prgm->philos[i].id, prgm, "died");
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	print_dead(int philos_id, t_program *prgm, char *msg)
{
	pthread_mutex_lock(&prgm->print_lock);
	printf("%zu %d %s\n", ft_gettime() - prgm->start_time, philos_id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (1);
}
