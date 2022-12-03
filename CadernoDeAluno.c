#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

unsigned int menu, menulembrete, menuflashcard, menuquiz, media, i = 0, numero = 0;

struct no {
    struct no *esq;
    char dado[20];
    struct no *dir;
};
typedef struct no *arvore;
arvore T = NULL;

typedef struct
{
    char nome[50];
    int pontuacao, perguntas;
}Materia; // Define o nome do novo tipo criado
Materia nomeM[10];

void funcQuiz();
void insertNode(arvore *t, char d[20]);
void inOrdem(arvore t);
int  procuraDado(arvore t, char d[20]);

int main()
{
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

            while(menulembrete == 1 || 2)
            {
                if(menulembrete == 1)
                {
                    printf ("\nMostrando lembretes...\n\n");
                    //chamar a função de ver lembretes
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menulembrete);
                }

                if(menulembrete == 2)
                {
                    printf ("\nAdicione o lembrete\n\n");
                    //Chamar a função de adicionar lembrete
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

        case 2:
            printf("\n\n______ FlashCards ______\n\n");

            printf ("Digite o que deseja (1 para ver,  2 para adicionar, 0 pra voltar): ");
            scanf ("%d", &menuflashcard);
            while(menuflashcard == 1 || 2)
            {
                if(menuflashcard == 1)
                {
                    printf ("\nMostrando FlashCards...\n\n");
                    //chamar a função de ver lembretes
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menuflashcard);
                }

                if(menuflashcard == 2)
                {
                    printf ("\nAdicione o novo FlashCard\n\n");
                    //Chamar a função de adicionar lembrete
                    printf ("1 para ver,  2 para adicionar, 0 pra voltar: ");
                    scanf ("%d", &menuflashcard);
                }

                if(menuflashcard == 0)
                {
                    printf ("\n\nVoltando a tela inicial...\n\n");
                    break;
                }

                if(menuflashcard > 2)
                {
                    printf("\n\nOpcao invalida para esse menu. Retornando...");
                    printf("\n\n------------------------------------------\n\n");
                    break;
                }
                printf("\n\n----------------------------------------------------------------------------------------------------------------\n\n");
            }
            break;

        case 3:
            printf("\n\n______ Quiz ______\n\n");

            printf ("Digite o que deseja (1 se avaliar, 0 pra voltar): ");
            scanf ("%d", &menuquiz);
            getchar();

            while(menuquiz != 0)
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
                    /*for(int i = 0; i < numero; i++)
                        printf("\nMateria: %s\nPontuacao: %d de %d questoes\n\n", nomeM[i].nome, nomeM[i].pontuacao, nomeM[i].perguntas);*/
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

void funcQuiz ()
{
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
    insertNode(&T, nomeM[numero].nome);
    numero++;
}

void insertNode(arvore *t, char d[20]) {
    if (*t == NULL) {
        *t = (struct no*) malloc(sizeof(struct no));
        if ( *t != NULL ) {
            (*t)->esq = NULL;
            (*t)->dir = NULL;
            strcpy((*t)->dado, d);
        } else
            printf("Memoria insuficiente");
    } else
        if (strcmp(d,(*t)->dado) < 0)
            insertNode(&(*t)->esq, d);
        else
            if (strcmp(d, (*t)->dado) > 0)
                insertNode(&(*t)->dir, d);
            else
                printf("Duplicação de no");
    return;
}

void inOrdem(arvore t) {
    if (t != NULL) {
        inOrdem(t->esq);
        printf("- %s\n", t->dado);
        inOrdem(t->dir);
    }
    return;
}

int  procuraDado(arvore t, char d[20]) {
    if (t == NULL)
        return 0;
    return ((strcmp(t->dado, d) == 0) ||
             procuraDado(t->esq, d) ||
             procuraDado(t->dir, d));
}

int maior(int a, int b) {
    if (a > b)
        return(a);
    return(b);
}
