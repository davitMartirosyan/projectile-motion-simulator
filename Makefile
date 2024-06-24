CLI_NAME = cli
SRV_NAME = srv

CC = gcc
CFLAGS = -std=c99 -Ilib -Imlx #-g -fsanitize=address -Wall -Wextra -Werror

CLI_SRC = $(wildcard src/client/*.c)
SRV_SRC = $(wildcard src/server/*.c)

CLI_OBJ = $(CLI_SRC:.c=.o)
SRV_OBJ = $(SRV_SRC:.c=.o)

ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lreadline
    INSTALL_DEPENDENCIES =
else
    LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lreadline
    INSTALL_DEPENDENCIES = \
        sudo apt-get update && \
        sudo apt-get install -y libx11-dev libxext-dev libreadline-dev
endif

all: $(CLI_NAME) $(SRV_NAME)

$(CLI_NAME): $(CLI_OBJ)
	$(CC) $(CLI_OBJ) $(CFLAGS) $(LDFLAGS) -o $(CLI_NAME) -lm

$(SRV_NAME): $(SRV_OBJ)
	$(CC) $(SRV_OBJ) $(CFLAGS) -o $(SRV_NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLI_OBJ) $(SRV_OBJ)

fclean: clean
	rm -f $(CLI_NAME) $(SRV_NAME)

re: fclean all

git:
	@echo "Enter Commit: "
	@read message; \
	git add . && git commit -m "$$message" && git push

.PHONY: all clean fclean re
