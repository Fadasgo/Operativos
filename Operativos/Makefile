# Archivo con las instrucciones para compilar los
# archivos de codigo fuente y crear el ejecutable.


CC = gcc
CFLAGS = -g -pthread -Wall -Wextra
DEPS = tls.h
OBJETOS = tls.o Funciones.o Pila.o Cola.o
PROGRAMA = tls

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

default: tls
tls: $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	-rm -f $(OBJETOS)
	-rm -f $(PROGRAMA)
