#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int menu, menulembrete, menuflashcard, menuquiz, media, i = 0, numero = 0, indice = 0, indiceUtilitario;
char pesquisa[50];

typedef struct //Struct para armazenar os dados do flashcard
{
    char materia[50];
    char nota[15];
} Flashcard; //Define o nome do novo tipo criado
Flashcard lista[10];

struct no   //Struct para percorrer a arvore
{
    struct no *esq;
    char dado[20];
    struct no *dir;
};
typedef struct no *arvore;
arvore T = NULL;


typedef struct //Struct para armazenar os dados do quiz
{
    char nome[50]; //Nome da materia
    int pontuacao, perguntas;
} Materia; //Define o nome do novo tipo criado


struct Registro //Struct para os lembretes
{
    char texto[200];
    struct Registro *prox;
};

typedef struct //Typedef referente ao Registro de lembretes
{
    struct Registro *inicio;
    struct Registro *final;

} Lista;

Materia nomeM[10];

void insereFlash();                     //Fun��o que recebe os dados da materia a nota da mesma
void pesquisaMateriaFlash();            //Fun��o para receber o nome da mat�ria que o usu�rio deseja pesquisar
void sortFlashcard(int tam);            //InsertionSort para ordena��o dos dados no flashcard
int pesquisaBinaria(char*, int, int);   //Fun��o que faz a busca do dado desejado pelo usu�rio
void funcQuiz();                        //Fun��o para o sub-menu do Quiz para que o usu�rio digite os dados
void insertNode(arvore *t, char d[20]); //Inserindo o no t para preparar a ordena��o
void inOrdem(arvore t);                 //Mostrar as materias inseridas no quiz em ordem alfabetica
void imprime_lista(Lista*lista2);       //Imprimir os lembretes
void le(char *texto);                   //Receber a variável texto para incluir na lista
int insere(Lista *lista2,char *texto);  //Incluir na lista o que texto recebeu
void cria(Lista *lista2);               //Criar lista para lembretes
void pulaLinha();                       //Função com vários \n apenas para melhor leitura e organização no terminal de saída

