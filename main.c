#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#define MAX_TITULOS 3
//#define MAX_USERS 3
#define TAM_TEXTO 120

//declaração antecipada:
typedef struct No_fila No_fila;
typedef struct FilaEspera FilaEspera;

typedef struct No_fila{
    int usuario;
    int livro;
    struct No_fila *prox;
}No_fila;

typedef struct FilaEspera{
    No_fila *inicio;
    No_fila *fim;
}FilaEspera;

typedef struct No_Livro{
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
    struct No_Livro *prox;

    FilaEspera *fila;
} No_Livro;

typedef struct No_user{
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
    struct No_user *prox;    
} No_user;



typedef struct No_historico {
    char info[TAM_TEXTO];
    struct No_historico *prox;
} No_historico;



//PROTÓRIPO DE FUNÇÕES
No_Livro *cadastrarTitulo(No_Livro *inicioLivros);
void listarTitulos(No_Livro *livros, No_Livro *livroEncontrado);
No_Livro *buscarTitulo(No_Livro *inicioLivros, int codigoBuscado);
int disponibilidadeTitulo(int qtdEstoque);
void liberarLivros(No_Livro *inicio);

No_user *cadastrarUser(No_user *userInicio);
void listarUsuario(No_user *usuarios, No_user *userEncontrado);
No_user *buscarUsuario(No_user *userInicio, int codigoBuscado);
void liberarUsuarios(No_user *inicio);

int registrarEmprestimo(No_user *user, int codigoLivro, No_Livro *livro);
int encerrarEmprestimos(No_user *user, No_Livro *livro);
int listarEmprestimos(No_user *user, No_Livro *livro);

FilaEspera *criar_fila(void);
int fila_vazia(FilaEspera *fila);
int entrarNaFilaDeEspera(No_user *user, No_Livro *livro, FilaEspera *fila);
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

