// HOJA 2 EJERCICIO 4
#include <string.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


int main(int argc, char* argv[])
{
	char* script_path = argv[1];
	struct stat sb;

	// si la llamada al lstat devuelve -1 (error)
	if (lstat(script_path, &sb) == -1) {
		char* s;
		perror(s);
		printf("Error en stat: %s\n", s);
		return 1;
	}

	printf("inodo: %ld\n", sb.st_ino);
	printf("numero de dispositivo: [%d,%d]\n", major(sb.st_dev), minor(sb.st_dev));

	// Tipo de archivo usando macros
	printf("tipo: ");
	if (S_ISREG(sb.st_mode)) printf("Fichero regular\n");
	else if (S_ISDIR(sb.st_mode)) printf("Directorio\n");
	else if (S_ISLNK(sb.st_mode)) printf("Enlace simbólico\n");
	else printf("otro\n");

	// Timestamps
	printf("Ultimo cambio de estado: %s", ctime(&sb.st_ctime));
	printf("Ultimo acceso: %s", ctime(&sb.st_atime));

	return 0;
}