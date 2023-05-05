#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_CMD_LEN 1024

void display_kernel_atlaunch() {
    	printf("      __________________\n");
    	printf("    .-'  \\ _.-''-._ /  '-.\n");
    	printf("  .-\\/   .'.      .'.   /\\-. \n");
    	printf(" _'/  \\.\"   \'.  .\'   \"/./  \\_\n");
    	printf(":======:======::======:======:\n");
    	printf(" '. \".  \\     ''     /  .\" .'\n");
    	printf("   '. \". \\   :  :   / .\" .'\n");
    	printf("     '.'. \\ '  ' /  .'.'\n");
    	printf("       ':\\  \\:/:/  :'\n");
    	printf("         '.\\  /.'\n");
    	printf("           '\\/'\n");
	printf("You can execute external commands, use `help` to see the different internal commands you can use or type `exit` to exit the shell\n");
}

int main() {

    	char input[MAX_CMD_LEN];
    	char *args[MAX_ARGS];
    	int status;
	display_kernal_atlaunch();
    	while (1) {
        	printf("$ ");
        	fflush(stdout);

        	// Read command input from user
        	if (!fgets(input, MAX_CMD_LEN, stdin))
        	    break;
	
        	// Parse command into arguments
        	int i = 0;
        	args[i] = strtok(input, " \t\n");
        	while (args[i] && i < MAX_ARGS - 1) {
        	    i++;
        	    args[i] = strtok(NULL, " \t\n");
        	}

        	// Check if the last argument is the '&' symbol
        	if (i > 0 && strcmp(args[i-1], "&") == 0) {
        	    // Multiple commands, split them and execute in parallel
        	    args[i-1] = NULL; // Remove the '&' symbol from the argument list
	
	            // Handle internal commands
	            if (args[0] && strcmp(args[0], "exit") == 0)
	                break;
	            else if (args[0] && strcmp(args[0], "print") == 0)
	                printf("Current pid: %d\n", getpid());
	            else if (args[0] && strcmp(args[0], "help") == 0) {
	                printf("This is a simple shell that can execute external commands as well as internal commands.\n");
	                printf("To execute an external command, simply enter the name of the command and its arguments.\n");
	                printf("To execute an internal command, enter one of the following:\n");
	                printf("\texit: terminate the shell\n");
	                printf("\tprint: print out the current pid\n");
	                printf("\thelp: display this help message\n");
	            }
	            else {
	                // Handle external commands
	                pid_t pid = fork();
	                if (pid == -1) {
	                    perror("fork");
	                    exit(EXIT_FAILURE);
	                }
	                else if (pid == 0) {
       	             // Child process
        	            execvp(args[0], args);
        	            perror(args[0]);
        	            exit(EXIT_FAILURE);
        	        }
        	    }
        	}
        	else {
        	    // Single command
        	    // Handle internal commands
        	    	if (args[0] && strcmp(args[0], "exit") == 0)
        	        	break;
            	   	else if (args[0] && strcmp(args[0], "print") == 0)
                		printf("Current pid: %d\n", getpid());
            		else if (args[0] && strcmp(args[0], "help") == 0) {
                		printf("This is a simple shell that can execute external commands as well as internal commands.\n");
                		printf("To execute an external command, simply enter the name of the command and its arguments.\n");
                		printf("To execute an internal command, enter one of the following:\n");
                		printf("\texit: terminate the shell\n");
                		printf("\tprint: print out the current pid\n");
                		printf("\thelp: display this help message\n");
            		}
            		else {
                		// Handle external commands
                		pid_t pid = fork();
                		if (pid == -1) {
                    			perror("fork");
                    			exit(EXIT_FAILURE);
                		}
                		else if (pid == 0) {
               			     // Child process
                		    execvp(args[0], args);
                    		    perror(args[0]);
                    	            exit(EXIT_FAILURE);
                		}
                		else {
                    		// Parent process
                    			waitpid(pid, &status, 0);
                		}		
            		}
        	}
    	}

    	printf("Exiting Simple Shell\n");
    	return 0;
}

