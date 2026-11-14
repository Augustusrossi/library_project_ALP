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

//PROTÓRIPO DE FUNÇÕES
void cadastrarTitulo(Livro *livros, Livro *inicioLivros, int posicao);
void listarTitulos(Livro *livros, int qtdTitulos, int posBusca);
int buscarTitulo(Livro *livros, int qtdTitulos, int codigoBuscado);
int disponibilidadeTitulo(int qtdEstoque);

void cadastrarUser(Usuario *usuarios, Usuario *inicioUsuarios, int posicao);
void listarUsuario(Usuario *usuarios, int qtdUsuarios, int posBusca);
int buscarUsuario(Usuario *usuarios, int qtdUsuarios, int codigoBuscado);


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
    Livro *pLivro = livros;

    if (posBusca != -1) {
        pLivro += posBusca; //deslocar o ponteiro para a posição do livro encontrado
        printf("\n+----------------------------------------+");
        printf("\n|          DETALHES DO LIVRO             |");
        printf("\n+----------------------------------------+");

        printf("\n| Codigo   : %-30d |", pLivro->codigo);
        if (disponibilidadeTitulo(pLivro->estoque))
            printf("\n| Status: Disponivel (%d em estoque)  |", pLivro->estoque);
        else
            printf("\n| Status: Indisponivel - Estoque: %d |", pLivro->estoque);

        printf("\n| Descricao: %-30s |", pLivro->descricao);
        printf("\n+----------------------------------------+\n");
    }
    else
    {
        printf("\n");
        printf("+------------------------------------------------------------+\n");
        printf("|                    CATALOGO DE LIVROS                      |\n");
        printf("+------------------------------------------------------------+\n");
        for (i = 0; i < qtdTitulos; i++){

            printf("|                                                            |\n");
            printf("|  LIVRO: %-50d |\n", i + 1);
            printf("+------------------------------------------------------------+\n");
            printf("|  Codigo: %-49d |\n", (pLivro+i)->codigo);
            if (pLivro->estoque >= 1)
                printf("| Status: Disponivel (%d em estoque)  %-49d |\n", (pLivro+i)->estoque);
            else
                printf("| Status: Indisponivel - Estoque: %-49d |\n", (pLivro+i)->estoque);

            printf("|  Descricao: %-49s \n", (pLivro+i)->descricao);
            printf("+------------------------------------------------------------+\n");
            pLivro++;
        }
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

//funções do usuários
void cadastrarUser(Usuario *pUser, Usuario *pUserInicio, int posicao){
    int caractere, i, j;

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
        printf("\n+----------------------------------------+");
        printf("\n|          DETALHES DO USUARIO           |");
        printf("\n+----------------------------------------+");

        printf("\n| Codigo   : %-30d |", pUsuario->codigo);
        printf("\n| Informacoes     : %-30s |", pUsuario->dados);
        printf("\n| Livro(s) emprestado(s): %-30s |", pUsuario->codigoLivroEmprestado == -1 ? "Nenhum" : "Possui livro(s) emprestado(s)");
        printf("\n+----------------------------------------+\n");
    }
    else
    {
        printf("\n");
        printf("+------------------------------------------------------------+\n");
        printf("|                    USUARIOS CADASTRADOS                    |\n");
        printf("+------------------------------------------------------------+\n");
        for (i = 0; i < qtdUsuarios; i++){

            printf("|                                                            |\n");
            printf("|  USUARIO: %-48d |\n", i + 1);
            printf("+------------------------------------------------------------+\n");
            if ((pUsuario+i)->codigoLivroEmprestado != -1) {
                printf("|  Livro emprestado: %-39d |\n",
                    (pUsuario+i)->codigoLivroEmprestado);
            } else {
                printf("|  Livro emprestado: %-39s |\n", "Nenhum - (%d)", (pUsuario+i)->codigoLivroEmprestado);
            }

            printf("+------------------------------------------------------------+\n");
            pUsuario++;
        }
        printf("\nTotal de usuarios cadastrados: %d\n", qtdUsuarios);
    }

}

int registrarEmprestimo( Usuario *user, int codigoLivro, Livro *livro){
    if (user->codigoLivroEmprestado != -1 && livro->estoque > 0) {
        return 0;
    }else{
        if (livro->estoque > 0){
            user->codigoLivroEmprestado = codigoLivro;
            livro->estoque = livro->estoque - 1;
            
            return 1;
        }
    }
}

