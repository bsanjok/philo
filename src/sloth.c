/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sloth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:55:17 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 17:30:00 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleeping(t_program *prgm, t_philo *philos)
{
	if (if_end(prgm))
		return (0);
	philo_print_statement(philos, prgm, "is sleeping");
	ft_usleep(prgm->time_to_sleep);
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
