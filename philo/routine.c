/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:31 by moduwole          #+#    #+#             */
/*   Updated: 2023/02/08 20:22:31 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->data->mymutex[phi->lfork]))
		return (0);
	if (!state_print(phi, phi->id + 1, GREEN, FORK))
		return (0);
	if (pthread_mutex_lock(&phi->data->mymutex[phi->rfork]))
		return (0);
	if (!state_print(phi, phi->id + 1, GREEN, FORK))
		return (0);
	if (!state_print(phi, phi->id + 1, PURPLE, EAT))
		return (0);
	phi->t_die = get_time();
	time_sim(phi->data->t_eat);
	pthread_mutex_unlock(&phi->data->mymutex[phi->lfork]);
	pthread_mutex_unlock(&phi->data->mymutex[phi->rfork]);
	phi->n_eaten++;
	return (1);
}

int	philo_sleep(t_philo *phi)
{
	if (!state_print(phi, phi->id + 1, BLUE, SLEEP))
		return (0);
	time_sim(phi->data->t_sleep);
	return (1);
}

int	philo_think(t_philo *phi)
{
	if (!state_print(phi, phi->id + 1, G_BLUE, THINK))
		return (0);
	return (1);
}

int	is_dead(t_philo *phi, int *i)
{
	int	time;

	if (*i == phi[*i].data->n_philo)
		*i = 0;
	time = time_diff(phi[*i].t_die);
	if (time > phi[*i].data->t_die)
	{
		state_print(&phi[*i], phi[*i].id + 1, RED, DIED);
		phi[*i].data->philo_died = 1;
		return (1);
	}
	i++;
	usleep(100);
	return (0);
}
