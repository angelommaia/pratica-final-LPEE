#include<iostream>
#include<cstdlib>
#include<cstdio>

void leitura_arquivo(float a[],float b[],float c[]){
    
    char str[30];
    float aaa;
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



int main(){
    
    int quant_amostras=3;
    float X[quant_amostras], Y[quant_amostras], abacate[quant_amostras];
    leitura_arquivo(X, Y, abacate);
    
    
    std::cout<<"X: "<<X[1]<<' '<<X[2]<<' '<<X[3]<<std::endl; 
    std::cout<<"Y: "<<Y[1]<<' '<<Y[2]<<' '<<Y[3]<<std::endl; 
   std::cout<<"COEF: "<<abacate[0]<<' '<<abacate[1]<<' '<<abacate[2]<<std::endl;
return 0;
}
