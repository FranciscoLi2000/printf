#!/bin/bash

# Test script for ft_printf mandatory part
# Place this in your project directory and make it executable with:
# chmod +x test_printf.sh

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compile your library
echo -e "${YELLOW}Compiling your ft_printf...${NC}"
make all

# Create a test program
echo -e "${YELLOW}Creating test program...${NC}"
cat << EOF > test_printf.c
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int	ft_printf(const char *format, ...);

int	main(void)
{
	int ft_ret, std_ret;
	int num = 42;
	int neg = -42;
	unsigned int unum = 42;
	char *str = "Hello World!";
	char *null_str = NULL;
	char ch = 'A';
	void *ptr = &num;

	printf("=== Testing mandatory conversions ===\n\n");

	/* Test %% */
	ft_ret = ft_printf("1. Your %%: [%%]\n");
	std_ret = printf("1. Std %%: [%%]\n");
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %c */
	ft_ret = ft_printf("2. Your c: [%c]\n", ch);
	std_ret = printf("2. Std c: [%c]\n", ch);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %s */
	ft_ret = ft_printf("3. Your s: [%s]\n", str);
	std_ret = printf("3. Std s: [%s]\n", str);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %s with NULL */
	ft_ret = ft_printf("4. Your s (NULL): [%s]\n", null_str);
	std_ret = printf("4. Std s (NULL): [%s]\n", null_str);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %p */
	ft_ret = ft_printf("5. Your p: [%p]\n", ptr);
	std_ret = printf("5. Std p: [%p]\n", ptr);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %d positive */
	ft_ret = ft_printf("6. Your d (+): [%d]\n", num);
	std_ret = printf("6. Std d (+): [%d]\n", num);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %d negative */
	ft_ret = ft_printf("7. Your d (-): [%d]\n", neg);
	std_ret = printf("7. Std d (-): [%d]\n", neg);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %i positive */
	ft_ret = ft_printf("8. Your i (+): [%i]\n", num);
	std_ret = printf("8. Std i (+): [%i]\n", num);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %i negative */
	ft_ret = ft_printf("9. Your i (-): [%i]\n", neg);
	std_ret = printf("9. Std i (-): [%i]\n", neg);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %u */
	ft_ret = ft_printf("10. Your u: [%u]\n", unum);
	std_ret = printf("10. Std u: [%u]\n", unum);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %x lowercase */
	ft_ret = ft_printf("11. Your x: [%x]\n", num);
	std_ret = printf("11. Std x: [%x]\n", num);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Test %X uppercase */
	ft_ret = ft_printf("12. Your X: [%X]\n", num);
	std_ret = printf("12. Std X: [%X]\n", num);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Edge cases */
	printf("\n=== Testing edge cases ===\n\n");

	/* Empty string */
	ft_ret = ft_printf("13. Your empty: []\n");
	std_ret = printf("13. Std empty: []\n");
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* INT_MAX and INT_MIN */
	ft_ret = ft_printf("14. Your INT_MAX: [%d]\n", INT_MAX);
	std_ret = printf("14. Std INT_MAX: [%d]\n", INT_MAX);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	ft_ret = ft_printf("15. Your INT_MIN: [%d]\n", INT_MIN);
	std_ret = printf("15. Std INT_MIN: [%d]\n", INT_MIN);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	/* Multiple formats */
	ft_ret = ft_printf("16. Your multi: [%d, %s, %x]\n", num, str, num);
	std_ret = printf("16. Std multi: [%d, %s, %x]\n", num, str, num);
	printf("Return: You: %d, Std: %d\n\n", ft_ret, std_ret);

	return 0;
}
EOF

# Compile the test program
echo -e "${YELLOW}Compiling test program...${NC}"
gcc -Wall -Wextra -Werror test_printf.c -L. -lftprintf -o test_printf

# Run the test program
echo -e "${YELLOW}Running tests...${NC}"
./test_printf

# Clean up
echo -e "${YELLOW}Cleaning up...${NC}"
rm -f test_printf test_printf.c

echo -e "${GREEN}Testing complete! Compare your output with standard printf output.${NC}"
