# Makefile in src/

compiler     = gcc
error_handling  = -Wall -Wextra
directory     = ../bin
location = $(directory)/customshell

src_files    = customshell.c utility.c
objects    = $(patsubst %.c, $(directory)/%.o, $(src_files))

all: $(location)

$(directory)/%.o: %.c header.h
	mkdir -p $(directory)
	$(compiler) $(error_handling) -c $< -o $@

$(location): $(objects)
	$(compiler) $(error_handling) -o $@ $(objects)

clean:
	rm -f $(directory)/*.o $(location)
