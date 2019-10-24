# Overview

In this coursework you are to build a command line application, called
preprocess, that contains basic functionality of a C language preprocessor.
Your application will read in a .c file containing source code written in the
C programming language, and output a preprocessed version of that file
according to the specification below.

# Specification

The features specified below are listed in increasing order of how dicult
they are to implement.
The preprocess application is required to read in a .c file and output
the following to the console:

1. The number of non-empty lines in the .c file. Non-empty lines are
defined as those that contain at least one character that is not a newline,
space, or tab.

2. The number of comments in the .c file. For this coursework, a comment
is defined as beginning with // and ending at the end of that line, i.e.
you do not need to consider multiline comments beginning with /*.

The application is also required to produce an output file which has the
same name as the .c input file but with a .o file extension. This output file
should contain a preprocessed version of the input file containing the same
lines of program code but modified according to the following specification:

3. All comments should be removed. As above, a comment is defined as
beginning with // and ending at the end of that line, i.e. you do not
need to consider multiline comments beginning with /*.

4. A line that begins with #include “filename.h” should be replaced with
the entire contents of the file called filename.h. Your application should
remove the quotes when processing the filename. You may assume that
filename.h is located in the same directory as the input file. The name
filename.h should be considered as a placeholder, i.e. your application
should work for any filename following a #include.

5. A line that begins with #define constant name value should be processed as follows. The line should be removed. Throughout the rest of
the input file, wherever constant name appears it should be removed
and replaced with value in the output file. You may assume that constant name will always be proceeded and followed by a space in the
input file. constant name and value should be considered as placeholders, i.e. your application should work for any sequence of characters in
place of constant name and value.

The application should understand the command line arguments shown
in Table 1, which should be accepted in any order.

Argument Description

**Argument** | **Description**
-------------|-----------------
-i filename | The name of the .c input file to preprocess.
-c | Indicates that comments should be left in the output file instead of being removed.


Table 1: Command line flags for the preprocess application.

Therefore we can preprocess the file myprog.c to produce the output file
myprog.o using the command:

**preprocess -i myprog.c**

We can also leave comments in the output file for myprog.c as follows:

**preprocess -i myprog.c -c**
