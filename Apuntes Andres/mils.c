// HOJA 2 EJERCICIO 9
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/limits.h>


int main(int argc, char* argv[])
{
	// Cogemos la informacion del fichero
	struct stat st;
	// Cogemos la informacion del archivo.
	if (stat(argv[1], &st) == -1) {
		perror("stat");
		return 1;
	}

	// Comprobamos que sea un directorio
	if (!S_ISDIR(st.st_mode)) {
		perror("No es un directorio");
		return 1;
	}

	// Comprobamos que tengamos permisos
	if (access(argv[1], R_OK | X_OK) == -1) {
		perror("No tienes permisos de lectura");
		return 1;
	}

	// Abrimos un directorio
	DIR* dir = opendir(argv[1]);
	struct dirent* dent;

	// Recorremos las entradas del directorio
	while ((dent = readdir(dir)) != NULL)
	{
		if (dent->d_type == DT_REG)
			printf("%s*\n", dent->d_name);
		if (dent->d_type == DT_DIR)
			printf("%s/\n", dent->d_name);
		if (dent->d_type == DT_LNK)
		{
			char origen[PATH_MAX];
			snprintf(origen, PATH_MAX, "%s/%s", argv[1], dent->d_name);

			char destino[PATH_MAX];
			if (readlink(origen, destino, PATH_MAX) == -1)
			{
				perror("readlink");
				continue;
			}
			printf("%s -> %s\n", origen, destino);
		}
	}

	return 0;
}