#include "../includes/push_swap.h"
#include <fcntl.h>

static int	exec_op(char *op, t_stack *a, t_stack *b)
{
	if (op[0] == '\0')
		return (1);
	if (ft_strncmp(op, "ss", 3) == 0)
		return (ss(a, b, NULL));
	if (ft_strncmp(op, "sa", 3) == 0)
		return (sa(a, NULL));
	if (ft_strncmp(op, "sb", 3) == 0)
		return (sb(b, NULL));
	if (ft_strncmp(op, "pa", 3) == 0)
		return (pa(a, b, NULL));
	if (ft_strncmp(op, "pb", 3) == 0)
		return (pb(a, b, NULL));
	if (op[0] == 'r' && op[1] == 'r' && op[2] == '\0')
		return (rr(a, b, NULL));
	if (ft_strncmp(op, "rrr", 4) == 0)
		return (rrr(a, b, NULL));
	if (ft_strncmp(op, "rra", 4) == 0)
		return (rra(a, NULL));
	if (ft_strncmp(op, "rrb", 4) == 0)
		return (rrb(b, NULL));
	if (ft_strncmp(op, "ra", 3) == 0)
		return (ra(a, NULL));
	if (ft_strncmp(op, "rb", 3) == 0)
		return (rb(b, NULL));
	return (0);
}

static char	*read_line(int *eof)
{
	char	*line;
	char	*tmp;
	char	buf[2];
	int		len;
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	len = 0;
	buf[1] = '\0';
	while (1)
	{
		ret = read(0, buf, 1);
		if (ret <= 0)
			break ;
		if (buf[0] == '\n')
			break ;
		tmp = ft_strjoin(line, buf);
		free(line);
		line = tmp;
		if (!line)
			return (NULL);
		len++;
	}
	if (ret <= 0 && len == 0)
	{
		*eof = 1;
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*op;
	int		arg_start;
	int		eof;
	int		stdout_fd;
	int		devnull;

	if (argc < 2)
		return (0);
	arg_start = 1;
	a = parse_args(argc, argv, &arg_start);
	if (!a)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	b = create_stack();
	if (!b)
	{
		free_stack(a);
		write(2, "Error\n", 6);
		return (1);
	}
	stdout_fd = dup(1);
	devnull = open("/dev/null", O_WRONLY);
	dup2(devnull, 1);
	close(devnull);
	eof = 0;
	while (!eof)
	{
		op = read_line(&eof);
		if (!op)
			break ;
		if (!exec_op(op, a, b))
		{
			free(op);
			free_stack(a);
			free_stack(b);
			dup2(stdout_fd, 1);
			close(stdout_fd);
			write(2, "Error\n", 6);
			return (1);
		}
		free(op);
	}
	dup2(stdout_fd, 1);
	close(stdout_fd);
	if (is_sorted(a) && b->size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(a);
	free_stack(b);
	return (0);
}
