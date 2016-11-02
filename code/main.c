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

/*The main function of program.*/
int main(int argc, char *argv[]) {
	int i;
	c = (counter *)malloc(sizeof(counter));
	set = (set_option *)malloc(sizeof(set_option));
	set -> print_line_number = OFF;
	set -> print_file_name = OFF; 
	set -> case_insensitive = OFF;
	set -> print_max_lines = OFF;
	set -> skip = OFF;
	set -> recurse = OFF;
	set -> print_help = OFF;
	set -> normal_grep = OFF;
	set -> line_grep = OFF;
	set -> word_grep = OFF;
	set -> row = set -> column = 0;
	set -> dir_name[0] = NULL;
	set -> file_name = NULL;
	init_print_result = OFF;
	choice = OFF;
	max = 1000;	
	for(i = 1; i <= (c -> options); i++) {
		if(strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-y") != 0 && strcmp(argv[i], "-v") != 0 &&
		   strcmp(argv[i], "-w") != 0 && strcmp(argv[i], "-x") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i], "-m") != 0 &&
	           strcmp(argv[i], "-o") != 0 && strcmp(argv[i], "-n") != 0 && strcmp(argv[i], "-G") != 0 && strcmp(argv[i], "-r") != 0 &&                 strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "-H") != 0 && strcmp(argv[i], "-l") != 0 && strcmp(argv[i], "-L") != 0 &&                 strcmp(argv[i], "--help") !=  0) {
			printf("Usage: grep [OPTION]... PATTERN [FILE]...\nTry 'grep --help' for more information.\n");
			return EINVAL;
		}
		if(strcmp(argv[i], "-m") == 0) {
			i++;
		}
	}
	count_function(argc, argv);
	method_select(argc, argv);
	free(c);
	free(set -> file_name);
	free(set);
	return 0;
}
