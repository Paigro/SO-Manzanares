// EJERCICIO 8 HOJA 2

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define TBUFF 8192

int main(int argc, char *argv[]){
	char* input_file = argv[1];
	char* output_file = argv[2];
	int block_size = atoi(argv[3]);
	int block_count = atoi(argv[4]);
	int seek = atoi(argv[5]);

	if(TBUFF < block_size) block_size=TBUFF;
	char buffer[TBUFF];
	// Descriptores.
	int d_in, d_out;
	// creamos el descriptor de entrada
	if(strcmp(input_file, "-")==0){
		d_in = 0;
	}else{
		d_in = open(input_file,O_RDONLY);
	}
	// creamos el descriptor de salida.
	if(strcmp(input_file, "-")==0){
		d_out = 0;
	} else{
		d_out =open(output_file,O_WRONLY|O_CREAT|O_TRUNC, 0664);
	}
	// Total de bytes leidos
	int total_bytes = 0;
	while (total_bytes < (block_count * block_size)){
		// bytes leidos en esta vuelta
		int actual_bytes=0;
		//printf("blocksize %i", block_size);
		// Leemos 1 boque
		while(actual_bytes < block_size){
			int n_read = read(d_in,
					buffer + (total_bytes + actual_bytes),
					block_size - actual_bytes);
			// n_read es la cantidad de bytes que hemos leido
			if (n_read == 0){
				break; // salimos del bucle
			}
			printf("total bytes %i || n read %i\n", total_bytes, n_read);
			actual_bytes += n_read;
		}
		if (actual_bytes == 0){ // no se ha leido nada (no hay mas que leer)
			break;
		} else {
			total_bytes += actual_bytes;
		}
	}


	while(total_bytes>0){
		int bytes_escritos = 0;
		while (bytes_escritos < block_size){
			int n_write = write (d_out,
						buffer + (total_bytes - bytes_escritos),
						block_size - bytes_escritos);
			if (n_write == 0) break; // no se ha escrito, salimos del buffer
			printf("total bytes %i || n write %i\n", total_bytes, n_write);
			bytes_escritos += n_write;
		}
		if (bytes_escritos == 0) break; // no hay nada que escribir
		total_bytes -= bytes_escritos;
	}
	// cerramos los descriptores
	close(d_in);
	close(d_out);
	return 0;

}

