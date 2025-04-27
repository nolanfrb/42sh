##
## EPITECH PROJECT, 2024
## 42sh
## File description:
## Makefile
##

SRC = $(shell cat src.list)
T_SRC = $(shell cat tests_src.list)
SRC_FOR_TESTS = $(shell cat src_for_tests.list)

OBJ = $(SRC:.c=.o)

HFILE_PATH = ./include/
CFLAGS = -Wall -Wextra -I$(HFILE_PATH)
CRITERION = -lcriterion --coverage -fprofile-arcs -ftest-coverage

BINARY = 42sh
T_BINARY = unit_tests

all: $(BINARY)

$(BINARY): $(OBJ)
	@echo "🛠️  [BUILD] Compilation du binaire..."
	@gcc $(SRC) -o $(BINARY) $(CFLAGS) -g
	@echo "✅ Compilation réussie ! 🎯"

%.o: %.c
	@gcc -c $< -o $@ $(CFLAGS)

tests_run: fclean create_cover
	@echo "🔁 Running tests..."
	@gcc -o $(T_BINARY) $(T_SRC) $(SRC_FOR_TESTS) \
		$(CFLAGS) $(CRITERION) -iquote .
	@./$(T_BINARY)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branches
	@gcovr --exclude tests/ --html-details gcovr/coverage.html
	@echo "✅ Tests run."

create_cover:
	mkdir -p gcovr

clean:
	@echo "🛠️  [BUILD] Nettoyage des fichiers objets..."
	@rm -f $(OBJ)
	@echo "✅ Nettoyage terminé."

fclean: clean
	@echo "🛠️  [BUILD] Nettoyage complet..."
	@rm -f $(BINARY)
	@rm -f $(T_BINARY)
	@rm -f *.gcov *.gcno *.gcda
	@echo "✅ Nettoyage complet effectué."


re: fclean all
