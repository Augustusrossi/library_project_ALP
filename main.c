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



int disponibilidadeTitulo(int qtdEstoque){
    if (qtdEstoque >= 1)
        return 1;
    else
        return 0;
}

int calcularQtdExemplares(Livro livros[], int qtdTitulos){
    int qtdExemplares = 0;

    for (int i = 0; i < qtdTitulos; i++)
    {
        qtdExemplares += livros[i].estoque;
    }

    return qtdExemplares;
}

void cadastrarTitulo(Livro livros[], int qtdTitulos){
    int caractere;
    // cadastrar codigo e estoque
    for (int i = 0; i < qtdTitulos; i++) {
        if (i == 0) {
            do{
                printf("\nDigite o codigo do novo livro: ");
                if ((scanf("%d", &livros[i].codigo)) == 1){
                    break;
                }

                while ((caractere = getchar()) != '\n' && caractere != EOF) ;
            }while (1);
        }

        if (i != 0) {
            //printf("\nverifica repeticao\n");

            printf("\nDigite o codigo do novo livro: ");
            scanf("%d", &livros[i].codigo);
            for (int j = 0; j <= i - 1; j++){

                if (livros[i].codigo == livros[j].codigo){
                    do{
                        printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");
                        printf("\nDigite o codigo do novo livro: ");
                        scanf("%d", &livros[i].codigo);
                    } while (livros[i].codigo == livros[j].codigo);
                }
            }
        }

        if (livros[i].codigo <= 0) {
            do {
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
                printf("Digite o codigo do novo livro: ");
                scanf("%d", &livros[i].codigo);
            } while (livros[i].codigo <= 0);
        }
        while ((caractere = getchar()) != '\n' && caractere != EOF);

        printf("Digite a quantidade de exemplares em estoque: ");
        scanf("%d", &livros[i].estoque);

        if (livros[i].estoque < 0){
            do{
                printf("Quantidade de exemplares invalida. Digite um valor maior ou igual a zero.\n");
                printf("\nDigite a quantidade de exemplares em estoque: ");
                scanf("%d", &livros[i].estoque);
            } while (livros[i].estoque < 0);
        }

        while ((caractere = getchar()) != '\n' && caractere != EOF);

        printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", livros[i].codigo);
        printf("nome: \nautor: \nano: \ngenero: \n");

        printf("descricao%d: ", i);
        fgets(livros[i].descricao, TAM_TEXTO, stdin);

        if (livros[i].descricao[0] == '\n' || livros[i].descricao[0] == '\0'){
            do{
                printf("Sem descricao.\n");
                printf("\nDigite algo na descricao: ");
                fgets(livros[i].descricao, TAM_TEXTO, stdin);
            } while (livros[i].descricao[0] == '\n' || livros[i].descricao[0] == '\0');
        }
    }

    // int qtdExemplares = calcularQtdExemplares(livros, qtdTitulos);
    // return qtdExemplares;
}

void listarTitulos(Livro livros[], int qtdTitulos, int posBusca){
    // for com tamnaho max sendo o max de valores nos arrays e printf no conteudo do indice
    // for(int i = 0; i < qtdTitulos; i++){

    if (posBusca != -1) {

        int disponivel = disponibilidadeTitulo(livros[posBusca].estoque);

        printf("\n==============");
        printf("\nCodigo: %d", livros[posBusca].codigo);
        if (disponivel >= 1)
            printf("\nTitúlo disponível - Estoque: %d", disponivel);
        else
            printf("\nTitúlo indisponível - Estoque: %d", disponivel);

        printf("\nDescricao: %s", livros[posBusca].descricao);
        printf("==============\n");
    }
    else
    {
        printf("\n======= LIVROS NO ACERVO =======");
        for (int i = 0; i < qtdTitulos; i++)
        {
            printf("\n==============\n");
            int disponivel = disponibilidadeTitulo(livros[i].estoque);
            printf("\nCodigo: %d", livros[i].codigo);
            if (livros[i].estoque >= 1)
                printf("\nTitúlo disponível - Estoque: %d", livros[i].estoque);
            else
                printf("\nTitúlo indisponível - Estoque: %d", livros[i].estoque);

            printf("\nDescricao: %s", livros[i].descricao);
        }
    }

    //}
}

int buscarTitulo(Livro livros[], int qtdTitulos, int codigoBuscado){
    int posBusca = -1;

    for (int i = 0; i < qtdTitulos; i++)
    {
        if (codigoBuscado == livros[i].codigo)
        {
            posBusca = i;
        }
    }

    if (posBusca == -1)
    {
        printf("\nNao possuimos este titulo no nosso acervo!");
        return posBusca;
    }
    else
    {
        return posBusca;
    }
}

// funções de usuário

