#!/bin/bash

# nombre extensión número ruta
# time(1000, 1): bash files.sh test py 1000 Test  3,14s user 2,90s system 73% cpu 8,269 total
# Bash es más lento por: (a) Es interpretado. (b) Hacer un archivo hace un fork. (c) Corre secuencial.

error() {
    echo $1
    exit 1
}

if [ $# -ne 4 ]; then
    error "Uso: script nombre extensión número ruta"
fi

if [ ! -d $4 ]; then
    error "Error: el directorio no existe"
fi

if [ $3 -lt 1 ]; then
    error "Error: el número de ficheros no puede ser menor que 1"
fi

for ((i = 0; i <= $3; i++)); do
    name="$4/$1$i.$2"
    if [ $i -lt 10 ]; then
        name="$4/$10$i.$2"
    fi
    touch $name
    echo "Fichero $name creado" | tr -s /
done
