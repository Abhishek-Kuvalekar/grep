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

/*"method_select" determins the mode of operation i.e. normal, recursive or just printing help menu.*/
void method_select(int argc, char **argv) {
	int i;
	char *err;
	ip = (input *)malloc(sizeof(input)); 
	if(ip == NULL) {
		err = strerror(errno);
		printf("Error:%s.\n", err);
		exit(errno);
	}
	if(set -> recurse == ON && set -> print_help == OFF) {	
		option_file_sort(argc, argv);
		if(set -> dir_name[0] == NULL) {
			set -> dir_name[0] = (char *)malloc(1000);
			set -> dir_name[0] = getcwd(set -> dir_name[0], 1000);
			(c -> directories)++;
		}
		for(i = 0; i < c -> directories; i++) {
			recursive_grep(set -> dir_name[i]);
		}
	}
	else if(set -> print_help == ON) {
		print_help();
	}
	else {
		option_file_sort(argc, argv);
		option_select(ip);
	}
	free(ip -> option);
	free(ip -> file);
	free(ip -> pattern);
	free(ip);
}
