/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA3 
* Graph.c 
* Implementation for the DFS Graph ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

/*** Structs ***/

// private GraphObj type
typedef struct GraphObj{
   List* adj;
   int* color; //colors: WHITE, GRAY, BLACK
   int* parent;
   int* discover;
   int* finish;

   int order;
   int size;
} GraphObj;


/*** Constructor-Deconstructor Functions ***/

/**
 * Graph newGraph(int n)
 * Creates a new instance of the Graph ADT and returns it
 */
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));

   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1,sizeof(int));

   for(int i = 1; i < n+1; ++i){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }

   G->order = n;
   G->size = 0;

   return G;
}

/**
 * void freeGraph(Graph* pG)
 * Frees a Graph ADT from the heap
 */
void freeGraph(Graph* pG){
   Graph G = (*pG);
   for(int i = 1; i < G->order + 1; ++i){
      freeList(&(G->adj[i]));
   }
   free(G->adj);
   free(G->color);
   free(G->parent);
   free(G->discover);
   free(G->finish);

   G->adj = NULL;
   G->color = G->parent = G->discover = G->finish = NULL;

   free(G);
   G = NULL;
   return;
}

/*** Access Function **/

/**
 * int getOrder(Graph G)
 * Returns the order of the graph G
 * 
 * Pre: G != NULL
 */
