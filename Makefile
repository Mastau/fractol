NAME = fractol
CC = cc
LIBFT = lib/libft/libft.so
MLX = lib/MacroLibX/libmlx.so
FLAGS = -Werror -Wall -Wextra -g
DIROBJS = .objs
OBJS = $(SRCS:%.c=$(DIROBJS)/%.o)
HEADER = -I lib/libft -I lib/MacroLibX/includes -I includes/
SRCS = src/fractol.c \
	   src/parsing.c \
	   src/mandel.c \
	   src/julia.c \

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -lSDL2 $(HEADER) -o $@
$(DIROBJS)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADER) $< -c -o $@
$(LIBFT):
	make -C lib/libft/ 
$(MLX):
	make -C lib/MacroLibX/ -j
clean:
	@rm -rf $(DIROBJS)
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
