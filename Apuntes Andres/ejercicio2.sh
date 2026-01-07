#!/bin/bash
# Obtiene todo lo detallado contenido de /run
ls -aliF /run
# Obtiene los tipos de ficheros del directorio
ls -l /run | cut -c 1 | tail -n +2
