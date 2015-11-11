#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

char cmd[100];
char *bagian[20];
int posisi=0;
char namakomputer[100];
char namadirektori[100];

int changedir()
{
	if (bagian[1]==NULL) chdir(getenv("HOME"));
		else{
			if(chdir(bagian[1])!=0) fprintf(stderr,"cd: No such file or directory\n");
		    }
		return 0;
}

int jalan(char** bagian,int posisi)
{
	pid_t pid;
	int cek=0;
	if(strcmp(bagian[0],"cd")==0)
	{
		int hasil;
		hasil = changedir();
		return hasil;
	}
	else
	{
		if(strcmp(bagian[posisi-1],"&")==0) cek=1;
		pid = fork();
		if(pid==0)
		{
			if(cek==1) bagian[posisi-1]='\0';
			execvp(bagian[0], bagian);
			return 0;
		}
		else if(pid<0)
		{
			printf("ERROR\n");
			return -1;
		}
		else
		{
			if(cek==1);
			else{
				int status;
				waitpid(pid,&status,0);
			    }
			return 0;
		}
	}
}
	
void signalhandler()
{
	fprintf(stderr,"\n%s@%s:~%s$ ",getenv("LOGNAME"),namakomputer,namadirektori);
}

int main()
{

	while(1){
		gethostname(namakomputer,100);
		getcwd(namadirektori,100);
		printf("%s@%s:~%s$ ",getenv("LOGNAME"),namakomputer,namadirektori);
                signal(SIGTSTP,signalhandler);
		if(fgets(cmd,100,stdin)==NULL){
			printf("\n");
			break;
		}
		if(cmd[strlen(cmd)-1]=='\n') cmd[strlen(cmd)-1]='\0';
		bagian[posisi]=strtok(cmd," ");
		for(posisi=1;posisi<20;posisi++){
			bagian[posisi] = strtok(NULL," ");
			if(bagian[posisi]==NULL) break;
		}
		if(strcmp(cmd, "exit")==0) break;
		else if(jalan(bagian,posisi)==-1) break;
		
	}
	return 0;
}

