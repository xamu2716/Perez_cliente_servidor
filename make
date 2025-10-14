GCC = gcc
FLAGS = 

PROGRAMAS = cliente servidor

cliente:
	$(GCC) $@.C -O $@ $(FLAGS)
servidor:
	$(GCC) $@.C -O $@ $(FLAGS)
	
clean:
	$(RM) $(PPROGRAMAS)
	
