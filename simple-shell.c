/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013

	20100006 Mohammad Raza Khawaja
	20100120 Umar Salman


 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

char* histarr[10];

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    	int should_run = 1;
	
	char buff[MAX_LINE/2 + 1];
	char temp[MAX_LINE/2 + 1];
	int i, upper;
	int j;
	char* ch;
	int hist = 0;

	char e; // for !
	char n; // for N
	char n2; // for 0

	int tenCmd = 0;

	int excl2 = 0;

	int cc = 0;
	for (cc; cc < 10; cc++)
	{
		histarr[cc] = "garbage";
	}
	int hc = 0;
	//int totalcmds = 0;


    while (should_run)
    {   
    	hist = 0;
    	tenCmd = 0;
    	excl2 = 0;

       	printf("osh>");
       	fflush(stdout);

		fgets(buff , sizeof buff, stdin);
		
		strcpy(temp, buff);

		//totalcmds ++;

		temp[strlen(temp) - 1] = 0; // removing the \n from the end.

		if (strcmp(temp, "history") == 0)
		{
			//hc--;
			hist = 1;
			printf("History command entered. Showing history: \n");
			if (hc > 0)
			{
				if (hc < 10)
				{
					int k;
					for (k = hc-1; k>=0; k--)
					{
						printf("Cmd: %s\n ", histarr[k]);	
					}		
		
				}
				else
				{
					int kk;
					for (kk = 9; kk>=0; kk--)
					{
						printf("Cmd: %s\n ", histarr[kk]);	
					}		
				
				}
			}
			else
			{
				printf("No %s\n");
			}
		}
		else if(strcmp(temp, "history") != 0 && strcmp(temp, "!!") != 0)// Not history command.
		{
			e = temp[0];
			n = temp[1];
			excl2 = 0;
			int chekk = 0;
			//printf("%s\n", "Here");

			if (e == '!' && n != '!')
			{
				if ( n == '0' )
				{
					printf("%s\n", "Only 1-10 inclusive allowed!" );
					chekk = 1;
	
				}
				if (strlen(temp) == 3 && chekk != 1)
				{
					n2 = temp[2];
					if (n2 == '0' && n == '1')
					{
						//printf("%s\n", "!10 was entered!!!" );
						tenCmd = 1;
						excl2 = 1;
					}
					else
					{
						printf("%s\n", "Only 1-10 inclusive allowed!" );
						chekk = 1;
					}
				}
				if (!chekk && !tenCmd)
				{
					//printf("%s\n", "!N entered!");
					excl2 = 1;					
				}
				
			}

			if (!excl2 && !chekk)
			{
				hc++ ; // Increment command count.
				//printf("Total commands: %d\n", hc);

				if (hc <= 10)
				{
					char *temp1 = strdup(temp);
					histarr[hc - 1] = temp1;

					//printf("Command %s added to history array \n", temp1);	
				}
				else if (hc > 10)
				{
					int u;
					for (u = 1; u < 10; u++) // Shift all commands one to the left.
					{
						char * t = strdup(histarr[u]);
						//printf("Replacing %s with %s\n", histarr[u-1], t);
						histarr[u-1] = t;

					}
					char * newcmd = strdup(temp);
					histarr[9] = newcmd; // Add new command to last position
					//printf("Last cmd stored is: %s\n", histarr[9]);
				}	
			}
					
		}
		
		
		//printf("%s\n", buff);

		//printf("total args are: %\d\n" , i);


		// char* newargs[i+1];
		int x;
		int lastele;
		int excl = 0;
		char inputcmd[80];
		int amp = 0;
		int amarray = 0;
		//char * inputcmd1;

		if (strcmp(temp, "!!") == 0) //  execute the last command in histarray
		{
			//printf("%s\n", "Execute last cmd");
			excl = 1;
			amarray = 1;
			//printf ("Hc is %d\n" , hc);

			if (hc >= 10)
			{
				strcpy(inputcmd, histarr[9]);
				//printf("%s\n", "here" );
				//printf("Extracted cmd is %s\n", inputcmd);
								
			}
			else if (hc > 0 && hc < 10)
			{
			
				strcpy(inputcmd, histarr[hc-1]);
				//printf("%s\n", "here3" );
				//printf("Extracted cmd is %s\n", inputcmd);
			}
		}
		// !N
		int whichArg;
		if (excl2 == 1)
		{
			if (tenCmd)
			{
				//printf("%s\n", "need to show 9th cmd" );
				if (hc >= 10)
				{	
					whichArg = 10;
					excl = 1;
					amarray = 1;
					strcpy(inputcmd, histarr[9]);
				}
				else if (hc < 10)
				{
					printf("%s\n", "No such command in history.");

				}
			}
			else
			{
				whichArg = n - '0';
				//printf("Arg num is: %d\n", whichArg);
				if (hc < whichArg)
				{
					printf("%s\n", "No such command in history.");
					fflush(stdout);
				}
				else if (whichArg > 0 && whichArg < 10)
				{
					excl = 1;
					amarray = 1;
					strcpy(inputcmd, histarr[whichArg - 1]);
					
				}
				else
				{
					printf("%s\n", "Usage: Enter !N where N is between 1 and 10 inclusive only");
				}
			}
		}


		if (excl == 0 && hist != 1)
		{
					ch = strtok(buff, " ");
						
					i = 0;
					j = 0;

					while (ch != NULL)
					{
						j++;
						//printf("%s\n", ch);
						args[i] = ch;
						i = i + 1;		
						ch = strtok(NULL, " ");
							
					}
				
					amp = 0;

		}
		else if (excl == 1 && hist != 1)
		{

					//printf("Inputcmd is %s\n",  inputcmd);
					ch = strtok(inputcmd, " ");
						
					i = 0;
					j = 0;

					while (ch != NULL)
					{
						j++;
						//printf("%s\n", ch);
						args[i] = ch;
						i = i + 1;		
						ch = strtok(NULL, " ");
							
					}
		}

		if (hist != 1)
		{
			char* newargs[i+1];
			//printf("Total strings are %d\n", i );

			for (x = 0; x < i; x++)
			{
				newargs[x] = args[x];
				lastele = x;
			}
			
			newargs[x] = NULL;

			if (amarray == 1)
			{
					// Nothing
			}
			else
			{
				int templen = strlen(newargs[j-1])-1; // Position of \n
				newargs[j-1][templen] = 0; // Removing "\n from last arg"		
			}
			
			//printf("%s\n", "ye do" );
			//printf("Command is %s\n", newargs[0]);
			//printf("%s\n", newargs[1]);

			if (strcmp(newargs[lastele], "&") == 0)
			{
				
				amp = 1;
				newargs[lastele] = NULL;	
			}

			if (strcmp(temp, "exit\n") == 0)
			{
				should_run = 0;
			}
			else
			{
				int pid = fork();
				if (pid < 0)
				{ 
					printf ("Fork failed!");
					should_run = 0;
				
				}
				if (pid == 0) // Child process
				{
					//printf("In Child \n");
					execvp(newargs[0], newargs);
				}
				else 
				{
					//printf("I'm in else \n" );
					//wait(2);
					
					if (amp) // concurrent
					{
						//printf("%s\n Here ampersand found");
						
					}
					else
					{
						//printf("Waiting");
						wait(0);		
					}		
				}

				amp = 0;
			}	
			
		}
		hist = 0;

		/**
	         * After reading user input, the steps are:
	         * (1) fork a child process
	         * (2) the child process will invoke execvp()
	         * (3) if command included &, parent will invoke wait()
	         */
    }
    
	return 0;
}
