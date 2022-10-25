#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_1 10    
#define TAM_2 1000
#define n_vertices_1 10
#define n_vertices_2 1000

/*

  TAM_1 100         -> Tamanho da 1° MATRIZ
  TAM_2 1000        -> Tamanho da 2° MATRIZ
  n_vertices_1 100  -> Número do vértices do 1° Grafo
  n_vertices_2 1000 -> Número do vértices do 2 Grafo

  */

struct vertice {

  int valor;
  struct vertice *next;
};

struct grafo {

  int n_vertice;           //
  int n_aresta;
  struct vertice *vertice; //Lista de vértices
};

struct grafo* construtorGrafo(int tamanho) {

  struct grafo *grafo = (struct grafo *)malloc(sizeof(struct grafo));
  grafo->vertice = (struct vertice *)calloc(tamanho, sizeof(struct vertice));

  grafo->n_vertice = -1;
  return grafo;
}

bool verticeExiste(struct grafo *grafo, int valor) {

  for (int i = 0; i <= grafo->n_vertice; i++) {
    if (grafo->vertice[i].valor == valor) {
      return true;
    }
  }

  return false;
}

struct grafo* construtorVertice(struct grafo *grafo, int valor,int tipo_insercao) {

  if (verticeExiste(grafo, valor) == false) {

    grafo->n_vertice += 1;
    grafo->vertice[grafo->n_vertice].valor = valor;
    grafo->vertice[grafo->n_vertice].next = NULL;

    return grafo;
  }

  else{
    if(tipo_insercao == 0){
      
      valor = (rand() % n_vertices_1);
      return construtorVertice(grafo,valor,0);
  
    }
    
    if(tipo_insercao == 1){
      
      valor = (rand() % n_vertices_2);
      return construtorVertice(grafo,valor,1);
  
    }

    return NULL;
  }
    
}

int n_arestaAdjacentes(struct grafo *grafo,int valor){

  for (int i = 0; i <= grafo->n_vertice; i++) {
    if (grafo->vertice[i].valor == valor){
      
      int numero = 0;
      struct vertice *aux = &grafo->vertice[i];
      
      while(aux->next != NULL){
        aux = aux->next;
        numero++;
      }
     
      return numero;
    }
  }
  return -1;
}

struct grafo* construirAresta(struct grafo *grafo, int vertice1, int vertice2) {

  if(vertice1 != vertice2){
    if(verticeExiste(grafo,grafo->vertice[vertice1].valor) == true && verticeExiste(grafo,grafo->vertice[vertice2].valor) == true){ //Talvez tenha que tirar
      
      if((n_arestaAdjacentes(grafo,grafo->vertice[vertice1].valor) < 3) && (n_arestaAdjacentes(grafo,grafo->vertice[vertice2].valor) < 3)){
          
          struct vertice *novo = (struct vertice*)malloc(sizeof(struct vertice));
          novo->valor = grafo->vertice[vertice2].valor;
          novo->next = NULL;
    
          struct vertice *aux = &grafo->vertice[vertice1];
         
          while(aux->next != NULL){
            aux = aux->next;
            
          }

          if(aux->valor == novo->valor){ //Não pode ocorrer repetição de arestas adjacentes
            free(novo);
            return grafo;
          }
    
          struct vertice *novo2 = (struct vertice*)malloc(sizeof(struct vertice));
          novo2->valor = grafo->vertice[vertice1].valor;
          novo2->next = NULL;
    
          struct vertice *aux2 = &grafo->vertice[vertice2];
          while(aux2->next != NULL){
            aux2 = aux2->next;
    
          }

          if(aux2->valor == novo2->valor){ //Não pode ocorrer repetição de arestas adjacentes
            free(novo);
            free(novo2);
            return grafo;
          }

          aux->next = novo;
          aux2->next = novo2;

          grafo->n_aresta += 1;
          
          return grafo;
      }
    }
    return grafo;
  }
  return grafo;
}

void imprimirGrafo(struct grafo *grafo){

  struct vertice *aux;
  for(int i = 0; i<= grafo->n_vertice; i++){
    printf("Grafo[%d] = %d",i,grafo->vertice[i].valor);
    aux = &grafo->vertice[i];
    while(aux->next != NULL){
      printf(" -> %d ",aux->next->valor);
      aux = aux->next;
    }
    printf("\n");
  }
  
}

//-----------------------------------------------------------------------------------------

void InicializandoMatrix_1(int matriz[][TAM_1]){

  for (int i = 0; i < TAM_1; i++){
    for (int j = 0; j < TAM_1; j++){
      
      matriz[i][j] = -1;

    }
  }

}

