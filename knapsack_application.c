/*
* DESCRI��O DO PROBLEMA | PROBLEM DESCRIPTION
*
* PORTUGU�S:
* Um pai deseja levar o filho ao parque de divers�es e divert�-lo o m�ximo poss�vel.
* O parque possui N brinquedos, numerados de 0 a N-1, cada um com um custo diferente
* de C[i] cr�ditos por corrida. O atencioso pai percebeu que o seu filho possui l�
* suas prefer�ncias e atribuiu a cada brinquedo um �ndice inicial de divers�o S[i]
* para i=0,...,N-1. A crian�a pode andar mais de uma vez em cada brinquedo, mas o pai
* tamb�m percebeu que a empolga��o vai diminuindo rapidamente a cada corrida.
* Ele associou a cada brinquedo um fator de aborrecimento B[i], e estimou que a divers�o
* obtida na k-�sima corrida no brinquedo i decai para F(i,k)=S[i]-(k-1)�*B[i],
* para k=1,2,3,..., sendo a divers�o considerada nula assim que esse valor de F(i,k)
* torna-se <=0. Sabendo que o pai s� disp�e de um cart�o com uma quantidade limitada
* de cr�ditos K, sua tarefa � ajud�-lo a escolher os brinquedos que resultem na maior divers�o poss�vel.
*
*
* ENGLISH:
* A father wants to take his son to the park and make him have as much fun as possible.
* The park has N attractions, numbered from 0 to N - 1, each one with a different cost of C[i] credits per round.
* The kind father knows his child preferences and assigned an initial fun index S[i](i = 0, ..., N - 1) for each
* attraction. The kid can play on each of them more than once, but the father realized the fun quickly shrinks at each
* round played so he associated a boredom factor B[i] and estimated that the fun had in the kth round on the
* attraction i decays for F(i, k) = S[i] - ((k - 1)^2 * B[i]), knowing that k = 1, 2, 3, ..., and the fun ends
* when the value of F(i, k) is <= 0. Given that the father has a limited card with credit K, your job is to help him
* choose the attractions which will maximize his son's fun at the park.
*/

/*
Input order:
N - Number of attractions
N lines reading the values of Fun, Boredom and Credit(cost) of each attraction
V - Number of visits to the park
V lines reading the available credits at each visit

Output:
Max. fun at each visit.

Test case:
Input:
5
235 47 6038
387 96 19923
554 22 16178
771 55 23611
127 5 3540
10
21673
1531
13059
24493
4154
3078
22124
23776
5927
13801

Output:
0: 681
1: 0
2: 423
3: 803
4: 127
5: 0
6: 681
7: 803
8: 127
9: 484
*/

#include "stdio.h"
#include "stdlib.h"

int zero_one_knapsack(int* values, int* weights, int* boredom, int capacity, int items_n);

int* rounds_played;

int main()
{
    int i;
    int attractions_n;
    int visits_n;
    int* fun_attr;
    int* boredom_attr;
    int* cost_attr;

    scanf("%d", &attractions_n);

    fun_attr = (int*) malloc(attractions_n * sizeof(int));
    boredom_attr = (int*) malloc(attractions_n * sizeof(int));
    cost_attr = (int*) malloc(attractions_n * sizeof(int));
    rounds_played = (int*) malloc(attractions_n * sizeof(int));

    for(i = 0; i < attractions_n; ++i)
    {
        rounds_played[i] = 1;
    }

    for(i = 0; i < attractions_n; ++i)
        scanf("%d %d %d", &fun_attr[i], &boredom_attr[i], &cost_attr[i]);

    scanf("%d", &visits_n);

    int credits;
    /*credits = (int*) malloc(visits_n * sizeof(int));*/

    for (i = 0; i < visits_n; ++i)
    {
        scanf("%d", &credits/*[i]*/);
        printf("%d: %d\n", i, zero_one_knapsack(fun_attr, cost_attr, boredom_attr, credits/*[i]*/, attractions_n));
    }
}

int fun_decay(int attraction, int round, int* fun_attr, int* boredom_attr)
{
    return (fun_attr[attraction] - (((round - 2)^2) * boredom_attr[attraction]));
}

int zero_one_knapsack(int* values, int* weights, int* boredom, int capacity, int items_n)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int** matrix;

    matrix = (int**) malloc((items_n + 1) * sizeof(int*));
    for(i = 0; i <= items_n; ++i)
        matrix[i] = (int*) calloc((capacity + 1), sizeof(int));

    for(i = 1; i <= items_n; ++i)
    {
        for(j = 1; j <= capacity; ++j)
        {
            if((weights[i - 1] <= j) && ((values[i - 1] + matrix[i - 1][j - weights[i - 1]]) > matrix[i - 1][j]))
                matrix[i][j] = values[i - 1] + matrix[i - 1][j - weights[i - 1]];
            else
                matrix[i][j] = matrix[i - 1][j];
        }
    }
    /*
    Pseudo code to find the elements which are in the bag:
    https://stackoverflow.com/questions/7489398/how-to-find-which-elements-are-in-the-bag-using-knapsack-algorithm-and-not-onl
        
    line <- W
    i <- n
    while (i> 0):
      if dp[line][i] - dp[line - weight(i)][i-1] == value(i):
          the element 'i' is in the knapsack
          i <- i-1 //only in 0-1 knapsack
          line <- line - weight(i)
      else: 
          i <- i-1 
    */

    int* used_items = NULL;
    int item_counter = 0;
    used_items = (int*) malloc(items_n * sizeof(int));

    int row = capacity;
    int column = items_n;
    while(column > 0)
    {
        if(matrix[row][column] - matrix[row - weights[i]][column - 1] == values[i])
        {
            used_items[item_counter] = column - 1;
            ++item_counter;
            --column;
            row -= weights[column];
        }
        else
            --column;
    }

    int x = 0;
    for(k = 0; k < item_counter; ++k)
    {
         x = fun_decay(k, rounds_played[k], values, boredom);
        if(x < 0)
            x = 0;
        values[k] = x;
        rounds_played[k]++; 
    }

    return matrix[i - 1][j - 1];
}
