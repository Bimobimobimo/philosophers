/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:33:37 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/07 12:49:21 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	arg_error(void)
{
	printf(BOLD "\n/!\\ Argument error, retry with:\n\n" RESET);
	printf("./philo ");
	printf(YELLOW "Number_of_philosophers " RESET);
	printf(RED "Time_to_die " RESET);
	printf(YELLOW "Time_to_eat " RESET);
	printf(RED "Time_to_sleep " RESET);
	printf("and optionally ");
	printf(YELLOW "Number_of_time_each_philosopher_must_eat\n" RESET);
	printf(BOLD "\nAll numbers must be positive and < 2147483647.\n\n" RESET);
}

bool	thread_mutex_error(t_option choice)
{
	if (choice == INIT)
		printf(BOLDRED "Mutex initiation error\n" RESET);
	else if (choice == DESTROY)
		printf(BOLDRED "Mutex destruction error\n" RESET);
	else if (choice == LOCK)
		printf(BOLDRED "Mutex lock error\n" RESET);
	else if (choice == UNLOCK)
		printf(BOLDRED "Mutex unlock error\n" RESET);
	else if (choice == CREATE)
		printf(BOLDRED "Thread creation error\n" RESET);
	else if (choice == JOIN)
		printf(BOLDRED "Thread joining error\n" RESET);
	else if (choice == DETACH)
		printf(BOLDRED "Thread detaching error\n" RESET);
	return (false);
}

bool	print_action(t_philo *philo, t_data *data, t_action action)
{
	long	time;

	time = timer() - get_long(&data->sim_lock, data->start_time);
	if (philo->finished)
		return (true);
	if (!mutex_option(&data->print_lock, LOCK)
		|| !mutex_option(&data->sim_lock, LOCK))
		return (false);
	if ((action == FIRST || action == SECOND) && !data->the_end)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (action == EAT && !data->the_end)
		printf(YELLOW "%ld %d is eating\n" RESET, time, philo->id);
	else if (action == SLEEP && !data->the_end)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (action == THINK && !data->the_end)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (action == DIED)
		printf(BOLDRED "%ld %d died\n" RESET, time, philo->id);
	if (!mutex_option(&data->print_lock, UNLOCK)
		|| !mutex_option(&data->sim_lock, UNLOCK))
		return (false);
	return (true);
}
