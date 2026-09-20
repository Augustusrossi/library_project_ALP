#include <stdio.h>
#define MAX_TITULOS 3
#define TAM_TEXTO 120

int main()
{
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    int qtdExemplares = 0;
    int codBusca;
    int posBusca = -1;
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    
    //escolha pessoal
    /*usar uma variavel descrição e cada uma das outras descrições servir de componente da descrição maior, por exemplo
        descricao 1: O Hobbit (nome)
        descricao 2: J. R. R. Tolkien (autor)
        descricao 3: 1937 (anoPublicacao)
        descricao 4: Fantasia (genero)
        concatencao: descricao1 + ";" + descricao2 + ";" + descricao3 + ";" + descricao4
        descricaoFinal: "O Hobbit; J. R. R. Tolkien; 1937; Fantasia”
    */


    int qtdTitulos = 0;//contador

    

    
    for(qtdTitulos = 0; qtdTitulos < MAX_TITULOS; qtdTitulos++){
        printf("\nDigite o codigo do novo livro: ");
        scanf("%d", &codigos[qtdTitulos]);
        if(codigos[qtdTitulos] < 0){
            do{
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
                printf("Digite o codigo do novo livro: ");
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
        
        
        printf("Digite a quantidade de exemplares em estoque: ");
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
    
    printf("\n==================================================\n==================================================\n");
    
    while (getchar() != '\n');
    for (int i = 0; i <MAX_TITULOS; i++){
        //limpeza de buffer
        
        
        printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", codigos[i]);
        printf("nome: \nautor: \nano: \ngenero: \n");
        
        if(i == 0){
            printf("descricao1: %d", i);
            fgets(descricao1, TAM_TEXTO, stdin);
        }
        if(i == 1){
            printf("descricao2: %d", i);
            fgets(descricao2, TAM_TEXTO, stdin);
        } 
        if(i == 2){
            printf("descricao3: %d", i);
            fgets(descricao3, TAM_TEXTO, stdin);
        }
    }
    
    
    printf("\n==================================================\n==================================================\n");
    
    
    for(int y = 0; y < MAX_TITULOS; y++){
        printf("\nLivro - codigo: %d possui %d exemplares em estoque. - ", codigos[y], estoques[y]);
        
        if(y == 0){
            printf("%s", descricao1);
        }else if(y == 1){
            printf("%s", descricao2);
        } else if(y == 2){
            printf("%s", descricao3);
        }
    }
    
    printf("\n\nO total de livros no sistema eh: %d", qtdExemplares);
    

    printf("\n==================================================\n==================================================\n");
    
    do{
        printf("\n\nDigite um codigo de livro para busca: ");
        scanf("%d", &codBusca);
    } while(codBusca < 0);
    
    for(int x = 0; x < MAX_TITULOS; x++){
        if(codBusca == codigos[x]){
            posBusca=x;
        }
    }
   
    if(posBusca == -1){
        printf("\nNao possuimos este titulo no nosso acervo!");
    } else{
        if(estoques[posBusca] == 0 ){
            printf("titulo temporiamente indisponivel - ");
            if(posBusca == 0){
                printf("%s \n", descricao1);
            }else if(posBusca == 1){
                printf("%s \n", descricao2);
            } else if(posBusca == 2){
                printf("%s \n", descricao3);
            }
            
        }else{
            printf("\ntitulo disponivel");
            printf("\nQuantidade disponivel em estoque para a obra %d: %d - ", codigos[posBusca], estoques[posBusca]);
            if(posBusca == 0){
                printf("%s \n", descricao1);
            }else if(posBusca == 1){
                printf("%s \n", descricao2);
            } else{
                printf("%s \n", descricao3);
            }
        }
    
    }
    
    
}
