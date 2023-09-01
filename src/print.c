/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:57:28 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 17:11:05 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_print_statement(t_philo *philos, t_program *prgm, char *msg)
{
	if (prgm->end_now > 1 || prgm->dead == 1)
		return (0);
	pthread_mutex_lock(&prgm->print_lock);
	if ((prgm->need_eat_count && check_eat_count(prgm)))
	{
		pthread_mutex_unlock(&prgm->print_lock);
		return (0);
	}
	printf("%zu %d %s\n", ft_gettime() - prgm->start_time, philos->id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (1);
}
