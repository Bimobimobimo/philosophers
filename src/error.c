/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:33:37 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/28 15:58:40 by lcollong         ###   ########.fr       */
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

bool	thread_mutex_error(t_action action)
{
	if (action == INIT)
		printf("Mutex initiation error\n");
	else if (action == DESTROY)
		printf("Mutex destruction error\n");
	else if (action == LOCK)
		printf("Mutex lock error\n");
	else if (action == UNLOCK)
		printf("Mutex unlock error\n");
	else if (action == CREATE)
		printf("Thread creation error\n");
	else if (action == JOIN)
		printf("Thread joining error\n");
	else if (action == DETACH)
		printf("Thread detaching error\n");
	return (false);
}
