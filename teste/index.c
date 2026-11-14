#include <stdio.h>
#include <locale.h>
#define MAX_TITULOS 3
#define MAX_USERS 3
#define TAM_TEXTO 120

typedef struct{
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

typedef struct{
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
} Usuario;

//protótipo de função para não quebrar o código ou haver conflito na ordem de chamada das funções
void cadastrarTitulo(Livro *livros, int posicao);
void listarTitulos(Livro *livros, int qtdTitulos, int posBusca);
int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado);
int disponibilidadeTitulo(int qtdEstoque);


void cadastrarTitulo(Livro *livros, int posicao){
    int i = 0, j = 0;
    // cadastrar codigo e estoque
    //for ( i = 0; i < qtdTitulos; i++) {

    int apenas_numeros = 1;
    do{
        //verifica se o codigo tem letra
        printf("\nDigite o codigo do novo livro: ");
        if (scanf("%d", &livros->codigo) == 1 && livros->codigo > 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Codigo invalido! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || livros->codigo <= 0);
        
        

    if (posicao != 0) {
        //printf("\nverifica repeticao\n");
        int busca_repeticao = -1;
        do {
            
            printf("\nDigite o codigo do novo livro: ");
            scanf("%d", &livros->codigo);

            do{
                printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");
                if (scanf("%d", &livros->codigo) == 1 && livros->codigo > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    break;
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            } while (livros->codigo == livros[j].codigo || livros->codigo <= 0 || apenas_numeros == 1);

            busca_repeticao = buscarTitulo(livros, posicao, livros->codigo);
        } while (busca_repeticao != -1);

    }

    do{
        //verifica se o estoque tem letra
        printf("\nDigite a quantidade de exemplares em estoque: ");
        if (scanf("%d", &livros->estoque) == 1 && livros->estoque >= 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Quantidade invalida! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || livros->estoque < 0);


    printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", livros->codigo);
    printf("nome: \nautor: \nano: \ngenero: \n");

    printf("descricao%d: ", i);
    fgets(livros->descricao, TAM_TEXTO, stdin);

    if (livros->descricao[0] == '\n' || livros->descricao[0] == '\0'){
        do{
            printf("Sem descricao.\n");
            printf("\nDigite algo na descricao: ");
            fgets(livros[i].descricao, TAM_TEXTO, stdin);
        } while (livros[i].descricao[0] == '\n' || livros[i].descricao[0] == '\0');
    }
}

void listarTitulos(Livro *livros, int qtdTitulos, int posBusca){
    int i;

    if (posBusca != -1) {
        printf("\n+----------------------------------------+");
        printf("\n|          DETALHES DO LIVRO             |");
        printf("\n+----------------------------------------+");

        int disponivel = disponibilidadeTitulo(livros[posBusca].estoque);

        printf("\n| Codigo   : %-27d |", livros[posBusca].codigo);
        if (disponivel)
            printf("\n| Status   : Disponivel (%d em estoque)  |", livros[posBusca].estoque);
        else
            printf("\n| Status   : Indisponivel - Estoque: %d |", livros[posBusca].estoque);

        printf("\n| Descricao: %-27s |", livros[posBusca].descricao);
        printf("\n+----------------------------------------+\n");
    }
    else
    {
        printf("\n==========================================");
        printf("\n          CATaLOGO DE LIVROS              ");
        printf("\n==========================================");
        for (i = 0; i < qtdTitulos; i++)
        {

            printf("\n+----------------------------------------+");
            int disponivel = disponibilidadeTitulo(livros[i].estoque);
            printf("\n| Codigo   : %-27d |", livros[i].codigo);
            if (livros[i].estoque >= 1)
                printf("\n| Status   : Disponivel (%d em estoque)  |", livros[i].estoque);
            else
                printf("\nTitulo indisponivel - Estoque: %d", livros[i].estoque);

            printf("\n| Descricao: %-27s |", livros[i].descricao);
            printf("\n+----------------------------------------+");
        }
    }

}

int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado){
    int posBusca = -1, i;

    for (i = 0; i < qtdTitulos; i++) {
        if (codigoBuscado == (livros + i)->codigo) {
            posBusca = i;
        }
    }

    if (posBusca == -1) {
        printf("\nNao possuimos este titulo no nosso acervo!");
        return posBusca;
    } else {
        return posBusca;
    }
}

int disponibilidadeTitulo(int qtdEstoque){
    if (qtdEstoque >= 1)
        return 1;
    else
        return 0;
}



int menu (){
    int opcao;
    printf("\n==========================================");
    printf("\n          MENU DE OPÇÕES                  ");
    printf("\n==========================================");
    printf("\n1 - Cadastrar titulo");
    printf("\n2 - Listar titulos");
    printf("\n3 - Buscar titulo");
    printf("\n4 - Cadastrar usuario");
    printf("\n5 - Listar usuarios");
    printf("\n6 - Registrar emprestimo");
    printf("\n7 - Encerrar emprestimo");
    printf("\n0 - Sair do programa");
    printf("\n==========================================\n");

    do{
        printf("Digite a opção desejada: ");
        if ((scanf("%d", &opcao)) == 1){
            break;
        }

        while ((getchar()) != '\n') ;
    }while (1);

    return opcao;
}


int main(){

    int qtdExemplares = 0, qtdTitulos = 0;
    int codBusca;
    int posBusca;
    Livro livros[MAX_TITULOS];
    Livro *pLivros = NULL;
    
    Usuario user[MAX_USERS];
    int contadorUsers = 0, contadorLivros = 0, opcao;

    //int *p = NULL;

    pLivros = &livros[0];
    do {
        opcao = menu();
        

        if(opcao == 1){
            if (contadorLivros < 3) {
                cadastrarTitulo(pLivros, contadorLivros);
                contadorLivros++;
                pLivros++;
            }
        } else if(opcao == 2){
            listarTitulos(pLivros, contadorLivros, -1);

        } else if(opcao == 3){
            for (int i = 0; i < contadorLivros; i++) {
                printf("Codigo do livro %d: %d\n", i, (pLivros + i)->codigo);
            }
            do {
                printf("Digite o codigo do livro que deseja buscar: ");
            
                scanf("%d", &codBusca);
                posBusca = buscarTitulo(pLivros, contadorLivros, codBusca);
            } while (posBusca == -1);
            
            listarTitulos(pLivros, contadorLivros, posBusca);
        }
        

    }while(opcao != 0);
    
}
