#include<stdio.h>
#include<stdlib.h>
const int MAX = 1900000;
int isSpecialCharacter(char ch)
{
	if (ch >= 'a' && ch <= 'z') return 0;
	if (ch >= 'A' && ch <= 'Z') return 0;
	if (ch >= '0' && ch <= '9') return 0;
	if (ch == '"') return 0;
    if (ch == '.') return 0;
 	return 1;
}
int main()
{
	FILE *ptr;
	ptr = fopen("input.txt", "r");
	char arr[MAX];
    char printout[MAX];
    int j =0,i=0;
    printf("******************************************\n");
    printf("                  INPUT CODE              \n");
    printf("******************************************\n");
    while (fgets(arr, MAX, ptr)) {
        printf("%s",arr);
    }
    printf("\n\n");
    fclose(ptr);
    printf("******************************************************************************\n");
    printf("  Lexicographic Analysis (using separation by spaces and special characters)  \n");
    printf("******************************************************************************\n");
	ptr = fopen("input.txt", "r");

    while (fgets(arr, MAX, ptr))
	{
		for (i = 0; arr[i] != '\0'; i++)
		{
			if (isSpecialCharacter(arr[i]) == 0)
			{
				// not special character
                printout[j++]= arr[i];
			}
			else
			{
                if (arr[i] == ' '){
                    printout[j++]= arr[i];
                }
				else if (arr[i] == '(')
				{
					while (arr[i] != ')')
					{   
                        if (isSpecialCharacter(arr[i]) == 0)
                            {
                                // not special character
                                printout[j++]= arr[i];
                            } else {
                                printout[j++]=' ';
                                printout[j++]=arr[i];
                                printout[j++]=' ';
                            }
						i++;
					}
                    
                    printout[j++]=' ';
                    printout[j++]=arr[i];
                    printout[j++]=' ';
					continue;
				}
                printout[j++]=' ';
                printout[j++]=arr[i];
                printout[j++]=' ';
			}
		}
    }
    printf("\n");
    for(j=0;printout[j] != '\0';) {
        while(printout[j] != ' '){
            printf("%c",printout[j]);
            j++;
        }
        printf("\n");
        while(printout[j]==' ' || printout[j]=='\n'){
            j++;
        }
        
    }
    fclose(ptr);
}
