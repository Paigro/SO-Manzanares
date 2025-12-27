// HOJA 3 EJERCICIO 2
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>

int main(int argc, char *argv[]){
	unsigned int pid= getpid();
	if (argc == 1) pid = atoi(argv[1]);
	printf("PID: %ui\nPPID: %ui\nPGID: %ui\nSID: %ui\n",
		pid,
		getppid(),
		getpgid(pid),
		getsid(pid));
	char buf[PATH_MAX];
	getcwd(buf, PATH_MAX);
	printf("Directorio de trabajo: %s\nIdentificador de usuario: %ui\nIdentificador de grupo: %ui\n",
		buf,
		getuid(),
		getgid());
	return 0;
}
