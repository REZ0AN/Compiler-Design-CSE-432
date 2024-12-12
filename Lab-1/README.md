# Lexical Analysis ( Separation by Special Character and Spaces)

## Rules
- If any special character are their then print it in single line
- If any spaces are found remove them
- And keywords and variables has to be printed like how they are written

## My Solution

### A function for checking Special Chacters except **"**
```c
    int isSpecialCharacter(char ch)
    {
        if (ch >= 'a' && ch <= 'z') return 0;
        if (ch >= 'A' && ch <= 'Z') return 0;
        if (ch >= '0' && ch <= '9') return 0;
        if (ch == '"') return 0;
        return 1;
    }
```
### Reading the Code form a FILE Line By Line
```c
    FILE *ptr;
	ptr = fopen("input.txt", "r");
```
### Storing the Lines in my format to Maintain the Rules
- If found normal character then keep it as it is
- If it is a space then keep it as it is
- If found **(** then iterate until found the **)**
    - Apply 1st rule 
    - Apply space before and after the special characters
- Continue Until `null_character` is found

```c
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
```
### Displaying after the Lexical Analysis
- Print characters until you get a `space`
- Then Print a new line
- Update Iteration for continues spaces or new_lines
- Repeat this process until we reach the `null_character`
```c
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
```