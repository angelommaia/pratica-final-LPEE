!comentar ou remover o comentario dependendo da situacao

subroutine mmqfortran
!program mmqfortran

IMPLICIT NONE
INTEGER :: i, j, m, k, g, quant_amostras
REAL :: MAT(100,100), VET(100), soma, COEF(100) !mat eh uma matrix mXm
!REAL,DIMENSION(:,:),ALLOCATABLE::MAT !aqui dizemos que a dimensao da matriz MAT deve ser alocada dinamicamente
REAL,ALLOCATABLE::X(:), F(:) !alocacao dinamica
character dummy

COMMON/PLOT/ m, quant_amostras


    open (unit=123, file="cpp_input.txt", status="unknown", action="write")!abertura do novo arquivo
    open (unit=321, file="entrada.txt", status="unknown", action="read")!abertura do novo arquivo 
    
    read(321,*)dummy !texto 
    read(321,*)m
    read(321,*)dummy !texto
    read(321,*)quant_amostras
    !PRINT*, 'Ordem do polinomio(maximo 99): ', m 
    m = m+1
    !PRINT*, 'Quantidade de amostras', quant_amostras
    
    ALLOCATE(X(quant_amostras))
    ALLOCATE(F(quant_amostras))

    WRITE(123,*) 'Valores de X'
    
    read(321,*)dummy !texto
        
    DO i=1,quant_amostras,1
        READ(321,*) X(i),F(i)
        WRITE(123,*) X(i)
    END DO
    
    WRITE(123,*) 'Valores de F(X)'
    DO i=1,quant_amostras,1
        WRITE(123,*) F(i)
    END DO

    DO i=1,quant_amostras,1
        print*,'X'
        !WRITE(*,*) X(i)
        print*,'FX'
        !WRITE(*,*) F(i)
    END DO

    soma = 0

    DO i=1,m+1,1

        DO j=1,i,1

            soma = 0
            k=i+j-2

            DO g=1,quant_amostras,1
                !Nessa parte que ocorre a soma dos termos relacionados a x da matriz do metodo dos minimos quadrados
                soma = soma + X(g)**k

            END DO
            !Aqui ocorre a atribuicao da soma
            MAT(i,j) = soma
            MAT(j,i) = soma

        END DO

        soma = 0

            DO g=1,quant_amostras,1
                !Nessa parte é feita a soma dos termos do vetor f(x)*x
                soma = soma +F(g)*(X(g)**(i-1))

            END DO
        !Aqui é atribuido a soma dos termos calculados acima
        VET(i) = soma

    END DO
    !Nessa parte é feita a reducao da matriz para facilitar o calculo da solucao dos coeficientes
    DO k=1,m-1,1
        DO i=k+1,m,1

            DO j=k+1,m,1

                MAT(i,j)= MAT(i,j) - (MAT(i,k)/MAT(k,k))*MAT(k,j)

            END DO

            VET(i) = VET(i)- (MAT(i,k)/MAT(k,k))*VET(k)

        END DO

    END DO

   !Aqui os valores dos coeficientes são atribuidos
    DO i=1,m,1
        COEF(i) = VET(i)/MAT(i,i)
    END DO

    soma = 0

    DO i = m-1,1,-1
        soma = 0

        DO j=i+1,m,1
            soma = soma + MAT(i,j)*COEF(j)
        END DO

    COEF(i) = (VET(i)-soma)/MAT(i,i)

    END DO

    WRITE(123,*) 'COEFICIENTES'
    DO i=0,m,1
        !PRINT*, COEF(i+1), '* X^',(i)
        WRITE(123,*) COEF(i+1)
    END DO

!deallocate(MAT) !necessario desalocar a memoria após o uso
    deallocate(X)
    deallocate(f)
    close(123)
    close(321)
END
