/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:12:52 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/27 15:53:57 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		td;
	int				philo_num;
	bool			is_dead;
	int				nb_of_meals;
	struct s_philo	*next;
}	t_philo;

typedef struct s_locks
{
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	thinking;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
}	t_locks;

typedef struct s_data
{
	int		nb;
	int		time2die;
	int		time2eat;
	int		time2sleep;
	int		min_meals;
	t_philo	**philo;
	t_locks	*locks;
}	t_data;

// Main functions
void		philosophers(t_data *ph);

// Threads
pthread_t	create_threads(void);
void		join_threads(pthread_t *philo);

// Routines
void		*philo_routine(void *ptr);
void		*monitoring(void *ptr);

// Mutexes
void		init_mutexes(t_locks *locks);
void		destroy_mutexes(t_locks *locks);

// Data
void		free_data_list(t_data *data);
void		free_philo_list(t_philo **philo);
t_philo		**create_philo_list(t_data *data);
t_philo		*create_philo_node(t_data *data);


// Utils
t_data		get_data(char **argv);
int			ft_atoi(const char *nptr);
bool		is_positive_nb(int argc, char **argv);

#endif
