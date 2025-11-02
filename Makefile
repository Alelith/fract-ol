NAME = fractol

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

INCLUDES = include/
CC = cc -Wall -Wextra -Werror
CFLAGS = -lm -lpthread -lSDL2

LIBS_DIR = lib/
PRINTF_DIR = $(LIBS_DIR)survival_lib/
PRINTF = $(PRINTF_DIR)survivalib.a

SRC_DIR = src/
OBJ_DIR = obj/

MAIN = main

COMPLEX_DIR = complex/
COMPLEX = complex_operations complex_trigonometric

FRACTALS_DIR = fractals/
FRACTALS = fractal_render julia mandelbrot sinh_mandelbrot eye_mandelbrot dragon_mandelbrot

UTILS_DIR = utils/
UTILS = color handlers img_manag string

SRC_FILES += main
SRC_FILES += $(addprefix $(COMPLEX_DIR), $(COMPLEX))
SRC_FILES += $(addprefix $(FRACTALS_DIR), $(FRACTALS))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS))

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJSF = .cache_exists

all: $(NAME)

$(NAME): $(PRINTF) $(OBJS)
	@$(CC) $(OBJS) $(PRINTF) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)Fractol compiled!$(DEF_COLOR)"

$(PRINTF):
	@echo "$(YELLOW)Making printf...$(DEF_COLOR)"
	@make -sC $(PRINTF_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJSF)
	@echo "$(CYAN)Compiling: $<$(DEF_COLOR)"
	@$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)
	
$(OBJSF):
	@echo "$(MAGENTA)Creating dirs$(DEF_COLOR)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(COMPLEX_DIR)
	@mkdir -p $(OBJ_DIR)$(FRACTALS_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)

bonus : all

clean:
	@echo "$(RED)Removing .o object files...$(DEF_COLOR)"
	@rm -rf $(OBJ_DIR)
	@make fclean -sC $(PRINTF_DIR)

fclean: clean
	@echo "$(RED)Removing fractol...$(DEF_COLOR)"
	@rm -f $(NAME)

re: clean all