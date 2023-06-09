/********************************************************************************* 
* Derfel Terciano, dtercian 
* 2022 Spring CSE101 PA1 
* GraphTest.c 
* Testing Harness for the Graph ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

int main(void){
   int i, n=35;
   // List  C = newList(); // central vertices 
   // List  P = newList(); // peripheral vertices 
   // List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);
   printGraph(stdout, G);
   List L = newList();
   BFS(G,9);
   getPath(L,G,31);
   printf("Path of 9-31: ");
   printList(stdout,L);
   printf("\n\n");

   printf("Order: %d\n",getOrder(G));
   printf("Size: %d\n",getSize(G));
   printf("Parent of 31: %d\n",getParent(G,31));
   printf("Distance of 9-31: %d\n", getDist(G,31));

   freeList(&L);

   // makeNull(G);
   // printGraph(stdout, G);

   freeGraph(&G);

   return EXIT_SUCCESS;
}