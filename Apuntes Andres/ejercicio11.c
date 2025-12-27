// HOJA 3 EJERCICIO 11
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void escribe(int n_hijo){
	int desct = open("./output.txt", O_WRONLY);
	// Ha habido un error abriendo el archivo
	if(desct == -1) return;

	char buff[6]; // 5 por hijo + \0
	for(int i=0;i<5; i++){
		buff[i] = '0'+ n_hijo; // ponemos 5 veces n_hijo
	}
	buff[5] ='\0';
	// Antes de escribir desplazamos la escritura (5 ceros + (n_hijo-1 *5)
	off_t off= (5 * n_hijo);
	// desplazamos
	lseek(desct,  off, SEEK_SET);
	write(desct, buff, 5);
	close(desct);
}

int main(int argc, char *argv[]){
	// escribimos los 0 iniciales
	int fd = open("./output.txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);
	write(fd, "00000", 5);
	close(fd);
	
	for(int i = 0; i<5; i++){
		pid_t pid = fork();

		switch(pid){
		case -1:
			perror("error en fork");
			exit(1);
		case 0:
			printf("Hijo: %i\n", i);
			escribe(i+1);
			exit(i);
		default:
			printf("Padre\n");
			break;
		}
	}
	int status;
	for(int i=0; i<5;i++){
		pid_t pid = wait(&status);
		printf("Hijo %d con PID %d terminó\n", WEXITSTATUS(status), pid);
	}
	return 0;
}
