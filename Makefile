NAME = fractol

INCLUDES = includes/
MLXINCLUDES = libs/mlx/
CC = cc# -Wall -Wextra -Werror

SRC = src/main.c src/color_utils.c src/complex_utils.c src/mandelbrot_utils.c src/julia_utils.c src/atod.c

LIBS = libs/mlx/libmlx.a libs/printf/libftprintf.a

all: $(NAME)

$(NAME): $(LIBS)
	$(CC) -D H=1080 -D W=1920 -g $(SRC) $(LIBS) -I $(INCLUDES) -Llibs/mlx -lmlx -lX11 -lXext -lm -lz -o $(NAME)

$(LIBS):
	make -C libs/mlx/
	make -C libs/printf/

clean:
	make clean -C libs/mlx/
	make fclean -C libs/printf/
	rm -rf $(NAME)

re: clean all