No_Livro *cadastrarTitulo(No_Livro *inicioLivros){

    No_Livro *novoLivro = malloc(sizeof(No_Livro));

    if (novoLivro == NULL) {
        printf("Erro ao alocar memoria!\n");
        return inicioLivros;
    }


    int apenas_numeros = 1;
    No_Livro *busca_repeticao = NULL;  

    do{
        printf("\nDigite o codigo do novo livro: ");
        if (scanf("%d", &novoLivro->codigo) == 1 && novoLivro->codigo > 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Codigo invalido! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || novoLivro->codigo <= 0);
        

    

    busca_repeticao = buscarTitulo(inicioLivros, novoLivro->codigo); //fazer o buscar
    if (busca_repeticao != NULL) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");    

    while (busca_repeticao != NULL){
        do{
            printf("\nDigite o codigo do novo livro: ");

            if (scanf("%d", &novoLivro->codigo) == 1 && novoLivro->codigo > 0) {
                apenas_numeros = 0;
                while (getchar() != '\n'); 
                break;
                
            } else{
                printf("Codigo invalido! Digite apenas numeros positivos.\n");
                apenas_numeros = 1;
                while (getchar() != '\n'); 
            }
        }while (novoLivro->codigo <= 0 || apenas_numeros == 1);
        
        busca_repeticao = buscarTitulo(inicioLivros, novoLivro->codigo);
        if (busca_repeticao != NULL) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");       
        
    } ;


    do{
        //verifica se o estoque tem letra
        printf("\nDigite a quantidade de exemplares em estoque: ");
        if (scanf("%d", &novoLivro->estoque) == 1 && novoLivro->estoque >= 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Quantidade invalida! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || novoLivro->estoque < 0);


    printf("\nComplete os seguintes campos, separando-os por (;) correspondentes a obra: %d\n", novoLivro->codigo);
    printf("nome: \nautor: \nano: \ngenero: \n");

    printf("descricao: ");
    fgets(novoLivro->descricao, TAM_TEXTO, stdin);
    int i = 0;
    while (novoLivro->descricao[i] != '\0' && novoLivro->descricao[i] != '\n') {
        i++;
    }
    novoLivro->descricao[i] = '\0';

    if (novoLivro->descricao[0] == '\n' || novoLivro->descricao[0] == '\0'){
        do{
            printf("Sem descricao.\n");
            printf("\nDigite algo na descricao: ");
            fgets(novoLivro->descricao, TAM_TEXTO, stdin);
                int i = 0;
                while (novoLivro->descricao[i] != '\0' && novoLivro->descricao[i] != '\n') {
                    i++;
                }
                novoLivro->descricao[i] = '\0';
        } while (novoLivro->descricao[0] == '\n' || novoLivro->descricao[0] == '\0');
    }

    novoLivro->fila = criar_fila();
    

    if (novoLivro->fila == NULL) {
        printf("Erro ao criar fila de espera!\n");
        free(novoLivro);
        return inicioLivros;
    }
    novoLivro->prox = inicioLivros;
    return novoLivro;
}

void listarTitulos(No_Livro *inicioLivros, No_Livro *livroEncontrado){
    No_Livro *livroAtual = inicioLivros;
    int contLivros = 0;

    if (livroAtual == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    if (livroEncontrado != NULL) {

        printf("\n+------------------------------------------------------------+\n");
        printf("|                    DETALHES DO LIVRO                       |\n");
        printf("+------------------------------------------------------------+\n");

        printf("| Codigo: %-49d |\n", livroEncontrado->codigo);
        printf("| Estoque: %-48d |\n", livroEncontrado->estoque);

        if (livroEncontrado->estoque >= 1)
            printf("| Status: %-49s |\n", "Disponivel");
        else
            printf("| Status: %-49s |\n", "Indisponivel");

        printf("| Descricao: %-46.46s |\n", livroEncontrado->descricao);
        printf("+------------------------------------------------------------+\n");
    }
    else {
        printf("\n");
        printf("+------------------------------------------------------------+\n");
        printf("|                    CATALOGO DE LIVROS                      |\n");
        printf("+------------------------------------------------------------+\n");
        while (livroAtual != NULL) {

            printf("| LIVRO: %-51d |\n", contLivros + 1);
            printf("+------------------------------------------------------------+\n");
            printf("| Codigo: %-49d |\n", livroAtual->codigo);
            printf("| Estoque: %-48d |\n", livroAtual->estoque);

            if (livroAtual->estoque >= 1)
                printf("| Status: %-49s |\n", "Disponivel");
            else
                printf("| Status: %-49s |\n", "Indisponivel");

            printf("| Descricao: %-46.46s |\n", livroAtual->descricao);
            printf("+------------------------------------------------------------+\n");

            contLivros++;
            livroAtual = livroAtual->prox;
        }
        printf("\nTotal de titulos cadastrados: %d\n", contLivros);
    }

}

No_Livro *buscarTitulo(No_Livro *inicioLivros, int codigoBuscado){

    No_Livro *livroAtual = inicioLivros;

    while (livroAtual != NULL){
        if(livroAtual->codigo == codigoBuscado){
            return livroAtual;
        }

        livroAtual = livroAtual->prox;
    }
    return NULL;
}

int alterarEstoque(No_Livro *livro, int valor){
    if (livro == NULL || valor < 0) {
        return 0;
    }

    livro->estoque = valor;
    return 1;
}

int verificarEstoqueVazio(No_Livro *livro){
    if (livro == NULL) {
        return 0;
    }
    //pegar um livro que deseja ser buscado e verificar o estoque desse livro todas as vezes que houver alteração nele
    if (livro->estoque == 0){
        printf("Estoque vazio para o livro: %d", livro->codigo);
        return 0;
    } else{
        printf("Estoque positivo para o livro: %d", livro->codigo);
        return 1;
    }
    

}

int contar(No_Livro *inicio) {
    int quantidade = 0;
    No_Livro *atual = inicio;
    while (atual != NULL) {
        quantidade++;
        atual = atual->prox;
    }
    return quantidade;
}

void liberarLivros(No_Livro *inicioLivro){
    No_Livro *atual = inicioLivro;
    No_Livro *proximo;
    while (atual != NULL) {
    // Salva o proximo antes de liberar.
        proximo = atual->prox;
        liberar_fila(atual->fila);
        free(atual);
        atual = proximo;
    }
}

//funções do usuários
No_user *cadastrarUser(No_user *userInicio){
    No_user *novoUser = malloc(sizeof(No_user));

    if (novoUser == NULL) {
        printf("Erro ao alocar memoria!\n");
        return userInicio;
    }


    novoUser->codigoLivroEmprestado = -1;

    int apenas_numeros = 1;
    No_user *busca_repeticao = NULL;

    do{
        printf("\nDigite o codigo do novo usuário: ");
        if (scanf("%d", &novoUser->codigo) == 1 && novoUser->codigo > 0) {
            apenas_numeros = 0;
            while (getchar() != '\n'); 
            break;
        } else{
            printf("Codigo invalido! Digite apenas numeros positivos.\n");
            apenas_numeros = 1;
            while (getchar() != '\n'); 
        }
    }while (apenas_numeros == 1 || novoUser->codigo <= 0);

    
    
    
    busca_repeticao = buscarUsuario(userInicio, novoUser->codigo);
    if (busca_repeticao != NULL) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");    

    while (busca_repeticao != NULL){
        do{
            printf("\nDigite o codigo do novo usuario: ");

            if (scanf("%d", &novoUser->codigo) == 1 && novoUser->codigo > 0) {
                apenas_numeros = 0;
                while (getchar() != '\n'); 
                break;
                
            } else{
                printf("Codigo invalido! Digite apenas numeros positivos.\n");
                apenas_numeros = 1;
                while (getchar() != '\n'); 
            }
        }while (novoUser->codigo <= 0 || apenas_numeros == 1);
        
        busca_repeticao = buscarUsuario(userInicio, novoUser->codigo);
        if (busca_repeticao != NULL) printf("Codigo invalido. Digite um valor diferente de um codigo ja inserido anteriormente.\n");       
        
    } ;
    

    printf("\nComplete os seguintes campos, separando-os por (;) correspondentes aos dados do usuario: %d\n", novoUser->codigo);
    printf("nome: \nidade: \nCPF: \ngenero: \n");

    printf("Dados do usuario: ");
    fgets(novoUser->dados, TAM_TEXTO, stdin);
    int i = 0;
    while (novoUser->dados[i] != '\0' && novoUser->dados[i] != '\n') {
        i++;
    }
    novoUser->dados[i] = '\0';

    if (novoUser->dados[0] == '\n' || novoUser->dados[0] == '\0'){
        do{
            printf("Sem informacoes.\n");
            printf("\nPreencha os dados do usuario: ");
            fgets(novoUser->dados, TAM_TEXTO, stdin);
        } while  (novoUser->dados[0] == '\n' || novoUser->dados[0] == '\0');
    }       
    
    novoUser->prox = userInicio;
    return novoUser;
}

No_user *buscarUsuario(No_user *userInicio, int codigoBuscado){
    
    No_user *userAtual = userInicio;

    while (userAtual != NULL){
        if(userAtual->codigo == codigoBuscado){
            return userAtual;
        }

        userAtual = userAtual->prox;
    }
    return NULL;
}

void listarUsuario(No_user *inicioUser, No_user *userEncontrado){
    
    No_user *userAtual = inicioUser;
    int contUsers = 0;

    if (userAtual == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    if (userEncontrado != NULL) {
        userAtual = userEncontrado; //deslocar o ponteiro para a posição do usuário encontrado
        printf("\n+------------------------------------------------------------+\n");
        printf("|                   DETALHES DO USUARIO                      |\n");
        printf("+------------------------------------------------------------+\n");
        printf("| Codigo: %-49d |\n", userAtual->codigo);
        printf("| Dados: %-51.51s |\n", userAtual->dados);
        if (userAtual->codigoLivroEmprestado != -1) {
            printf("| Livro emprestado: %-40d |\n",
                userAtual->codigoLivroEmprestado);
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
        while (userAtual != NULL) {

            printf("| USUARIO: %-49d |\n", contUsers + 1);
            printf("+------------------------------------------------------------+\n");
            printf("| Codigo: %-50d |\n", userAtual->codigo);
            printf("| Dados: %-51.51s |\n", userAtual->dados);

            if (userAtual->codigoLivroEmprestado != -1) {
                printf("| Livro emprestado: %-40d |\n",
                    userAtual->codigoLivroEmprestado);
            } else {
                printf("| Livro emprestado: %-40s |\n", "Nenhum");
            }

            printf("+------------------------------------------------------------+\n");
            contUsers++;
            userAtual = userAtual->prox;
        }
        printf("\nTotal de usuarios cadastrados: %d\n", contUsers);
    }

}

void liberarUsuarios(No_user *inicioUser){
    No_user *atual = inicioUser;
    No_user *proximo;
    while (atual != NULL) { 
    // Salva o proximo antes de liberar.
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

//funções de emprestimo
int registrarEmprestimo( No_user *user, int codigoLivro, No_Livro *livro){

    if (user == NULL || livro == NULL) {
        return 0;
    }

    if (livro->codigo != codigoLivro) {
        return 0;
    }

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

int encerrarEmprestimos( No_user *user, No_Livro *livro){
    if (user == NULL || livro == NULL) {
        return 0;
    }

    if (user->codigoLivroEmprestado == -1) {
        return 0;
    }

    if (user->codigoLivroEmprestado != livro->codigo) {
        return 0;
    }

    user->codigoLivroEmprestado = -1;
    livro->estoque++;

    return 1;
    
}

int listarEmprestimos(No_user *inicioUsuarios, No_Livro *inicioLivros){

    No_user *userAtual = inicioUsuarios;
    No_Livro *livroEncontrado;
    int quantidade = 0;

    while (userAtual != NULL) {
        if (userAtual->codigoLivroEmprestado != -1){
            livroEncontrado = buscarTitulo(inicioLivros, userAtual->codigoLivroEmprestado);
            if (livroEncontrado != NULL) {
                printf("\nUsuario: %d\n", userAtual->codigo);
                printf("Dados: %s\n", userAtual->dados);
                printf("Livro: %d\n", livroEncontrado->codigo);
                printf("Descricao: %s\n", livroEncontrado->descricao);

                quantidade++;
            }
        }
        userAtual = userAtual->prox;
    }
    if (quantidade == 0) {
        printf("\nNenhum emprestimo registrado.\n");
    }
    return quantidade;
}

FilaEspera *criar_fila(){
    FilaEspera *fila = (FilaEspera*) malloc (sizeof(FilaEspera));

    if (fila == NULL) {
        return 0;
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

int fila_vazia(FilaEspera *fila){
    return (fila == NULL || fila->inicio == NULL);
}

int entrarNaFilaDeEspera(No_user *user, No_Livro *livro, FilaEspera *fila){
    if (user == NULL || livro == NULL || fila == NULL) {
        return 0;
    }

    printf("\nO livro %d nao possui estoque disponivel no momento.\n", livro->codigo);
    int opcao;
    do{
        printf("Deseja ser adicionado a fila de espera para o livro %d? (1 - Sim / 0 - Nao): ", livro->codigo);
        
        if (scanf("%d", &opcao) == 1 && (opcao == 1 || opcao == 0)) {
            while (getchar() != '\n'); 

            
            if (opcao == 0) {
                return 0;
            } 

            return adicionarFilaDeEspera(user->codigo, livro->codigo, fila);


        } else{
            printf("Opcao invalida! Digite apenas 1 para Sim ou 0 para Nao.\n");
            while (getchar() != '\n'); 
        }
    } while (opcao != 1 && opcao != 0);

    return 1;
}

int adicionarFilaDeEspera(int userCodigo, int livroCodigo, FilaEspera *fila){

    if (fila == NULL) {
        return 0;
    }

    //verificar se o user já esta na fila do livro em especifico
    No_fila *atual = fila->inicio;

    while (atual != NULL) {
        if (atual->usuario == userCodigo) {
            printf("Usuario ja esta na fila de espera.\n");
            return 0;
        }

        atual = atual->prox;
    }


    No_fila *novoNo = (No_fila*) malloc(sizeof(No_fila));


    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 0;
    }else {
        novoNo->usuario = userCodigo;
        novoNo->livro = livroCodigo;
        novoNo->prox = NULL;
        if (fila_vazia(fila))
            fila->inicio = novoNo;
        else{
            fila->fim->prox = novoNo;
        }
        fila->fim = novoNo;
        
        printf("\nUsuario %d adicionado a fila de espera para o livro %d.\n", userCodigo, livroCodigo);
    }

    return 1;
}

void retirarDaFila(FilaEspera *fila) {
    if (fila == NULL || fila->inicio == NULL) {
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
    if (fila_vazia(fila)) {
        return 0;
    }

    No_fila *auxAtual = fila->inicio;
    int cont = 0;

    while (auxAtual != NULL && (quantidade == -1 || cont < quantidade)){
        printf(" user: %7d | Livro: %5d\n", auxAtual->usuario, auxAtual->livro);
        auxAtual = auxAtual->prox;
        cont++;
    }
    return 1;
}


//libera todos os elementos da fila
void liberar_fila(FilaEspera *fila){
    if (fila == NULL) {
        return;
    }

    No_fila *p;
    No_fila *q = fila->inicio;

    while (q != NULL){
        p = q->prox;
        free(q);
        q = p;
    }
    free(fila);
}

//histórico de ações
No_historico *empilhar(No_historico *topo, char *info){
    No_historico *novo = malloc(sizeof(No_historico));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return topo;
    }
    
    int i = 0;

    while (info[i] != '\0' && i < TAM_TEXTO - 1) {
        novo->info[i] = info[i];
        i++;
    }

    novo->info[i] = '\0';
    novo->prox = topo;

    topo = novo;
    //printf("func %d visitada!\n", func);
    return topo;
}

No_historico *desempilhar(No_historico *topo) {
    //pilha vazia
    if (topo == NULL) {
        printf("Historico vazio!\n");
        return topo;
    }
    // endereco q sera removido.
    No_historico *remover = topo;
    printf("Saindo da pagina %s\n", topo->info);
    // O segundo -> novo topo.
    topo = topo->prox;

    free(remover);
    if (topo != NULL) {
        printf("Pagina atual: %s\n", topo->info);
    } else {
        printf("Nao ha paginas anteriores.\n");
    }
    return topo;
}

void exibirHistorico(No_historico *topo) {
    No_historico *atual = topo;
    if (atual == NULL) {
        printf("Historico vazio!\n");
        return;
    }
    printf("\nHistorico de navegacao:\n");
    while (atual != NULL) {
        printf("Pagina %s\n", atual->info);
        // Avanca para o proximo no.
        atual = atual->prox;
    }
}

void liberarPilha(No_historico *topo) {
    No_historico *atual = topo;
    No_historico *proximo;
    while (atual != NULL) {
    // Salva o proximo antes de liberar.
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int menu (){
    //No_historico *topo = NULL;
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
    printf("|  11 - Exibir historico de operacoes                     |\n");
    printf("|  12 - Consultar a situacao dos emprestimos              |\n");
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

    int codBusca;
    

    //No_Livro livros[MAX_TITULOS];
    No_Livro *pLivros = NULL;
    No_Livro *inicioLivros = NULL;
    
    No_historico *topo = NULL;

    //No_user inicioUsers[MAX_USERS];
    No_user *pUsers = NULL;
    No_user *inicioUsers = NULL;

    int contadorUsers = 0;
    int contadorLivros = 0, opcao;

    //pLivros = &livros[0];
    //pUsers = &inicioUsers[0];
    do {
        opcao = menu();

        if(opcao == 1){
            No_Livro *inicioAnterior = inicioLivros;
            inicioLivros = cadastrarTitulo(inicioLivros);

            if (inicioLivros != inicioAnterior) {
                contadorLivros++;
                topo = empilhar(topo, "Cadastro de Livros - 1");
            }
            

        } else if(opcao == 2){
            if(contadorLivros == 0){
                printf("\nNao ha titulos cadastrados no momento.\n");
            } else {
                listarTitulos(inicioLivros, NULL);
            }


        } else if(opcao == 3){
            int apenas_numeros = 1;
            
            No_Livro *livroEncontrado;

            printf("\n============================================\n");
            printf("              BUSCA DE TITULOS              \n");
            printf("============================================\n");
            
            No_Livro *livroAtual = inicioLivros;
            while (livroAtual != NULL) {
                printf("Codigo: %d\n", livroAtual->codigo);
                livroAtual = livroAtual->prox;
            }

            if (inicioLivros == NULL) {
                printf("Nao ha livros cadastrados.\n");
                continue;
            }

            printf("--------------------------------------------\n");
            do {
                
                printf("Digite o codigo do livro que deseja buscar: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    livroEncontrado  = buscarTitulo(inicioLivros, codBusca);
                    if (livroEncontrado == NULL) {
                        printf("Titulo nao encontrado.\n");
                    } else {
                        printf("Titulo encontrado : %d\n", livroEncontrado->codigo);
                        break;
                    }
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (codBusca <= 0 || apenas_numeros == 1);
            
            listarTitulos(inicioLivros, livroEncontrado);
        } else if(opcao == 4){
            No_user *inicioAnterior = inicioUsers;

            inicioUsers = cadastrarUser(inicioUsers);
            if (inicioUsers != inicioAnterior) {
                contadorUsers++;
                topo = empilhar(topo, "Cadastro de Usuarios - 4");
            }
            
        } else if(opcao == 5){
            if(contadorUsers == 0){
                printf("\nNao ha usuarios cadastrados no momento.\n");
            } else {
                listarUsuario(inicioUsers, NULL);
            }
        
        } else if(opcao == 6){

            if (inicioUsers == NULL) {
                printf("\nNao ha usuarios cadastrados.\n");
                continue;
            }
                    
            int apenas_numeros = 1;
            No_user *userEncontrado;
            
            printf("\n============================================\n");
            printf("              BUSCA DE USUARIOS             \n");
            printf("============================================\n");
            No_user *userAtual = inicioUsers;

            while (userAtual != NULL) {
                printf("Codigo: %d\n", userAtual->codigo);
                userAtual = userAtual->prox;
            }
            printf("--------------------------------------------\n");
            do {
                
                printf("Digite o codigo do usuario que deseja buscar: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    userEncontrado = buscarUsuario(inicioUsers, codBusca);
                    if (userEncontrado == NULL) {
                        printf("Usuario nao encontrado.\n");
                    } else {
                        printf("Usuario encontrado com o codigo: %d\n", userEncontrado->codigo);
                    }
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (apenas_numeros == 1 || userEncontrado == NULL);
            
            listarUsuario(inicioUsers, userEncontrado);
        } else if(opcao == 7){
            
            if (contadorLivros == 0) {
                printf("\nNao ha livros cadastrados.\n");
                continue;
            }
            
            // Alterar estoque de titulo
            int apenas_numeros = 1, novoEstoque;
            No_Livro *livroAtual = inicioLivros;
            No_Livro *livroEncontrado;
            No_user *userEncontrado;

            printf("\n============================================\n");
            printf("              ALTERAR ESTOQUE               \n");
            printf("============================================\n");
            


            while (livroAtual != NULL) {
                printf("Codigo: %d | Estoque: %d\n", livroAtual->codigo,livroAtual->estoque);
                livroAtual = livroAtual->prox;
            }
            printf("--------------------------------------------\n");
            do {
                
                printf("Digite o codigo do livro que deseja alterar o estoque: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    livroEncontrado = buscarTitulo(inicioLivros, codBusca);
                    
                    if (livroEncontrado == NULL) printf("Titulo nao encontrado.\n");
                                        
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (apenas_numeros == 1 || livroEncontrado == NULL);
            
            do {
                
                printf("Digite o valor do novo estoque para o livro: ");
                if (scanf("%d", &novoEstoque) == 1 && novoEstoque >= 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                } else{
                    printf("Quantidade invalida! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (apenas_numeros == 1 || livroEncontrado == NULL);

            if(alterarEstoque(livroEncontrado, novoEstoque)){
                topo = empilhar(topo, "Alterar estoque - 7");
                printf("--------------------------------------------\n");
                printf("        ALTERACAO FEITA COM SUCESSO         \n");
                printf("--------------------------------------------\n");

            } else {
                printf("\nErro ao alterar estoque.\n");
            }

            //verificar o próximo da lista
            if (!fila_vazia(livroEncontrado->fila)){            

                if(livroEncontrado->fila->inicio->livro == codBusca){

                    userEncontrado = buscarUsuario(inicioUsers, livroEncontrado->fila->inicio->usuario);

                    int emprestimo = registrarEmprestimo(inicioUsers, codBusca, inicioLivros);

                    if(emprestimo == 0) printf("| -- Emprestimo invalido, titulo sem estoque ou usuario selecionado com devolucao pendente -- |\n");

                    else {
                        printf("| -- Emprestimo valido, deu bom -- |\n");
                        printf("Emprestimo realizado para o usuario %d.\n", inicioUsers->codigo);
                        retirarDaFila(livroEncontrado->fila);
                    }

                } else{
                    printf("| -- usuario: %d quer o livro: %d e não o livro: %d -- |", livroEncontrado->fila->inicio->usuario, livroEncontrado->fila->inicio->livro);
                }
            }

        } else if(opcao == 8){
            // Registrar emprestimo
            int apenas_numeros = 1, emprestimo, entrarEspera, usuariosDisponiveis = 0;
            int posBuscaUser;
            No_user *userEncontrado = NULL;
            No_user *userAtual = inicioUsers;
            No_Livro *livroEncontrado = NULL;
            No_Livro *livroAtual;

            if (inicioLivros == NULL || inicioUsers == NULL) {
                printf("\nCadastre pelo menos um usuario e um livro antes de registrar emprestimos.\n");
                continue;
            }

            do{
                printf("\n============================================\n");
                printf("           REGISTRAR EMPRESTIMO             \n");
                printf("============================================\n");
                
                // Sub-bloco usuário
                printf("--- SELECIONE O USUARIO ---\n");
                
                while (userAtual != NULL) {

                    if (userAtual->codigoLivroEmprestado == -1) {

                        printf("Codigo do usuario: %d\n", userAtual->codigo);
                        usuariosDisponiveis++;
                    }

                    userAtual = userAtual->prox;
                }

                printf("--------------------------------------------\n");
                if (usuariosDisponiveis == 0) {
                    printf("Nao ha usuarios disponiveis para emprestimo.\n");
                    break;
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do usuario que deseja fazer o emprestimo: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 
                        userEncontrado = buscarUsuario(inicioUsers, codBusca);

                        if (userEncontrado == NULL) {
                            printf("Usuario nao encontrado.\n");
                        }else if (userEncontrado->codigoLivroEmprestado != -1) {
                            printf("Usuario ja possui um livro emprestado.\n");
                            userEncontrado = NULL;
                        }                  
                    }else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (apenas_numeros == 1 || posBuscaUser == -1);
                
    
                printf("\n--- SELECIONE O LIVRO ---\n");
                livroAtual = inicioLivros;

                while (livroAtual != NULL) {
                    printf("Codigo: %d | Estoque: %d\n", livroAtual->codigo, livroAtual->estoque);
                    livroAtual = livroAtual->prox;
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do livro que deseja emprestar: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 

                        livroEncontrado = buscarTitulo(inicioLivros, codBusca);
                        if (livroEncontrado == NULL) {
                            printf("Titulo nao encontrado.\n");
                        } 
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || livroEncontrado == NULL);
                
                if (!fila_vazia(livroEncontrado->fila)) {

                    printf("\nJa existem usuarios aguardando este livro.\n");

                    entrarNaFilaDeEspera(userEncontrado, livroEncontrado, livroEncontrado->fila);
                }else if (disponibilidadeTitulo(livroEncontrado->estoque)){

                    emprestimo = registrarEmprestimo(userEncontrado, livroEncontrado->codigo, livroEncontrado); 
                
                    if(emprestimo == 0){
                        printf("\n| -- Titulo sem estoque ou usuario selecionado com devolucao pendente -- |");
                    } else {
                        printf("\nEmprestimo realizado com sucesso.\n");
                        topo = empilhar(topo, "Emprestimo de Livros - 8");
                    }
                } else{
                    entrarNaFilaDeEspera(userEncontrado, livroEncontrado, livroEncontrado->fila);
                }
                
            }while(emprestimo == 0);


        } else if(opcao == 9){
            // Encerrar emprestimo
            int apenas_numeros = 1, devolucao, possuiEmprestimos = 0, atenderFila;
            No_user *userEscolhido;
            No_Livro *livroEncontrado;
            No_user *proximoUser = NULL;
            No_user *userAtual = inicioUsers;

            if (contadorUsers == 0) {
                printf("\nNao ha usuarios cadastrados.\n");
                continue;
            }

            // emprestimos ativos.
            while (userAtual != NULL) {
                if (userAtual->codigoLivroEmprestado != -1) {
                    possuiEmprestimos = 1;
                    break;
                }
                userAtual = userAtual->prox;
            }

            printf("\n============================================\n");
            printf("           ENCERRAR EMPRESTIMO              \n");
            printf("============================================\n");
            

            printf("--- USUARIOS COM EMPRESTIMOS ATIVOS ---\n");
            userAtual = inicioUsers;

            while (userAtual != NULL) {
                if (userAtual->codigoLivroEmprestado != -1) {
                    printf("Usuario: %d | Livro emprestado: %d\n", userAtual->codigo,userAtual->codigoLivroEmprestado);
                }
                userAtual = userAtual->prox;
            }
            
            printf("--------------------------------------------\n");

            do {
                    
                printf("Digite o codigo do usuario que deseja devolver um livro: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 

                    userEscolhido = buscarUsuario(inicioUsers, codBusca);

                    if (userEscolhido == NULL) {
                        printf("Usuario nao encontrado.\n");
                    } else if (userEscolhido->codigoLivroEmprestado == -1) {
                        
                        printf("Usuario encontrado : %d\n", userEscolhido->codigo);
                        break;
                    }
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (apenas_numeros == 1 || userEscolhido == NULL);

            livroEncontrado = buscarTitulo(inicioLivros, userEscolhido->codigoLivroEmprestado);
            if (livroEncontrado == NULL) {
                printf("Titulo nao encontrado.\n");
                continue;
            } 

            printf("\nUsuario selecionado: %d\n", userEscolhido->codigo);
            printf("Titulo encontrado: %d\n", livroEncontrado->codigo);
            
            devolucao = encerrarEmprestimos(userEscolhido, livroEncontrado);
            
            if (devolucao == 0 ) {
                printf("| -- Usuario selecionado não tem nenhum titulo associado a ele -- |");
                continue;
            }
    
            topo = empilhar(topo, "Devolucao de Livros - 9");;

            //verificar o próximo da lista
            if (!fila_vazia(livroEncontrado->fila)) {

                printf("\nProximo usuario da fila: %d\n", livroEncontrado->fila->inicio->usuario);

                proximoUser = buscarUsuario(inicioUsers, livroEncontrado->fila->inicio->usuario);

                if(livroEncontrado->fila->inicio->livro != livroEncontrado->codigo){
                    printf("usuario da fila esta associado a outro livro.\n");
                    printf("| -- usuario: %d quer o livro: %d e não o livro: %d -- |", livroEncontrado->fila->inicio->usuario, livroEncontrado->fila->inicio->livro);
                } else if (proximoUser == NULL) {
                    printf("Usuario nao encontrado no cadastro.\n");
                } else if (proximoUser->codigoLivroEmprestado != -1) {
                    printf("usuario ja possui um emprestimo ativo.\n");
                }else{

                    do {
                        printf("\nDeseja efetivar o emprestimo para o proximo usuario? (1 - Sim / 0 - Nao): ");
                    
                        if (scanf("%d", &atenderFila) == 1 && (atenderFila == 1 || atenderFila == 0)) {
                            while (getchar() != '\n');
                            break;
                        } else {
                            printf("Opcao invalida! Digite 1 ou 0: ");
                            while (getchar() != '\n');
                        }
                    } while ((atenderFila != 1 || atenderFila != 0));

                    if (atenderFila == 1) {

                        int emprestimo = registrarEmprestimo(proximoUser,livroEncontrado->codigo, livroEncontrado);

                        if (emprestimo == 1) {
                            printf("\nEmprestimo realizado para o usuario %d.\n",proximoUser->codigo);
                            retirarDaFila(livroEncontrado->fila);
                            topo = empilhar(topo, "Emprestimo de Livros - 8");
                        } else {
                            printf("\nNao foi possivel efetivar o emprestimo.\n");
                            printf("O usuario ta na fila de espera.\n");
                        }

                    } else {
                        printf("\nO usuario ta na fila de espera.\n");
                    }
                }

            } else {

                printf("\nNao ha usuarios esperando este livro.\n");
            }

            printf("--------------------------------------------\n");
            printf("        Devolucao feita com sucesso         \n");
            printf("--------------------------------------------\n");

        } else if(opcao == 10){
            printf("\n============================================\n");
            printf("        FILA DE ESPERA PARA EMPRESTIMO        \n");
            printf("============================================\n");
            

            int apenas_numeros = 1, filaEspera;
            No_Livro *livroEncontrado = NULL;
            No_Livro *livroAtual = inicioLivros;

            if (inicioLivros == NULL) {
                printf("\nNao ha livros cadastrados.\n");
                continue;
            }

            printf("--- LIVROS CADASTRADOS ---\n");
            while (livroAtual != NULL) {
                printf("Codigo: %d | %s\n", livroAtual->codigo, livroAtual->descricao);
                livroAtual = livroAtual->prox;
            }

            printf("--------------------------------------------\n");

            do{
                printf("Digite o codigo do livro para consultar a fila: ");
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n');
                    livroEncontrado = buscarTitulo(inicioLivros, codBusca);

                    if (livroEncontrado == NULL) {
                        printf("Titulo nao encontrado.\n");
                    }
                } else {
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n');
                }
            } while (apenas_numeros == 1 || livroEncontrado == NULL);
                
            printf("\n---  Fila de espera do livro: %d ---\n", livroEncontrado->codigo);

            printf("+--------------------------------+\n");
            printf("| Usuario       | Livro          |\n");
            printf("+--------------------------------+\n");

            filaEspera = mostrarFilaEspera(livroEncontrado->fila, -1);

            if (filaEspera == 0){
                printf("\n| --         FILA DE ESPERA ESTA VAZIA        -- |\n");
                printf("| -- Nao ha nenhum usuario na lista de espera -- |\n");
            } 
            
        } else if(opcao == 11){    
            exibirHistorico(topo);
        }else if (opcao == 12) {
            if (inicioUsers == NULL) {
                printf("\nNao ha usuarios cadastrados.\n");
                continue;
            }
            listarEmprestimos(inicioUsers, inicioLivros);    
        } else if(opcao == 0){
            printf("\nSaindo do programa...\n");
        } else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }

    }while(opcao != 0);
    liberarLivros(inicioLivros);
    liberarUsuarios(inicioUsers);
    liberarPilha(topo);
    
    return 0;
}
