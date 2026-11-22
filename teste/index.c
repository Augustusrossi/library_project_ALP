#include <stdio.h>
#include <stdlib.h>
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

typedef struct No_fila{
    int usuario;
    int livro;
    struct No_fila *prox;
}No_fila;

typedef struct FilaEspera{
    No_fila *inicio;
    No_fila *fim;
}FilaEspera;

//PROTÓRIPO DE FUNÇÕES
void cadastrarTitulo(Livro *livros, Livro *inicioLivros, int posicao);
void listarTitulos(Livro *livros, int qtdTitulos, int posBusca);
int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado);
int disponibilidadeTitulo(int qtdEstoque);

void cadastrarUser(Usuario *usuarios, Usuario *inicioUsuarios, int posicao);
void listarUsuario(Usuario *usuarios, int qtdUsuarios, int posBusca);
int buscarUsuario(Usuario *usuarios, int qtdUsuarios, int codigoBuscado);

int registrarEmprestimo(Usuario *user, int codigoLivro, Livro *livro);
int encerrarEmprestimos(Usuario *user, Livro *livro);
int listarEmprestimos(Usuario *user, Livro *livro);

FilaEspera *criar_fila(void);
int fila_vazia(FilaEspera *fila);
int entrarNaFilaDeEspera(Usuario *user, Livro *livro, FilaEspera *fila);
int adicionarFilaDeEspera(int userCodigo, int livroCodigo, FilaEspera *fila);
void retirarDaFila(FilaEspera *fila);
int mostrarFilaEspera(FilaEspera *fila, int quantidade);
void liberar_fila(FilaEspera *fila);

int disponibilidadeTitulo(int qtdEstoque){
    if (qtdEstoque >= 1)
        return 1;
    else
        return 0;
}

void cadastrarTitulo(Livro *pLivro, Livro *inicioLivros, int posicao){

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

        busca_repeticao = buscarTitulo(inicioLivros, posicao, pLivro->codigo);
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
            
            busca_repeticao = buscarTitulo(inicioLivros, posicao, pLivro->codigo);
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

    printf("descricao: ");
    fgets(pLivro->descricao, TAM_TEXTO, stdin);
    int i = 0;
    while (pLivro->descricao[i] != '\0' && pLivro->descricao[i] != '\n') {
        i++;
    }
    pLivro->descricao[i] = '\0';

    if (pLivro->descricao[0] == '\n' || pLivro->descricao[0] == '\0'){
        do{
            printf("Sem descricao.\n");
            printf("\nDigite algo na descricao: ");
            fgets(pLivro->descricao, TAM_TEXTO, stdin);
                int i = 0;
                while (pLivro->descricao[i] != '\0' && pLivro->descricao[i] != '\n') {
                    i++;
                }
                pLivro->descricao[i] = '\0';
        } while (pLivro->descricao[0] == '\n' || pLivro->descricao[0] == '\0');
    }
}

void listarTitulos(Livro *livros, int qtdTitulos, int posBusca){
    int i;
    Livro *pLivro = livros;

    if (posBusca != -1) {
        if (posBusca < 0 || posBusca >= qtdTitulos) {
            printf("\nTitulo nao encontrado.\n");
            return;
        }

        pLivro += posBusca; //deslocar o ponteiro para a posição do livro encontrado
        printf("\n+------------------------------------------------------------+\n");
        printf("|                    DETALHES DO LIVRO                       |\n");
        printf("+------------------------------------------------------------+\n");

        printf("| Codigo: %-49d |\n", pLivro->codigo);
        printf("| Estoque: %-48d |\n", pLivro->estoque);

        if (pLivro->estoque >= 1)
            printf("| Status: %-49s |\n", "Disponivel");
        else
            printf("| Status: %-49s |\n", "Indisponivel");

        printf("| Descricao: %-46.46s |\n", pLivro->descricao);
        printf("+------------------------------------------------------------+\n");
    }
    else
    {
        printf("\n");
        printf("+------------------------------------------------------------+\n");
        printf("|                    CATALOGO DE LIVROS                      |\n");
        printf("+------------------------------------------------------------+\n");
        for (i = 0; i < qtdTitulos; i++){

            printf("| LIVRO: %-51d |\n", i + 1);
            printf("+------------------------------------------------------------+\n");
            printf("| Codigo: %-49d |\n", pLivro->codigo);
            printf("| Estoque: %-48d |\n", pLivro->estoque);

            if (pLivro->estoque >= 1)
                printf("| Status: %-49s |\n", "Disponivel");
            else
                printf("| Status: %-49s |\n", "Indisponivel");

            printf("| Descricao: %-46.46s |\n", pLivro->descricao);
            printf("+------------------------------------------------------------+\n");

            pLivro++;
        }
        printf("\nTotal de titulos cadastrados: %d\n", qtdTitulos);
    }

}

