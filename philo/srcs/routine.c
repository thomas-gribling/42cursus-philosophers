/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:06:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/23 08:45:00 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	die(t_philo *phi)
{
	pthread_mutex_lock(&phi->all->death_mutex);
	if (!phi->all->dead)
		put_message(MSG_DIE, phi);
	phi->all->dead = 1; //data_race
	pthread_mutex_unlock(&phi->all->death_mutex);
}

static void	*check_death(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	ft_usleep(phi->all->t_die + 1);
	pthread_mutex_lock(&phi->eat_mutex);
	if (get_time() - phi->last_eat >= phi->all->t_die)
		die(phi);
	pthread_mutex_unlock(&phi->eat_mutex);
	return (NULL);
}

static void	philo_eat(t_philo *phi)
{
	if (phi->i % 2)
	{
		pthread_mutex_lock(&phi->lf);
		put_message(MSG_FORK, phi);
		pthread_mutex_lock(phi->rf);
	}
	else
	{
		pthread_mutex_lock(phi->rf);
		put_message(MSG_FORK, phi);
		pthread_mutex_lock(&phi->lf);
	}
	put_message(MSG_FORK, phi);
	put_message(MSG_EAT, phi);
	pthread_mutex_lock(&phi->eat_mutex);
	phi->last_eat = get_time();
	pthread_mutex_unlock(&phi->eat_mutex);
	if (phi->meals_left > 0)
		phi->meals_left--;
	ft_usleep(phi->all->t_eat);
	pthread_mutex_unlock(phi->rf);
	pthread_mutex_unlock(&phi->lf);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	phi->last_eat = phi->start;
	if (phi->i % 2)
		ft_usleep(phi->all->t_eat);
	while (!phi->all->dead)
	{
		pthread_create(&phi->death_check, NULL, check_death, phi);
		philo_eat(phi);
		if (!phi->meals_left)
		{
			pthread_detach(phi->death_check);
			break ;
		}
		put_message(MSG_SLEEP, phi);
		ft_usleep(phi->all->t_sleep);
		put_message(MSG_THINK, phi);
		pthread_detach(phi->death_check);
	}
	return (NULL);
}