int main()
{
    int op = -1;
    char texto[200] = {0};
    struct Registro *elemento;
    Lista lista2;
    cria(&lista2);

    printf("\tBem-vindo(a)!\n\n ");
    do
    {
        printf("Escolha uma opcao:\n\n 1- Lembretes\n 2- FlashCards \n 3- Quiz \n 0- Sair\n");
        printf("\nDigite aqui: ");
        scanf("%d", &menu);
        getchar();

        switch(menu)
        {
        case 1: //Menu do lembtrete, onde o aluno pode deixar anotações importantes
            printf("\n\n______ Lembretes ______\n\n");

            printf ("\nDigite o que deseja (1 para ver,  2 para adicionar, 0 pra voltar): ");
            scanf ("%d", &menulembrete);
            getchar();

            while(menulembrete == 1 || 2)
            {
                if(menulembrete == 1)
                {
                    pulaLinha();
                    printf ("\n\n------------------------------------------ Mostrando lembretes ------------------------------------------\n");
                    imprime_lista(&lista2);
                    printf("\n=====================================================================\n\n");
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menulembrete);
                    getchar();
                }

                if(menulembrete == 2)
                {
                    pulaLinha();
                    printf ("\n++++++++++++ Adicione o lembrete ++++++++++++\n\n");
                    le(texto);
                    insere(&lista2, texto);
                    getchar();
                    memset(texto, '\0', 200);
                    printf("\n=====================================================================\n\n");
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menulembrete);
                    getchar();
                }

                if(menulembrete == 0)
                {
                    pulaLinha();
                    printf("\nAgradecemos por usar o Caderno de Aluno! Encerrando...\n\n");
                    printf("\n###########################\n\n");
                    printf("2022. By: Gabriel Dina Sales, Gabriel Sasuke Yamauchi de Souza, Luiz Felipe Terra da Silva e Vittoria Dutra Teixeira Pirro.");
                    break;
                }

                if(menulembrete > 2)
                {
                    printf("\n\nOpcao invalida para esse menu. Retornando...");
                    printf("\n\n------------------------------------------\n\n");
                    break;
                }
                printf("\n\n----------------------------------------------------------------------------------------------------------------\n\n");
            }
            break;

        case 2: //Menu do FlashCard, onde o aluno pode armazenar as notas totais de cada mat�ria, por exemplo: Modelagem 3D - 90; AOC - 70
            printf("\n\n______ FlashCards ______\n\n");

            printf ("Digite o que deseja (1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair): ");
            scanf ("%d", &menuflashcard);
            getchar();

            while(menuflashcard == 1 || 2 || 3) //Loop para que continue sendo executado enquanto o usuario n�o digitar 0 para voltar ao menu principal
            {
                if(menuflashcard == 1)
                {
                    pulaLinha();
                    printf ("\n\n------------------------------------------ Exibindo listas de materias ------------------------------------------\n");
                    for(i=0; i < indice; i++)
                        printf("%2d-\t%s\t%s\n", i+1, lista[i].materia, lista[i].nota);
                    printf("\n=====================================================================\n\n");
                    printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                    scanf ("%d", &menuflashcard);
                    getchar();
                }

                if(menuflashcard == 2)
                {
                    pulaLinha();
                    if(indice < 10)
                    {
                        printf("\n++++++++++++ Inserindo materia ++++++++++++\n\n");
                        insereFlash();
                    }
                    else
                        printf("\n\nMaximo de materias!\n");
                        printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                        scanf ("%d", &menuflashcard);
                        getchar();
                }

                if(menuflashcard == 3)
                {
                    pulaLinha();
                    printf("\n************** Pesquisando materia **************\n");
                    pesquisaMateriaFlash();
                    printf("\n=====================================================================\n\n");
                    printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                    scanf ("%d", &menuflashcard);
                    getchar();
                }

                if(menuflashcard == 0)
                {
                    pulaLinha();
                    printf("\nAgradecemos por usar o Caderno de Aluno! Encerrando...\n\n");
                    printf("\n###########################\n\n");
                    printf("2022. By: Gabriel Dina Sales, Gabriel Sasuke Yamauchi de Souza, Luiz Felipe Terra da Silva e Vittoria Dutra Teixeira Pirro.");
                    break;
                }

                if(menuflashcard > 4)
                {
                    printf("\n\nOpcao invalida para esse menu. Retornando...");
                    printf("\n\n------------------------------------------\n\n");
                    break;
                }
                printf("\n\n----------------------------------------------------------------------------------------------------------------\n\n");
            }
            break;

        case 3: //Menu do quiz, onde o aluno pode adicionar uma materia e se auto-avaliar/ registrar desempenho
            printf("\n\n______ Quiz ______\n\n");

            printf ("Digite o que deseja (1 se avaliar, 0 para voltar): ");
            scanf ("%d", &menuquiz);
            getchar();

            while(menuquiz != 0) //Loop para que continue sendo executado enquanto o usuario n�o digitar 0 para voltar ao menu principal
            {
                if(menuquiz == 1)
                {
                    pulaLinha();
                    printf ("!!!!!!!!!!!!!! Comecando o quiz !!!!!!!!!!!!!!\n\n");
                    funcQuiz();
                    printf("\n=====================================================================\n\n");
                    printf ("\n1 se avaliar novamente, 2 ver materias adicionadas, 0 pra voltar: ");
                    scanf ("%d", &menuquiz);
                    getchar();
                }

                if(menuquiz == 2)
                {
                    printf("\n\n------------------------------------------ Mostrando materias ------------------------------------------\n");
                    printf("Ordem alfabetica (A-Z):\n\n");
                    inOrdem(T);
                    printf("\n=====================================================================\n\n");
                    break;
                }

                if(menuquiz == 0)
                {
                    pulaLinha();
                    printf("\nAgradecemos por usar o Caderno de Aluno! Encerrando...\n\n");
                    printf("\n###########################\n\n");
                    printf("2022. By: Gabriel Dina Sales, Gabriel Sasuke Yamauchi de Souza, Luiz Felipe Terra da Silva e Vittoria Dutra Teixeira Pirro.");
                    break;
                }

                if(menuquiz > 2)
                {
                    printf("\n\nOpcao invalida para esse menu. Retornando...");
                    printf("\n\n------------------------------------------\n\n");
                    break;
                }
                printf("\n\n----------------------------------------------------------------------------------------------------------------\n\n");
            }
            break;

        case 0:
            printf("\nAgradecemos por usar o Caderno de Aluno! Encerrando...\n\n");
            printf("\n###########################\n\n");
            printf("By: \n | Gabriel Dina Sales | \n | Gabriel Sasuke Yamauchi de Souza | \n | Luiz Felipe Terra da Silva | \n | Vittoria Dutra Teixeira Pirro |\n\n");
            printf("\t\t\t||  ||\n\t\t\t\\\\()//\n                       //(__)\\\\\n                       ||    ||\n \t\t       Dez. 2022\n\n");
            break;

        default:
            printf("\n\nNumero invalido, voltando ao menu inicial...\n\n\n\n");
            printf("###########################\n\n");
        }
    }
    while (menu != 0);
}

