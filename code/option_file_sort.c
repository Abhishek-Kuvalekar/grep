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

/*"option_file_sort" function sorts the option according to their preference and stores them in the array "option" in structure "input". If more than one option of same precedence are input by the user, it stores last option entered of the same precedence and forgets previously entered options of that precedence. It also stores text files in "file" array and assigns a value of "file_count". if binary file is detected, it is simply skipped.*/
void option_file_sort(int argc, char **argv) {
	int i, j, file_type, count_bin_files = 0, recurse_flag = 0, allocated[8], count_repeat = 0;
	char *err;
	ip -> option = (char **)malloc(8  * sizeof(char *));
	ip -> file = (char **)malloc((c -> files) * sizeof(char *));
	ip -> pattern = (char *)malloc(32);
	if(ip -> option == NULL || ip -> file == NULL || ip -> pattern == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	for(i = 0; i < 8; i++) {
		allocated[i] = 0;
	}
	for(i = 0; i < 8; i++) {
		ip -> option[i] = NULL;
	}
	if(c -> options == 0) {
		i = 1;
	}
	else { 
		for(i = 1; (c -> options == 0) ? i < 2 : (i <= (c -> options + c -> other)); i++) {
			if(strcmp(argv[i], "-r") == 0) {
				recurse_flag = 1;
				continue;
			}
			if(c -> options == 1 || c -> options == 0) {
				ip -> option[0] = (char *)malloc(8);
				if(ip -> option[0] == NULL) {
					err = strerror(errno);
					printf("Error:%s.\n", err);
					exit(errno);
				}
				strcpy(ip -> option[0], argv[i]);
				if(strcmp(argv[i], "-m") == 0) {
					i++;
					temp_number = atoi(argv[i]);
				}
			}
			else {
				if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-H") == 0) {
					ip -> option[0] = (char *)malloc(8);
					if(ip -> option[0] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[0], argv[i]);
					count_repeat += check_allocated(allocated, 0);
				}
				else if(strcmp(argv[i] ,"-n") == 0 || strcmp(argv[i], "-c") == 0) {
					ip -> option[1] = (char *)malloc(8);
					if(ip -> option[1] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[1], argv[i]);
					count_repeat += check_allocated(allocated, 1);
				} 
				else if(strcmp(argv[i], "-v") == 0) {
					ip -> option[2] = (char *)malloc(8);
					if(ip -> option[2] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[2], argv[i]);
				}
				else if(strcmp(argv[i], "-o") == 0) {
					ip -> option[3] = (char *)malloc(8);
					if(ip -> option[3] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[3], argv[i]);
				}
				else if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-y") == 0) {
					ip -> option[4] = (char *)malloc(8);
					if(ip -> option[4] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[4], argv[i]);
					count_repeat += check_allocated(allocated, 4);
				}
				else if(strcmp(argv[i], "-m") == 0) {
					ip -> option[5] = (char *)malloc(8);
					if(ip -> option[5] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[5], argv[i]);
					i++;
					temp_number = atoi(argv[i]);
				}
				else if(strcmp(argv[i], "-G") == 0 || strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "-w") == 0) {
					ip -> option[6] = (char *)malloc(8);
					if(ip -> option[6] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[6], argv[i]);
					count_repeat += check_allocated(allocated, 6);
				}
				else if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-L") == 0) {
					ip -> option[7] = (char *)malloc(8);
					if(ip -> option[7] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[7], argv[i]);
					count_repeat += check_allocated(allocated, 7);
					set -> skip = ON;
				} 
				
				
			}
		}
	}
	strcpy(ip -> pattern, argv[i]);
	for(i = 0; i < 7; i++) {
		if(ip -> option[i] == NULL) {
			j = i + 1;
			if(ip -> option[j] != NULL) {
				ip -> option[i] = (char *)malloc(8);
				if(ip -> option[i] == NULL) {
					err = strerror(errno);
					printf("Error:%s.\n", err);
					exit(errno);
				} 
				strcpy(ip -> option[i], ip -> option[j]);
				free(ip -> option[j]);
				ip -> option[j] = NULL;
			}
			else {
				while(j < 8 && ip -> option[j] == NULL) {
					j++;
				}
				if(j == 8) {
					break;
				}
				else {
					ip -> option[i] = (char *)malloc(8);
					if(ip -> option[i] == NULL) {
						err = strerror(errno);
						printf("Error:%s.\n", err);
						exit(errno);
					}
					strcpy(ip -> option[i], ip -> option[j]);
					free(ip -> option[j]);
					ip -> option[j] = NULL;
				}
			}
		} 	 
	}   		
	j = 0;
	for(i = ((c -> options) + (c -> other) + 2); i < ((c -> options) + (c -> other) + 2 + (c -> files) + (c -> directories)); i++) {
		if(recurse_flag == 1) {
			set -> dir_name[j] = (char *)malloc(1000);
			if(set -> dir_name[j] == NULL) {
				err = strerror(errno);
				printf("Error:%s.\n", err);
				exit(errno);
			}
			strcpy(set -> dir_name[j], argv[i]);
			j++;
			continue;
		}
		file_type = get_file_type(argv[i]);
		if(file_type == -1) {
			exit(0);
		}
		else if(file_type == 1) {
			count_bin_files++;
			continue;
		}
		else {
			ip -> file[j] = (char *)malloc(1000);
			if(ip -> file[j] == NULL) {
				err = strerror(errno);
				printf("Error:%s.\n", err);
				exit(errno);
			}
			strcpy(ip -> file[j], argv[i]);
		}
		j++;
	}
	(ip -> file_count) = c -> files - count_bin_files;
	if(recurse_flag == 1) {
		(c -> options)--;
	}
	c -> options -= count_repeat; 
}

/*"check_allocated" checks if there are more than one options of same precedence. If more than one option of same precedence are found it returns 1, else it returns 0.*/
int check_allocated(int *allocated, int i) {
	if(allocated[i] == 0) {
		allocated[i] = 1;
		return 0;
	}
	return 1;
}
