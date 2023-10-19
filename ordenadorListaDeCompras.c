
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTEXTO 500
#define MAXITENS 1000

typedef struct {
  char nome[MAXTEXTO];
  int qtd;
  int valido; // 0 ou 1
} Itens;

/* prototipos das funcoes */
int insereItem(
    Itens item[], char proxItem[],
    int topo); // retorno : 1, lista aumentou de tamanho, 0 não aumentou
void removeItem(Itens item[], char proxItem[], int topo);
//int buscaItem(Itens item[], int iFinal,char procurado[]); // retorno : -1 item nao encontrado, indice de
                                 // item[] se encontrado
void inicialMaiscula(Itens item[], int iFinal);
void caixaAlta(Itens item[], int iFinal);
void ordenaLista(Itens item[], int iFinal);
void imprimeLista(Itens item[], int iFinal);

int main() {
  Itens item[MAXITENS];
  int topo = 0; //qnt itens diferentes
  char proxItem[MAXTEXTO];
  char op;
  int i;

  for (i = 0; i < MAXITENS; i++) {
    item[i].qtd = 0;
    item[i].valido = 0;
  }
  printf("Digite a opção I(inserir um item na lista), R(remover um item da lista), S(encerrar o programa): \n");
  do {
    
    scanf(" %c", &op);
    getchar();
    switch (op) {
    case 'I':
      scanf(" %[^\n]", proxItem);
      getchar();
      topo += insereItem(item, proxItem, topo);
      break;
    case 'R':
      scanf(" %[^\n]", proxItem);
      getchar();
      removeItem(item, proxItem, topo);
      break;
    default:
      break;
    }
  } while (op != 'S');

  inicialMaiscula(item, topo); // para itens com qtd == 1

  caixaAlta(item, topo); // para itens com qtd > 1

  ordenaLista(item, topo);

  printf("\n");
  printf("Segue lista após ordenação: \n");
  imprimeLista(item, topo);

  return (0);
}




int insereItem(Itens item[], char proxItem[], int topo) {
  //int iRepetido = buscaItem(item, topo, proxItem);
  int i = 0;
  char c, arrayaux[MAXTEXTO];

  //coloca tudo em minúsculo
  for (int i = 0; proxItem[i] != '\0'; i++) {
    proxItem[i] = tolower(proxItem[i]);
  }


  //repetido
  for (int i = 0; i < topo; i++) {
    if (strcmp(item[i].nome, proxItem) == 0) {
      item[i].qtd++;
      
      return 0;
    }
  }
  
  for (int i = 0; i < MAXITENS; i++) {
    if (item[i].qtd == 0) {
      strcpy(item[i].nome, proxItem);
      item[i].qtd++;
      
      return 1;
    }
  }

  return -1;
}

void removeItem(Itens item[], char proxItem[], int topo) {
  for (int i = 0; i < MAXITENS; i++) {
    if (strcmp(item[i].nome, proxItem) == 0 ) {
      if(item[i].qtd > 0){
        item[i].qtd--;
        
      }
      
      break;
    }
  }
}

void inicialMaiscula(Itens item[], int iFinal) {
  for (int i = 0; i < MAXITENS; i++) {
    if (item[i].qtd > 0) {
      item[i].nome[0] = toupper(item[i].nome[0]);
    }
  }



  int j = 0;
  for (int i = 0; i < MAXITENS;i++) {
    j = 0;
    if (item[i].qtd > 0) {
      while (item[i].nome[j] != '\0') {
        if(item[i].nome[j] == ' '){
          item[i].nome[j+1] = toupper(item[i].nome[j+1]);
        }
        j++;
        
      }
    
    }
  }
}

void caixaAlta(Itens item[], int iFinal) {
  int j = 0;
  for (int i = 0; i < MAXITENS;i++) {
    j = 0;
    if (item[i].qtd > 1) {
      while (item[i].nome[j] != '\0') {
        item[i].nome[j] = toupper(item[i].nome[j]);
        j++;
      }
    
    }
  }
}

void ordenaLista(Itens item[], int iFinal) {  
  int itens=0;
  for(int i=0; i< MAXITENS ; i++){
    if(item[i].qtd > 0){
      itens++;//qnt de itens
    }
  }

  
  for (int i = 0; i < itens - 1; i++) {
    int indiceMin = i;
    for (int j = i + 1; j < itens; j++) {
      if (strcmp(item[indiceMin].nome, item[j].nome) > 0) {
        indiceMin = j;
      }
    }
    if (indiceMin != i) {
      char temp[MAXTEXTO];
      strcpy(temp, item[i].nome);
      int qtdtemp = item[i].qtd;
      int qtdindice = item[indiceMin].qtd;
      strcpy(item[i].nome, item[indiceMin].nome);
      item[i].qtd = qtdindice;
      item[indiceMin].qtd = qtdtemp;
      strcpy(item[indiceMin].nome, temp);
    }
  }
}

void imprimeLista(Itens item[], int iFinal){
  for(int i=0; i < MAXITENS; i++){
    if(item[i].qtd>0){
      printf("%s X%d\n", item[i].nome, item[i].qtd);
    }
    
  }
}

