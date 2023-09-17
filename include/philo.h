/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:55 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/03 19:08:01 by sbhatta          ###   ########.fr       */
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
	int					fork_taken;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		fork_taken_lock;
	pthread_mutex_t		meals_eaten_lock;
	pthread_mutex_t		ate_count_lock;
	int					is_eating;
	size_t				last_meal;
	struct s_program	*prgm;

}	t_philo;

typedef struct s_program
{
	int					end;
	int					need_eat_count;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		meals_eaten_lock;
	pthread_mutex_t		fork_taken_lock;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	size_t				start_time;
	int					number_of_philosophers;
	int					num_times_to_eat;
	t_philo				*philos;
	pthread_t			monitor_end;
	pthread_t			monitor_eating;
}	t_program;

//TIME
size_t		ft_gettime(void);
int			ft_usleep(size_t ms, t_program *prgm);

//PHILO LIFECYCLE
int			init_prgm(t_program *prgm, char **argv);
int			philo_init(t_program *prgm);
void		*start_program(void *philos);
int			sleeping(t_program *prgm, t_philo *philos);
int			if_end(t_program *prgm);

//PRINT
int			print_dead(int philos_id, t_program *prgm, char *msg);
int			philo_print_statement(t_philo *philos, t_program *prgm, char *msg);

//MUTEX AND FREE
int			mutex_destroy(t_program *prgm);
void		free_and_exit(t_program *prgm);

//PARSE CHECK
void		check_need_of_eat_count(t_program *prgm, int argc);
int			check_valid_args(char **argv);
int			check_valid_time_to(t_program *prgm, char **argv);

//MONITOR
void		*monitor_end(void *holder);
void		*monitor_eat_count(void *holder);

//UTILS
void		ft_free(void *ptr);
long		ft_atoi_long(const char *str);
int			ft_isnumber(char *str);

//EAT
int			get_eat_count(t_philo *philos);

//FORKS
int			take_fork_to_eat(t_program *prgm, t_philo *philos);
int			take_left_fork(t_program *prgm, t_philo *philos);
int			take_right_fork(t_program *prgm, t_philo *philos);
void		unlock_forks(t_program *prgm, t_philo *philos);
#endif