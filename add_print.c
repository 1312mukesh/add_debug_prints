# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char buf[] = "\n\tprintk(KERN_ALERT \" traversing from guest to host:: %s %d %s\\n\", __func__, __LINE__, __FILE__);\n";


int main(int argc ,char *argv[])
{
	FILE *src;	// file pointer
	FILE *dst;	// file pointer

	char replced_with[30];

	char ch;		// stores each character read from file
	/* if number of commandline arguments are less then tell usage */
	if (argc != 2) {
		printf("Usage : exe filename \n");
		return 0;
	}

	/* open file and check for error */
	if (!(src = fopen(argv[1] ,"r"))) {
		printf("File not found\n");
		return 0;
	}

	memset(replced_with, '\0', sizeof(replced_with));
	sprintf(replced_with, "%s__", argv[1]);

	if (!(dst = fopen("dummy", "w"))) {
		printf("File not found\n");
		return 0;
	}

	while (1) {
		
		if ((ch = fgetc(src)) == EOF)
			break;
		fputc(ch, dst);
		/* when separator is reached check whether word is a  keyword*/
		
		if (ch == ')') {
		
			if ((ch = fgetc(src)) == EOF)
				break;
			fputc(ch, dst);
			
			while (ch == ' ') {
				if ((ch = fgetc(src)) == EOF)
					break;
				fputc(ch, dst);
			}	
			if (ch == '\n') {
		
				if ((ch = fgetc(src)) == EOF)
					break;
				fputc(ch, dst);
		
				if (ch == '{') 
					fputs(buf,dst);
			}
		} 
	}
	fclose(src);
	fclose(dst);

	if (rename(argv[1], replced_with) == -1)
		perror("replaced_with");
	if (rename("dummy", argv[1]) == -1)	
		perror("replaced");
	return 0;
}


