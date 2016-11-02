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
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "grep.h"

/*"option_select" works as a filter for operations of grep. It operates one operation a time sequentially on all input text files and produces the result.*/
void option_select(input *ip) {
	int i, j, k, print_flag = 0, flag = 0, temp, mode;
	char *str, *err;
	set -> file_name = NULL;
	str = (char *)malloc(max);
	if(str == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	mode = normal;
	for(j = 0; j < (ip -> file_count); j++) {	
		if((ip -> file_count) != 1 || set -> print_file_name == ON) {
			(set -> file_name) = (char *)malloc(strlen(ip -> file[j]) + 1);
			if(set -> file_name == NULL) {
				err = strerror(errno);
				printf("Error:%s.\n", err);
				exit(errno);
			}
			strcpy((set -> file_name), ip -> file[j]);
			(set -> print_file_name) = ON;
		}
		for(k = 0; (c -> options == 0) ? k < 1 : (k < (c -> options)); k++) {
			line_count = 0;
			set -> row = set -> column = set -> temp = 0;
			while(1){
				i = readline(ip -> file[j], str);
				if(i == -1) {
					exit(EXIT_FAILURE);
				}
				else if(i == 1) {
					break;
				} 
				line_count++;
				if(c -> options == 0) {
					normal_grep(str, ip -> pattern, mode);
					print_flag = 1;
				}				
				else {
					if(ip -> option[i] == NULL) {
						continue;
					}
					else {
						if(strcmp(ip -> option[k], "-h") == 0) {
							set -> print_file_name = OFF;
							if(k == c -> options - 1) {
								normal_grep(str, ip -> pattern, mode);
								print_flag = 1;
							}
						}
						else if(strcmp(ip -> option[k], "-H") == 0) {
							set -> print_file_name = ON;
							if(ip -> file_count == 1) {
								set -> file_name = (char *)malloc(strlen(ip -> file[j]) + 1);
								if(set -> file_name == NULL) {
									err = strerror(errno);
									printf("Error:%s.\n", err);
									exit(errno);
								}
								strcpy(set -> file_name, ip -> file[j]);
							}
							if(k == c -> options - 1) {
								normal_grep(str, ip -> pattern, mode);
								print_flag = 1;
							}
						}  
						else if(strcmp(ip -> option[k], "-v") == 0) {
							if(choice == only_matching && set -> skip == OFF) {
								exit(0);
							}
							mode = inverse;
							if(k == (c -> options - 1)) {
								normal_grep(str, ip -> pattern, mode);
								if(print_flag == 0) {
									print_flag = 1;
								}
							}
						}
						else if(strcmp(ip -> option[k], "-i") == 0 || strcmp(ip -> option[i], "-y") == 0) {
							set -> case_insensitive = ON;
							if(k == (c -> options - 1)) {
								normal_grep(str, ip -> pattern, mode);
								if(print_flag == 0) {
									print_flag = 1;
								}
							}
						}
						else if(strcmp(ip -> option[k], "-G") == 0) {
							set -> normal_grep = ON;
							if(set -> skip == OFF) {
								normal_grep(str, ip -> pattern, mode);
							}
							if(print_flag == 0 && set -> print_max_lines == OFF) {
								print_flag = 1;
							}
						}
						else if(strcmp(ip -> option[k], "-o") == 0) {
							if(mode == inverse && set -> skip == OFF) {
								exit(0);
							}
							choice = only_matching;
							if(k == (c -> options - 1)) {
								normal_grep(str, ip -> pattern, mode);
								if(print_flag == 0) {
									print_flag = 1;
								}
							}
						}
						else if(strcmp(ip -> option[k], "-x") == 0) {
							set -> line_grep = ON;
							if(set -> skip == OFF) {
								matching_lines(str, ip -> pattern, mode);
							}
							if(print_flag == 0 && set -> print_max_lines == OFF) {
								print_flag = 1;
							}
						}
						else if(strcmp(ip -> option[k], "-w") == 0) {
							set -> word_grep = ON;
							if(set -> skip == OFF) {
								print_word_grep(str, ip -> pattern, mode);
							}
							if(print_flag == 0 && set -> print_max_lines == OFF) {
								print_flag = 1;
							}
						}
						else if(strcmp(ip -> option[k], "-c") == 0) {
							if(k == c -> options - 1) {
								normal_grep(str, ip -> pattern, mode);
								init_print_result = ON;
							}
							print_flag = 2;
						}
						else if(strcmp(ip -> option[k], "-n") == 0) {
							set -> print_line_number = ON;
							if(k == c -> options - 1) {
								normal_grep(str, ip -> pattern, mode);
							}
							if(print_flag == 0 && set -> print_max_lines == OFF) {
								print_flag = 1;
							}
						}
						else if(strcmp(ip -> option[k], "-m") == 0) {
							if(flag == 0) {
								set -> print_max_lines = ON;
								set -> max_lines = temp_number;
								flag = 1;
							}
							if(k == c -> options - 1) {
								normal_grep(str, ip -> pattern, mode);
							}
							print_flag = 3;
						}
						else if(strcmp((ip -> option[k]), "-l") == 0) {
							if(ip -> file_count == 1) {
								set -> file_name = (char *)malloc(strlen(ip -> file[j]) + 1);
								if(set -> file_name == NULL) {
									err = strerror(errno);
									printf("Error:%s.\n", err);
									exit(errno);
								}
								strcpy(set -> file_name, ip -> file[j]);
							}
							temp = file_with_match(str, ip -> pattern, mode);
							print_flag = 0;
							if(temp == 1) {
								break;
							}
						}
						else if(strcmp((ip -> option[k]), "-L") == 0) {
							if(ip -> file_count == 1) {
								set -> file_name = (char *)malloc(strlen(ip -> file[j]) + 1);
								if(set -> file_name == NULL) {
									err = strerror(errno);
									printf("Error:%s.\n", err);
									exit(errno);
								}
								strcpy(set -> file_name, ip -> file[j]);
							}
							temp = file_without_match(str, ip -> pattern, mode);
							if(temp == 1) {
								print_flag = 4;
							}
							else {
								print_flag = 0;
								break;
							}
						}
					}
				}	 
			}
		}
		if(print_flag == 1 && init_print_result == ON) {
			print_result();
			init_print_result = OFF;
		}
		else if(print_flag == 2 && init_print_result == ON) {
			count_line();
			init_print_result = OFF;
		}
		else if(print_flag == 3 && init_print_result == ON) {
			max_lines();
			flag = 0;
			init_print_result = OFF;
		}
		else if(print_flag == 4) {
			printf("%s%s\n", ANSI_COLOR_BLUE, set -> file_name);
		}
		print_flag = 0;
	}
	free(str);
}
