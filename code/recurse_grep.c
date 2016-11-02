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

/*"recursive_grep" reads the given directory and its subdirectories and searches for a pattern in all present text files.*/ 
void recursive_grep(char *directory) {
	int i, file_type;
	char *dir, *file, *err;
	input *ip2;
	DIR *dp;
	struct dirent *ep;
	ip2 = (input *)malloc(sizeof(input));
	if(ip2 == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	ip2 -> option = (char **)malloc(c -> options * sizeof(char *));
	ip2 -> file = (char **)malloc(512);
	ip2 -> pattern = (char *)malloc(32);
	if(ip2 -> option == NULL || ip2 -> file == NULL || ip2 -> pattern == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	dir = (char *)malloc(1000);
	if(dir == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	ip2 -> file_count = 0;
	strcpy(ip2 -> pattern, ip -> pattern);
	for(i = 0; i < c -> options; i++) {
		ip2 -> option[i] = (char *)malloc(8);
		if(ip2 -> option[i] == NULL) {
			err = strerror(errno);
			printf("Error:%s.\n", err);
			exit(errno);
		}
		strcpy(ip2 -> option[i], ip -> option[i]);
	}
	dp = opendir(directory);
	if(dp == NULL) {
		err = strerror(errno);
		printf("Error:%s: %s.\n", directory, err);
		exit(errno);
	}
	while((ep = readdir(dp))) {
		if(ep -> d_type == DT_DIR) {
			strcpy(set -> directory, directory);
			if(strcmp(ep -> d_name, ".") == 0 || strcmp(ep -> d_name, "..") == 0) {
				continue;
			} 
			strcpy(dir, directory);
			strcat(dir, "/");
			strcat(dir, ep -> d_name);
			recursive_grep(dir);
		}
		else if(ep -> d_type == DT_REG) {
			strcpy(set -> directory, directory);
			file = (char *)malloc(strlen(set -> directory) + strlen(ep -> d_name) + 2);
			if(file == NULL) {
				err = strerror(errno);
				printf("Error:%s.\n", err);
				exit(errno);
			}
			strcpy(file, directory);
			strcat(file, "/");
			strcat(file, ep -> d_name);
			file_type = get_file_type(file);
			if(file_type == 1) {
				continue;
			}
			(ip2 -> file_count)++;	
			ip2 -> file[(ip2 -> file_count) - 1] = (char *)malloc(1000);
			if(ip2 -> file[(ip2 -> file_count) - 1] == NULL) {
				err = strerror(errno);
				printf("Error:%s.\n", err);
				exit(errno);
			}
			strcpy(ip2 -> file[(ip2 -> file_count) - 1], file);
			free(file);
		}
	} 
	set -> print_file_name = ON;
	option_select(ip2);
	for(i = 0; i < ip2 -> file_count; i++) {
		free(ip2 -> file[i]);
	}
	for(i = 0; i < c -> options; i++) {
		free(ip2 -> option[i]);
	}
	free(ip2 -> pattern); 
	free(ip2 -> file);
	free(ip2 -> option);
	free(ip2);
	free(dir);
}		 
