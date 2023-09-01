/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sloth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:55:17 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 14:07:32 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_program *prgm, t_philo *philos)
{
	size_t	sleep_time;

	sleep_time = 0;
	if (prgm->dead)
		return (0);
	philo_print_statement(philos, prgm, "is sleeping");
	while (1)
	{
		ft_usleep(1);
		sleep_time++;
		if (prgm->dead == 1 || prgm->end_now >= 1)
			return (0);
		check_death(prgm, philos);
		if (sleep_time == prgm->time_to_sleep)
			break ;
	}
	return (1);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
		usleep(500);
	return (1);
}
