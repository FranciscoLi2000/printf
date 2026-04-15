/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int	g_pass = 0;
static int	g_fail = 0;

static void	check(int r1, int r2, const char *label)
{
	if (r1 == r2)
	{
		printf("  [PASS] %s (ret=%d)\n", label, r1);
		g_pass++;
	}
	else
	{
		printf("  [FAIL] %s printf=%d ft_printf=%d\n", label, r1, r2);
		g_fail++;
	}
}

static void	test_mandatory(void)
{
	int	r1;
	int	r2;
	int	x;

	printf("\n=== MANDATORY TESTS ===\n\n");

	printf("--- %%c ---\n");
	r1 = printf("[%c]\n", 'A');
	r2 = ft_printf("[%c]\n", 'A');
	check(r1, r2, "%c basic");

	r1 = printf("[%c]\n", 0);
	r2 = ft_printf("[%c]\n", 0);
	check(r1, r2, "%c nul char");

	printf("\n--- %%%% ---\n");
	r1 = printf("100%%\n");
	r2 = ft_printf("100%%\n");
	check(r1, r2, "%% percent");

	printf("\n--- %%s ---\n");
	r1 = printf("[%s]\n", "hello");
	r2 = ft_printf("[%s]\n", "hello");
	check(r1, r2, "%s basic");

	r1 = printf("[%s]\n", "");
	r2 = ft_printf("[%s]\n", "");
	check(r1, r2, "%s empty");

	{
		char	*null_s = NULL;
		r1 = printf("[%s]\n", null_s);
		r2 = ft_printf("[%s]\n", null_s);
		check(r1, r2, "%s NULL");
	}

	printf("\n--- %%d/%%i ---\n");
	r1 = printf("[%d]\n", 42);
	r2 = ft_printf("[%d]\n", 42);
	check(r1, r2, "%d positive");

	r1 = printf("[%d]\n", -42);
	r2 = ft_printf("[%d]\n", -42);
	check(r1, r2, "%d negative");

	r1 = printf("[%d]\n", 0);
	r2 = ft_printf("[%d]\n", 0);
	check(r1, r2, "%d zero");

	r1 = printf("[%d]\n", INT_MAX);
	r2 = ft_printf("[%d]\n", INT_MAX);
	check(r1, r2, "%d INT_MAX");

	r1 = printf("[%d]\n", INT_MIN);
	r2 = ft_printf("[%d]\n", INT_MIN);
	check(r1, r2, "%d INT_MIN");

	r1 = printf("[%i]\n", -12345);
	r2 = ft_printf("[%i]\n", -12345);
	check(r1, r2, "%i signed");

	printf("\n--- %%u ---\n");
	r1 = printf("[%u]\n", 42u);
	r2 = ft_printf("[%u]\n", 42u);
	check(r1, r2, "%u basic");

	r1 = printf("[%u]\n", 0u);
	r2 = ft_printf("[%u]\n", 0u);
	check(r1, r2, "%u zero");

	r1 = printf("[%u]\n", UINT_MAX);
	r2 = ft_printf("[%u]\n", UINT_MAX);
	check(r1, r2, "%u UINT_MAX");

	printf("\n--- %%x/%%X ---\n");
	r1 = printf("[%x]\n", 255);
	r2 = ft_printf("[%x]\n", 255);
	check(r1, r2, "%x lowercase");

	r1 = printf("[%X]\n", 255);
	r2 = ft_printf("[%X]\n", 255);
	check(r1, r2, "%X uppercase");

	r1 = printf("[%x]\n", 0);
	r2 = ft_printf("[%x]\n", 0);
	check(r1, r2, "%x zero");

	r1 = printf("[%x]\n", UINT_MAX);
	r2 = ft_printf("[%x]\n", UINT_MAX);
	check(r1, r2, "%x UINT_MAX");

	printf("\n--- %%p ---\n");
	x = 42;
	r1 = printf("[%p]\n", (void *)&x);
	r2 = ft_printf("[%p]\n", (void *)&x);
	check(r1, r2, "%p address");

	r1 = printf("[%p]\n", (void *)NULL);
	r2 = ft_printf("[%p]\n", (void *)NULL);
	check(r1, r2, "%p NULL");

	printf("\n--- Mixed ---\n");
	r1 = printf("%c%s%d%i%u%x%X%p%%\n",
		'A', "ok", -1, 2, 3u, 255, 255, (void *)&x);
	r2 = ft_printf("%c%s%d%i%u%x%X%p%%\n",
		'A', "ok", -1, 2, 3u, 255, 255, (void *)&x);
	check(r1, r2, "all specifiers mixed");
}

