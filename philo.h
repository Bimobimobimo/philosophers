/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:12:52 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:56:43 by lcollong         ###   ########.fr       */
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
# include <sys/time.h>
# include <limits.h>

typedef struct	s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;


typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		finished;
	long		last_meal_time;
	t_data		*data;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	tid;
}	t_philo;


typedef struct s_data
{
	long			philo_nb;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	long			min_meals; // argument facultatif
	long			start_time;
	bool			the_end; // si un philo meurt ou si tous finished
	bool			threads_ready;
	pthread_mutex_t	sim_mutex; // permet d'eviter les data races
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
}	t_data;


typedef enum	s_action
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,	
} t_action;


// Parsing
bool		valid_arguments(int argc, char **argv);
bool		valid_nb(char *str);
bool		too_many_digits(char *str);
long		atol_philo(const char *nptr);

bool		parse_data(t_data *data, char **argv);
bool		get_philos(t_data *data);
bool		get_forks(t_data *data);

// Main functions
void		philosophers(t_data *ph);
bool		get_philos(t_data *data);
void		simulation(t_data *data);

// Time Management
long		timer(void);
void		waiting(long time, t_data *data);

// Mutexes
bool		mutex_action(pthread_mutex_t *mutex, t_action action);

// Threads
bool		thread_action(pthread_t thread, t_action action,
				void *(*routine)(void *), t_data *data);
void		philo_routine(void *argt);
void		*monitoring(t_data *data);

// Error
void		arg_error(void);
bool		thread_mutex_error(t_action action);

// Clean up
void		free_all(t_data *data);









// // Threads
// pthread_t	create_threads(void);
// void		join_threads(pthread_t *philo);

// // Routines
// void		*philo_routine(void *ptr);
// void		*monitoring(void *ptr);



// Utils



#endif
