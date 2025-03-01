// requirements:
// * gnuplot has to be installed (http://www.gnuplot.info/download.html)
// * for Windows: set Path-Variable for Gnuplot path (e.g. C:/program files/gnuplot/bin)
//             or set Gnuplot path with: Gnuplot::set_GNUPlotPath(const std::string &path);

//=====Diretivas de Pre Compilacao====//
#include <iostream>
#include <cmath>
#include "gnuplot_i.hpp" //ate o fim, diretivas do gnuplot
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
 #include <conio.h>   //for getch(), needed in wait_for_key()
 #include <windows.h> //for Sleep()
 void sleep(int i) { Sleep(i*1000); }
#endif
#define SLEEP_LGTH 2  // sleep time in seconds
void wait_for_key(); // programa espera ate uma tecla ser pressionada
using namespace std;


                        /************************************************************************************************************************
                        * No bloco extern, passamos as variaveis do fortran para o C.                                                           *
                        * Para realizarmos essa passagem, devemos, pensar em algumas coisas, sendo a correspondência de tipos a primeira delas. *
                        * O INTEGER do fortran chega ao C como int, já o REAL, chega como float.                                                *   
                        * Vale notar também que vetores do C começam em 0, no fortran, em 1.                                                    *
                        * As variáveis da extern struct, localizada no bloco extern, so podem ser chamadas apos serem utilizadas no fortran.    *
                        * No nosso caso, as variaveis podem ser chamadas após o uso da subrotina mmqfortran_();.                                *
                        *                                                                                                                       *    
                        *************************************************************************************************************************/

extern"C"{ 
        
    void mmqfortran_(); //Subrotina do arquivo mmq.f90. Realiza o metodo dos minimos quadrados. 
    
    extern struct{
        int m, quant_amostras; //dimensao da equacao, dada pelo usuario e quantidade de amostras fornecidas
    } plot_; //bloco common da rotina em fortran
}


void graph_2d(float a[], float b[], float c[]){

    
    float valor_y=0; 
    
    try{
        Gnuplot g1("Grafico1");

        cout << "Plotando Grafico sem ajuste" << endl;
        g1.set_title("Janela Comparativa");
        g1.showonscreen(); // window output
        
        std::vector<double> x, y; //vetores que armazenam as variaveis

            for (int i = 1; i <=plot_.quant_amostras; i++){ //nesse laco, simplesmente armazenamos os pontos dados pelo usuario 
                x.push_back(a[i]); // x[i]
                y.push_back(b[i]); // y[i]
            }
              
        g1.set_grid();
        
        g1.set_style("points").set_pointsize(3).plot_xy(x,y,"Pontos definidos Pelo Usuario"); //aqui plotamos os dados fornecidos pelo usuario em forma de pontos

        
        cout << "Plotando Grafico ajustado" << endl;
        
        std::vector<double> xb, yb; //vetores para os pontos ajustados
        
            for (int i =1 ; i <= plot_.quant_amostras; i++){  // laço mais externo do preenchimento dos pontos ajustados. variacao das amostras

                valor_y=0; //devemos zerar o valor_y para cada i, caso contrário, teremos um somatório de valor_y
                    
                ///melhorar esse laço, pois ainda plotamos a funcao de forma grosseira, AUMENTAR A QUANTIDADE DE PONTOS
                
                   
                    
                    cout<<"valor de plot_.m "<<plot_.m<<endl;
                    
                    for (int j=1 ; j<=plot_.m; j++){ //nesse laço, calculamos a funcao em cada x. variacao das dimensoes 
                        
                    valor_y = valor_y+c[j]*pow(a[i],j-1);// y=a+bx+cx²+...
                        //y = valor anterior + coefiente*x^i, sendo x variavel e coef fixo para cada x 
                        
                    }
                std::cout<<"valor_y["<<i<<"]: "<<valor_y<<std::endl; 
                    
                xb.push_back(a[i]); //x[i]
                yb.push_back(valor_y); // y[i]
            }
            
        g1.set_grid();
        g1.set_style("lines").plot_xy(xb,yb,"Pontos Ajustados Pelo Metodo "); //plotamos o grafico ajustado pelo metodo e podemos ver a distribuição dos pontos do usuario, sobre ele, ja que a plotagem eh feita na mesma janela g1.

     
//==============================================
    /*    float vetor_dados[10];
        
        std::vector<double> xb, yb; //vetores para os pontos austados
        
        int aux=1;
        vetor_dados[0]=a[0];
        
        for (int i=2 ; i <= 10; i=i+2){
            vetor_dados[i]=((a[aux-1]+a[aux])/2);
            aux=aux+1;
        }
        aux=1;
         for (int i=0 ; i < 5; i++){  
            vetor_dados[2*i+1]=((a[aux-1]+a[aux])/2);
             aux=aux+1;
        }
        
            for (int var_amostras=0 ; var_amostras < 10; var_amostras++){  // laço mais externo do preenchimento dos pontos ajustados. variacao das amostras

                valor_y=0; //devemos zerar o valor_y para cada i, caso contrário, teremos um somatório de valor_y
                    
                ///melhorar esse laço, pois ainda plotamos a funcao de forma grosseira, AUMENTAR A QUANTIDADE DE PONTOS
                
                    for (int var_dim=0 ; var_dim<plot_.m; var_dim++){ //nesse laço, calculamos a funcao em cada x. variacao das dimensoes 
                        
                            valor_y = valor_y+c[var_dim]*pow(a[var_amostras],var_dim);// y=a+bx+cx²+...
                            //y = valor anterior + coefiente*x^i, sendo x variavel e coef fixo para cada x 
                    
                    }
                std::cout<<"valor_y["<<var_amostras<<"]: "<<valor_y<<std::endl; 
                    
                
                xb.push_back(vetor_dados[var_amostras]); //x[i]
                yb.push_back(var_amostras); // y[i]
            }
            
            
        g1.set_grid();
        g1.set_style("lines").plot_xy(xb,yb,"Grafico ajustado"); //plotamos o grafico ajustado pelo metodo e podemos ver a distribuição dos pontos do usuario, sobre ele, ja que a plotagem eh feita na mesma janela g1.
        */
        wait_for_key(); //funcao fornecida pelo gnuplot usada para que o grafico nao desapareca repentinamente 

    }
    
    catch (GnuplotException ge){
        cout << ge.what() << endl;
    }
    
}

