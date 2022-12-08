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

struct no { //Struct para percorrer a arvore
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
}Materia; //Define o nome do novo tipo criado
Materia nomeM[10];

void insereFlash();                     //Função que recebe os dados da materia a nota da mesma
void pesquisaMateriaFlash();            //Função para receber o nome da matéria que o usuário deseja pesquisar
void sortFlashcard(int tam);            //InsertionSort para ordenação dos dados no flashcard
int pesquisaBinaria(char*, int, int);   //Função que faz a busca do dado desejado pelo usuário
void funcQuiz();                        //Função para o sub-menu do Quiz para que o usuário digite os dados
void insertNode(arvore *t, char d[20]); //Inserindo o no t para preparar a ordenação
void inOrdem(arvore t);                 //Mostrar as materias inseridas no quiz em ordem alfabetica

int main()
{
    int op = -1;

    printf("\tBem-vindo(a)!\n\n ");
    do
    {
        printf("Escolha uma opcao:\n\n 1- Lembretes\n 2- FlashCards \n 3- Quiz \n 0- Sair\n");
        printf("\nDigite aqui: ");
        scanf("%d", &menu);
        getchar();

        switch(menu)
        {
        case 1:
            printf("\n\n______ Lembretes ______\n\n");

            printf ("Digite o que deseja (1 para ver,  2 para adicionar, 0 pra voltar): ");
            scanf ("%d", &menulembrete);
            getchar();

            while(menulembrete == 1 || 2)
            {
                if(menulembrete == 1)
                {
                    printf ("\nMostrando lembretes...\n\n");
                    //chamar a fun��o de ver lembretes
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menulembrete);
                }

                if(menulembrete == 2)
                {
                    printf ("\nAdicione o lembrete\n\n");
                    //Chamar a fun��o de adicionar lembrete
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menulembrete);
                }

                if(menulembrete == 0)
                {
                    printf ("\n\nVoltando a tela inicial...\n\n");
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

        case 2: //Menu do FlashCard, onde o aluno pode armazenar as notas totais de cada matéria, por exemplo: Modelagem 3D - 90; AOC - 70
            printf("\n\n______ FlashCards ______\n\n");

            printf ("Digite o que deseja (1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair): ");
            scanf ("%d", &menuflashcard);
            getchar();

            while(menuflashcard == 1 || 2 || 3) //Loop para que continue sendo executado enquanto o usuario não digitar 0 para voltar ao menu principal
            {
                if(menuflashcard == 1)
                {
                    printf("\nExibindo lista de materias...\n");
                    for(i=0; i < indice; i++)
                        printf("%2d-\t%s\t%s\n", i+1, lista[i].materia, lista[i].nota);

                    printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                    scanf ("%d", &menuflashcard);
                    getchar();
                }

                if(menuflashcard == 2)
                {
                    if(indice < 10)
                {
                    printf("\nInserindo materia...\n");
                    insereFlash();
                }
                    else
                    printf("Maximo de materias!\n");

                    printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                    scanf ("%d", &menuflashcard);
                    getchar();
                }

                if(menuflashcard == 3)
                {
                    printf("\nPesquisando materia...\n");
                    pesquisaMateriaFlash();

                    printf ("\n1 mostrar materias,  2 inserir materia, 3 pesquisar materia ou 0 para sair: ");
                    scanf ("%d", &menuflashcard);
                    getchar();
                }

                if(menuflashcard == 0)
                {
                    printf ("\n\nVoltando a tela inicial...\n\n");
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

            while(menuquiz != 0) //Loop para que continue sendo executado enquanto o usuario não digitar 0 para voltar ao menu principal
            {
                if(menuquiz == 1)
                {
                    printf ("Comecando o quiz...\n\n");
                    funcQuiz();
                    printf ("\n1 se avaliar novamente, 2 ver materias adicionadas, 0 pra voltar: ");
                    scanf ("%d", &menuquiz);
                    getchar();
                }

                if(menuquiz == 2){
                    printf("\n\n------------------------------------------ Mostrando materias ------------------------------------------\n");
                    printf("Ordem alfabetica (A-Z):\n\n");
                    inOrdem(T);
                    printf("\n=====================================================================\n\n");
                break;
                }

                if(menuquiz == 0)
                {
                    printf ("\n\nVoltando a tela inicial...\n\n");
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
            printf("\nEncerrando...\n\n");
            printf("\n###########################\n\n");
            break;

        default:
            printf("\n\nNumero invalido, voltando ao menu inicial...\n\n\n\n");
            printf("###########################\n\n");
        }
    }
    while (menu != 0);
}

void funcQuiz (){ //Onde o usuario informa sobre o quiz de autoavaliação
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
    insertNode(&T, nomeM[numero].nome); //Endereço T receberá o nome de cada matéria adicionada
    numero++;
}

void insertNode(arvore *t, char d[20]){ //t é inserido na árvore
    if (*t == NULL) {
        *t = (struct no*) malloc(sizeof(struct no));//Alocando memória e verificando se tem espaço suficiente
        if (*t != NULL) {
            (*t)->esq = NULL;
            (*t)->dir = NULL;
            strcpy((*t)->dado, d);
        } else
            printf("ERRO: Memoria insuficiente!");
    } else
        if (strcmp(d,(*t)->dado) < 0) //Comparando os dados e informando se há uma duplicação ou não
            insertNode(&(*t)->esq, d);
        else
            if (strcmp(d, (*t)->dado) > 0)
                insertNode(&(*t)->dir, d);
            else
                printf("ATENCAO: Duplicacao de no!");
    return;
}

void inOrdem(arvore t){ //Função para organizar e printar em ordem ALFABETICA
    if (t != NULL) {
        inOrdem(t->esq);
        printf("- %s\n", t->dado);
        inOrdem(t->dir);
    }
    return;
}

void insereFlash(){ //Função que recebe os dados da materia a nota da mesma e logo em seguida lança para o sort
    printf("Digite o materia da materia: ");
    scanf("%s", &lista[indice].materia);
    getchar();

    printf("Digite a nota de %s: ", lista[indice].materia);
    scanf("%s", &lista[indice++].nota);
    getchar();
    sortFlashcard(indice);
}

void pesquisaMateriaFlash(){  //Função para receber o nome da matéria que o usuário deseja pesquisar e que é enviado para a pesquisa binaria
    printf("Digite o nome da materia: ");
    scanf("%s", &pesquisa);
    getchar();
    indiceUtilitario = pesquisaBinaria(pesquisa, 0, indice);
    printf("Nota de %s: %s\n", pesquisa, lista[indiceUtilitario].nota);
}

void sortFlashcard(int tam){ //InsertionSort para ordenação dos dados no flashcard e jogando para a lista e seu aux
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

int pesquisaBinaria(char dado[], int inicio, int fim){ //Função que faz a busca do dado desejado pelo usuário que é informado no menu do flashcard
 //É feito a comparação utilizando o método de pesquisa binária
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
