#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "investidor.h"

///MAIN
int main(){


    //menu
        printf("\nJogo do investimento\n");
        printf("\nComo jogar:\n");
        printf("\n-Escolha uma fase");
        printf("\n-Informe seu nome");
        printf("\n-Informe a acao escolhida");
        printf("\nInsira a porcentagem da acao que queira investir");
        printf("\nE pronto voce pode continuar investindo se quiser\n");

        printf("\n-------------MENU---------------\n");
        printf("\n[1] - JOGAR\n");
        printf("\n[2] - I.A.\n");
        printf("\n[3] - SAIR\n");
        printf("\n-------------------------------\n");

        int nMenu;
        printf("\nInsira a opcao desejada:\n");
        scanf("%d", &nMenu);

    //"final" do menu

    Investidor *inv;
    Acao *acoes;
    // Declarei o contador "i" porque no meu pc não roda declarando dentro do for
    // Declarei uma variável chamada level para seleção do cenário
    int qtdAcoes, i, level;
    FILE  *arquivo;
    double dinheiro;
    char test[100];
    // Criei um contador que será usado na função de compra, e para imprimir as aquisições na tela
    int aux, cont = 0;
    int auxFase;
    int auxNivel;
    char nome[50];
    int dif;
    double l; 

    double menorValor = acoes[0].preco;


    switch (nMenu)
    {
    case (1):
        // Criei um comando de seleção do nível
        printf("Informe o nivel\n");
        printf("\n[1] - 8 acoes\n");
        printf("\n[2] - 10 acoes\n");
        printf("\n[3] - 15 acoes\n");
        printf("\n[4] - 24 acoes\n");
        printf("\n[5] - 100 acoes\n\n");
        scanf("%d", &level);

        switch (level){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            case 4: arquivo = fopen("investimento/invest4.txt", "r"); break;
            case 5: arquivo = fopen("investimento/invest5.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }
        // Eu limpo o ENTER que fica depois que a pessoa digita o nivel
        setbuf(stdin, NULL);
     if(level >= 1 && level<=5){
        //fazer um if para verificar se o arquivo foi aberto
        if(arquivo != NULL){
 
                fscanf(arquivo, "%d", &qtdAcoes);
                fscanf(arquivo, "%d", &aux);
                dinheiro = aux/1.0;
                acoes = (Acao*)malloc(sizeof(Acao)*qtdAcoes);

                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &acoes[i].lucro);
                }
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(acoes[i].preco));
                }
   
                    for( i=0; i<qtdAcoes; i++){
                    printAcao((acoes+i), i);
                    printf("\n");
                    }
                
              
        }


            // Cadastra o novo jogador
            inv = (Investidor*) novoInvestidor(dinheiro);
            if (inv == NULL) printf("Erro na alocacao de novoInvestidor");
            
            // acao servirá para guardar o lucro e o preco das ações para cada investimento
            for (i = 0; i <100; i++){
                inv->investimentos[i].acao = malloc(sizeof(Acao));
            }
            // Atualiza o dinehiro na struct do investidor
            inv->dinheiro = dinheiro;

            for(i=0;i<qtdAcoes;i++){
                if(menorValor > acoes[i].preco){
                menorValor = acoes[i].preco * 0.1;
                }
            }




            // Enquanto ele tiver dinheiro ou não optar por sair, o jogador pode comprar mais ações
            while (inv->dinheiro > menorValor ) {
                //printar acoes sempre que o user for invesir
                int choice = 0;
                choice = compra(acoes, inv, &cont, menorValor);
                if (choice == -1) break;

               
                    for( i=0; i<qtdAcoes; i++){
                        printAcao((acoes+i), i);
                        printf("\n");
                    }
                

            }
            
            
            printf("\n\nResumo dos Investimentos de %s\n", inv->name);


            for (i = 0; i <cont; i++){
                printf("\nCusto:%.2lf Lucro %.2lf\n",inv->investimentos[i].d_investido,inv->investimentos[i].lucro);
            }                               
            printf("\nDinheiro Final:%.2lf\n", inv->dinheiro);
            printf("Lucro Final:%.2lf\n", inv->totalLucro);
            printf("Vezes investidas:%d\n", inv->qtdInvestimentos);

           
        }
        break;

    case 2:
        // Criei um comando de seleção do nível

        printf("Informe o a dificuldade\n");
        printf("\n[1] - Easy\n");
        printf("\n[2] - medium\n");
        printf("\n[3] - Hard\n");
        scanf("%d",&dif);
        switch (dif){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }



        if(dif<0 || dif>3){
            break;
        }
        printf("Informe o nivel\n");
        printf("\n[1] - 8 acoes\n");
        printf("\n[2] - 10 acoes\n");
        printf("\n[3] - 15 acoes\n");
        printf("\n[4] - 24 acoes\n");
        printf("\n[5] - 100 acoes\n\n");
        scanf("%d", &level);

        switch (level){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            case 4: arquivo = fopen("investimento/invest4.txt", "r"); break;
            case 5: arquivo = fopen("investimento/invest5.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }
        // Eu limpo o ENTER que fica depois que a pessoa digita o nivel
        setbuf(stdin, NULL);

        int auxValue;
     if(level >= 1 && level<=5){
        //fazer um if para verificar se o arquivo foi aberto
        if(arquivo != NULL){
 
                fscanf(arquivo, "%d", &qtdAcoes);
                fscanf(arquivo, "%d", &aux);
                int profit[qtdAcoes];
                int price[qtdAcoes];
                dinheiro = aux/1.0;
                acoes = (Acao*)malloc(sizeof(Acao)*qtdAcoes);
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(profit[i]));
                }
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(price[i]));
                }

            if(dif == 1){
                 ga(aux,price,profit,20); 

            }
               if(dif == 2){
                 ga(aux,price,profit,50); 

            }
               if(dif == 3){
                 ga(aux,price,profit,200); 

            }              
        }


           
        }
        break;

    case 3:
        break;
    default:
        printf("\nOpcao inexistente\n");
        break;
    }
   

 

    
   
   
  //inv->investimentos[i].d_investido 
  //o que é:
  // um ponteiro do tipo investidor que 
  //aponta para um vetor alocado dinamicamente 
  //que é preenchido por d-investido.



system("pause");

}