//===FUNCAO QUE IMPRIME OS COEFICIENTES NA TELA===//
void lista_coeficientes(float a[],float b[], float c[]){
    
    cout<<"Coeficientes"<<endl;
        
        for (int var=1;var<=plot_.m;var++){
        
            //if (c[var]!=0){
                printf("%f*X^%d\n",c[var], var-1);
            //}
        }            
    
    cout<<"Pontos informados pelo Usuario"<<endl;
    
        for (int var=1;var<=plot_.quant_amostras;var++){
        
            printf("X=%f. F[X]=%f \n", a[var],b[var] );
    
        }     
}


void leitura_arquivo(float a[],float b[],float c[]){
    
    char str[30];
    FILE *arch;
    arch=fopen("cpp_input.txt","r");
    
    fgets(str, 25, arch);//linha de texto, deve ser ignorada
    
    for(int i=1;i<=plot_.quant_amostras;i++){
        fgets(str, 25, arch);
        a[i]=atof(str); //tranforma o float apontado pela string em um float de fato
    }
    
    fgets(str, 25, arch);//linha de texto, deve ser ignorada
  
    for(int i=1;i<=plot_.quant_amostras;i++){
        fgets(str, 25, arch);
        b[i]=atof(str); //tranforma o float apontado pela string em um float de fato
    }
    
    fgets(str, 25, arch);//linha de texto, deve ser ignorada
  
    for(int i=1;i<=plot_.m;i++){
        fgets(str, 25, arch);
        c[i]=atof(str); //tranforma o float apontado pela string em um float de fato
    }    
} 

int main(int argc, char* argv[]){    
    
    mmqfortran_(); //gera arquivo com coeficientes e passa 
    
    float X[plot_.quant_amostras], Y[plot_.quant_amostras], COEF[plot_.m];
    
    leitura_arquivo(X,Y,COEF);
    
    /*std::cout<<"X: "<<X[1]<<' '<<X[2]<<' '<<X[3]<<std::endl; 
    std::cout<<"Y: "<<Y[1]<<' '<<Y[2]<<' '<<Y[3]<<std::endl; 
    std::cout<<"COEF: "<<COEF[1]<<' '<<COEF[2]<<' '<<COEF[3]<<std::endl;
    */
    lista_coeficientes(X,Y,COEF);
    graph_2d(X,Y,COEF);
    
return 0;
}




//===FUNCAO NECESSARIA PARA O GRAFICO NAO "SUMIR" IMEDIATAMENTE APOS SER PLOTADO===//
void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) 
    cout << endl << "Pressione qualquer tecla para continuar" << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Pressione ENTER para continuar" << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
