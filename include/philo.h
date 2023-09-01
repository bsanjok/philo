/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:55 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 18:31:08 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			threads;
	int					id;
	int					meals_eaten;
	int					*left_fork_usage;
	int					*right_fork_usage;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meals_eaten_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	size_t				last_meal;
	struct s_program	*prgm;

}	t_philo;

typedef struct s_program
{
	int					dead;
	int					need_eat_count;
	int					*fork_usage;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		end_lock;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	size_t				start_time;
	int					number_of_philosophers;
	int					num_times_to_eat;
	int					end_now;
	int					all_eaten;
	t_philo				*philos;

}	t_program;

size_t		ft_gettime(void);
int			ft_usleep(size_t ms);
int			sleeping(t_program *prgm, t_philo *philos);
int			check_death(t_program *prgm, t_philo *philos);
int			print_dead(t_philo *philos, t_program *prgm, char *msg);
int			philo_print_statement(t_philo *philos, t_program *prgm, char *msg);
void		*start_program(void *philos);
int			mutex_destroy(t_program *prgm);
void		free_and_exit(t_program *prgm);
int			init_prgm(t_program *prgm, char **argv, int argc);
int			philo_init(t_program *prgm);
int			take_fork_to_eat(t_program *prgm, t_philo *philos);
int			check_eat_count(t_program *prgm);
void		check_need_of_eat_count(t_program *prgm, int argc);
void		ft_free(void *ptr);

#endif