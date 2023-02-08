#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura dos Nós 
typedef struct no{
    char nome[64]; // Char para um nome até 64 caracteres
    struct no * prox; // Ponteiro para receber um endereço de um nó
} No;

typedef No * link; // Ponteiro para uma estrutura de um nó

// Estrutura da minha lista
typedef struct{
    link ini;
    link fim;
}Lista;

// Cria um novo nó
link novo_no(char info[]){
    link novo = malloc(sizeof(No)); // Aloca memória com o tamanho de um nó
    strcpy(novo->nome, info); // Copia a string de info para o nome no novo nó criado
    novo->prox = NULL; // Inicializa o ponteiro com NULL para que não fique atrelado endereços indesejados
    return novo; // retorna o novo nó
}

// Insere um nó no inicio da lista 
Lista insere_inicio(Lista lista, char info[]){
    link novo = novo_no(info); // Cria um novo nó 

    /* Verifica se a lista está vazia.
       Se a lista estiver vazia, tanto o inicio quanto
       o fim da lista recebem o mesmo nó criado */
    if(lista.ini == NULL){
        lista.fim = novo;
    }else{
        // O ponteiro prox do novo nó recebe quem antes era o primeiro elemento da lista
        novo->prox = lista.ini; 
    }
    lista.ini = novo;

    return lista; 
}

// Insere um nó no fim da lista 
Lista insere_final(Lista lista, char info[]){
    link novo = novo_no(info); // Cria um novo nó
    
    /* Verifica se a lista está vazia.
       Se a lista estiver vazia, tanto o inicio quanto
       o fim da lista recebem o mesmo nó criado */
    if(lista.ini == NULL){
        lista.ini = novo;
    }else{
        // O ultimo nó da lista agora aponta para o novo ultimo nó
        lista.fim->prox = novo;
    }
    lista.fim = novo;

    return lista;
}

// Insere os alementos ordenadamente na lista 
Lista insere_ordenado(Lista lista, char info[]){

    // A função strcmp copia o conteúdo de um ponteiro para outro
    // e retorna um umteiro para indicar se é igual, menor ou maior.

    /* Se a lista estiver vázia ou o primeiro nome a ser inserido
       for menor que o primeiro elemento, insere no incio da lista */
    if(lista.ini == NULL || strcmp(lista.ini->nome, info) >= 0){
        lista = insere_inicio(lista, info);

    /* Se o nome a ser inserido for maior que o ultimo nome
       da lista, insere no fim */
    }else if(strcmp(lista.fim->nome, info) <= 0){
        lista = insere_final(lista, info);

    // Se o elemento estiver no meio da lista
    }else{
        link novo = novo_no(info); // cria um novo nó
        link p = lista.ini; // Variavel para percorrer a lista

        /* Percorre a lista enquanto os nomes da lista for menor que
           o nome a ser inserido na lista*/
        // Sempre compara com um nó a frente 
        while(strcmp(p->prox->nome, info) <= 0){
            p = p->prox; // Ponteiro pra um nó "incrementa" recebendo o próximo nó da lista
        }
        // O While para quando p é um nó antes do nó quem contem o nome procurado
        
        novo->prox = p->prox; // O novo nó criado apontará para o próximo no na ordem correta
        p->prox = novo;  // O nó que deve ficar anterior ao novo nó recebe o novo nó
    }
    return lista;
}

