##
## EPITECH PROJECT, 2024
## B-CPE-110-NAN-1-1-my_radar-lukas.renaud
## File description:
## Makefile
##

SRC = $(shell cat src.list)

OBJ = $(SRC:.c=.o)

T_SRC = $(shell cat tests_src.list)

T_SRC += $(filter-out src/main.c, $(SRC))

HFILE = shell.h

HFILE_PATH = ./include/

CFLAGS = -Wall -Wextra

CRITERION = -lcriterion -lgcov --coverage -fprofile-arcs -ftest-coverage

BINARY = 42sh

T_BINARY = unit_tests

all: $(BINARY)

$(BINARY): $(OBJ)
	@echo "🛠️  [BUILD] Compilation du binaire..."
	@gcc $(SRC) -o $(BINARY) -I $(HFILE_PATH) $(CFLAGS) -g
	@echo "✅  Compilation réussie ! 🎯"

%.o: %.c
	@gcc -c $< -o $@ -I $(HFILE_PATH) $(CFLAGS)

tests_run:	fclean $(OBJ) $(LIBMY) create_cover
	@echo "🔁 Running tests..."
	gcc -o $(T_BINARY) $(T_SRC) -I $(HFILE_PATH) $(CFLAGS) $(CRITERION)
	./$(T_BINARY)
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches
	gcovr --exclude tests/ --html-details gcovr/coverage.html
	@echo "✅ Tests run."

create_cover:
	mkdir -p gcovr

clean:
	@echo "🛠️  [BUILD] Nettoyage des fichiers objets..."
	@rm -f $(OBJ)
	@echo "✅  Nettoyage terminé."

fclean: clean
	@echo "🛠️  [BUILD] Nettoyage complet..."
	@rm -f $(BINARY)
	@rm -f $(T_BINARY)
	@rm -f *.gcov
	@rm -f *.gcno
	@rm -f *.gcda
	@echo "✅  Nettoyage complet effectué."

re: fclean all
