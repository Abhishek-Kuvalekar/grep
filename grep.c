#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "grep.h"
#define ANSI_COLOR_BOLDRED "\033[1m\033[31m"
#define ANSI_COLOR_RESET "\x1B[0m"
#define ANSI_COLOR_GREEN "\x1B[32m"
#define ANSI_COLOR_BLUE "\x1B[35m"
int position[1000];
int substring(char *str, char *pattern) {
	int i, j, k, l = 0, flag = 0, max, size_str, size_pattern, start_pos, end_pos, result = 0;
	size_str = strlen(str);
	size_pattern = strlen(pattern);
	max = size_str - size_pattern + 1;
	for(i = 0; i < 1000; i++) {
		position[i] = -1;
	}
	for(i = 0; i < max; i++) {
		flag = 0;
		for(j = i,k=0; j < (i + size_pattern); j++,k++) {
			if(set -> case_insensitive == OFF) {
				if(str[j] == pattern[k]) {
					flag++;
					if(j == i) {
						start_pos = j;
					}
					else if(j == (i + size_pattern - 1)) {
						end_pos = j;
					}
				}
				else {
					start_pos = end_pos = -1;
					flag = 0;
					break;
				}
			}
			else {
				if(str[j] == pattern[k] || str[j] == (pattern[k] - 32) || str[j] == (pattern[k] + 32)) {
					flag++;
					if(j == i) {
						start_pos = j;
					}
					else if(j == (i + size_pattern - 1)) {
						end_pos = j;
					}
				}
				else {
					start_pos = end_pos = -1;
					flag = 0;
					break;
				}
			}
		}
		if(flag == size_pattern) {
			position[l++] = start_pos;
			position[l++] = end_pos;
			start_pos = end_pos = -1; 
			result = 1;
		}
	}
	return result;
}
void normal_grep(char *str, char *pattern) {
	int result, i, j = 0, size_str;
	result = substring(str, pattern);
	size_str = strlen(str);
	if(result == 1) {
		if(set -> print_max_lines == ON) {
			(set -> max_lines)--;
		}
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			printf("%s%d:", ANSI_COLOR_GREEN, line_count);
		}
		for(i = 0; i < size_str; i++) {
			if(i >= position[j] && i <= position[j + 1]) {
				printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
				if(i == position[j + 1]) {
					j += 2;
				}
			}
			else {
				printf("%s%c", ANSI_COLOR_RESET, str[i]);
			}
		}	
	}
}
void count_line(char *str, char *pattern, int choice, int end) {
	int result;
	static int count = 0;
	if(choice == 0) {
		result = substring(str, pattern);
		if(result == 1) {
			count++;
		}
	}
	if(end == 1) {
		printf("%s%d\n", ANSI_COLOR_RESET, count);
		count = 0;
	}
}
void inverse_grep(char *str, char *pattern) {
	int result; 
	result = substring(str, pattern);
	if(result == 0) {
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			printf("%s%d:", ANSI_COLOR_GREEN, line_count);
		}
		printf("%s%s", ANSI_COLOR_RESET, str);
	}
}
void only_matching_grep(char *str, char *pattern) {
	int result, i, j = 0, size_str;
	result = substring(str, pattern);
	size_str = strlen(str);
	if(result == 1) {
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			printf("%s%d:", ANSI_COLOR_GREEN, line_count);
		}
		for(i = 0; i < size_str; i++) {
			if(i >= position[j] && i <= position[j + 1]) {
				printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
			 	if(i == position[j + 1]) {
			 		j += 2;
			 	}
			 }
		}
		printf("\n");
	}
}
void matching_lines(char *str, char *pattern) {
	int i, size_str;
	char *temp;
	size_str = strlen(str);
	temp = (char *)malloc(size_str);
	for(i = 0; i < size_str; i++) {
		temp[i] = str[i];
		if(i == (size_str - 1)) {
			temp[i] = '\0';
		}
	}
	if(strcmp(temp, pattern) == 0) {
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			printf("%s%d:", ANSI_COLOR_GREEN, line_count);
		}
		printf("%s%s", ANSI_COLOR_BOLDRED, str);
	}
}
void print_word_grep(char *str, char *pattern) {
	int i, j, k, l = 0, size_str, size_pattern, max, flag = 0, start_pos, end_pos;
	start_pos = end_pos = -1;
	size_str = strlen(str);
	size_pattern = strlen(pattern);
	max = size_str - size_pattern + 1;
	for(i = 0; i < 1000; i++) {
		position[i] = -1;
	}
	for(i = 0; i < max; i++) {
		flag = 0;
		for(j = i, k = 0; k < size_pattern; j++, k++) {
			if(set -> case_insensitive == OFF) {
				if(str[j] == pattern[k]) {
					if(k == 0) {
						if((j != 0 || j == i) && (isalnum(str[j - 1]) ||str[j - 1] == '_')) {
							break;
						}
					}
					else if(k == (size_pattern - 1)) {
						if((j != (size_str - 1) || j == (i + size_pattern -1)) && (isalnum(str[j + 1]) || str[j + 1] == '-')) {
							break;
						}
					}
					flag++;
					if(j == i) {
						start_pos = j;
					}
					else if(j == (i + size_pattern - 1)) {
						end_pos = j;
					}
				}
				else {
					start_pos = end_pos = -1;
					flag = 0; 
					break;
				}
				if(flag == size_pattern) {
					position[l++] = start_pos;
					position[l++] = end_pos;
					start_pos = end_pos = -1; 
				}
			}
			else {
				if(str[j] == pattern[k]) {
					if(k == 0) {
						if(j != 0 && (isalnum(str[j - 1]) ||str[j - 1] == '_')) {
							break;
						}
					}
					else if(k == (size_pattern - 1)) {
						if(j != (size_str - 1) && (isalnum(str[j + 1]) || str[j + 1] == '-')) {
							break;
						}
					}
					flag++;
					if(j == i) {
						start_pos = j;
					}
					else if(j == (i + size_pattern - 1)) {
						end_pos = j;
					}
				}
				else {
					start_pos = end_pos = -1;
					flag = 0; 
					break;
				}
				if(flag == size_pattern) {
					position[l++] = start_pos;
					position[l++] = end_pos;
					start_pos = end_pos = -1; 
				}
			}
		}
	}
	j = 0;
	while(position[j] != -1) {
		for(i = 0; i < size_str; i++) {
			if(i >= position[j] && i <= position[j + 1]) {
				printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
			 	if(i == position[j + 1]) {
			 		j += 2;
			 	}
			}
			 else {
			 	printf("%s%c", ANSI_COLOR_RESET, str[i]);
			 }
		}
	}		
}
