/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef INCLUDED_GLOBBINGS_H
    #define INCLUDED_GLOBBINGS_H
    #include "ast.h"

typedef struct {
    char **array;
    int count;
    int capacity;
} string_array_t;

typedef struct {
    const char *base_dir;
    char **components;
    int comp_idx;
    int comp_count;
} pattern_ctx_t;

typedef struct {
    char **results;
    int count;
} expansion_result_t;

typedef struct {
    char **matches;
    int count;
} match_result_t;

typedef struct {
    char **argv;
    int index;
    string_array_t *result;
    int remaining_args;
} arg_context_t;

void globbings(ast_node_t *node);
int count_arguments(char **argv);
int process_single_argument(arg_context_t *ctx);
char **expand_arguments(char **argv, int *argc);
int process_token(string_array_t *components, char *token);
int add_copy_to_array(string_array_t *arr, const char *str);
char **resize_result_array(string_array_t *result, int match_count,
    int remaining_args);
int is_directory(const char *path);
char **get_directory(const char *dir_path, int *count);
int has_glob_chars(const char *str);
int match_directory_entries(char **dir_entries, int dir_count,
    pattern_ctx_t ctx, string_array_t *results);
match_result_t create_match_result(char **matches, int count);
match_result_t handle_no_matches(const char *arg);
int handle_glob_matches(match_result_t matches, arg_context_t *ctx);
char **handle_base_case(const char *base_dir, expansion_result_t
    *result);
int handle_terminal_component(char *new_path, string_array_t *results);
int handle_directory_entries(expansion_result_t *sub_result,
    string_array_t *results);
char **handle_non_glob_component(pattern_ctx_t ctx,
    expansion_result_t *result);
void init_string_array(string_array_t *arr, int initial_capacity);
void free_string_array_struct(string_array_t *array);
void init_string_results(string_array_t *results, int capacity);
char **init_pattern_expansion(const char *pattern, int *comp_count);
char *join_path(const char *dir, const char *file);
char **process_directory_component(char *new_path, pattern_ctx_t ctx,
    expansion_result_t *result);
int process_directory_entry(pattern_ctx_t ctx, char *entry_name,
    string_array_t *results);
char **process_glob_component(pattern_ctx_t ctx,
    expansion_result_t *result);
char **process_last_component(char *new_path, expansion_result_t
    *result);
char **create_empty_result(expansion_result_t *result);
void init_expansion_result(expansion_result_t *result);
int add_entries_to_results(string_array_t *results, char **entries,
    int count);
char **sort_and_clean_results(expansion_result_t *result,
    char **components);
char **get_files(const char *pattern, int *count);
void free_string_array(char **array);
int add_string_to_array(string_array_t *arr, char *str);
char **split_path(const char *path, int *count);
char **expand_pattern_recursive(pattern_ctx_t ctx, expansion_result_t
    *result);
int compare_strings(const void *a, const void *b);
pattern_ctx_t create_pattern_ctx(const char *base_dir, char **components
    , int comp_idx, int comp_count);



#endif
