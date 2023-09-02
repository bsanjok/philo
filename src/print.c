/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:57:28 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 17:33:30 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_print_statement(t_philo *philos, t_program *prgm, char *msg)
{
	pthread_mutex_lock(&prgm->print_lock);
	if (if_end(prgm))
		return (0);
	printf("%zu %d %s\n", ft_gettime() - prgm->start_time, philos->id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (1);
}
