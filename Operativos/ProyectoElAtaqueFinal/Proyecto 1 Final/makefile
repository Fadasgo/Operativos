# Archivo con las instrucciones para compilar los
# archivos de codigo fuente y crear el ejecutable.


CC = gcc
CFLAGS = -g -Wall -Wextra
DEPS = buscadorDirectorios.h
OBJETOS = buscadorDirectorios.o ProcesaEntrada.o ProcesaString.o ProcesaManejoDeArchivos.o Procesos.o
PROGRAMA = buscadorDirectorios

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

default: buscadorDirectorios
buscadorDirectorios: $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	-rm -f $(OBJETOS)
	-rm -f $(PROGRAMA)
