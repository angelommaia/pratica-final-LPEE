#!/bin/bash


#####################################################################################################################################################################
##                                                                                                                                                                 ## 
##                                                       Script mk.sh para plotar graficos                                                                         ##
##  Se o projeto estiver preparado para receber inputs manuais, deve ser executado pelo script grafico_de_funcao.sh                                                ##
##  Para rodar o codigo sem abrir outra coisa além do grafico final, deve-se simplesmente executar o arquivo atual com a presenca de um arquivo de dados iniciais  ##                                                                                                                                                             ##                                                                                                                                                                 ##
##                                                                                                                                                                 ##
#####################################################################################################################################################################



#echo "Compilando gerador de gráficos"

cp $PWD/entrada.txt $PWD/codigos/entrada.txt

cd $PWD/codigos/ #acessar a pasta dos codigos

gfortran -c mmq.f90 #compilando o arquivo em fortran

g++ -c jogador.cpp #compilando o arquivo em cpp

g++ jogador.o mmq.o -o  plotar_grafico -lgfortran #linkando os dois codigos. sem o -lgfortran, o g++ nao entende as funcoes em fortran

#echo "Gerador de gráficos compilado!"

$PWD/plotar_grafico #executando o programa compilado 

okular $PWD/novografico.ps #abrindo o arquivo .ps (post script) gerado atraves da biblioteca gnuplot
        
rm mmq.o jogador.o plotar_grafico cpp_input.txt entrada.txt #$PWD/novografico.ps #removendo os arquivos gerados

cd .. #voltar para a pasta raiz do programa

mkdir resultados

mv $PWD/codigos/novografico.ps $PWD/resultados/novografico.ps

mv $PWD/codigos/funcao.txt $PWD/resultados/funcao.txt

exit
        
#OBS:
    #cd eh o comando para acessar determinado diretorio
    #$PWD eh o comando de script que indica o diretorio atual
    #Okular eh o software usado para visualizar o .ps
    #echo eh o stdout em script, semelhante ao print (fortran), cout (c++) e disp (matlab/octave)
    #rm eh o comando para remover arquivos
    #cp eh o comando para copiar arquivos
    #mv eh o comando para mover arquivos
    
