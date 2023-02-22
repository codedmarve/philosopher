/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:41 by moduwole          #+#    #+#             */
/*   Updated: 2023/02/08 20:22:41 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine2(void *args)
{
	t_philo	*phi;

	phi = args;
	if (phi->data->n_eat > 0)
		routine2_helper1(phi);
	else
		routine2_helper2(phi);
	return (NULL);
}

int	simulation(t_philo *phi)
{
	if (!philo_eat(phi))
		return (0);
	if (phi->n_eaten != phi->data->n_eat)
	{
		if (!philo_sleep(phi))
			return (0);
		if (!philo_think(phi))
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = arg;
	if (phi->data->n_eat > 0)
		routine_helper1(phi);
	else
		routine_helper2(phi);
	return (NULL);
}

int	th_create(t_philo *phi)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&phi[i].data->shared, NULL))
		return (printf("Error: failed to initialise mutex\n"), 0);
	if (pthread_mutex_init(&phi[i].data->tm, NULL))
		return (printf("Error: failed to initialise mutex\n"), 0);
	if (pthread_create(&phi[0].data->monitor, NULL, routine2, phi))
		return (printf("Error: failed to create thread\n"), 0);
	usleep(1000);
	phi->data->time = get_time();
	while (i < phi->data->n_philo)
	{
		if (pthread_create(&phi[i].th, NULL, routine, &phi[i]))
			return (printf("Error: failed to create thread\n"), 0);
		i++;
		usleep(1000);
	}
	i = -1;
	while (++i < phi->data->n_philo)
		if (pthread_join(phi[i].th, NULL))
			return (printf("Error: failed to join thread\n"), 0);
	if (pthread_join(phi->data->monitor, NULL))
		return (printf("Error: failed to join thread\n"), 0);
	return (1);
}
