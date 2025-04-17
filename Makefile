# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

# Project structure
SRCS_DIR = src
BONUS_DIR = bonus
SRCS = $(wildcard $(SRCS_DIR)/*.c)
SRCS_BONUS = $(wildcard $(BONUS_DIR)/*_bonus.c)
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPENDS = $(OBJS:.o=.d)
DEPENDS_BONUS = $(OBJS_BONUS:.o=.d)
LIB = libftprintf.a

# Default rule (compile library)
all: $(LIB)

# Link library from object files
$(LIB): $(OBJS)
	ar rcs $@ $^

bonus: $(OBJS_BONUS)
	ar rcs $(LIB) $^

# Compile .c to .o with header dependencies
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

# Clean temporary files
clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(DEPENDS) $(DEPENDS_BONUS)

# Full clean (objects + library)
fclean: clean
	rm -f $(LIB)

# Rebuild from scratch
re: fclean all

# Include auto-generated dependencies
-include $(DEPENDS) $(DEPENDS_BONUS)

.PHONY: all clean fclean re bonus
