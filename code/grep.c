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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include "grep.h"

/*2 dimensional array named position is used to store indices of start and end of the matching part in a given string 'str' successively.*/ 
int position[1000][1000];

/*"substring" checks for the presence of a character sequence 'pattern' in a character sequence 'str' according to given conditions and returns 1 if presence is deteceted, else it returns 0.*/
int substring(char *str, char *pattern) {
	int i, j, k, flag = 0, max, size_str, size_pattern, start_pos, end_pos, result = 0;
	size_str = strlen(str);
	size_pattern = strlen(pattern);
	max = size_str - size_pattern + 1;
	if(set -> temp == 0) {
		for(i = 0; i < 1000; i++) {
			for(j = 0; j < 1000; j++) {
				position[i][j] = -1;
			}
		}
		set -> temp = 1;
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
			position[set -> row][set -> column++] = start_pos;
			position[set -> row][set -> column++] = end_pos;
			start_pos = end_pos = -1; 
			result = 1;
		}
	}
	if(result == 1) {
		set -> column = 0;
		set -> row++;
	}
	return result;
}

/*"normal_grep" does basic operation of grep. It checks for a presence of character sequence 'pattern' in a character sequence 'str' by calling "substring" function. It stores the string 'str' in a temporary file named 'resultfile'. It also stores linenumbers of matched lines in a temporary file named "linenumber" if '-n' is invoked. It returns 1 if substring is found and returns 0 if not found. It handles normal and inverse mode operations.*/
int normal_grep(char *str, char *pattern, int mode) {
	int result;
	FILE *fp;
	if(mode == inverse) {
		choice = invert;
	}
	result = substring(str, pattern);
	if((result == 1 && mode == normal) || (result == 0 && mode == inverse)) {
		init_print_result = ON;
		fp = fopen("resultfile", "a");
		if(fp == NULL) {
			exit(EXIT_FAILURE);
		}
		fputs(str, fp);
		fclose(fp);
		if((set -> print_line_number) == ON) {
			fp = fopen("linenumber", "a");
			if(fp == NULL) {
				exit(EXIT_FAILURE);
			}
			fprintf(fp, "%d\n", line_count);
			fclose(fp);
		}
		result = 0;
		return 1;	
	}
	return 0;
}

/*"count_line" counts the number of lines present in a temporary file "resultfile".*/
void count_line(void) {
	FILE *fp;
	int count = 0;
	char *str;
	fp = fopen("resultfile", "r");
	if(fp == NULL) {
		if((set -> print_file_name) == ON) {
			printf("%s%s:%s0\n", ANSI_COLOR_BLUE, set -> file_name, ANSI_COLOR_RESET);
		}
		else {
			printf("0\n");
		}
	}
	else {
		str = (char *)malloc(1000);
		while(fgets(str, 1000, fp)) {
			count++;
		}
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		fclose(fp);
		remove("resultfile");
		free(str);
		printf("%s%d\n", ANSI_COLOR_RESET, count);
	}
}

/*"max_lines" prints maximum lines equal to 'NUM' where 'NUM' is an integer given by user. It also prints linenumbers if required.*/
void max_lines(void) {
	FILE *fp1, *fp2;
	char *str;
	int i, j = 0, count = 0, line_number, size_str;
	fp1 = fopen("resultfile", "r");
	if(fp1 == NULL) {
		exit(EXIT_FAILURE);
	}
	if((set -> print_line_number) == ON) {
		fp2 = fopen("linenumber", "r");
		if(fp2 == NULL) {
			exit(EXIT_FAILURE);
		}	 
	}
	str = (char *)malloc(1000);
	while(fgets(str, 1000, fp1)) {
		if(set -> max_lines == 0) {
			set -> max_lines = 0;
			break;
		}
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			fscanf(fp2, "%d", &line_number);
			printf("%s%d:", ANSI_COLOR_GREEN, line_number);
		}
		size_str = strlen(str);
		for(i = 0; i < size_str; i++) {
			if(choice == OFF) {
				if(i >= position[count][j] && i <= position[count][j + 1]) {
					printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
					if(i == position[count][j + 1]) {
						j += 2;
					}
				}
				else {
					printf("%s%c", ANSI_COLOR_RESET, str[i]);
				}
			}
			else if(choice == invert){
				printf("%s%c", ANSI_COLOR_RESET, str[i]);
			}
			else if(choice == only_matching) {
				if(i >= position[count][j] && i <= position[count][j + 1]) {
					printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
					if(i == position[count][j + 1]) {
						j += 2;
						printf(" ");
					}
				}
			}
		}
		if(choice == only_matching) {
			printf("%s\n", ANSI_COLOR_RESET);
		}
		j = 0;
		count++;
		(set -> max_lines)--;
	}
	for(i = 0; i <= set -> row; i++) {
		for(j = 0; position[i][j] != -1; j++) {
			position[i][j] = -1;
		}
	}
	set -> row = set -> column = set -> temp = 0;
	fclose(fp1);
	remove("resultfile");
	if((set -> print_line_number) == ON) {
		fclose(fp2);
		remove("linenumber");
	}
	free(str);
}	

