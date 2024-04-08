OBJ_DIR := obj/

NAME = philo_bonus

src := big_brother_bonus.c check_args_bonus.c init_bonus.c main_bonus.c philosophers_bonus.c rotine_philo_bonus.c rotine_philo_utils_bonus.c utils_bonus.c
obj := $(src:%.c=$(OBJ_DIR)%.o)

CC = cc
FLAGS = 
CFLAGS =

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

$(NAME): $(obj)
	$(CC) $(FLAGS) $^ -o $@

helgrind: re
	 clear; valgrind --tool=helgrind ./$(NAME) 4 410 200 200

test1: re
	./$(NAME) 1 800 200 200

test2: re
	clear; ./$(NAME) 5 800 200 200

test3: re
	./$(NAME) 4 410 200 200

test4: re
	clear; ./$(NAME) 4 310 200 100

valgrind: re
	clear; valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 4 310 200 100

clean:
	rm -rf $(OBJ_DIR)

gdb: $(NAME)
	gdb --tui --args ./$(NAME) 5 800 200 200

fclean: clean
	rm -f $(NAME)
	@echo "\033[36m[✓] \033[1m\033[1m$(NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re helgrind valgrind gdb
