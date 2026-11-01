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
    int qtdExemplares = 0, i;

    for (i = 0; i < qtdTitulos; i++)
    {
        qtdExemplares += livros[i].estoque;
    }

    return qtdExemplares;
}

void cadastrarTitulo(Livro livros[], int qtdTitulos){
    int caractere, i, j;
    // cadastrar codigo e estoque
    for ( i = 0; i < qtdTitulos; i++) {
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
        
            for ( j = 0; j <= i - 1; j++){

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
        printf("\n          CATÁLOGO DE LIVROS              ");
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

int buscarTitulo(Livro livros[], int qtdTitulos, int codigoBuscado){
    int posBusca = -1, i;

    for (i = 0; i < qtdTitulos; i++)
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

// funcões de usuário

void cadastrarUser(Usuario user[], int qtdUsers, Livro livros[], int qtdTitulos){
    int caractere, i, j;

    for (i = 0; i < qtdUsers; i++){
        user[i].codigoLivroEmprestado = -1;
        int posBusca = -1;
        if (i == 0){
            printf("\nDigite o codigo do Usuario: ");
            scanf("%d", &user[i].codigo);
        }

        if (i != 0){
            //  printf("\n2===== %d =====\n", codigos[i]);
            printf("\nverifica repeticao\n");

            printf("\nDigite o codigo do Usuario: ");
            scanf("%d", &user[i].codigo);
            for (j = 0; j <= i - 1; j++) {

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
        // inicializacao 
        
    }
}

void alterarEstoque( Livro *livro, int valor){
    livro->estoque = valor;
}

void listarUsers(Usuario user[], int qtdUsers, int posBusca){
    int i;

    if (posBusca != -1){
        printf("\n+----------------------------------------+");
        printf("\n|          DETALHES DO USUÁRIO           |");
        printf("\n+----------------------------------------+");
        printf("\n| Codigo : %-29d |", user[posBusca].codigo);
        printf("\n| Dados  : %-29s |", user[posBusca].dados);
        
        if (user[posBusca].codigoLivroEmprestado == -1 ) printf("\n| Emprestimo: Nenhum livro em posse      |");
        else printf("\n| Emprestimo: Livro emprestado - Codigo: %-15d |", user[posBusca].codigoLivroEmprestado);

        printf("\n+----------------------------------------+\n");
    }
    else{
        printf("\n==========================================");
        printf("\n          LISTAGEM USUÁRIOS            ");
        printf("\n==========================================");
        for (i = 0; i < qtdUsers; i++){

            printf("\n+----------------------------------------+");
            printf("\n| Codigo : %-29d |", user[i].codigo);
            printf("\n| Dados  : %-29s |", user[i].dados);

            if ( user[i].codigoLivroEmprestado == -1) printf("\n| Usuário sem emprestimo      |");
            else printf("\n| Emprestimo: Livro Cod. %-15d |", user[i].codigoLivroEmprestado);
            
            printf("\n+----------------------------------------+\n");
        }
    }


}


void registrarEmprestimo( Usuario *user, int codigoLivro, Livro *livro){
    if (user->codigoLivroEmprestado != -1) {
        printf("Usuario ja possui um livro emprestado.\n");
        return;
    }else{
        if (livro->estoque > 0){
            user->codigoLivroEmprestado = codigoLivro;
            livro->estoque = livro->estoque - 1;
        } else {
            printf("\nNao e possivel efetuar o emprestimo pois nao há exemplares em estoque");
        }
    }
    
}

void encerrarEmprestimo( Usuario *user, Livro *livro){
    if (user->codigoLivroEmprestado == -1) {
        printf("Usuario nao possui livro emprestado.\n");
        return;
    } else{
        user->codigoLivroEmprestado = -1;
        livro->estoque = livro->estoque + 1;
    }
}


int main(){

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


    //PASSANDO O ENDEREcO A LISTA DE LIVROS E A POSIcaO DO LIVRO Q QUERO ALTERAR
    alterarEstoque(&livros[0], 1);

    printf("Alterando estoque do livro com codigo %d para %d\n", livros[0].codigo, livros[0].estoque);
    listarTitulos(livros, MAX_TITULOS, 0);
    printf("\n--------------------------------\n");
    alterarEstoque(&livros[0], 12222);

    printf("Alterando estoque do livro com codigo %d para %d\n", livros[0].codigo, livros[0].estoque);
    listarTitulos(livros, MAX_TITULOS, 0);

    //PASSANDO O ENDEREcO A LISTA DE USUÁRIOS E A POSIcaO DO LIVRO Q FOI EMPRESTADO
    registrarEmprestimo(&user[1], 0, &livros[2]);

    printf("Usuário com codigo %d emprestou o livro com codigo %d\n", user[1].codigo, livros[2].codigo);
    listarUsers(user, MAX_USERS, 1);

    printf("Livro com codigo %d agora tem estoque de %d\n", livros[2].codigo, livros[2].estoque);
    listarTitulos(livros, MAX_TITULOS, 2); 
    
    //PASSANDO O ENDEREcO A LISTA DE USUÁRIOS 
    printf("\n=== Finalizar emprestimo ===");
    encerrarEmprestimo(&user[1], &livros[0]);
    listarUsers(user, MAX_USERS, 1);

    
}
