OBJ_DIR := obj/

NAME = philo

src := main.c utils.c
obj := $(src:%.c=$(OBJ_DIR)%.o)

CC = cc
FLAGS = -g3 -O0
CFLAGS =

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

$(NAME): $(obj)
	$(CC) $(FLAGS) $^ -o $@

helgrind: all
	valgrind --tool=helgrind ./$(NAME)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 50 300 200 200

clean:
	rm -rf $(OBJ_DIR)

gdb: $(NAME)
	gdb --tui ./$(NAME)

fclean: clean
	rm -f $(NAME)
	@echo "\033[36m[✓] \033[1m\033[1m$(NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re helgrind valgrind gdb
