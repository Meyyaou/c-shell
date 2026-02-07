#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


//const
#define SEASHELL_RL_BUFSIZE 1024
//read function
//and hope we dont crash with a buffer overflow haha

//this can be done way easier with getline function
char *seashell_read_line(void){
	
	int buffersize=SEASHELL_RL_BUFSIZE;
	int pos=0;
	//init allocation of buffer
	char *buffer = malloc(sizeof(char)*buffersize);
	int c;
	
	if (!buffer){
		fprintf(stderr, "seashell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(1){
		//read a char
		c=getchar();
		
		//if end of file, reaplce it with a null char and return
		if (c==EOF || c=='\n'){
			buffer[pos]='\0';
			return buffer;
		}else{
			buffer[pos]=c;
		}
		pos++;
		
		//if buffer exceeded, reallocation do
		if (pos>=buffersize){
			buffersize+=SEASHELL_RL_BUFSIZE;
			buffer=realloc(buffer,buffersize);
			if (!buffer){
				fprintf(stderr, "seashell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		} 
	}
}

//const declaration
#define SEASHELL_TOKKEN_BUFSIZE 64
#define SEASHELL_TOKKEN_DELIMITER " \t\r\n\a"
//
char **seashell_split_line(char *line){
	int buffersize=SEASHELL_TOKKEN_BUFSIZE, pos=0;
	char **tokkens = malloc(buffersize * sizeof(char*));
	char *tokken;
	
	if (!tokkens){
	fprintf(stderr, "seashell: allocation error\n");
    exit(EXIT_FAILURE);
	}
	
	//strtok returns pointers to within the str you give it, adds \0 at the end of each tokken.
	tokken= strtok(line, SEASHELL_TOKKEN_DELIMITER);
	while(tokken != NULL){
		tokkens[pos]= tokken;
		pos++;
	if (pos>= buffersize){
		buffersize +=SEASHELL_TOKKEN_BUFSIZE;
		tokkens=realloc(tokkens, buffersize * sizeof(char*));
		if (!tokkens){
			fprintf(stderr, "seashell: allocation error\n");
    		exit(EXIT_FAILURE);
		}
	}
	tokken=strtok(NULL, SEASHELL_TOKKEN_DELIMITER);
	}
	tokkens[pos]= NULL;
	return tokkens;
}

int seashell_launch(char **args){
	pid_t pid, wpid;
	int status;
	
	pid= fork();
	if (pid==0){
		//it's the child process so we call the exec sys call
		if(execvp(args[0], args)==-1){
			perror("seashell");
		}
		exit(EXIT_FAILURE);
	}else if(pid<0){
		//fork error no handeling of it
		perror("seashell");
	}else{
		//it's the parent process
		do{
			//basic process managements with signals and waits
			wpid=waitpid(pid, &status, WUNTRACED);
		}while(!WIFEXITED(status)&& !WIFSIGNALED(status));
	}
	return 1;
}
/*
  forward functions Declarations for builtin shell commands:
 */
int seashell_cd(char **args);
int seashell_help(char **args);
int seashell_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &seashell_cd,
  &seashell_help,
  &seashell_exit
};

int seashell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int seashell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "seashell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("seashell");
    }
  }
  return 1;
}

int seashell_help(char **args)
{
  int i;
  printf("Mey Yaou's SEASHELL:'\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < seashell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int seashell_exit(char **args)
{
  return 0;
}

int seashell_exe(char **args){
	int i;
	if (args[0]==NULL){
		//empty cmd
		return 1;
	}
	for (i =0 ; i<seashell_num_builtins();i++){
		if(strcmp(args[0], builtin_str[i])==0){
			return (*builtin_func[i])(args);
		}
	}
	return seashell_launch(args);
}


void seashell_loop(void){
	//declaration bloc
	char *line;
	char **args;
	int status;
	
	do{
		//prompt printing
		printf("> ");
		//reads line cmd
		line=seashell_read_line();
		//split args
		args=seashell_split_line(line);
		//exectue args
		status=seashell_exe(args);
		
		free(line);
		free(args);
	}while (status);
}

int main(int argc, char **argv){
	seashell_loop();
	return EXIT_SUCCESS;
	}	
