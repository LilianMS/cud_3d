# ****************************************************
#                     CONFIGURAÇÃO
# ****************************************************

NAME			= cub3D
NAME_BONUS		= cub3D_bonus

LIBS_FOLDER		= ./lib
LIBMLX			= $(LIBS_FOLDER)/MLX42
LIBFT			= $(LIBS_FOLDER)/libft

LIBFT_A			= $(LIBFT)/libft.a
MLX_A			= $(LIBMLX)/build/libmlx42.a

HEADERS			= ./includes/cub3d.h

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS_MLX		= -Wunreachable-code -Ofast
LFLAGS_MLX		= -ldl -lglfw -pthread -lm

LIBS			= $(MLX_A) $(LIBFT_A)

INCLUDES		= -Iincludes -I$(LIBMLX)/include -I$(LIBFT) -I$(LIBFT)/gnl/includes -I$(LIBFT)/ft_printf/includes

# ****************************************************
#                     FONTES
# ****************************************************

SRC = \
	src/main.c \
	src/mlx_utils.c \
	src/map/map.c \
	src/map/map_utils.c \
	src/map/map_utils_2.c \
	src/movement.c \
	src/wall.c \
	src/tools/utils.c \
	src/tools/utils_2.c \
	src/tools/clean.c \
	src/validation/validations.c \
	src/validation/validation_utils.c \
	src/validation/check_chars.c \
	src/validation/check_textures.c \
	src/validation/check_elements.c \
	src/validation/map_validation.c \
	src/validation/map_validation_utils.c \
	src/raycasting/ray.c \
	src/raycasting/render.c \
	src/raycasting/render_utils.c \

SRC_BONUS = \
	src/bonus/main_bonus.c \
	src/bonus/mlx_utils_bonus.c \
	src/bonus/mini_map/mini_map_bonus.c \
	src/bonus/mini_map/mini_map_utils_bonus.c \
	src/bonus/animation/animation_bonus.c \
	src/bonus/animation/animation_utils_bonus.c \
	src/bonus/clean_bonus.c \
	src/map/map.c \
	src/map/map_utils.c \
	src/map/map_utils_2.c \
	src/movement.c \
	src/wall.c \
	src/tools/utils.c \
	src/tools/utils_2.c \
	src/validation/validations.c \
	src/validation/validation_utils.c \
	src/validation/check_chars.c \
	src/validation/check_textures.c \
	src/validation/check_elements.c \
	src/validation/map_validation.c \
	src/validation/map_validation_utils.c \
	src/raycasting/ray.c \
	src/raycasting/render.c \
	src/raycasting/render_utils.c \

# ****************************************************
#                     OBJETOS
# ****************************************************

OBJS		= $(SRC:.c=.o)
OBJS_BONUS	= $(SRC_BONUS:.c=.o)

# ****************************************************
#                      REGRAS
# ****************************************************

all: libmlx libft $(NAME)
	@echo "✔️ Everything is up to date."

bonus: libmlx libft $(NAME_BONUS)

libmlx:
	@echo "Compiling graphical lib (MLX42)..."
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build --no-print-directory

libft: $(LIBFT_A)

$(LIBFT_A):
	@echo "Checking Libft..."
	@make -C $(LIBFT) --no-print-directory

$(NAME): $(OBJS)
	@echo "Creating binary $(NAME)"
	@$(CC) $(CFLAGS) $(CFLAGS_MLX) $(OBJS) $(LIBS) -o $(NAME) $(LFLAGS_MLX)

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "Creating binary $(NAME_BONUS)"
	@$(CC) $(CFLAGS) $(CFLAGS_MLX) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS) $(LFLAGS_MLX)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) $(CFLAGS_MLX) $(INCLUDES) -o $@ -c $< && echo "Compiling: $(notdir $<)"

# ****************************************************
#                    LIMPEZA
# ****************************************************

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C $(LIBFT) --no-print-directory
	@echo "Cleaning MLX build..."
	@rm -rf $(LIBMLX)/build
	@echo "Done."

fclean: clean
	@echo "Removing executables..."
	@rm -f $(NAME) $(NAME_BONUS)
	@make fclean -C $(LIBFT) --no-print-directory
	@echo "Done."

re: fclean all

# ****************************************************
#                  UTILITÁRIOS
# ****************************************************

run: all
	@./$(NAME) assets/map/minimalist_map.cub

val: all
	@valgrind --leak-check=full --suppressions=lib/MLX42/mlx42.supp --show-leak-kinds=all ./$(NAME) assets/map/minimalist_map.cub

# ****************************************************
#                     PHONY
# ****************************************************

.PHONY: all bonus libmlx libft clean fclean re run valgrind
