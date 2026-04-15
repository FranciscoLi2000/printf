# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yourname <yourname@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/15 00:00:00 by yourname          #+#    #+#              #
#    Updated: 2026/04/15 00:00:00 by yourname         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -rf

INCLUDES	= -I./includes

SRC_DIR		= src
BONUS_DIR	= bonus
OBJ_DIR		= obj
BONUS_OBJ_DIR	= obj_bonus

SRC_FILES	= ft_printf.c \
			  ft_printf_chars.c \
			  ft_printf_nbr.c \
			  ft_printf_hex.c

BONUS_FILES	= ft_printf_bonus.c \
			  ft_printf_parse_bonus.c \
			  ft_printf_utils_bonus.c \
			  ft_printf_chars_bonus.c \
			  ft_printf_nbr_bonus.c \
			  ft_printf_hex_bonus.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

BONUS_SRC	= $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
BONUS_OBJ	= $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Built $(NAME) (mandatory)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/ft_printf.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(BONUS_OBJ_DIR) $(BONUS_OBJ)
	@$(AR) $(NAME) $(BONUS_OBJ)
	@echo "Built $(NAME) (bonus)"

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c includes/ft_printf_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "Cleaned object files"

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleaned library"

re: fclean all

test: all
	@$(CC) $(CFLAGS) $(INCLUDES) tests/main.c -L. -lftprintf -o test_printf
	@echo "Test binary built: ./test_printf"

test_bonus: bonus
	@$(CC) $(CFLAGS) $(INCLUDES) tests/main.c -L. -lftprintf -o test_printf
	@echo "Test binary (bonus) built: ./test_printf"

.PHONY: all clean fclean re bonus test test_bonus
