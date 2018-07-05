cd /home/hiki/Documentos/projeto-final-lpaee/

gfortran -c mmq.f90
g++ -c jogador.cpp
g++ jogador.o mmq.o -o  teste -lgfortran
