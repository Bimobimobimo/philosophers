/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:12:52 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 12:38:39 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

#define GREY "\033[90m"
#define BOLDRED "\033[1;31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m" 
#define BOLD "\033[1m"
#define YELLOW "\033[38;2;255;165;0m"
#define RED "\033[31m"

typedef struct	s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	lock;
	int				id;
	long			meals_counter;
	long			last_meal_time;
	bool			finished;
	bool			died;
	t_data			*data;
	t_fork			*first_fork;
	t_fork			*second_fork;
}	t_philo;

struct s_data
{
	long			philo_nb;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	long			min_meals;
	long			start_time;
	// bool			threads_ready;
	bool			the_end;
	pthread_mutex_t	sim_lock; // permet de lire data
	pthread_mutex_t	print_lock;
	pthread_t		monitor;
	t_fork			*forks;
	t_philo			*philos;
};

typedef enum	s_option
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,	
} t_option;

typedef enum	s_action
{
	FIRST,
	SECOND,
	EAT,
	SLEEP,
	THINK,
	DIED,
}	t_action;


// Parsing
bool		valid_arguments(int argc, char **argv);
bool		valid_nb(char *str);
bool		too_many_digits(char *str);
long		atol_philo(const char *nptr);
bool		parse_data(t_data *data, char **argv);
bool		get_forks(t_data *data);

// Main functions
void		philosophers(t_data *ph);
bool		init_philos(t_data *data, t_philo *philos);
void		simulation(t_data *data);

// Time Management
long		timer(void);
void		waiting(long time, t_data *data);
bool		desynchronize_philos(t_philo *philo, t_data *data);

// Mutexes
bool		mutex_option(pthread_mutex_t *mutex, t_option choice);
bool		get_bool(pthread_mutex_t *mutex, bool value);
bool		set_bool(pthread_mutex_t *mutex, bool *value, bool result);
long		get_long(pthread_mutex_t *mutex, long value);
long		set_long(pthread_mutex_t *mutex, long *value, long result);

// Threads
bool		thread_option(pthread_t *thread, t_option choice,
				void *(*routine)(void *), void *argt);
void		*philo_routine(void *argt);
void		*monitoring(void *argt);

// Printing messages
void		arg_error(void);
bool		thread_mutex_error(t_option option);
bool		print_action(t_philo *philo, t_data *data, t_action action);

// Clean up
void		free_all(t_data *data);

#endif