void cadastrarUser(Usuario user[], int qtdUsers, Livro livros[], int qtdTitulos){
    int caractere;

    for (int i = 0; i < qtdUsers; i++){
        user[i].codigoLivroEmprestado = -1;
        int posBusca = -1;
        if (i == 0){
            printf("\nDigite o codigo do Usuario: ");
            scanf("%d", &user[i].codigo);
        }

        if (i != 0){
            //  printf("\n2===== %d =====\n", codigos[i]);
            printf("\nverifica repetição\n");

            printf("\nDigite o codigo do Usuario: ");
            scanf("%d", &user[i].codigo);
            for (int j = 0; j <= i - 1; j++) {

                //    printf("\n3===== %d =====\n", codigos[i]);
                //  printf("\nj: %d - codigos: %d\ncodigo em qtdTitulos: %d\nqtdTitulos: %d\n", j, codigos[j], codigos[i], i);

                if (user[i].codigo == user[j].codigo){
                    //    printf("\n4===== %d =====\n", codigos[i]);
                    do{
                        printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");
                        printf("\nDigite o codigo do Usuario: ");
                        scanf("%d", &user[i].codigo);
                    } while (user[i].codigo == user[j].codigo);
                }
            }
        }

        if (user[i].codigo <= 0) {
            do {
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
                printf("Digite o codigo do Usuario: ");
                scanf("%d", &user[i].codigo);
            } while (user[i].codigo <= 0);
        }

        while ((caractere = getchar()) != '\n' && caractere != EOF);

        printf("\nComplete os seguintes campos, separando-os por (;) correspondentes aos dados do usuario: %d\n", user[i].codigo);
        printf("nome: \nidade: \nCPF: \ngenero: \n");

        printf("Dados do usuario%d: ", i);
        fgets(user[i].dados, TAM_TEXTO, stdin);

        if (user[i].dados[0] == '\n' || user[i].dados[0] == '\0'){
            do{
                printf("Sem informacoes.\n");
                printf("\nPreencha os dados do usuario: ");
                fgets(user[i].dados, TAM_TEXTO, stdin);
            } while  (user[i].dados[0] == '\n' || user[i].dados[0] == '\0');
        }
        // inicialização 
        
    }
}

void alterarEstoque( Livro *livro, int valor){
    livro->estoque = valor;
}

void listarUsers(Usuario user[], int qtdUsers, int posBusca){

    if (posBusca != -1){
        printf("\n==============");
        printf("\nCodigo: %d", user[posBusca].codigo);
        printf("\nDados: %s", user[posBusca].dados);
        
        if (user[posBusca].codigoLivroEmprestado == -1 ) printf("\nUsuário sem empréstimo");
        else printf("\nUsuário com empréstimo feito - código livro emprestado: %d", user[posBusca].codigoLivroEmprestado);

        printf("\n==============\n");
    }
    else{
        printf("\n======= Usuários =======");
        for (int i = 0; i < qtdUsers; i++){

            printf("\n==============");
            printf("\nCodigo: %d", user[i].codigo);
            printf("\nDados: %s", user[i].dados);

            if ( user[i].codigoLivroEmprestado == -1) printf("\nUsuário sem empréstimo");
            else printf("\nUsuário com empréstimo feito - código livro emprestado: %d", user[i].codigoLivroEmprestado);
            
            printf("\n==============\n");
        }
    }


}


void registrarEmprestimo( Usuario *user, int codigoLivro, Livro *livro){
    if (livro->codigo > 0){
        user->codigoLivroEmprestado = codigoLivro;
        livro->estoque--;
    } else {
        printf("\nNão é possível efetuar o empréstimo pois não há exemplares em estoque");
    }
    
}

void encerrarEmprestimo( Usuario *user, Livro *livro){
    user->codigoLivroEmprestado = -1;
    livro->estoque++;
}


int main(){
    // Define a página de código do console para UTF-8 (65001)
    setlocale(LC_ALL, "Portuguese"); 

    int qtdExemplares = 0, qtdTitulos = 0;
    int codBusca;
    int posBusca;
    Livro livros[MAX_TITULOS];
    Usuario user[MAX_USERS];

    int *p = NULL;

    cadastrarTitulo(livros, MAX_TITULOS);

    qtdExemplares = calcularQtdExemplares(livros, MAX_TITULOS);
    printf("Total de exemplares: %d\n", qtdExemplares);

    cadastrarUser(user, MAX_USERS, livros, qtdTitulos);
    listarTitulos(livros, MAX_TITULOS, -1);


    //PASSANDO O ENDEREÇO A LISTA DE LIVROS E A POSIÇÃO DO LIVRO Q QUERO ALTERAR
    printf("\n=== ALTERAR O ESTOQUE ===");
    alterarEstoque(&livros[0], 1);
    listarTitulos(livros, MAX_TITULOS, 0);

    //PASSANDO O ENDEREÇO A LISTA DE USUÁRIOS E A POSIÇÃO DO LIVRO Q FOI EMPRESTADO
    printf("\n=== REGISTRAR EMPRESTIMO ===\n");


    registrarEmprestimo(&user[1], 0, &livros[0]);
    printf("\n\n===================\n");
    listarUsers(user, MAX_USERS, 1);
    printf("\n===================");

    printf("\n\n===================\n");
    listarTitulos(livros, MAX_TITULOS, 0); 
    printf("\n===================\n\n");
    
    //PASSANDO O ENDEREÇO A LISTA DE USUÁRIOS 
    printf("\n=== Finalizar emprestimo ===");
    //encerrarEmprestimo(&user[1], &livros[0]);

    
}

/*
    IDEIAS:
    fazer uma struct de usuario que guarda um array de quantidades e um array de codigo de livros emprestado, com os indices correspondentes entre eles. E também funções de correção e alteração desses campos


*/
