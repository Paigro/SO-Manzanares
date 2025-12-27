// HOJA 3 EJERCICIO 9
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

	pid_t pid = fork();
	switch (pid) {
	case-1:
		perror("fork");
		exit(1);
	case 0:
		execvp(argv[1], &argv[1]);
		//execl("/bin/sh", "sh", "-c", argv[1], NULL); // Para el caso donde el argumento es toda una cadena de texto.
		perror("Error al ejecutar el comando");
		exit(1);
	default:
		int status;
		wait(&status);
		if(WIFEXITED(status))
			printf("El proceso hijo terminó con codigo de salida: %i\n", WIFEXITED(status));
		else if(WIFSIGNALED(status))
			printf("El proceso hijo terminó por señal: %i\n", WIFSIGNALED(status));
		break;
	}
	return 0;

}
