#include <stdio.h>
#define MAX_TITULOS 3

int main()
{
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    int qtdExemplares = 0;
    int codBusca;
    int posBusca = -1;

    int qtdTitulos = 0;//contador

    

    
    for(qtdTitulos = 0; qtdTitulos < 3; qtdTitulos++){
        printf("\nDigite o codigo do novo livro: ");
        scanf("%d", &codigos[qtdTitulos]);
        if(codigos[qtdTitulos] < 0){
            do{
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
                printf("\nDigite o codigo do novo livro: ");
                scanf("%d", &codigos[qtdTitulos]);
            }while (codigos[qtdTitulos] < 0);
        }
        
        if(qtdTitulos != 0){
            //printf("\nverifica repetição\n");
            for(int j = 0; j <= qtdTitulos-1; j++){
                //printf("\nj: %d - codigos: %d", j, codigos[j]);
                if(codigos[qtdTitulos] == codigos[j]){
                    do{
                        printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");
                        printf("\nDigite o codigo do novo livro: ");
                        scanf("%d", &codigos[qtdTitulos]);
                    }while (codigos[qtdTitulos] == codigos[j]);
                }
            }
        }
        
        printf("\nDigite a quantidade de exemplares em estoque: ");
        scanf("%d", &estoques[qtdTitulos]);
        
        if(estoques[qtdTitulos] < 0){
            do{
                printf("Quantidade de exemplares invalida. Digite um valor maior ou igual a zero.\n");
                printf("\nDigite a quantidade de exemplares em estoque: ");
                scanf("%d", &estoques[qtdTitulos]);
            }while (estoques[qtdTitulos] < 0);
        }
        
        
        qtdExemplares += estoques[qtdTitulos];
    }
    
    for(int y = 0; y < 3; y++){
        printf("\nLivro - codigo: %d possui %d exemplares em estoque.", codigos[y], estoques[y]);
    }
    
    printf("\n\nO total de livros no sistema eh: %d", qtdExemplares);
    
    
    do{
        printf("\n\nDigite um codigo de livro para busca: ");
        scanf("%d", &codBusca);
    } while(codBusca < 0);
    
    for(int x = 0; x < 3; x++){
        if(codBusca == codigos[x]){
            posBusca=x;
        }
    }
    if(posBusca == -1){
        printf("\nNao possuimos este titulo no nosso acervo!");
    } else{
        if(estoques[posBusca] == 0 )
            printf("titulo temporiamente indisponivel");
        else{
            printf("\ntitulo disponivel");
            printf("\nQuantidade disponivel em estoque para a obra %d: %d", codigos[posBusca], estoques[posBusca]);
        }
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
