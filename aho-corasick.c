#include <stdio.h>
#include <stdlib.h>

int** g;
int **occ;
typedef struct listState{
    int state;
    struct test *nxt;
} listState;

int** goTo(char** patterns, int np)
{
    //Para cada estado uma linha será inserida na matriz
    g = (int**) malloc(sizeof(int*));
    g[0] = calloc(sizeof(int), 256);

    printf("NP %d \n", np);

    //Para cada estado, uma nova linha será inserida na matriz
    occ = (int**) malloc(sizeof(int*));
    occ[0] = (int*) malloc(sizeof(int));
    occ[0][0] = 1;

    int next = 0;
    int i, current, j;
    char *pat;
    int m, a,b;
    for(i=0; np > i; i++)
    {
        pat = *(patterns + i);
        m = strlen(pat);
        current = 0;
        j = 0;

        while (j<m && (g[current][pat[j]]!=0))
        {
            current = g[current][pat[j]];
            j++;

        }
        while (j<m)
        {
            next++;
            g[current][pat[j]] = next;
            current = next;
            g = (int**) realloc(g, sizeof(int*)*(next+1));
            g[next] = calloc(sizeof(int), 256);
            occ = (int**) realloc(occ,sizeof(int*)*(next+1));
            occ[current] = (int*) malloc(sizeof(int));
            occ[current][0] = 1;
            j++;

        }
        occ[current] = (int*) malloc(sizeof(int)*2);
        occ[current][0] = 2;
        occ[current][1] = i;

    }
    return next;
}

int* fail(char **patterns, int nStates)
{
    listState *q = NULL;
    listState *lastQ = NULL;
    listState *auxQ = NULL;
    int *f = (int*) calloc(sizeof(int), nStates);
    int i, j;
    int current, next, brd;

    for(i=0; i <256; i++)
    {
        if(g[0][i]!=0)
        {
            if (q== NULL)
            {
                q = (listState*) malloc(sizeof(listState));
                q->nxt = NULL;
                q->state = g[0][i];
                lastQ = q;
            }
            else
            {
                lastQ->nxt = (listState*) malloc(sizeof(listState));
                lastQ = lastQ->nxt;
                lastQ->nxt = NULL;
                lastQ->state = g[0][i];
            }
            f[g[0][i]]= 0;
        }
    }
    while(q != NULL)
    {
        current = q->state;
        auxQ = q;
        q = q->nxt;
        free(auxQ);

        for(i=0; i<256;i++)
        {
            if(g[current][i] != 0)
            {
                next=g[current][i]; //next recebe o próximo estado determinado por g

                //Adiciona next á fila
                lastQ->nxt = (listState*) malloc(sizeof(listState));
                lastQ = lastQ->nxt;
                lastQ->nxt = NULL;
                lastQ->state = next;

                brd = f[current];

                while (g[brd][i] == 0)
                {
                    if(brd != f[brd])
                        brd = f[brd];
                    else
                        break;
                }
                f[next] = g[brd][i];
                occ[next][0] = occ[next][0]+occ[f[next]][0]-1;
                occ[next] = realloc(occ[next], sizeof(int)*(occ[next][0]));
                for(j = occ[f[next]][0]-1; j > 0; j--)
                {
                    occ[next][occ[next][0]+j] = occ[f[next]][j];
                }
            }
        }
    }

    return f;
}


int scan(char* text, char** patterns, int np, int *f)
{
    int n = strlen(text);
    int **o = (int**) calloc(sizeof(int), np);
    int teste = 0;
    int i, current;

    current = 0;
    for (i=0; i<n; i++)
    {
        while(g[current][text[i]] == 0)
        {
            if(current != f[current])
                current = f[current];
            else
                break;
        }
        current= g[current][text[i]];
        if(occ[current][0] > 1)
        {
            teste++;
        }
    }

    printf(" \n N:%d ", teste);
    return teste;
}


int main()
{
    printf("Hello world!\n");
    char **v = (char**) malloc (sizeof(char*)*5);
    int *f;
    int i = 0;
    int nStates;

    FILE *text = fopen("myfile.txt", "r");
    char *line = (char *) malloc(1024);

    for(i=0; i<5; i++)
    {
       v[i] = (char*) malloc (sizeof(char)*10);
    }



    strcpy(v[0], "louis");
    strcpy(v[1], "adabcada");
    strcpy(v[2], "ha");
    strcpy(v[3], "amor");
    strcpy(v[4], "Teste");


    nStates = goTo(v, 5);
    f = fail(v, nStates);

    while(fgets(line,1024,text)!= NULL)
        i = i + scan(line, v, 5, f);

    fclose(text);

    return 0;
}
