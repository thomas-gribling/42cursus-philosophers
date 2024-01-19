/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:21 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/19 11:17:00 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_vals(t_stats *st, int ac)
{
	int	state;

	state = 0;
	if (st->n_philos < 1)
		state = 1;
	if (st->t_die < 60 || st->t_eat < 60 || st->t_sleep < 60)
		state = 1;
	if (ac == 6 && st->n_eat < 0)
		state = 1;
	return (state);
}

int	check_args(t_stats *st, int ac, char **av)
{
	if (ac < 5)
		printf("Not enough arguments!\n");
	if (ac > 6)
		printf("Too much arguments!\n");
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	st->n_philos = ft_atol(av[1]);
	st->t_die = ft_atol(av[2]);
	st->t_eat = ft_atol(av[3]);
	st->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		st->n_eat = ft_atol(av[5]);
	else
		st->n_eat = -1;
	return (check_vals(st, ac));
}

int	main(int ac, char **av)
{
	t_stats	*st;

	st = malloc(sizeof(t_stats));
	if (check_args(st, ac, av))
		return (free(st), 1);
	printf("Philosophers: %li\n", st->n_philos);
	printf("Time to die: %li\n", st->t_die);
	printf("Time to eat: %li\n", st->t_eat);
	printf("Time to sleep: %li\n", st->t_sleep);
	printf("Number of eat needed: %li\n", st->n_eat);
	create_philos(st);
	return (free(st), 0);
}
