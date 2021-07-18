/*
    Grupo:
    NATHAN RODRIGUES TAVARES DE LIMA - 20180017834
    WESLLEY DEZIDERIO DA SILVA - 20180017244
    GABRIEL ASSIS GUEDES ROSAS - 20180029497
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <math.h>
#include <ctime>

#include "../include/Vertex.hpp"

#define N_MOVES 3

int main(void)
{
    clock_t t;
    clock_t v;
    t = clock();
    v = clock();

    int n, p, sol;
    std::vector<std::vector<int>> mtx;
    std::vector<int> index;

    // int sol_swap, sol_opt, sol_ins;
    int moves = N_MOVES;
    int sol_final;

    Vertex matrixRoute;

    // matrixRoute.entryRead("../instances/n10p4.txt");
    // matrixRoute.entryRead("../instances/n15p5.txt");
    // matrixRoute.entryRead("../instances/n29p7A.txt");
    // matrixRoute.entryRead("../instances/n29p8B.txt");
    // matrixRoute.entryRead("../instances/n40p11.txt");
    // matrixRoute.entryRead("../instances/n52p11.txt");

    // matrixRoute.entryRead("../instances/cup1.txt");
    // matrixRoute.entryRead("../instances/cup2.txt");
    // matrixRoute.entryRead("../instances/cup3.txt");

    n = matrixRoute.getVertices();
    p = matrixRoute.getMaxRoutes();
    mtx = matrixRoute.getMatrix();

    matrixRoute.nearestNeighbor(mtx, n, p);
    index = matrixRoute.getVerIndex();

    sol = matrixRoute.getSolution();
    std::cout << "sol = " << sol << std::endl;

    v = clock() - v;
    std::cout << "Time elapsed for base result: " << (((float)v) / CLOCKS_PER_SEC) << " seconds" << std::endl;

    // sol_swap = matrixRoute.moveSwap(sol, mtx, index);
    // std::cout << "SWAP = " << sol_swap << std::endl;

    // sol_opt = matrixRoute.moveOpt(sol, mtx, index);
    // std::cout << "2-OPT = " << sol_opt << std::endl;

    // sol_ins = matrixRoute.moveSelect(sol, mtx, index);
    // std::cout << "INS_select = " << sol_ins << std::endl;

    sol_final = matrixRoute.vnd(sol, moves, mtx, index);
    std::cout << "Final solution = " << sol_final << std::endl;

    t = clock() - t;
    std::cout << "Time elapsed for VND: " << (((float)t)/CLOCKS_PER_SEC) << " seconds" << std::endl;

    // for (int i = 0; i < index.size(); i++)
    // {
    //     std::cout << index[i] << " -> ";
    // }
    // printf("\n");

    // printf("n %d m %d\n", n, p);

    //imprimir a matrix
    // for (int i = 0; i < mtx.size(); i++)
    // {

    //     for (int j = 0; j < mtx[i].size(); j++)
    //     {

    //         std::cout << mtx[i][j] << std::endl;
    //     }
    // }

    return 0;
}