void InicializandoMatrix_2(int matriz_1[][TAM_1],int matriz_2[][TAM_2]){

  for (int i = 0; i < TAM_2; i++){
    for (int j = 0; j < TAM_2; j++){

      if((i < TAM_1) && (j < TAM_1)){

        if(matriz_1[i][j] == 1){
          matriz_2[i][j] = 1;
        }
        if(matriz_1[i][j] == 0){
          matriz_2[i][j] = 0;
        }
        if(matriz_1[i][j] == -1){
          matriz_2[i][j] = -1;
        }
      }
      else{
         matriz_2[i][j] = -1;
      }
    }
  }
  
}

void ConstrutorVerticeMatrix_1(int matriz[][TAM_1],int valor){ 
  
  while(matriz[valor][valor] == 0 || matriz[valor][valor] == 1){
    valor = (rand() % TAM_1); //0 até 999
  }

  matriz[valor][valor] = 0;
  
}

void ConstrutorVerticeMatrix_2(int matriz[][TAM_2],int valor){ 

  while(matriz[valor][valor] == 0 || matriz[valor][valor] == 1){
    valor = (rand() % TAM_2); //0 até 99999
  }
  
  matriz[valor][valor] = 0;

}

int N_aresta_AdjacentesMatrix_1(int matriz[][TAM_1],int valor){

  int soma = 0;

  for (int i = 0; i < TAM_1; i++){

    if(matriz[valor][i] == 1){
      soma += 1;
    }
    
  }

  return soma;

}

int N_aresta_AdjacentesMatrix_2(int matriz[][TAM_2],int valor){

  int soma = 0;

  for (int i = 0; i < TAM_2; i++){

    if(matriz[valor][i] == 1){
      soma += 1;
    }
    
  }

  return soma;

}

bool verticeExisteMatrix_1(int matriz[][TAM_1],int valor){
  
  if(matriz[valor][valor] == 1 || matriz[valor][valor] == 0){
    
    return true;

  }
  
  return false;

}

bool verticeExisteMatrix_2(int matriz[][TAM_2],int valor){
  
  if(matriz[valor][valor] == 1 || matriz[valor][valor] == 0){

    return true;

  }
  
  return false;

}

void ConstruirArestaMatrix_1(int matriz[][TAM_1],int vertice1,int vertice2){
 
  if(vertice1 != vertice2){
  
    if(verticeExisteMatrix_1(matriz,vertice1) == true && verticeExisteMatrix_1(matriz,vertice2) == true){

      if(N_aresta_AdjacentesMatrix_1(matriz,vertice1) < 3 && N_aresta_AdjacentesMatrix_1(matriz,vertice2) < 3){

        matriz[vertice1][vertice2] = 1;
        matriz[vertice2][vertice1] = 1;
        
      }
    
    }
        
  }
    
}

void ConstruirArestaMatrix_2(int matriz[][TAM_2],int vertice1,int vertice2){
 
  if(vertice1 != vertice2){
  
    if(verticeExisteMatrix_2(matriz,vertice1) == true && verticeExisteMatrix_2(matriz,vertice2) == true){

      if(N_aresta_AdjacentesMatrix_2(matriz,vertice1) < 3 && N_aresta_AdjacentesMatrix_2(matriz,vertice2) < 3){

        matriz[vertice1][vertice2] = 1;
        matriz[vertice2][vertice1] = 1;
        
      }
    
    }
        
  }
    
}

void imprimir_matrix_1(int matriz[][TAM_1]){

  for (int i = 0; i < TAM_1; i++){
    if(matriz[i][i] == 1 || matriz[i][i] == 0){
      printf("Matriz[%d]",i);
      for(int j = 0; j < TAM_1; j++){
        if(matriz[i][j] == 1){
          printf(" -> Matriz[%d]",j);
        }
      }
    printf("\n");
    }
  
  }

}

void imprimir_matrix_2(int matriz[][TAM_2]){

  for (int i = 0; i < TAM_2; i++){
    if(matriz[i][i] == 1 || matriz[i][i] == 0){
      printf("Matriz[%d]",i);
      for(int j = 0; j < TAM_2; j++){
        if(matriz[i][j] == 1){
          printf(" -> Matriz[%d]",j);
        }
      }
    printf("\n");
    }
  
  }

}

