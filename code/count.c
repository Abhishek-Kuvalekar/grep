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

/*"count_function" counts the number of options, files and directories given by user on command line.*/
void count_function(int n, char **argv) {
	int i, flag = 0, recurse_flag = 0;
	(c -> options) = 0;
	(c -> files) = 0;
	(c -> other) = 0;
	(c -> directories) = 0;
	for(i = 1; i < n; i++) {
		if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-w") == 0 ||                 strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "-o") == 0 ||                 strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-G") == 0 || strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-h") == 0 ||                 strcmp(argv[i], "-H") == 0 || strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "--help") == 0) {
		   	(c -> options)++;
		   	if(strcmp(argv[i], "-r") == 0) {
		   		recurse_flag = 1;
		   		set -> recurse = ON;
		   	}
		   	else if(strcmp(argv[i], "-m") == 0) {
		   		i++;
		   		(c -> other)++;
		   	}
		   	else if(strcmp(argv[i], "--help") == 0) {
		   		set -> print_help = ON;
		   	}
		}
		else {
			if(flag == 0) {
				flag = 1;
			}
			else {
				if(recurse_flag == 1) {
					(c -> directories)++;
				}
				else {
					(c -> files)++;
				}
			}
		}
	}
}
