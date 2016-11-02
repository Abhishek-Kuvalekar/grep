/*****************************************************************************
 * Copyright (C) Kuvalekar Abhishek Vijay kuvalekarav15.it@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
 
#ifndef __GREP_H
#define __GREP_H

/*MACRO definitions*/
#define ON 1
#define OFF 0
#define invert 1
#define only_matching 2
#define ANSI_COLOR_BOLDRED "\033[1m\033[31m"
#define ANSI_COLOR_RESET "\x1B[0m"
#define ANSI_COLOR_GREEN "\x1B[32m"
#define ANSI_COLOR_BLUE "\x1B[35m"
#define normal 0
#define inverse 1

/*Structure definitions*/
typedef struct set_option {
	int print_line_number;
	int print_file_name;
	int case_insensitive;
	int print_max_lines;
	int normal_grep;
	int line_grep;
	int word_grep;
	int skip;
	int max_lines;
	int recurse;
	int print_help;
	char *file_name;
	char *dir_name[16];
	char directory[1000];
	int row, column, temp;
}set_option;
typedef struct counter {
	int options;
	int files;
	int other;
	int directories;
}counter;
typedef struct input {
	char **option, **file;
	char *pattern;
	int file_count;
}input;

/*Prototypes of functions.*/
void count_function(int, char **);
int readline(char *, char *);
int get_file_type(char *);
void method_select(int, char **);
void option_select(input *);
void option_file_sort(int, char **);
int check_allocated(int *, int);
void print_help(void);
void recursive_grep(char *);
int substring(char *, char *);
int normal_grep(char *, char *, int);
void count_line(void);
void max_lines(void);
int matching_lines(char *, char *, int);
int print_word_grep(char *, char *, int);
int file_with_match(char *, char *, int);
int file_without_match(char *, char *, int);
void print_result(void);

/*Global declarations.*/
set_option *set;
counter *c;
input *ip;
int line_count;
int temp_number;
int init_print_result;
int choice;
int max; 

#endif