int encerrarEmprestimo( Usuario *user, Livro *livro){
    if (user->codigoLivroEmprestado == -1) {
        return 0;
    } else{
        user->codigoLivroEmprestado = -1;
        livro->estoque = livro->estoque + 1;
        return 1;
    }
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

                    listarUsuario(users, contadorUsers, posBusca);
                    
                } else{
                    printf("Codigo invalido! Digite apenas numeros positivos.\n");
                    apenas_numeros = 1;
                    while (getchar() != '\n'); 
                }
            }while (codBusca <= 0 || apenas_numeros == 1 || posBusca == -1);
                
            
            listarUsuario(users, contadorUsers, posBusca);
        } else if(opcao == 7){
            // Alterar estoque de titulo
            int apenas_numeros = 1;
            int posBusca;
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
                if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                    apenas_numeros = 0;
                    while (getchar() != '\n'); 
                    alterarEstoque(&livros[posBusca], codBusca);
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

        } else if(opcao == 8){
            // Registrar emprestimo
            int apenas_numeros = 1, emprestimo;
            int posBuscaUser, posBuscaLivro;
            //verifica código do usuário
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
                            break;
                        }
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaUser == -1);
                
    
                printf("\n--- SELECIONE O LIVRO ---\n");
                for (int i = 0; i < contadorLivros; i++) {
                    printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do livro que deseja alterar o estoque: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 
                        posBuscaLivro = buscarTitulo(livros, contadorLivros, codBusca);
                        if (posBuscaLivro == -1) {
                            printf("Titulo nao encontrado.\n");
                        } else {
                            printf("Titulo encontrado na posicao: %d\n", posBuscaLivro);
                            break;
                        }
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaLivro == -1);
                
                emprestimo = registrarEmprestimo(&users[posBuscaUser], (pLivros + posBuscaLivro)->codigo, &livros[posBuscaLivro]);
                
                if(emprestimo == 0) printf("| -- Emprestimo invalido, titulo sem estoque ou usuario selecionado com devolucao pendente -- |");
                
            }while(emprestimo == 0);


        } else if(opcao == 9){
            // Encerrar emprestimo
            int apenas_numeros = 1, devolucao;
            int posBuscaUser, posBuscaLivro;
            //verifica código do usuário
            do{
                printf("\n============================================\n");
                printf("           ENCERRAR EMPRESTIMO              \n");
                printf("============================================\n");
                
                // Sub-bloco usuário
                printf("--- SELECIONE O USUARIO ---\n");
                for (int i = 0; i < contadorUsers; i++) {
                    printf(" [%d] Codigo do usuario: %d\n", i, (pUsers + i)->codigo);
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
                
    
                printf("\n--- SELECIONE O LIVRO ---\n");
                for (int i = 0; i < contadorLivros; i++) {
                    printf(" [%d] Codigo do livro: %d\n", i, (pLivros + i)->codigo);
                }
                printf("--------------------------------------------\n");
    
                do {
                    
                    printf("Digite o codigo do livro que deseja devolver: ");
                    if (scanf("%d", &codBusca) == 1 && codBusca > 0) {
                        apenas_numeros = 0;
                        while (getchar() != '\n'); 
                        posBuscaLivro = buscarTitulo(livros, contadorLivros, codBusca);
                        if (posBuscaLivro == -1) {
                            printf("Titulo nao encontrado.\n");
                        } else {
                            printf("Titulo encontrado na posicao: %d\n", posBuscaLivro);
                            break;
                        }
                        
                    } else{
                        printf("Codigo invalido! Digite apenas numeros positivos.\n");
                        apenas_numeros = 1;
                        while (getchar() != '\n'); 
                    }
                }while (codBusca <= 0 || apenas_numeros == 1 || posBuscaLivro == -1);
    
                devolucao = encerrarEmprestimo(&users[posBuscaUser], &livros[posBuscaLivro]);
                if (devolucao == 0 ) printf("| -- Usuario selecionado não tem nenhum titulo associado a ele -- |");
            }while(devolucao == 0);
            
            printf("--------------------------------------------\n");
            printf("        Devolucao feita com sucesso         \n");
            printf("--------------------------------------------\n");
            

        } else if(opcao == 0){
            printf("\nSaindo do programa...\n");
        } else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }

    }while(opcao != 0);
    
    return 0;
}