int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado){
    int posBusca = -1, i;
    Livro *pLivro = livros;

    for (i = 0; i < qtdTitulos; i++) {
        if (codigoBuscado == pLivro->codigo) {
            posBusca = i;
        }
        pLivro++;
    }

    if (posBusca == -1) {
        return posBusca;
    } else {
        return posBusca;
    }
}

void alterarEstoque( Livro *livro, int valor){
    livro->estoque = valor;
}

int verificarEstoqueVazio(Livro *livro, int posbusca){
    //pegar um livro que deseja ser buscado e verificar o estoque desse livro todas as vezes que houver alteração nele
    if (livro->estoque == 0){
        printf("Estoque vazio para o livro: %d", livro->codigo);
        return 0;
    } else{
        printf("Estoque positivo para o livro: %d", livro->codigo);
        return 1;
    }
    

}

//funções do usuários
void cadastrarUser(Usuario *pUser, Usuario *pUserInicio, int posicao){
    int caractere;

    pUser->codigoLivroEmprestado = -1;

    int apenas_numeros = 1;
    int busca_repeticao = -1;  

    do{
        printf("\nDigite o codigo do novo usuário: ");
        if (scanf("%d", &pUser->codigo) == 1 && pUser->codigo > 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Codigo invalido! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || pUser->codigo <= 0);

    
    if (posicao != 0) {

        busca_repeticao = buscarUsuario(pUserInicio, posicao, pUser->codigo);
        if (busca_repeticao != -1) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");    

        while (busca_repeticao != -1){
            do{
                printf("\nDigite o codigo do novo usuario: ");

                if (scanf("%d", &pUser->codigo) == 1 && pUser->codigo > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    break;
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (pUser->codigo <= 0 || apenas_numeros == 1);
            
            busca_repeticao = buscarUsuario(pUserInicio, posicao, pUser->codigo);
            if (busca_repeticao != -1) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");       
            
        } ;
    }

    printf("\nComplete os seguintes campos, separando-os por (;) correspondentes aos dados do usuario: %d\n", pUser->codigo);
    printf("nome: \nidade: \nCPF: \ngenero: \n");

    printf("Dados do usuario: ");
    fgets(pUser->dados, TAM_TEXTO, stdin);
    int i = 0;
    while (pUser->dados[i] != '\0' && pUser->dados[i] != '\n') {
        i++;
    }
    pUser->dados[i] = '\0';

    if (pUser->dados[0] == '\n' || pUser->dados[0] == '\0'){
        do{
            printf("Sem informacoes.\n");
            printf("\nPreencha os dados do usuario: ");
            fgets(pUser->dados, TAM_TEXTO, stdin);
        } while  (pUser->dados[0] == '\n' || pUser->dados[0] == '\0');
    }       
    
}

int buscarUsuario(Usuario *usuarios, int qtdUsuarios, int codigoBuscado){
    
    int posBusca = -1, i;
    Usuario *pUsuario = usuarios; 

    for (i = 0; i < qtdUsuarios; i++) {
        if (codigoBuscado == pUsuario->codigo) {
            posBusca = i;
        }
        pUsuario++;
    }

    if (posBusca == -1) {
        return posBusca;
    } else {
        return posBusca;
    }
}

void listarUsuario(Usuario *usuarios, int qtdUsuarios, int posBusca){
    int i;
    Usuario *pUsuario = usuarios;

    if (posBusca != -1) {
        pUsuario += posBusca; //deslocar o ponteiro para a posição do usuário encontrado
        printf("\n+------------------------------------------------------------+\n");
        printf("|                   DETALHES DO USUARIO                      |\n");
        printf("+------------------------------------------------------------+\n");
        printf("| Codigo: %-49d |\n", pUsuario->codigo);
        printf("| Dados: %-51.51s |\n", pUsuario->dados);
        if (pUsuario->codigoLivroEmprestado != -1) {
            printf("| Livro emprestado: %-40d |\n",
                pUsuario->codigoLivroEmprestado);
        } else {
            printf("| Livro emprestado: %-40s |\n", "Nenhum");
        }
        printf("+------------------------------------------------------------+\n");
    }
    else {
        printf("\n");
        printf("+------------------------------------------------------------+\n");
        printf("|                    USUARIOS CADASTRADOS                    |\n");
        printf("+------------------------------------------------------------+\n");
        for (i = 0; i < qtdUsuarios; i++){

            printf("| USUARIO: %-49d |\n", i + 1);
            printf("+------------------------------------------------------------+\n");
            printf("| Codigo: %-50d |\n", pUsuario->codigo);
            printf("| Dados: %-51.51s |\n", pUsuario->dados);

            if (pUsuario->codigoLivroEmprestado != -1) {
                printf("| Livro emprestado: %-40d |\n",
                    pUsuario->codigoLivroEmprestado);
            } else {
                printf("| Livro emprestado: %-40s |\n", "Nenhum");
            }

            printf("+------------------------------------------------------------+\n");
            pUsuario++;
        }
        printf("\nTotal de usuarios cadastrados: %d\n", qtdUsuarios);
    }

}

//funções de emprestimo
int registrarEmprestimo( Usuario *user, int codigoLivro, Livro *livro){
    if (user->codigoLivroEmprestado != -1) {
        printf("\nUsuario ja possui um livro emprestado.\n");
        return 0;
    }
    if (livro->estoque <= 0) {
        printf("\nLivro sem estoque disponivel.\n");
        return 0;
    }
    user->codigoLivroEmprestado = codigoLivro;
    livro->estoque--;
    return 1;
}

int encerrarEmprestimos( Usuario *user, Livro *livro){
    if (user->codigoLivroEmprestado == -1) {
        return 0;
    }

    user->codigoLivroEmprestado = -1;
    livro->estoque++;

    return 1;
    
}

int listarEmprestimos(Usuario *user, Livro *livro){
    Livro *pLivro = livro;
    Usuario *pUser = user;

    for (int i = 0; i < MAX_USERS; i++){
        if (pUser->codigoLivroEmprestado != -1){
            buscarUsuario(user, MAX_USERS, pUser->codigo);
            buscarTitulo(livro, MAX_TITULOS, pUser->codigoLivroEmprestado);       
        }
        pUser++;
    }
}

FilaEspera *criar_fila(){
    FilaEspera *fila = (FilaEspera*) malloc (sizeof(FilaEspera));
    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

int fila_vazia(FilaEspera *fila){
    return (fila->inicio == NULL);
}

int entrarNaFilaDeEspera(Usuario *user, Livro *livro, FilaEspera *fila){
    printf("\nO livro %d nao possui estoque disponivel no momento.\n", livro->codigo);
    int opcao;
    do{
        printf("Deseja ser adicionado a fila de espera para o livro %d? (1 - Sim / 0 - Nao): ", livro->codigo);
        
        if (scanf("%d", &opcao) == 1 && (opcao == 1 || opcao == 0)) {
            while (getchar() != '\n'); 

            
            if (opcao == 0) {
                return 0;
            } else if (opcao == 1) {
                
                adicionarFilaDeEspera(user->codigo, livro->codigo, fila);
                return 1;
            }

        } else{
            printf("Opcao invalida! Digite apenas 1 para Sim ou 0 para Nao.\n");
            while (getchar() != '\n'); 
        }
    } while (opcao != 1 && opcao != 0);

    return 1;
}

int adicionarFilaDeEspera(int userCodigo, int livroCodigo, FilaEspera *fila){
    printf("\nUsuario %d adicionado a fila de espera para o livro %d.\n", userCodigo, livroCodigo);

    No_fila *novoNo = (No_fila*) malloc(sizeof(No_fila));
    if (novoNo == NULL)
        exit(1);
    else {
        novoNo->usuario = userCodigo;
        novoNo->livro = livroCodigo;
        novoNo->prox = NULL;
        if (fila_vazia(fila))
            fila->inicio = novoNo;
        else{
            fila->fim->prox = novoNo;
        }
        fila->fim = novoNo;
    }

    return 1;
}

void retirarDaFila(FilaEspera *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No_fila *remover = fila->inicio;

    // O segundo vira primeiro.
    fila->inicio = fila->inicio->prox;

    // Libera a memoria.
    free(remover);

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
}

int mostrarFilaEspera(FilaEspera *fila, int quantidade){
    No_fila *auxAtual = fila->inicio;
    int cont = 0;

    if(fila_vazia(fila)) {
        return 0;
    }
    else{

        //printf("          |           ");
        while (auxAtual != NULL && (quantidade == -1 || cont < quantidade)){
            printf(" user: %7d | Livro: %5d\n", auxAtual->usuario, auxAtual->livro);
            auxAtual = auxAtual->prox;
            cont++;
        }
        return 1;
    }
}

//libera todos os elementos da fila
void liberar_fila(FilaEspera *fila){
    No_fila *p, *q = fila->inicio;
    while (q != NULL){
        p = q->prox;
        free(q);
        q = p;
    }
    free(fila);
}




int menu (){
    int opcao;
    printf("\n");
    printf("+---------------------------------------------------------+\n");
    printf("|                    MENU DE OPCOES                       |\n");
    printf("+---------------------------------------------------------+\n");
    printf("|  1 - Cadastrar titulo                                   |\n");
    printf("|  2 - Listar titulos                                     |\n");
    printf("|  3 - Buscar titulo                                      |\n");
    printf("|  4 - Cadastrar usuario                                  |\n");
    printf("|  5 - Listar usuarios                                    |\n");
    printf("|  6 - Buscar usuarios                                    |\n");
    printf("|  7 - Alterar estoque de titulo                          |\n");
    printf("|  8 - Registrar emprestimo                               |\n");
    printf("|  9 - Encerrar emprestimo                                |\n");
    printf("|  10 - Consultar fila de espera                          |\n");
    printf("|  0 - Sair do programa                                   |\n");
    printf("+---------------------------------------------------------+\n");

    do{
        printf("Digite a opcao desejada: ");
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
    

    Livro livros[MAX_TITULOS];
    Livro *pLivros = NULL;

    Usuario users[MAX_USERS];
    Usuario *pUsers = NULL;

    int contadorUsers = 0;
    int contadorLivros = 0, opcao;

    FilaEspera *fila = criar_fila();


    pLivros = &livros[0];
    pUsers = &users[0];
    do {
        opcao = menu();
        if(opcao == 1){
            if (contadorLivros < qtdTitulos) {
                cadastrarTitulo(pLivros + contadorLivros, pLivros, contadorLivros);
                contadorLivros++;
            } else {
                printf("\nNao e possivel cadastrar mais titulos. Limite atingido.\n");
            }

        } else if(opcao == 2){
            if(contadorLivros == 0){
                printf("\nNao ha titulos cadastrados no momento.\n");
            } else {
                listarTitulos(livros, contadorLivros, -1);
            }


        } else if(opcao == 3){
            int apenas_numeros = 1;
            int posBusca;

            printf("\n============================================\n");
            printf("              BUSCA DE TITULOS              \n");
            printf("============================================\n");
            for (int i = 0; i < contadorLivros; i++) {
                printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
            }
            printf("--------------------------------------------\n");
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
        } else if(opcao == 4){
            if (contadorUsers < MAX_USERS) {
                cadastrarUser(pUsers + contadorUsers, pUsers, contadorUsers);
                contadorUsers++;
            } else {
                printf("\nNao e possivel cadastrar mais usuarios. Limite atingido.\n");
            }
        } else if(opcao == 5){
            if(contadorUsers == 0){
                printf("\nNao ha usuarios cadastrados no momento.\n");
            } else {
                listarUsuario(users, contadorUsers, -1);
            }
        
        } else if(opcao == 6){
            int posBusca;
            int apenas_numeros = 1;
            
            printf("\n============================================\n");
            printf("              BUSCA DE USUARIOS             \n");
            printf("============================================\n");
            for (int i = 0; i < contadorUsers; i++) {
                printf(" [%d] Codigo do usuario: %d\n", i, (pUsers+ i)->codigo);
            }
            printf("--------------------------------------------\n");
            do {
                
                printf("Digite o codigo do usuario que deseja buscar: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    posBusca = buscarUsuario(users, contadorUsers, codBusca);
                    if (posBusca == -1) {
                        printf("Usuario nao encontrado.\n");
                    } else {
                        printf("Usuario encontrado na posicao: %d\n", posBusca);
                        break;
                    }
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (codBusca <= 0 || apenas_numeros == 1 || posBusca == -1);
                
            
            listarUsuario(users, contadorUsers, posBusca);
        } else if(opcao == 7){
            
            if (contadorLivros == 0) {
                printf("\nNao ha livros cadastrados.\n");
                continue;
            }
            
            // Alterar estoque de titulo
            int apenas_numeros = 1, posBusca, novoEstoque, codBusca, posBuscaUser, emprestimo;
            printf("\n============================================\n");
            printf("              ALTERAR ESTOQUE               \n");
            printf("============================================\n");
            for (int i = 0; i < contadorLivros; i++) {
                printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
            }
            printf("--------------------------------------------\n");
            do {
                
                printf("Digite o codigo do livro que deseja alterar o estoque: ");
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
            
            do {
                
                printf("Digite o valor do novo estoque para o livro: ");
                if (scanf("%d", &novoEstoque) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    alterarEstoque(&livros[posBusca], novoEstoque);
                    if (posBusca == -1) {
                        printf("Erro ao alterar estoque.\n");
                    } else {
                        printf("Estoque alterado com sucesso.\n");
                        break;
                    }
                    
                } else{
                    printf("Quantidade invalida! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (codBusca <= 0 || apenas_numeros == 1 || posBusca == -1);

            printf("--------------------------------------------\n");
            printf("        ALTERACAO FEITA COM SUCESSO         \n");
            printf("--------------------------------------------\n");

            //verificar o próximo da lista
            if (!fila_vazia(fila)){            

                if(fila->inicio->livro == codBusca){

                    int posBuscaUser = buscarUsuario(users, 1, fila->inicio->usuario);

                    emprestimo = registrarEmprestimo(&users[posBuscaUser], codBusca, &livros[posBusca]);

                    if(emprestimo == 0) printf("| -- Emprestimo invalido, titulo sem estoque ou usuario selecionado com devolucao pendente -- |\n");

                    else {
                        printf("| -- Emprestimo valido, deu bom -- |\n");
                        printf("Emprestimo realizado para o usuario %d.\n", users[posBuscaUser].codigo);
                        retirarDaFila(fila);
                    }

                } else{
                    printf("| -- usuario: %d quer o livro: %d e não o livro: %d -- |", fila->inicio->usuario, fila->inicio->livro);
                }
            }

        } else if(opcao == 8){
            // Registrar emprestimo
            int apenas_numeros = 1, emprestimo, entrarEspera;
            int posBuscaUser, posBuscaLivro;
            //verifica código do usuário

            if (contadorUsers == 0 || contadorLivros == 0) {
                printf("\nCadastre pelo menos um usuario e um livro antes de registrar emprestimos.\n");
                continue;
            }

            do{
                printf("\n============================================\n");
                printf("           REGISTRAR EMPRESTIMO             \n");
                printf("============================================\n");
                
                // Sub-bloco usuário
                printf("--- SELECIONE O USUARIO ---\n");
                for (int i = 0; i < contadorUsers; i++) {
                    printf(" [%d] Codigo do usuario: %d\n", i, (pUsers + i)->codigo);
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do usuario que deseja fazer o emprestimo: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 
                        posBuscaUser = buscarUsuario(users, contadorUsers, codBusca); 

                        if (posBuscaUser == -1) {
                            printf("Usuario nao encontrado.\n");
                        } else {
                            printf("Usuario encontrado na posicao: %d\n", posBuscaUser);

                            //ponteiro para usuario encontrado
                            Usuario *userEncontrado = &users[posBuscaUser];
                            if (userEncontrado->codigoLivroEmprestado != -1){
                                printf("| --- Usuario com livro emprestado --- |\n");
                                printf("| ---    Procure outro usuario     --- |");
                                posBuscaUser = -1;
                            }                        
                        }
                            
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (apenas_numeros == 1 || posBuscaUser == -1);
                
    
                printf("\n--- SELECIONE O LIVRO ---\n");
                for (int i = 0; i < contadorLivros; i++) {
                    printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do livro que deseja emprestar: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 

                        posBuscaLivro = buscarTitulo(livros, contadorLivros, codBusca);
                        if (posBuscaLivro == -1) {
                            printf("Titulo nao encontrado.\n");
                        } 
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaLivro == -1);
                
                emprestimo = registrarEmprestimo(&users[posBuscaUser], codBusca, &livros[posBuscaLivro]); 
                
                if(emprestimo == 0){
                    printf("\n| -- Titulo sem estoque ou usuario selecionado com devolucao pendente -- |");

                    entrarEspera = entrarNaFilaDeEspera(&users[posBuscaUser], &livros[posBuscaLivro], fila);
                    
                    if(entrarEspera == 0 ) printf("| -- Erro ao adicionar usuario na fila de espera -- |");
                    
                    break;

                } else {
                    printf("\nEmprestimo realizado com sucesso.\n");
                }
                
            }while(emprestimo == 0);


        } else if(opcao == 9){
            // Encerrar emprestimo
            int apenas_numeros = 1, devolucao;
            int posBuscaUser, posBuscaLivro;

            if (contadorUsers == 0) {
                printf("\nNao ha usuarios cadastrados.\n");
                continue;
            }

            do{
                printf("\n============================================\n");
                printf("           ENCERRAR EMPRESTIMO              \n");
                printf("============================================\n");
                
                // Sub-bloco usuário
                printf("--- SELECIONE O USUARIO ---\n");
                printf("--- SELECIONE O USUARIO ---\n");

                int usuariosDisponiveis = 0;
                No_fila *auxFila;

                for (int i = 0; i < contadorUsers; i++) {

                    if ((pUsers + i)->codigoLivroEmprestado == -1) {

                        int usuarioNaFila = 0;
                        auxFila = fila->inicio;

                        // Verifica se o usuario ja esta na fila de espera
                        while (auxFila != NULL) {
                            if (auxFila->usuario == (pUsers + i)->codigo) {
                                usuarioNaFila = 1;
                                break;
                            }

                            auxFila = auxFila->prox;
                        }

                        if (!usuarioNaFila) {
                            printf(" [%d] Codigo do usuario: %d\n",
                                i, (pUsers + i)->codigo);

                            usuariosDisponiveis++;
                        }
                    }
                }

                printf("--------------------------------------------\n");

                if (usuariosDisponiveis == 0) {
                    printf("Nao ha usuarios disponiveis para emprestimo.\n");
                    continue;
                }

                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do usuario que deseja devolver um livro: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 

                        posBuscaUser = buscarUsuario(users, contadorUsers, codBusca);

                        if (posBuscaUser == -1) {
                            printf("Usuario nao encontrado.\n");
                        } else {
                            printf("Usuario encontrado na posicao: %d\n", posBuscaUser);
                            break;
                        }
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaUser == -1);

                //ponteiro para usuario escolhido
                Usuario *userEscolhido = &users[posBuscaUser];

                posBuscaLivro = buscarTitulo(livros, contadorLivros, userEscolhido->codigoLivroEmprestado);
                if (posBuscaLivro == -1) {
                    printf("Titulo nao encontrado.\n");
                } else {
                    printf("Titulo encontrado na posicao: %d\n", posBuscaLivro);
                    break;
                }
                
    
                // printf("\n--- SELECIONE O LIVRO ---\n");
                // for (int i = 0; i < contadorLivros; i++) {
                //     printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
                // }
                // printf("--------------------------------------------\n");
    
                // do {
                    
                //     printf("Digite o codigo do livro que deseja devolver: ");
                //     if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                //         apenas_numeros = 0;
                //         while (getchar() != '\n'); 
                //         posBuscaLivro = buscarTitulo(livros, contadorLivros, codBusca);
                //         if (posBuscaLivro == -1) {
                //             printf("Titulo nao encontrado.\n");
                //         } else {
                //             printf("Titulo encontrado na posicao: %d\n", posBuscaLivro);
                //             break;
                //         }
                        
                //     } else{
                //         printf("Codigo invalido! Digite apenas numeros positivos.\n");
                //         apenas_numeros = 1;
                //         while (getchar() != '\n'); 
                //     }
                // }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaLivro == -1);
    
                devolucao = encerrarEmprestimos(&users[posBuscaUser], &livros[posBuscaLivro]);
                if (devolucao == 0 ) printf("| -- Usuario selecionado não tem nenhum titulo associado a ele -- |");
            }while(devolucao == 0);
            
            printf("--------------------------------------------\n");
            printf("        Devolucao feita com sucesso         \n");
            printf("--------------------------------------------\n");

            //verificar o próximo da lista
            int emprestimo;
            if (!fila_vazia(fila)) {

                if(fila->inicio->livro == codBusca){
                    emprestimo = registrarEmprestimo(&users[posBuscaUser], fila->inicio->livro, &livros[posBuscaLivro]);
                    
                    if(emprestimo == 0) printf("| -- Emprestimo invalido, titulo sem estoque ou usuario selecionado com devolucao pendente -- |");
                    else {
                        printf("| -- Emprestimo valido, deu bom -- |");
                        printf("Livro emprestado ao proximo usuario da fila: %d.\n", users[posBuscaUser].codigo);
                        retirarDaFila(fila);
                    }

                } else{
                    printf("| -- usuario: %d quer o livro: %d e não o livro: %d -- |", fila->inicio->usuario, fila->inicio->livro);
                }
            }
            

        } else if(opcao == 10){
            printf("\n============================================\n");
            printf("        FILA DE ESPERA PARA EMPRESTIMO        \n");
            printf("============================================\n");
            printf("+--------------------------------+\n");
            printf("| Usuario       | Livro          |\n");
            printf("+--------------------------------+\n");

            int filaEspera = mostrarFilaEspera(fila, -1);
            if (filaEspera == 0){
                printf("\n| --         FILA DE ESPERA ESTA VAZIA        -- |\n");
                printf("| -- Nao ha nenhum usuario na lista de espera -- |\n");
            } 
            
            
        } else if(opcao == 0){
            printf("\nSaindo do programa...\n");
        } else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }

    }while(opcao != 0);
    
    return 0;
}

/*
    preciso na hora de encerrar o empréstimo ou alterar o estoque de algum livro verificar quem é o próximo da fila e ver se o livro dele corresponde com o livro que foi alterado o estoque, nesse caso, se for o mesmo alterar o estoque para subtrair 1 pq o que estava na vila vai receber esse livro, e seguir com a lógica de realização de empréstimo 

    - encerrar empréstimo
    verifico se o livro que foi devolvido é o solicitado pelo primeiro da lista de espera
    se for 
        - eu chamo a função de remover da fila 
        - eu chamo a função de emprestar passando o livro devolvido e o usuario da fila->inicio

    se não 
        - mantém o fluxo feito anteriormente

    
    - alterar o estoque
    assim que algum estoque for alterado eu vejo se o estoque desse livro é > 0 e se o primeiro da fila quer ele
    se for e tiver
        - chamo a função de realizar emrpestimo, pegando o livro que foi alterado e o 1º user da fila
        - chamo a função de remoção da fila.



    Inconsistencias notadas:
    - na devolução de estoque não está trocando o valor do campo codigoLivroEmprestado para -1 do usuário que foi devolver
    - não consegui identificar o a listagem de fila de espera pq aparecia repitido apenas o início
    - arrumar exibição do buscar livro 
    - atualizar o prox da lista de espera para mostrar os que estão com livros pendentes
    - exibição de listagem de informações

*/