int getOrder(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the order of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

/**
 * int getSize(Graph G)
 * Returns the size of the Graph T
 * 
 * Pre: G != NULL
 */
int getSize(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the order of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

/**
 * int getParent(Graph G, int u)
 * Returns the parent of vertex u in Graph G
 * 
 * Pre: G != NULL && u is between 1 and getOrder(G)
 */
int getParent(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the parent of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: parent of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->parent[u];
}

/**
 * int getDiscover(Graph G, int u)
 * Returns the discover time of Graph G at vertex u
 * 
 * Pre: G != NULL && u is between 1 and getOrder(G)
 */
int getDiscover(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the discover time of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: discover time of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->discover[u];
}

/**
 * int getFinish(Graph G, int u)
 * Returns the finish time of Graph G at vertex u
 * 
 * Pre: G != NULL && u is between 1 and getOrder(G)
 */
int getFinish(Graph G, int u){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Getting the finish time of a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: finish time of u needs to be between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   return G->finish[u];
}

/*** Manipulation Procedures ***/

/*
Private function
addArcHelper(Graph G, int u, int v)
Adds an arc to a graph without increasing its size
This is done so the function can be used in other functions as well
such as addEdge()

Insertion Sort algorithm was taken from Derfel's pa1 Lex.c file

Pre: None -> public functions that use this function should handle the preconditions
*/
void addArcHelper(Graph G, int u, int v){
   List curr_list = G->adj[u];

   int prev_len = length(curr_list);

   if(prev_len == 0){
      prepend(curr_list, v);
   } else {
      for(moveFront(curr_list); index(curr_list) >=0 && prev_len == length(curr_list); moveNext(curr_list)){
         if(v < get(curr_list)){ //we need to make sure we don't add the same vertex twice
            insertBefore(curr_list, v);
         }
      }

      int new_len = length(curr_list);
      if (new_len == prev_len && v > back(curr_list)){
         append(curr_list, v);
      }
   }
   return;
}

/**
 * addArc(Graph G, int u, int v)
 * Adds an arc to Graph G
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
void addArc(Graph G, int u, int v){
   if(G == NULL){
      printf("GRAPH ERROR: Adding an Arc to a NULL Graph\n");
      exit(EXIT_FAILURE);
   }

   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("GRAPH ERROR: addArc(): u or v is not between 1 and %d\n", getOrder(G));
      exit(EXIT_FAILURE);
   }
   

   if(contains(G->adj[u],v) == false){
      addArcHelper(G,u,v);
      G->size++;
   }
   return;
}

/**
 * addEdge(Graph G, int u, int v)
 * adds an Edge to graph G
 * 
 * Pre: G != NULL && u must be 1 <= u <= getOrder(G)
 */
void addEdge(Graph G, int u, int v){
   if(G==NULL){
      printf("GRAPH ERROR: Adding an Edge to a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("GRAPH ERROR: addEdge(): u or v is not between 1 and %d\n", getOrder(G));
      exit(EXIT_FAILURE);
   }

   addArcHelper(G,u,v);
   addArcHelper(G,v,u);
   G->size++;
   return;
}

/**
 * Private helper function
 * 
 * void Visit(Grapg G, List S, int x, int* time)
 * Vists the adjacent Vertices of x
 * This also updates Graph G
 * 
 * Pre: G != NULL && x is between 1 and getOrder(G)
 * 
 * NOTE: Pseudocode taken from Prof. Tantalo
 */
void Visit(Graph G, List S, int x, int* time){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Cannot Visit x when G is NULL\n");
      exit(EXIT_FAILURE);
   }
   if(x < 1 || x > getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: Cannot Visit x if x is not between 1 and getOrder(G)\n");
      exit(EXIT_FAILURE);
   }
   G->discover[x] = ++(*time);
   G->color[x] = GRAY;
   List adj_x = G->adj[x];

   for(moveFront(adj_x); index(adj_x) >= 0; moveNext(adj_x)){
      int y = get(adj_x);
      if(G->color[y] == WHITE){
         G->parent[y] = x;
         Visit(G, S, y, time);
      }
   }
   G->color[x] = BLACK;
   G->finish[x] = ++(*time);
   prepend(S, x); // this should already set the list into decreasing order 
   //TODO: change prepend if needed
   return;
}

/**
 * void DFS(Graph G, List S)
 * Runs the DFS algorithm on Graph G and
 * manipulates List S with decreasing starting times
 * 
 * Pre: G !- NULL && length(S) != getOrder(G)
 */
void DFS(Graph G, List S){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Cannot Visit x when G is NULL\n");
      exit(EXIT_FAILURE);
   }
   if(length(S) != getOrder(G)){
      fprintf(stderr, "GRAPH ERROR: Cannot run DFS if List S != getOrder(G)\n");
      exit(EXIT_FAILURE);
   }

   List cpy_s = copyList(S); //Let's use a copy as a reference
   clear(S); //Clear S so we can update it in the DFS algorithm
   
   /*** INITALIZATION ***/
   for(moveFront(cpy_s); index(cpy_s) >= 0; moveNext(cpy_s)){
      int x = get(cpy_s);
      G->color[x] = WHITE;
      G->parent[x] = NIL;
   }

   int time = 0;

   /*** MAIN DFS LOOP ***/
   for(moveFront(cpy_s); index(cpy_s) >=0; moveNext(cpy_s)){
      int x = get(cpy_s);
      if(G->color[x] == WHITE){
         Visit(G, S, x, &time);
      }
   }

   freeList(&cpy_s);
   return;
}

/*** Other Functions ***/

/**
 * Graph transpose(Graph G)
 * Returns a transposed graph of G
 * 
 * Pre: G != NULL
 */
Graph transpose(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Can't transpose a NULL Graph\n");
      exit(EXIT_FAILURE);
   }

   Graph new_g = newGraph(getOrder(G));

   for(int i = 1; i < getOrder(new_g) + 1; ++i){
      List adj_x = G->adj[i];
      for(moveFront(adj_x); index(adj_x) >= 0; moveNext(adj_x)){
         addArc(new_g, get(adj_x), i);
      }
   }
   return new_g;
}

/**
 * Graph copyGraph(Graph G)
 * Returns a copy of Graph G
 * 
 * Pre: G != NULL
 */
Graph copyGraph(Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Can't copy a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   Graph new_g = newGraph(getOrder(G));

   for(int i = 1; i < getOrder(G) + 1; ++i){
      List adj_x = G->adj[i];
      for(moveFront(adj_x); index(adj_x) >= 0; moveNext(adj_x)){
         addArc(new_g, i, get(adj_x));
      }
   }
   return new_g;
}

/**
 * printGraph(FILE* out, Graph G)
 * Prints out the adjacency list of Graph G
 */
void printGraph(FILE* out, Graph G){
   if(G == NULL){
      fprintf(stderr, "GRAPH ERROR: Can't print a NULL Graph\n");
      exit(EXIT_FAILURE);
   }
   
   for(int i = 1; i < getOrder(G) + 1; ++i){
      fprintf(out, "%d: ",i);
      printList(out, G->adj[i]);
      fprintf(out,"\n");
   }
   return;
}