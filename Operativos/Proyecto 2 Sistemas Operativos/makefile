# Archivo con las instrucciones para compilar los
# archivos de codigo fuente y crear el ejecutable.


CC = gcc
CFLAGS = -g -Wall -Wextra -pthread
DEPS = ensamble.h
OBJETOS = ensamble.o ProcesaEntrada.o TablaHash.o Archivo.o hilos.o
PROGRAMA = ensamble

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

default: ensamble
ensamble: $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	-rm -f $(OBJETOS)
	-rm -f $(PROGRAMA)
