/*
*
*  @author: Valeri Vladimirov 40399682
*  Last Modified: 23/02/2019
*  Purpose: To preprocess files.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 1000

// Structure used to save #define names and values.
struct define
{
	char name[20];
	char value[20];
};

// Function to remove new lines.
void remove_newline(char* str)
{
	int len = strlen(str);
	
	if(len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int main(int argc, char **argv)
{
	// Declaring all the files and other variables needed for the exercises.
	FILE *fp;
	FILE *file;
	FILE *string_functions;
	FILE *math_functions;
	char filename[20];
	char *file_name;
	char line [LINE_LENGTH];
	int flag = 0;
	int count = 0; 
	int comment = 0;
	char *name;
	char *value;
	int temp = 0;
	int temp2 = 0;
	struct define arr_define[10];
	
	// Used to seperate the file and detect if there is -c in the input.
	for(int i = 0; i < argc; ++i)
	{
		if(strcmp(argv[i], "math_functions.c") == 0 || strcmp(argv[i], "string_functions.c") == 0)
		{
			strcpy(filename, argv[i]);
		}
		if(strcmp(argv[i], "-c") == 0)
		{
			flag = 1;
		}
	}
	
	// Opening all the needed files for the program.
	string_functions = fopen("string_functions.h", "r");
	math_functions = fopen("math_functions.h", "r");
	
	fp = fopen(filename, "r");
	
	file_name = strtok(filename, ".");
	strcat(file_name, ".o");
	
	file = fopen(file_name, "w+");
	
	if (fp == NULL) 
    { 
        printf("Could not open file %s", file_name); 
        return 0; 
    }

	// Make the files without the comments.
	if(flag == 0)
	{
		
		// While loop where all the file reading and writing happens.
		while(fgets (line, LINE_LENGTH, fp))
		{
			int num = strlen(line);
			
			// For loop to count the number of lines with characters.
			for(int i = 0; i < num; i++)
			{
				if((line[i] != ' ') && (line[i] != '\n') && (line[i] != '\t'))
				{
					count++;
					break;
				}
			}
		
			// If statement to save the #define values and names in the structure array.
			if(line[0] == '#' && line[1] == 'd')
			{
				strtok(line, " #");
				name = strtok(NULL, " ");
				value = strtok(NULL, " ");
			
				remove_newline(value);
			
				strcpy(arr_define[temp].name, name);
				strcpy(arr_define[temp].value, value);
				temp++;
			}
		
			// For loop to count the number of comments in the file.
			for(int i = 0; i < num; i++)
			{
				if(line[i] == '/' && line[i + 1] == '/')
				{
					comment++;
					break;
				}
			}
		
			// For loop to write to the new file.
			for(int i = 0; i < num; i++)
			{				
				// Removes the comments.
				if((line[i] == '/' && line[i + 1] == '/')) 
				{
					fprintf(file, "%c", '\n');
					break;
				}
			
				// Removes the lines with #define and #include.
				if(line[0] == '#' && (line[1] == 'i' || line[1] == 'd'))
				{
					fprintf(file, "%c", ' ');
					break;
				}
			
				// Replaces the names from #define with their values for the math file.
				if(line[i] == arr_define[temp2].name[0] && (line[i] >= 'A' && line[i] <= 'Z') && file_name[0] == 'm')
				{
					if(temp2 == 4)
					{
						temp2++;
					}
					fprintf(file, "%s", arr_define[temp2].value);
				
					if(file_name[0] == 'm')
					{
						temp2++;
					}
				}
			
				// Replaces the names from #define with their values for the string file.
				else if (line[i] == arr_define[temp2].name[0] && (line[i] >= 'A' && line[i] <= 'Z') && file_name[0] == 's' && line[i + 1] == arr_define[temp2].name[1])
				{
					if(temp2 == 4)
					{
						temp2++;
					}
					fprintf(file, "%s", arr_define[temp2].value);
				
					if(file_name[0] == 'm')
					{
						temp2++;
					}
				}
			
				// Writes everything else.
				else if (!(line[i] >= 'A' && line[i] <= 'Z'))
				{
					if(!(line[i] == '_' && (line[i-1] == 'D' || line[i-1] == 'F')))
					{
						fprintf(file, "%c", line[i]);
					}
				}	
			}
		
			// If statements to replace the #include with the provided functions.
			if(line[0] == '#' && line[1] == 'i')
			{	
				// For the math_functions file.
				if(line[10] == 'm')
				{
					while(fgets (line, LINE_LENGTH, math_functions))
					{
						for(int k = 0; k < strlen(line); k++)
						{
							fprintf(file, "%c", line[k]);
						}
					}
					fprintf(file, "%c", '\n');
					fprintf(file, "%c", '\n');
				}
				// For the string_functions file.
				if(line[10] == 's')
				{
					while(fgets (line, LINE_LENGTH, string_functions))
					{
						for(int k = 0; k < strlen(line); k++)
						{
							fprintf(file, "%c", line[k]);
						}
					}
					fprintf(file, "%c", '\n');
				}
			}
		}	
	}
	
	
	// Make the files with the comments.
	if(flag == 1)
	{
	
		// While loop where all the file reading and writing happens.
		while(fgets (line, LINE_LENGTH, fp))
		{
			int num = strlen(line);
		
			// For loop to count the number of lines with characters.
			for(int i = 0; i < num; i++)
			{
				if((line[i] != ' ') && (line[i] != '\n') && (line[i] != '\t'))
				{
					count++;
					break;
				}
			}
		
			// If statement to save the #define values and names in the structure array.
			if(line[0] == '#' && line[1] == 'd')
			{
				strtok(line, " #");
				name = strtok(NULL, " ");
				value = strtok(NULL, " ");
			
				remove_newline(value);
			
				strcpy(arr_define[temp].name, name);
				strcpy(arr_define[temp].value, value);
				temp++;
			}
		
			// For loop to count the number of comments in the file.
			for(int i = 0; i < num; i++)
			{
				if(line[i] == '/' && line[i + 1] == '/')
				{
					comment++;
					break;
				}
			}
		
			// For loop to write to the new file.
			for(int i = 0; i < num; i++)
			{				
				// Removes the lines with #define and #include.
				if(line[0] == '#' && (line[1] == 'i' || line[1] == 'd'))
				{
					fprintf(file, "%c", ' ');
					break;
				}
			
				// Replaces the names from #define with their values for the math file.
				if(line[i] == arr_define[temp2].name[0] && (line[i] >= 'A' && line[i] <= 'Z') && file_name[0] == 'm'  && (strstr(line, "//") == NULL))
				{
					if(temp2 == 4)
					{
						temp2++;
					}
					fprintf(file, "%s", arr_define[temp2].value);
				
					if(file_name[0] == 'm')
					{
						temp2++;
					}
				}
			
				// Replaces the names from #define with their values for the string file.
				else if (line[i] == arr_define[temp2].name[0] && (line[i] >= 'A' && line[i] <= 'Z') && file_name[0] == 's' && line[i + 1] == arr_define[temp2].name[1])
				{
					if(temp2 == 4)
					{
						temp2++;
					}
					fprintf(file, "%s", arr_define[temp2].value);
				
					if(file_name[0] == 'm')
					{
						temp2++;
					}
				}
			
				// Writes the comments.
				else if(strstr(line,"//") != NULL)
				{
					fprintf(file, "%c", line[i]);
				}
			
				// Writes everything else.
				else if (!(line[i] >= 'A' && line[i] <= 'Z'))
				{
					if(!(line[i] == '_' && (line[i-1] == 'D' || line[i-1] == 'F')))
					{
						fprintf(file, "%c", line[i]);
					}
				}	
			}
		
			// If statements to replace the #include with the provided functions.
			if(line[0] == '#' && line[1] == 'i')
			{	
				// For the math_functions file.
				if(line[10] == 'm')
				{
					while(fgets (line, LINE_LENGTH, math_functions))
					{
						for(int k = 0; k < strlen(line); k++)
						{
							fprintf(file, "%c", line[k]);
						}
					}
					fprintf(file, "%c", '\n');
					fprintf(file, "%c", '\n');
				}
				// For the string_functions file.
				if(line[10] == 's')
				{
					while(fgets (line, LINE_LENGTH, string_functions))
					{
						for(int k = 0; k < strlen(line); k++)
						{
							fprintf(file, "%c", line[k]);
						}
					
					}
					fprintf(file, "%c", '\n');
				}
			}
		}	
	}
	
	// Closing all the files and writing the number of comments and lines to the console.
	fclose(math_functions);
	fclose(string_functions);
	fclose(file);
	fclose(fp);
	printf("The file has %d lines\n",count); 
	printf("The file has %d comments\n",comment); 
	return 0;
}