static void	test_bonus(void)
{
	int	r1;
	int	r2;

	printf("\n=== BONUS TESTS ===\n\n");

	printf("--- Width (right-align) ---\n");
	r1 = printf("[%5d]\n", 42);
	r2 = ft_printf("[%5d]\n", 42);
	check(r1, r2, "width right-align pos");

	r1 = printf("[%5d]\n", -42);
	r2 = ft_printf("[%5d]\n", -42);
	check(r1, r2, "width right-align neg");

	r1 = printf("[%5s]\n", "hi");
	r2 = ft_printf("[%5s]\n", "hi");
	check(r1, r2, "width string right");

	printf("\n--- Width (left-align -) ---\n");
	r1 = printf("[%-5d]\n", 42);
	r2 = ft_printf("[%-5d]\n", 42);
	check(r1, r2, "width left-align");

	r1 = printf("[%-5s]\n", "hi");
	r2 = ft_printf("[%-5s]\n", "hi");
	check(r1, r2, "width string left");

	printf("\n--- Zero-padding (0) ---\n");
	r1 = printf("[%05d]\n", 42);
	r2 = ft_printf("[%05d]\n", 42);
	check(r1, r2, "zero-pad positive");

	r1 = printf("[%05d]\n", -42);
	r2 = ft_printf("[%05d]\n", -42);
	check(r1, r2, "zero-pad negative");

	r1 = printf("[%05u]\n", 42u);
	r2 = ft_printf("[%05u]\n", 42u);
	check(r1, r2, "zero-pad unsigned");

	r1 = printf("[%05x]\n", 255);
	r2 = ft_printf("[%05x]\n", 255);
	check(r1, r2, "zero-pad hex");

	printf("\n--- Precision ---\n");
	r1 = printf("[%.5d]\n", 42);
	r2 = ft_printf("[%.5d]\n", 42);
	check(r1, r2, "precision int");

	r1 = printf("[%.0d]\n", 0);
	r2 = ft_printf("[%.0d]\n", 0);
	check(r1, r2, "precision 0 value 0");

	r1 = printf("[%.5s]\n", "hello world");
	r2 = ft_printf("[%.5s]\n", "hello world");
	check(r1, r2, "precision string truncate");

	r1 = printf("[%.0s]\n", "hello");
	r2 = ft_printf("[%.0s]\n", "hello");
	check(r1, r2, "precision 0 string");

	printf("\n--- Width + Precision ---\n");
	r1 = printf("[%8.3d]\n", 42);
	r2 = ft_printf("[%8.3d]\n", 42);
	check(r1, r2, "width+precision int");

	r1 = printf("[%-8.3d]\n", 42);
	r2 = ft_printf("[%-8.3d]\n", 42);
	check(r1, r2, "width+precision left");

	r1 = printf("[%8.3s]\n", "hello");
	r2 = ft_printf("[%8.3s]\n", "hello");
	check(r1, r2, "width+precision string");

	printf("\n--- # flag ---\n");
	r1 = printf("[%#x]\n", 255);
	r2 = ft_printf("[%#x]\n", 255);
	check(r1, r2, "#x prefix");

	r1 = printf("[%#X]\n", 255);
	r2 = ft_printf("[%#X]\n", 255);
	check(r1, r2, "#X prefix");

	r1 = printf("[%#x]\n", 0);
	r2 = ft_printf("[%#x]\n", 0);
	check(r1, r2, "#x zero (no prefix)");

	printf("\n--- Space flag ---\n");
	r1 = printf("[% d]\n", 42);
	r2 = ft_printf("[% d]\n", 42);
	check(r1, r2, "space positive");

	r1 = printf("[% d]\n", -42);
	r2 = ft_printf("[% d]\n", -42);
	check(r1, r2, "space negative (no space)");

	printf("\n--- Flag combinations ---\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
	r1 = printf("[%05.3d]\n", 42);
#pragma GCC diagnostic pop
	r2 = ft_printf("[%05.3d]\n", 42);
	check(r1, r2, "0-pad ignored with precision");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
	r1 = printf("[%-05d]\n", 42);
#pragma GCC diagnostic pop
	r2 = ft_printf("[%-05d]\n", 42);
	check(r1, r2, "left-align overrides 0-pad");

	r1 = printf("[%#010x]\n", 255);
	r2 = ft_printf("[%#010x]\n", 255);
	check(r1, r2, "#x with width and 0-pad");

	r1 = printf("[% 8d]\n", 42);
	r2 = ft_printf("[% 8d]\n", 42);
	check(r1, r2, "space with width");

	printf("\n--- Char width ---\n");
	r1 = printf("[%5c]\n", 'A');
	r2 = ft_printf("[%5c]\n", 'A');
	check(r1, r2, "char with width right");

	r1 = printf("[%-5c]\n", 'A');
	r2 = ft_printf("[%-5c]\n", 'A');
	check(r1, r2, "char with width left");
}

int	main(void)
{
	test_mandatory();
	test_bonus();
	printf("\n=== RESULTS: %d PASS, %d FAIL ===\n\n", g_pass, g_fail);
	if (g_fail > 0)
		return (1);
	return (0);
}