/*"matching_lines" checks if 'pattern' matches the whole line. If operates in normal and inverse mode. Storing of matched lines and linenumbers is same as that of "normal_grep". It returns 1 if match is found, else returns 0.*/ 	
int matching_lines(char *str, char *pattern, int mode) {
	int i, size_str, size_temp, size_pattern;
	char *temp;
	FILE *fp;
	temp = (char *)malloc(1000);
	size_str = strlen(str);
	for(i = 0; i < size_str; i++) {
		temp[i] = str[i];
		if(i == (size_str - 1)) {
			temp[i] = '\0';
		}
	}
	size_temp = strlen(temp);
	size_pattern = strlen(pattern);
	if(mode == inverse) {
		choice = invert;
	}
	if((mode == normal) ? size_temp == size_pattern : 1) {
		if((set -> case_insensitive == OFF) ? ((mode == normal) ? (strcmp(temp, pattern) == 0) : (strcmp(temp, pattern) != 0)) : ((mode == normal) ? ((strcmp(temp, pattern) == 0 || strcmp(temp, pattern) == -32 || strcmp(temp, pattern) == 32)) : ((size_temp == size_pattern) ? (strcmp(temp, pattern) != 0 && strcmp(temp, pattern) != -32 && strcmp(temp, pattern) != 32) : 1))) {
			init_print_result = ON;
			fp = fopen("resultfile", "a");
			if(fp == NULL) {
				exit(EXIT_FAILURE);
			}
			fputs(str, fp);
			fclose(fp);
			position[set -> row][set -> column++] = 0;
			position[set -> row][set -> column++] = (size_str - 2);
			(set -> row)++;
			(set -> column) = 0;
			if((set -> print_line_number) == ON) {
				fp = fopen("linenumber", "a");
				if(fp == NULL) {
					exit(EXIT_FAILURE);
				}
				fprintf(fp, "%d\n", line_count);
				fclose(fp);
			}
			return 1;
		}
	}
	return 0;
}

/*"print_word_grep" searches for a word matching 'pattern' in a given line 'str'.It operates in normal and reverse mode. It returns 1 is required match is found, else it returns 0.*/
int print_word_grep(char *str, char *pattern, int mode) {
	int i, j, k, size_str, size_pattern, max, flag = 0, start_pos, end_pos, result = 0;
	FILE *fp;
	start_pos = end_pos = -1;
	size_str = strlen(str);
	size_pattern = strlen(pattern);
	max = size_str - size_pattern + 1;
	if(mode == inverse) {
		choice = invert;
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
					position[set -> row][set -> column++] = start_pos;
					position[set -> row][set -> column++] = end_pos;
					result = 1;
					start_pos = end_pos = -1; 
				}
			}
			else {
				if(str[j] == pattern[k] || str[j] == pattern[k] + 32 || str[j] == pattern[k] - 32) {
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
					position[set -> row][set -> column++] = start_pos;
					position[set -> row][set -> column++] = end_pos;
					result = 1;
					start_pos = end_pos = -1; 
				}
			}
		}
	}
	if((result == 1 && mode == normal) || (result == 0 && mode == inverse)) {
		init_print_result = ON;
		if(set -> print_line_number == ON) {
			fp = fopen("linenumber", "a");
			if(fp == NULL) {
				exit(EXIT_FAILURE);
			}
			fprintf(fp, "%d\n", line_count);
			fclose(fp);
		}
		fp = fopen("resultfile","a");
		if(fp == NULL) {
			exit(EXIT_FAILURE);
		}
		fputs(str, fp);
		fclose(fp);
		result = 0; 
		(set -> row)++;
		(set -> column) = 0;
		return 1;
	}		
	return 0;
}

