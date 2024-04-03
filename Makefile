OBJ_DIR := obj/

NAME = philo

src := main.c utils.c check_args.c threads.c
obj := $(src:%.c=$(OBJ_DIR)%.o)

CC = cc
FLAGS = -g3 -O0 -pthread
CFLAGS =

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

$(NAME): $(obj)
	$(CC) $(FLAGS) $^ -o $@

helgrind: all
	clear; valgrind --tool=helgrind ./$(NAME) 4 310 200 100

test1: all
	./$(NAME) 1 800 200 200

test2: all
	clear; ./$(NAME) 4 800 200 200

test3: all
	./$(NAME) 4 410 200 200

test4: all
	clear; ./$(NAME) 4 310 200 100

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 50 300 200 200

clean:
	rm -rf $(OBJ_DIR)

gdb: $(NAME)
	gdb --tui --args ./$(NAME) 5 800 200 200

fclean: clean
	rm -f $(NAME)
	@echo "\033[36m[✓] \033[1m\033[1m$(NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re helgrind valgrind gdb
