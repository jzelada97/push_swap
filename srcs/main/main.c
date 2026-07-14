#include "push_swap.h"

static void	error_exit(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}

static int	set_flag(char *arg, int *strategy, int *bench, int *strategy_set)
{
	if (ft_strncmp(arg, "--simple", 9) == 0)
	{
		if (*strategy_set)
			return (0);
		*strategy = FLAG_SIMPLE;
		*strategy_set = 1;
	}
	else if (ft_strncmp(arg, "--medium", 9) == 0)
	{
		if (*strategy_set)
			return (0);
		*strategy = FLAG_MEDIUM;
		*strategy_set = 1;
	}
	else if (ft_strncmp(arg, "--complex", 10) == 0)
	{
		if (*strategy_set)
			return (0);
		*strategy = FLAG_COMPLEX;
		*strategy_set = 1;
	}
	else if (ft_strncmp(arg, "--adaptive", 11) == 0)
	{
		if (*strategy_set)
			return (0);
		*strategy_set = 1;
	}
	else if (ft_strncmp(arg, "--bench", 8) == 0)
		*bench = 1;
	else
		return (0);
	return (1);
}

static int	parse_flags(int argc, char **argv, int *strategy, int *bench)
{
	int	i;
	int	strategy_set;

	*strategy = FLAG_ADAPTIVE;
	*bench = 0;
	strategy_set = 0;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			break ;
		if (argv[i][1] != '-')
			break ;
		if (!set_flag(argv[i], strategy, bench, &strategy_set))
			return (-1);
		i++;
	}
	return (i);
}

static void	run_strategy(t_stack *a, t_stack *b, int strategy, t_bench *bench)
{
	if (strategy == FLAG_SIMPLE)
	{
		bench->strategy_name = "simple";
		bench->complexity = "O(n^2)";
		sort_simple(a, b, &bench->ops);
	}
	else if (strategy == FLAG_MEDIUM)
	{
		bench->strategy_name = "medium";
		bench->complexity = "O(n*sqrt(n))";
		sort_medium(a, b, &bench->ops);
	}
	else if (strategy == FLAG_COMPLEX)
	{
		bench->strategy_name = "complex";
		bench->complexity = "O(n*log(n))";
		sort_complex(a, b, &bench->ops);
	}
	else
		sort_adaptive(a, b, bench);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	t_bench	bench;
	int		strategy;
	int		arg_start;

	if (argc < 2)
		return (0);
	arg_start = parse_flags(argc, argv, &strategy, &bench.enabled);
	if (arg_start == -1)
		error_exit(NULL, NULL);
	if (arg_start >= argc)
		return (0);
	a = parse_args(argc, argv, &arg_start);
	if (!a || a->size == 0)
		error_exit(a, NULL);
	if (!assign_indexes(a))
		error_exit(a, NULL);
	b = create_stack();
	if (!b)
		error_exit(a, NULL);
	bench.ops = (t_ops_count){0};
	bench.disorder = compute_disorder(a);
	run_strategy(a, b, strategy, &bench);
	if (bench.enabled)
		print_bench(&bench);
	free_stack(a);
	free_stack(b);
	return (0);
}
