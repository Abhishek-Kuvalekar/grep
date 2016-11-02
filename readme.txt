Student Name: Kuvalekar Abhishek Vijay
MIS: 111508043
Project Name: Implementation 'grep' command

Synopsis:
    ‘grep’ searches input files for lines containing a match to a given pattern list.  When it finds a match in a line, it copies the line to
standard output (by default), or produces whatever other sort of output you have requested with options.
    If the final byte of an input file is not a newline, ‘grep’ silently supplies one.Since newline is also a separator for the list of patterns, there is no way to match newline characters in a text.


Features:
	Regexp selection and interpretation:
	  -G         PATTERN is a basic regular expression (BRE).
	  -i         Ignore case distinctions in both the pattern and input files. 
	  -w         Force PATTERN to match only whole words.
	  -x         Force PATTERN to match only whole lines.
	  -v         Invert the sense of matching, to select non-matching lines.
	  -y         Obsolete synonym for -i.

        Miscellaneous:
	  --help     Display this help text and exit.

	Output control:
	  -m NUM     Stop reading a file after NUM matches.
	  -n         Prefix each line of output with the 1-based line number within 
		     its input file.
	  -o         Print only the matched parts of a matching line. 
	  -r         Read all files under each directory, recursively. Note that, multiple 
		     directories can be given(maximum 16) on command line.
	  -c         Suppress  normal output; instead print a count of matching lines
		     for each input file. With the -v option, count non-matching lines.
	  -l         Suppress  normal  output; instead print the name of each input file from 
		     which output would normally have been printed. The scanning will stop on the first match.
	  -L         Suppress normal output; instead print the name of each input file from 
		     which no output would normally have been printed. The scanning will stop on the first match.
	  -h         Suppress the prefixing of file names on output. This is the default when 
		     there is only one file (or only standard input) to search.
	  -H         Print the file name for each match. This is the default when there is more than one file to search.
	 
	 
NOTE:
     In combination of above options if more than one option of same percedence is given the rightmost option of that precedence is considered. The options enclosed in paranthesis have same precedence: (-h, -H), (-n, -c), (-i, -y), (-G, -x, -w), (-l, -L).
     
