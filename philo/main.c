/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:22:14 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/09 10:00:53 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *phi)
{
	pthread_mutex_lock(&phi->all->death_mutex);
	phi->all->dead = 1;
	put_message(MSG_DIE, phi);
	pthread_mutex_unlock(&phi->all->death_mutex);
}

void	*check_death(void *arg)
{
	t_philo *phi;

	phi = (t_philo *)arg;
	while (!phi->all->dead)
		if (!phi->eating)
			if (get_time() - phi->last_eat >= phi->all->t_die)
				die(phi);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*phi;
	pthread_t		death_check;

	phi = (t_philo *)arg;
	if (phi->i % 2)
		ft_usleep(phi->all->t_eat / 10);
	pthread_create(&death_check, NULL, check_death, phi);
	while (!phi->all->dead)
	{
		pthread_mutex_lock(phi->rf);
		put_message(MSG_FORK, phi);
		pthread_mutex_lock(&phi->lf);
		put_message(MSG_FORK, phi);
		put_message(MSG_EAT, phi);
		phi->eating = 1;
		ft_usleep(phi->all->t_eat);
		phi->last_eat = get_time();
		phi->eating = 0;
		pthread_mutex_unlock(&phi->lf);
		pthread_mutex_unlock(phi->rf);
		put_message(MSG_SLEEP, phi);
		ft_usleep(phi->all->t_sleep);
		put_message(MSG_THINK, phi);
	}
	return (NULL);
}

void	init_philos(t_common *all)
{
	t_philo	**phi;
	int		i;

	phi = malloc(all->n_philo * sizeof(t_philo *));
	i = -1;
	while (++i < all->n_philo)
	{
		phi[i] = malloc(sizeof(t_philo));
		phi[i]->all = all;
		phi[i]->i = i;
		phi[i]->eating = 0;
		pthread_mutex_init(&phi[i]->lf, NULL);
	}
	i = -1;
	while (++i < all->n_philo)
	{
		if (i == all->n_philo - 1)
			phi[i]->rf = &phi[0]->lf;
		else
			phi[i]->rf = &phi[i + 1]->lf;
	}
	all->start = get_time();
	i = -1;
	while (++i < all->n_philo)
		phi[i]->last_eat = all->start;
	i = -1;
	while (++i < all->n_philo)
		pthread_create(&phi[i]->brain, NULL, routine, phi[i]);
	i = -1;
	while (++i < all->n_philo)
		pthread_join(phi[i]->brain, NULL);
}

int	main(int ac, char **av)
{
	t_common	all;

	if (ac < 5 || ac > 6)
		return (1);
	all.n_philo = ft_atol(av[1]);
	all.t_die = ft_atol(av[2]);
	all.t_eat = ft_atol(av[3]);
	all.t_sleep = ft_atol(av[4]);
	if (ac == 6)
		all.n_eat = ft_atol(av[5]);
	all.dead = 0;
	pthread_mutex_init(&all.write_mutex, NULL);
	pthread_mutex_init(&all.death_mutex, NULL);
	init_philos(&all);
}
