NAME = fdf
NAME_BONUS = fdf_bonus

SRC_DIR = mandatory
BONUS_DIR = bonus

SRC = $(SRC_DIR)/fdf.c $(SRC_DIR)/ft_free.c $(SRC_DIR)/get_list.c $(SRC_DIR)/check_and_fix.c $(SRC_DIR)/get_next_line.c \
      $(SRC_DIR)/get_next_line_utils.c $(SRC_DIR)/the_map.c $(SRC_DIR)/get_pts_infos.c $(SRC_DIR)/map_utils.c $(SRC_DIR)/put_pixels.c \
      $(SRC_DIR)/trgb_colors.c $(SRC_DIR)/colors.c $(SRC_DIR)/hundle_hooks.c $(SRC_DIR)/rotation.c

BNS = $(BONUS_DIR)/the_map_bonus.c $(BONUS_DIR)/check_and_fix_bonus.c $(BONUS_DIR)/get_next_line_bonus.c \
      $(BONUS_DIR)/get_next_line_utils_bonus.c $(BONUS_DIR)/get_pts_infos_bonus.c \
      $(BONUS_DIR)/ft_free_bonus.c $(BONUS_DIR)/fdf_bonus.c $(BONUS_DIR)/get_list_bonus.c $(BONUS_DIR)/map_utils_bonus.c $(BONUS_DIR)/map_utils2_bonus.c \
      $(BONUS_DIR)/rotation_bonus.c $(BONUS_DIR)/put_pixels_bonus.c $(BONUS_DIR)/trgb_colors_bonus.c $(BONUS_DIR)/colors_bonus.c \
      $(BONUS_DIR)/hundler_bonus.c $(BONUS_DIR)/zoom_translate_bonus.c $(BONUS_DIR)/map_utils3_bonus.c $(BONUS_DIR)/map_utils4_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BNS = $(BNS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
PIXELS1 = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(PIXELS1) -o $@

$(NAME_BONUS): $(OBJ_BNS)
	$(CC) $(OBJ_BNS) $(PIXELS1) -o $(NAME_BONUS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BNS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all