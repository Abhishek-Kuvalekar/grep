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

/*"get_file_type" checks whether the file input by user is text or binary. It returns 1 if file is binary and returns 0 if the file is text. It returns -1 on error.*/
int get_file_type(char *file) {
	char *err;
	FILE *fp;
	char ch;
	fp = fopen(file, "r");
	if(fp == NULL) {
		err = strerror(errno);
		printf("Error:%s:%s.\n", file, err);
		exit(errno);
	}
	while(fscanf(fp, "%c", &ch) != EOF) {
		if(ch == '\0') {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