// Deleta um elemento da lista
Lista deletar(Lista lista, char alvo[]){
    // Se a lista estiver vázia, nada pode ser deletado
    if(lista.ini == NULL){
        printf("\e[1;34mNão pode deletar, a lista está vazia \n\e[m");
        return lista; // Retorna a lista sem fazer nada 
    }

    // Se o elemento a ser deletado está no inicio da lista...
    if(strcmp(lista.ini->nome, alvo) == 0){
        link aux = lista.ini;   // Váriavel auxiliar para liberar a memória do ponteiro;
        lista.ini = lista.ini->prox; // O inicio da minha lista recebe o segundo elemento como novo inicio
        free(aux); // libero a memoria do antigo primeiro elemeto que foi deletado
        printf("\e[1;31m%s deletado \n\e[m", alvo);
        return(lista);

    // Caso o elemento a ser deletado não esteja no ininio da lista
    }else{
        link p = lista.ini; // variavel para percorrer a lista
        link aux; // Variavel auxiliar para liberar memoria do elemento deletado

        
        // Percorre a lista enquanto estiver conteúdo no nó seguinte
        while(p->prox != NULL) {

            // Se encontrar o alvo procurado
            if(strcmp(p->prox->nome, alvo) == 0){
                
                aux = p->prox; // variavel auxiliar recebe o segundo proximo nó para liberar memoria postermente
                
                // Se p->prox já aponta para o último elemento da lista
                // não posso fazer com que p->prox recebe p->prox->prox 
                // pois esse elemento não faz parte da minha lista
                if(p->prox->prox == NULL){
                    lista.fim = p; // Devo atualizar o meu lista.fim pois não existe mais aquele ultimo elemento
                    p->prox = NULL; // Como o p é o ultimo elemento da lista nesse caso, ele recebe NULL no prox
                }else{
                    // O nó anterior ao nó a ser deletado apontará ao próximo nó do no a ser deletado
                    p->prox = p->prox->prox; 
                }
                
                free(aux); // Libera memoria do nó deletado
                
                printf("\e[1;31m%s deletado \n\e[m", alvo);
                return(lista);
            }
            
            p = p->prox; // "incrementa" o p para o proximo nó
            aux = p->prox; // variavel auxiliar recebe o segundo proximo nó para liberar memoria postermente
        }

        printf("\e[1;31m%s não existe na lista \n\e[m", alvo);
        return lista;
    }
}

// Imprime os elemetos da lista
void imprime(Lista lista){
    // Se a lista estiver fazua, não faz nada
    if(lista.ini == NULL){
        printf("\e[1;35mA lista está vazia \n\e[m");
    }
    
    link p; // variavel para percorrer a lista;
    // Percorre a lista até o ultimo elemento e vai imprimindo cada nó
    for(p = lista.ini; p != NULL; p = p->prox){
        printf("\e[1;30m%s \n\e[m", p->nome);
    }
}

// Libera a memória da lista com recursão
void libera_rec(link ini) {
    if (ini == NULL) return; // Se o inicio for nulo, retorna a lista
    libera_rec(ini->prox); // Chama a função passando o proximo nó como argumento
    free(ini); // Quando a lista chega no fim, todas as chamandas vão sendo retornadas e liberando memória
}

// Chama a função de liberar a memoria passando ao inicio da lista como argumento
void libera(Lista lista) {
    libera_rec(lista.ini); 
}


int main(void){
    Lista lista; // Cria a lista
    lista.ini = lista.fim = NULL; // Inicializa os ponteiros com NULL

    int fim = 0; // variavel tipo "bool" para controle de loop
    char escolha, string_nome[64], entrada[64]; // Variaveis para manipulação dos dados no programa

    printf("\nOlá! Estamos em um sistema de armazenamento de nomes\n\n");
    
    // Loop do programa 
    while(!fim){
        printf("\nEscolha:\ni - Inserir nome\np - Mostrar nomes\nd - Deletar nome\nq - Finalizar programa\n> ");
        scanf(" %c", &escolha);
        
        switch(escolha){
            case 'i':
                printf("Qual nome você deseja inserir: ");
                scanf("%s", entrada);
                strcpy(string_nome, entrada);
                lista = insere_ordenado(lista, string_nome);
                printf("\e[1;32m%s inserido \n\e[m", string_nome);
                break;
            case 'p':
                imprime(lista);
                break;
            case 'd':
                printf("Qual nome você deseja deletar: ");
                scanf("%s", entrada);
                strcpy(string_nome, entrada);
                lista = deletar(lista, string_nome);
                break;
            case 'q':
                libera(lista);
                printf("\e[1;32mPrograma encerrado! \n\e[m");
                fim = 1;
                break;
            default:
                printf("\e[1;31mEscolha invalida \n\e[m");
                break;
        }
    }
    return 0;
}