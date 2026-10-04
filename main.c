#include <stdio.h>
#define MAX_TITULOS 3
#define TAM_TEXTO 120

int disponibilidadeTitulo( int qtdEstoque){
    if(qtdEstoque >= 1) return 1;
    else return 0;
}

int calcularQtdExemplares(int estoques[], int qtdTitulos){
    int qtdExemplares = 0;
    
    
    for(int i = 0; i < qtdTitulos; i++){
        qtdExemplares += estoques[i];
    }
    
    return qtdExemplares;
}


int cadastrarTitulo( int codigos[], int estoques[], char descricao1[], char descricao2[], char descricao3[], int qtdTitulos){
    
    int qtdExemplares;
    
    //cadastrar codigo e estoque
    for(int i = 0; i < qtdTitulos; i++){
        if(i == 0){
            printf("\nDigite o codigo do novo livro: ");
            scanf("%d", &codigos[i]);
            //printf("\n===== %d =====\n", codigos[i]);
        }
        
        
        if(codigos[i] < 0){
            do{
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
                printf("Digite o codigo do novo livro: ");
                scanf("%d", &codigos[i]);
            }while (codigos[i] < 0);
            
        }
        //printf("\n1===== %d =====\n", codigos[i]);
        //printf("\nqtdTitulos: %d\n", i);
        
        if(i != 0){
          //  printf("\n2===== %d =====\n", codigos[i]);
            printf("\nverifica repetição\n");
            
            printf("\nDigite o codigo do novo livro: ");
            scanf("%d", &codigos[i]);
            for(int j = 0; j <= i-1; j++){
               
            //    printf("\n3===== %d =====\n", codigos[i]);
              //  printf("\nj: %d - codigos: %d\ncodigo em qtdTitulos: %d\nqtdTitulos: %d\n", j, codigos[j], codigos[i], i);
                
                if(codigos[i] == codigos[j]){
                //    printf("\n4===== %d =====\n", codigos[i]);
                    do{
                        printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");
                        printf("\nDigite o codigo do novo livro: ");
                        scanf("%d", &codigos[i]);
                    }while (codigos[i] == codigos[j]);
                }
            }
        }
        
        //quantidade em esotque
        printf("Digite a quantidade de exemplares em estoque: ");
        scanf("%d", &estoques[i]);
        
        if(estoques[i] < 0){
            do{
                printf("Quantidade de exemplares invalida. Digite um valor maior ou igual a zero.\n");
                printf("\nDigite a quantidade de exemplares em estoque: ");
                scanf("%d", &estoques[i]);
            }while (estoques[i] < 0);
        }
        
        //buffer. limpeza do \n
        //while ((codigos[i] = fgetc(stdin)) != '\n' && codigos[i] != EOF);
     
        //cadasro da descrição 
    }
    
    
    //buffer. limpeza do \n
    while ((codigos[qtdTitulos] = fgetc(stdin)) != '\n' && codigos[qtdTitulos] != EOF);
    
    for (int i = 0; i <MAX_TITULOS; i++){
        //limpeza de buffer
        
        
        printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", codigos[i]);
        printf("nome: \nautor: \nano: \ngenero: \n");
        
        if(i == 0){
            printf("descricao1: ");
            fgets(descricao1, TAM_TEXTO, stdin);
        }
        if(i == 1){
            printf("descricao2: ");
            fgets(descricao2, TAM_TEXTO, stdin);
        } 
        if(i == 2){
            printf("descricao3: ");
            fgets(descricao3, TAM_TEXTO, stdin);
        }
    }
    
    qtdExemplares = calcularQtdExemplares(estoques, qtdTitulos);
    return qtdExemplares;
}



void listarTitulos(int codigos, int estoques, char descricao1[], char descricao2[], char descricao3[], int qtdTitulos, int posBusca){
    //for com tamnaho max sendo o max de valores nos arrays e printf no conteudo do indice
    //for(int i = 0; i < qtdTitulos; i++){
    int disponivel = disponibilidadeTitulo(estoques);
    printf("\n==============");
    printf("\nCodigo: %d", codigos);
    if(estoques >= 1) printf("\nTitúlo disponível - Estoque: %d", estoques);
    else printf("\nTitúlo indisponível - Estoque: %d", estoques);
    if(posBusca == 0) printf("\nDescricao: %s", descricao1);
    else if(posBusca == 1) printf("\nDescricao: %s", descricao2);
    else printf("\nDescricao: %s", descricao3);
    printf("==============\n");
    //}
}



int buscarTitulo(int codigos[], int qtdTitulos, int codigoBuscado){
    int posBusca = -1;

    for(int x = 0; x < qtdTitulos; x++){
        if(codigoBuscado == codigos[x]){
            posBusca=x;
        }
    }
   
    if(posBusca == -1){
        printf("\nNao possuimos este titulo no nosso acervo!");
        return posBusca;
    } else{
        return posBusca;
    }
}


int main(){
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    int qtdExemplares = 0;
    int codBusca;
    int posBusca;
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    
    qtdExemplares = cadastrarTitulo(codigos, estoques, descricao1, descricao2, descricao3, MAX_TITULOS);
    
    //escolha pessoal
    /*usar uma variavel descrição e cada uma das outras descrições servir de componente da descrição maior, por exemplo
        descricao 1: O Hobbit (nome)
        descricao 2: J. R. R. Tolkien (autor)
        descricao 3: 1937 (anoPublicacao)
        descricao 4: Fantasia (genero)
        concatencao: descricao1 + ";" + descricao2 + ";" + descricao3 + ";" + descricao4
        descricaoFinal: "O Hobbit; J. R. R. Tolkien; 1937; Fantasia”
    */
    
    printf("\n\nO total de livros no sistema eh: %d", qtdExemplares);

    printf("\n==================================================\n==================================================\n");
    
    for(int i = 0; i < MAX_TITULOS; i++){
        printf("\n%d", codigos[i]);
    }
    
    printf("\n==================================================\n==================================================\n");
    
    do{
        printf("\n\nDigite um codigo de livro para busca: ");
        scanf("%d", &codBusca);
    } while(codBusca < 0);
    posBusca = buscarTitulo(codigos, MAX_TITULOS, codBusca);
    
    if(posBusca != -1){
       listarTitulos(codigos[posBusca], estoques[posBusca], descricao1, descricao2, descricao3, MAX_TITULOS, posBusca);
    }
    
    
    
    
    
}