/*"file_with_match" prints the name of the file if required match is found from that file.*/
int file_with_match(char *str, char *pattern, int mode) {
	int result;
	if(set -> normal_grep == ON) {
		result = normal_grep(str, pattern, mode);
	}
	else if(set -> line_grep == ON) {
		result = matching_lines(str, pattern, mode);
	}
	else {
		result = print_word_grep(str, pattern, mode);
	}
	if(result == 1) {
		printf("%s%s%s\n", ANSI_COLOR_BLUE, set -> file_name, ANSI_COLOR_RESET);
		remove("resultfile");
	}
	return result;
}

/*"file_without_match" prints the name of the file if required match is not found from that file.*/
int file_without_match(char *str, char *pattern, int mode) {
	int result;
	if(set -> normal_grep == ON) {
		result = normal_grep(str, pattern, mode);
	}
	else if(set -> line_grep == ON) {
		result = matching_lines(str, pattern, mode);
	}
	else {
		result = print_word_grep(str, pattern, mode);
	}
	if(result == 1) {
		remove("resultfile");
		return 0;
	}
	return 1;
}

/*"print_result" prints the required result. It prints the matching parts in BOLDRED, linenumbers in GREEN and filenames in BLUE. After the required printing it removes "resultfile" and "linenumber". */
void print_result(void) {
	int i, j = 0, size_str;
	int count = 0, line_number;
	char *str;
	FILE *fp1, *fp2;
	str = (char *)malloc(1000);
	fp1 = fopen("resultfile", "r");
	if(fp1 == NULL) {
		exit(EXIT_FAILURE);
	} 
	if((set -> print_line_number) == ON) {
		fp2 = fopen("linenumber", "r");
		if(fp2 == NULL) {
			exit(EXIT_FAILURE);
		}
	} 
	while(fgets(str, 1000, fp1)) {
		if((set -> print_file_name) == ON) {
			printf("%s%s:", ANSI_COLOR_BLUE, set -> file_name);
		}
		if((set -> print_line_number) == ON) {
			fscanf(fp2, "%d", &line_number);
			printf("%s%d:", ANSI_COLOR_GREEN, line_number);
		}
		size_str = strlen(str);
		for(i = 0; i < size_str; i++) {
			if(choice == OFF) {
				if(i >= position[count][j] && i <= position[count][j + 1]) {
					printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
					if(i == position[count][j + 1]) {
						j += 2;
					}
				}
				else {
					printf("%s%c", ANSI_COLOR_RESET, str[i]);
				}
			}
			else if(choice == invert){
				printf("%s%c", ANSI_COLOR_RESET, str[i]);
			}
			else if(choice == only_matching) {
				if(i >= position[count][j] && i <= position[count][j + 1]) {
					printf("%s%c", ANSI_COLOR_BOLDRED, str[i]);
					if(i == position[count][j + 1]) {
						j += 2;
						printf(" ");
					}
				}
			}
		}
		if(choice == only_matching) {
			printf("%s\n", ANSI_COLOR_RESET);
		}
		while(j >= 0) {
			position[count][j] = -1;
			j--;
		}
		j = 0;
		count++;
	}
	set -> row = set -> column = set -> temp = 0;
	fclose(fp1);
	remove("resultfile");
	if((set -> print_line_number) == ON) {
		fclose(fp2);
		remove("linenumber");
	}
	init_print_result = OFF;
	free(str);
}
