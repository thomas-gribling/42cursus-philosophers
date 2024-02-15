/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:22:14 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/15 08:35:45 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_puterror(char *s, int format)
{
	int	i;

	i = -1;
	if (format)
		write(2, "Error: ", 7);
	while (s[++i])
		write(2, &s[i], 1);
	if (format)
		write(2, "\n", 1);
	return (1);
}

int	put_errors(t_common *all, int ac)
{
	if (all->n_philo <= 0 || all->n_philo > 200)
		return (ft_puterror("Invalid philos amount. (1 - 200)", 1));
	if (all->t_die < 60 || all->t_eat < 60 || all->t_sleep < 60)
		return (ft_puterror("All times must be at least 60ms.", 1));
	if (ac == 6 && all->n_eat < 1)
		return (ft_puterror("The amount of meals must be at leat 1.", 1));
	return (0);
}

int	check_max_int(char *s)
{
	if (ft_strlen(s) > 10)
		return (1);
	if (ft_strlen(s) < 10)
		return (0);
	if (s[0] >= '2' && s[1] >= '1' && s[2] >= '4')
		if (s[3] >= '7' && s[4] >= '4' && s[5] >= '8')
			if (s[6] >= '3' && s[7] >= '6' && s[8] >= '4')
				if (s[9] > '7')
					return (1);
	return (0);
}

int	check_args(int ac, char **av, t_common *all)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_num(av[i]))
			return (ft_puterror("Invalid characters.", 1), 1);
		if (check_max_int(av[i]))
			return (ft_puterror("Value beyond max int.", 1), 1);
	}
	all->n_philo = ft_atol(av[1]);
	all->t_die = ft_atol(av[2]);
	all->t_eat = ft_atol(av[3]);
	all->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		all->n_eat = ft_atol(av[5]);
	else
		all->n_eat = -1;
	return (put_errors(all, ac));
}

int	main(int ac, char **av)
{
	t_common	all;

	if (ac < 5 || ac > 6)
	{
		ft_puterror("Arguments:\n- number_of_philos\n- time_to_die\n", 0);
		ft_puterror("- time_to_eat\n- time_to_sleep\n", 0);
		ft_puterror("- number_of_meals (optional)\n", 0);
		return (1);
	}
	if (check_args(ac, av, &all))
		return (1);
	all.dead = 0;
	printf(" ___________________________________\n");
	printf("|__TIME___ID______ACTION____________|\n");
	if (all.n_philo == 1)
	{
		put_msg_quick(MSG_FORK, 0, 0);
		ft_usleep(all.t_die);
		put_msg_quick(MSG_DIE, all.t_die, 0);
		return (printf("|___________________________________|\n"), 0);
	}
	pthread_mutex_init(&all.write_mutex, NULL);
	pthread_mutex_init(&all.death_mutex, NULL);
	init_philos(&all);
	return (printf("|___________________________________|\n"), 0);
}
