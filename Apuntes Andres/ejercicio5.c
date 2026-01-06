// HOJA 3 EJERCICIO 5
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	//if (argc != 2){
	//	printf("args: Seg Padre, Seg Hijo\n");
	//}
	int seg_padre = atoi(argv[1]);
	int seg_hijo = atoi(argv[2]);
	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		perror("fork");
		exit(1);
	case 0:	// HIJO
		// ESTO SE USA PARA LLAMAR A OTROS PROGRAMAS SIN PERDER LA EJECUCION DE ESTE
		//char str_pid[11]; // unsigned int de 32 tiene maximo 10 digitos + \0
		//sprintf(str_pid, "./ejercicio2 %u", getpid());
		// imprimimos las cosas (Ejercicio 2).
		//system(str_pid);
		//fflush(stdout);
		printf("HIJO EMPIEZA\n");
		sleep(seg_hijo);
		printf("HIJO TERMINA\n");
		//fflush(stdout);
		break;
	default: // PADRE.
		wait(NULL);
		//char str_pid[11]; // unsigned int de 32 tiene maximo 10 digitos + \0
		//sprintf(str_pid, "./ejercicio2 %u", getpid());
		// imprimimos las cosas (Ejercicio 2).
		//system(str_pid);
		//fflush(stdouT); // FUERZA LA SALIDA POR SALIDA STANDAR
		printf("PADRE EMPIEZA\n");
		sleep(seg_padre);
		printf("PADRE TERMINA\n");
		//fflush(stdout);
		break;
	}

	//perror("execl");
	return 0;
}