void funcQuiz (){  //Onde o usuario informa sobre o quiz de autoavalia��o
    printf("Digite o nome da materia: ");
    scanf("%s", nomeM[numero].nome);
    getchar();

    printf("Quantas perguntas voce fez? Digite aqui: ");
    scanf("%d", &nomeM[numero].perguntas);
    getchar();

    printf("Quantas voce acertou? Digite aqui: ");
    scanf("%d", &nomeM[numero].pontuacao);
    getchar();

    media = nomeM[numero].perguntas/2;
    if (media < nomeM[numero].pontuacao)
    {
        printf("\nParabens! Acima da media na materia: %s\n", nomeM[numero].nome);
    }
    else
    {
        printf("\nVoce precisa estudar mais na materia: %s! Abaixo da media\n", nomeM[numero].nome);
    }
    insertNode(&T, nomeM[numero].nome); //Endere�o T receber� o nome de cada mat�ria adicionada
    numero++;
}

void insertNode(arvore *t, char d[20]){  //t � inserido na �rvore
    if (*t == NULL)
    {
        *t = (struct no*) malloc(sizeof(struct no));//Alocando mem�ria e verificando se tem espa�o suficiente
        if (*t != NULL)
        {
            (*t)->esq = NULL;
            (*t)->dir = NULL;
            strcpy((*t)->dado, d);
        }
        else
            printf("ERRO: Memoria insuficiente!");
    }
    else if (strcmp(d,(*t)->dado) < 0)  //Comparando os dados e informando se h� uma duplica��o ou n�o
        insertNode(&(*t)->esq, d);
    else if (strcmp(d, (*t)->dado) > 0)
        insertNode(&(*t)->dir, d);
    else
        printf("ATENCAO: Duplicacao de no!");
    return;
}

void inOrdem(arvore t){  //Fun��o para organizar e printar em ordem ALFABETICA
    if (t != NULL)
    {
        inOrdem(t->esq);
        printf("- %s\n", t->dado);
        inOrdem(t->dir);
    }
    return;
}

void insereFlash(){  //Fun��o que recebe os dados da materia a nota da mesma e logo em seguida lan�a para o sort
    printf("Digite o materia da materia: ");
    scanf("%s", &lista[indice].materia);
    getchar();

    printf("Digite a nota de %s: ", lista[indice].materia);
    scanf("%s", &lista[indice++].nota);
    getchar();
    sortFlashcard(indice);
    printf("\n=====================================================================\n\n");
}

void pesquisaMateriaFlash(){   //Fun��o para receber o nome da mat�ria que o usu�rio deseja pesquisar e que � enviado para a pesquisa binaria
    printf("Digite o nome da materia: ");
    scanf("%s", &pesquisa);
    getchar();
    indiceUtilitario = pesquisaBinaria(pesquisa, 0, indice);
    printf("Nota de %s: %s\n", pesquisa, lista[indiceUtilitario].nota);
}

void sortFlashcard(int tam){  //InsertionSort para ordena��o dos dados no flashcard e jogando para a lista e seu aux
    int k, j;
    Flashcard aux;
    for (k = 1; k <= tam - 1; k++)
    {
        aux = lista[k];
        j = k - 1;
        while (j >= 0 && strcmp(aux.materia, lista[j].materia) < 0)
        {
            lista[j+1] = lista[j];
            j--;
        }
        lista[j+1] = aux;
    }
    return;
}

int pesquisaBinaria(char dado[], int inicio, int fim){  //Fun��o que faz a busca do dado desejado pelo usu�rio que � informado no menu do flashcard
//� feito a compara��o utilizando o m�todo de pesquisa bin�ria
    int meio = (inicio + fim)/2;
    if (strcmp(lista[meio].materia, dado) == 0)
        return(meio);
    if (inicio >= fim)
        return -1;
    if (strcmp(dado, lista[meio].materia) < 0)
        pesquisaBinaria(dado, inicio, meio-1);
    else
        pesquisaBinaria(dado, meio+1, fim);
    return 0;
}

void cria(Lista *lista2){ //Cria a lista para lembretes
    lista2->inicio=NULL;
    lista2->final=NULL;
}

int insere(Lista *lista2,char *texto){ //Nesta função utilizamos o malloc para alocação dinamica, e atribuimos texto a lista de lembretes
    struct Registro *aux=(struct Registro*)malloc(sizeof(struct Registro));
    if(aux == NULL) return 0;
    strcpy(aux->texto,texto);
    aux->prox=NULL;

    if(lista2->inicio==NULL)
        lista2->inicio=lista2->final=aux;
    else
    {
        lista2->final->prox=aux;
        lista2->final=aux;
    }
    return 1;
}

void le(char *texto){ //Recebe a variável texto
printf("\nEscreva seu recadinho: ");
scanf("%[^\n]s",texto);
}

void imprime_lista(Lista*lista2){ //Imprimir lista de lembretes
struct Registro*aux = lista2->inicio;
while(aux!=NULL){
printf("\n%s\n", aux->texto);
aux=aux->prox;
}
}

void pulaLinha(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
