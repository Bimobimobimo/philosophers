/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:33:37 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 15:24:03 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	arg_error(void)
{
	printf("\033[1m\nArgument error, retry with:\n\033[31;0m./philo ");
	printf("\033[38;2;255;165;0mNumber_of_philosophers ");
	printf("\033[31mTime_to_die \033[38;2;255;165;0mTime_to_eat ");
	printf("\033[31mTime_to_sleep \033[0mand optionally");
	printf("\033[38;2;255;165;0m Number_of_time_each_");
	printf("philosopher_must_eat\n\033[0m");
	printf("\033[1mAll numbers must be positive and ");
	printf("< 2'147'483'647.\033[0m\n\n");
}

bool	thread_mutex_error(t_option choice)
{
	if (choice == INIT)
		printf("Mutex initiation error\n");
	else if (choice == DESTROY)
		printf("Mutex destruction error\n");
	else if (choice == LOCK)
		printf("Mutex lock error\n");
	else if (choice == UNLOCK)
		printf("Mutex unlock error\n");
	else if (choice == CREATE)
		printf("Thread creation error\n");
	else if (choice == JOIN)
		printf("Thread joining error\n");
	else if (choice == DETACH)
		printf("Thread detaching error\n");
	return (false);
}

bool	print_action(t_philo *philo, t_data *data, t_action action)
{
	long	time;

	time = timer() / 1000 - data->start_time / 1000; // en millisecondes
	if (philo->finished)
		return (true);
	if (!mutex_option(&data->print_mutex, LOCK))
		return (false);
	if (action == LEFT || action == RIGHT && !data->the_end)
		printf("%ld   %d has taken a fork\n", time, philo->id);
	else if (action == EAT && !data->the_end)
		printf("%ld   %d is eating\n", time, philo->id);
	else if (action == SLEEP && !data->the_end)
		printf("%ld   %d is sleeping\n", time, philo->id);
	else if (action == THINK && !data->the_end)
		printf("%ld   %d is thinking\n", time, philo->id);
	else if (action == DIED)
		printf("%ld   %d died\n", time, philo->id);
	if (!mutex_option(&data->print_mutex, UNLOCK))
		return (false);
	return (true);
}
