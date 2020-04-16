#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
const int MAX = 500;
char cwd[1024];
extern char **environ;
char *stored_path[100];

char* gettingEnv(){
	int j=0;
	char *env , *str;
	char *tok[100], *saveptr;
	env = getenv("PATH");
	for (j=0,str=env; ;str= NULL,j++) {
		tok[j] = strtok_r(str, ":", &saveptr);
		if (tok[j] == NULL) break;
		stored_path[j]=tok[j];
	}
	int i = 0;
	while(tok[i] != 0){
		tok[i]=NULL;
	i++;
	}

	return 0;
}


int process(char *input_str){
	int i = 0;
	pid_t pid;
	char *str = strtok(input_str," ");
	char *tok[100];
	char *stored_str[100];
	while(tok[i] != 0){
		tok[i] = NULL;
		i++;
	}
	i = 0;
	while(str != NULL){
		tok[i] = str;
		str = strtok(NULL," ");
		stored_str[i] = tok[i];
		i++;
	}
	if(strcmp(stored_str[0],"cd") == 0){
		if(chdir(stored_str[1]) == 0);
		else printf("cd_failed");
	}else{
		pid = fork();
		if(pid < 0){
			perror("fork error");
			exit(0);
		}else if(pid == 0){
			if(strcmp(stored_str[0],"ls") == 0){
				execv("/bin/ls",stored_str);
			}else if(strcmp(stored_str[0],"cp")==0){
				execv("/bin/cp",stored_str);
			}else if(strcmp(stored_str[0],"pwd")==0){
				execv("/bin/pwd",stored_str);
			}
			exit(0);
		}else{
			wait(0);
		}
	}
	i = 0;
	while(stored_str[i] != NULL){
		stored_str[i] = NULL;
		i++;
	}
	return 0;
}


int main(){
	int i = 0;
	char str[100];
	char *tok[100];
	gettingEnv();
	while(1){
		getcwd(cwd,sizeof(cwd));
		printf("%s >>>",cwd);
		fgets(str,sizeof(str),stdin);
		str[strlen(str)-1] = '\0';
		if(strcmp(str,"quit")==0){
			exit(0);
		}
		process(str);
		}	
	 return 0;
}