int main(){
  
  clock_t tempo;
  double soma = 0;

  srand(time(NULL));

  struct grafo *grafo_lista;
  int grafoMatriz[TAM_1][TAM_1];
  
  grafo_lista = construtorGrafo(TAM_1);
  InicializandoMatrix_1(grafoMatriz);

  int numero_aleatorio;

  //Construindo Vértices
  for(int i = 0; i< n_vertices_1; i++){ //n_vertices_1 = 100
    numero_aleatorio = (rand() % n_vertices_1); //0 até 99
    grafo_lista = construtorVertice(grafo_lista,numero_aleatorio,0);
    ConstrutorVerticeMatrix_1(grafoMatriz,numero_aleatorio);
  }

  int numero_aleatorio2;

  //Construindo Arestas, Cada vértice terá um número aleatório de arestas menor ou igual a três.  
  for(int i = 0; i< n_vertices_1; i++){ //n_vertices_1 = 100
    numero_aleatorio = rand() % 4; //0 até 3
    for(int j = 0; j< numero_aleatorio;j++){
      numero_aleatorio2 = rand() % n_vertices_1; //0 até 99
      grafo_lista = construirAresta(grafo_lista,i,numero_aleatorio2);
      ConstruirArestaMatrix_1(grafoMatriz,grafo_lista->vertice[i].valor,grafo_lista->vertice[numero_aleatorio2].valor); //A construção das Arestas sera a mesma do grafo de Listas Adjacentes
    }
  }

  FILE *file;
  file = fopen("lista_adjacencias.txt","w");
  struct vertice *aux;
  for(int i = 0; i<= grafo_lista->n_vertice; i++){
    fprintf(file,"Grafo[%d] = %d",i,grafo_lista->vertice[i].valor);
    aux = &grafo_lista->vertice[i];
    while(aux->next != NULL){
      fprintf(file," -> %d ",aux->next->valor);
      aux = aux->next;
    }
    fprintf(file,"\n");
  }
  fclose(file);


  file = fopen("tabela_adjacencias.txt","w");

  for (int i = 0; i < TAM_1; i++){
    if(grafoMatriz[i][i] == 1 || grafoMatriz[i][i] == 0){
      fprintf(file,"Matriz[%d]",i);
      for(int j = 0; j < TAM_1; j++){
        if(grafoMatriz[i][j] == 1){
          fprintf(file," -> Matriz[%d]",j);
        }
      }
    fprintf(file,"\n");
    }

  }

  fclose(file);

  //--------------Mudando o tamanho do grafo para 100.000 vértices-----------------------

  grafo_lista->vertice = realloc(grafo_lista->vertice,n_vertices_2*(sizeof(struct vertice)));

  int grafo_matriz_2[TAM_2][TAM_2];
  InicializandoMatrix_2(grafoMatriz,grafo_matriz_2);

  //--------------Tempo para inserção dos Vértices de lista adjacencias ------------------

  int n_insercao = 99;
  int laco = 0;
  int limite = 20; //20
  int comeco = 10; //Número de vértices já criados

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){
      numero_aleatorio = (rand() % n_vertices_2);  // 0 até 999
      grafo_lista = construtorVertice(grafo_lista,numero_aleatorio,1);
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo para inserção dos vértices da lista de adjacencias: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio para inserção dos vértices da lista de adjacencias: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //-----------Tempo para inserção das Arestas de lista adjacencias----------------------


  n_insercao = 99;
  laco = 0;
  limite = 20; 
  comeco = 10;

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      numero_aleatorio = rand() % 4;  // 0 até 3
      for(int j = 0; j< numero_aleatorio;j++){
        numero_aleatorio2 = (rand() % n_vertices_2); // 0 até 999
        grafo_lista = construirAresta(grafo_lista,i,numero_aleatorio2);
      }
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  } 

  tempo = clock() - tempo;

  printf("\nTempo para inserção das arestas da lista de adjacencias: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio para inserção das arestas da lista de adjacencias: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //-----------Tempo para inserção dos Vértices da tabela de adjacencias--------------------
   
  
  n_insercao = 99;
  laco = 0;
  limite = 20; //20
  comeco = 10; //Número de vértices já criados

  tempo = clock();
  
  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      numero_aleatorio = (rand() % n_vertices_2); // 0 até 999
      ConstrutorVerticeMatrix_2(grafo_matriz_2,numero_aleatorio);
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo para inserção dos vértices da tabela de adjacencias: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio para inserção dos vértices da tabela de adjacencias: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

  //-----------Tempo para inserção das Arestas de lista adjacencias----------------------


  n_insercao = 99;
  laco = 0;
  limite = 20; 
  comeco = 10;

  tempo = clock();

  while(laco < n_insercao){
    for(int i = comeco; i< limite; i++){ 
      numero_aleatorio = rand() % 4;  // 0 até 3
      for(int j = 0; j< numero_aleatorio;j++){
        numero_aleatorio2 = (rand() % n_vertices_2); // 0 até 999
        ConstruirArestaMatrix_2(grafo_matriz_2,i,numero_aleatorio2);
      }
    }
    limite += 10; 
    comeco += 10; 
    laco++;
  }

  tempo = clock() - tempo;

  printf("\nTempo para inserção das arestas da tabela de adjacencias: %fs\n",((double)tempo)/CLOCKS_PER_SEC);
  printf("Tempo médio para inserção das arestas da tabela de adjacencias: %fs\n\n",(((double)tempo)/CLOCKS_PER_SEC)/n_insercao);

 
  return 0;
  
}