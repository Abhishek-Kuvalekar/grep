#ifndef __GREP_H
#define __GREP_H
#define ON 1
#define OFF 0
typedef struct set_option {
	int print_line_number;
	int print_file_name;
	int case_insensitive;
	int print_max_lines;
	int max_lines;
	char *file_name;
}set_option;
void count_function(int, char **);
int readline(char *, char *);
char get_file_type(char *);
int substring(char *, char *);
void normal_grep(char *, char *);
void count_line(char *, char *, int, int);
void inverse_grep(char *, char *);
void only_matching_grep(char *, char *);
void print_line_number(char *, char *, int, int);
void matching_lines(char *, char *);
void print_word_grep(char *, char *);
set_option *set;
int line_count;
#endif
