/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:52:36 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/27 12:57:30 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutexes(t_locks *locks)
{
	pthread_mutex_init(&(locks->eating), NULL);
	pthread_mutex_init(&(locks->sleeping), NULL);
	pthread_mutex_init(&(locks->thinking), NULL);
	pthread_mutex_init(&(locks->l_fork), NULL);
	pthread_mutex_init(&(locks->r_fork), NULL);
}

void	destroy_mutexes(t_locks *locks)
{
	pthread_mutex_destroy(&(locks->eating));
	pthread_mutex_destroy(&(locks->sleeping));
	pthread_mutex_destroy(&(locks->thinking));
	pthread_mutex_destroy(&(locks->l_fork));
	pthread_mutex_destroy(&(locks->r_fork));
}
