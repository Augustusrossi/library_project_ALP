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


void cadastrarTitulo(Livro *livros, int posicao);
void listarTitulos(Livro *livros, int qtdTitulos, int posBusca);
int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado);
int disponibilidadeTitulo(int qtdEstoque);


int disponibilidadeTitulo(int qtdEstoque){
    if (qtdEstoque >= 1)
        return 1;
    else
        return 0;
}



void cadastrarTitulo(Livro *livros, int posicao){
    //ponteiro específico
    Livro *pLivro = &livros[posicao];

    int apenas_numeros = 1;
    int busca_repeticao = -1;  

    do{
        printf("\nDigite o codigo do novo livro: ");
        if (scanf("%d", &pLivro->codigo) == 1 && pLivro->codigo > 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Codigo invalido! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || pLivro->codigo <= 0);
        

    if (posicao != 0) {
        //printf("\nverifica repeticao\n");

        busca_repeticao = buscarTitulo(livros, posicao, pLivro->codigo);
        if (busca_repeticao != -1) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");    

        while (busca_repeticao != -1){
            do{
                printf("\nDigite o codigo do novo livro: ");

                if (scanf("%d", &pLivro->codigo) == 1 && pLivro->codigo > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    break;
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (pLivro->codigo <= 0 || apenas_numeros == 1);
            
            busca_repeticao = buscarTitulo(livros, posicao, pLivro->codigo);
            if (busca_repeticao != -1) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");       
            
        } ;
    }

    do{
        //verifica se o estoque tem letra
        printf("\nDigite a quantidade de exemplares em estoque: ");
        if (scanf("%d", &pLivro->estoque) == 1 && pLivro->estoque >= 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Quantidade invalida! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || pLivro->estoque < 0);


    printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", pLivro->codigo);
    printf("nome: \nautor: \nano: \ngenero: \n");

    printf("descricao%d: ", posicao);
    fgets(pLivro->descricao, TAM_TEXTO, stdin);

    if (pLivro->descricao[0] == '\n' || pLivro->descricao[0] == '\0'){
        do{
            printf("Sem descricao.\n");
            printf("\nDigite algo na descricao: ");
            fgets(pLivro->descricao, TAM_TEXTO, stdin);
        } while (pLivro->descricao[0] == '\n' || pLivro->descricao[0] == '\0');
    }
}

void listarTitulos(Livro *livros, int qtdTitulos, int posBusca){
    int i;
    Livro *pLivro = &livros[posBusca];

    if (posBusca != -1) {
        printf("\n+----------------------------------------+");
        printf("\n|          DETALHES DO LIVRO             |");
        printf("\n+----------------------------------------+");

        printf("\n| Codigo   : %-27d |", pLivro->codigo);
        if (disponibilidadeTitulo(pLivro->estoque))
            printf("\n| Status   : Disponivel (%d em estoque)  |", pLivro->estoque);
        else
            printf("\n| Status   : Indisponivel - Estoque: %d |", pLivro->estoque);

        printf("\n| Descricao: %-27s |", pLivro->descricao);
        printf("\n+----------------------------------------+\n");
    }
    else
    {
        printf("\n==========================================");
        printf("\n          CATALOGO DE LIVROS              ");
        printf("\n==========================================");
        for (i = 0; i < qtdTitulos; i++)
        {

            printf("\n+----------------------------------------+");
            printf("\n| Codigo   : %-27d |", (livros + i)->codigo);
            if ((livros + i)->estoque >= 1)
                printf("\n| Status   : Disponivel (%d em estoque)  |", (livros + i)->estoque);
            else
                printf("\nTitulo indisponivel - Estoque: %d", (livros + i)->estoque);

            printf("\n| Descricao: %-27s |", (livros + i)->descricao);
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
        //printf("\nNao possuimos este titulo no nosso acervo!");
        return posBusca;
    } else {
        return posBusca;
    }
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

    int qtdTitulos = MAX_TITULOS;
    int codBusca;
    int posBusca;
    Livro livros[MAX_TITULOS];
    Livro *pLivros = NULL;


    //Usuario user[MAX_USERS];
    int contadorUsers = 0;
    int contadorLivros = 0, opcao;

    //int *p = NULL;

    pLivros = &livros[0];
    do {
        opcao = menu();
        if(opcao == 1){
            if (contadorLivros < qtdTitulos) {
                cadastrarTitulo(pLivros, contadorLivros);
                contadorLivros++;
                pLivros++;
            }

        } else if(opcao == 2){
            if(contadorLivros == 0){
                printf("\nNao ha titulos cadastrados no momento.\n");
                //printf("\nNao ha titulos cadastrados no momento - %d.\n", sizeof(livros));
            } else {
                listarTitulos(livros, contadorLivros, -1);
            }


        } else if(opcao == 3){
            int apenas_numeros = 1;

            for (int i = 0; i < contadorLivros; i++) {
                printf("Codigo do livro %d: %d\n", i, (pLivros + i)->codigo);
            }
            do {
                
                printf("Digite o codigo do livro que deseja buscar: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    posBusca = buscarTitulo(livros, contadorLivros, codBusca);
                    if (posBusca == -1) {
                        printf("Titulo nao encontrado.\n");
                    } else {
                        printf("Titulo encontrado na posicao: %d\n", posBusca);
                        break;
                    }
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (codBusca <= 0 || apenas_numeros == 1 || posBusca == -1);
                
            
            listarTitulos(livros, contadorLivros, posBusca);
        }
    

        printf("\n==========================================");
        printf("\n        contadorLivros: %d", contadorLivros);
        printf("\n==========================================");


    }while(opcao != 0);
    
}
    