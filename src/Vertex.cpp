#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "../include/Vertex.hpp"

Vertex::Vertex(std::vector<std::vector<int>> mtx, std::string file, int n, int p)
{
}

Vertex::Vertex()
{
}

Vertex::~Vertex()
{
}

// =================================================================================== GETS ===================================================================================

int Vertex::getVertices()
{
    return n_vertices;
}

int Vertex::getMaxRoutes()
{
    return max_routes;
}

int Vertex::getSolution()
{
    return solution;
}

std::vector<std::vector<int>> Vertex::getMatrix()
{
    return matrix;
}

std::vector<int> Vertex::getVerIndex()
{
    return verIndex;
}

// =================================================================================== SETS ===================================================================================

void Vertex::setVertices(int num)
{
    n_vertices = num;
}

void Vertex::setMaxRoutes(int max)
{
    max_routes = max;
}

void Vertex::setSolution(int sol)
{
    solution = sol;
}

// =================================================================================== METHODS ===================================================================================

int Vertex::fileExtract(FILE *file)
{
    char line[100];
    fgets(line, 100, file);

    std::stringstream ss;
    std::string temp;

    ss << (std::string)line;
    int found;
    while (!ss.eof())
    {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found)
        {

            // std::cout << found << " ";

            /* To save from space at the end of string */
            temp = "";
        }
    }
    return found;
}

void Vertex::entryRead(std::string file)
{
    FILE *arquivo;

    arquivo = fopen(file.c_str(), "r");

    n_vertices = fileExtract(arquivo);
    max_routes = fileExtract(arquivo);
    fileExtract(arquivo);
    // printf("n %d m %d\n", n_vertices, max_routes);
    //Parte a solucionar: Chamada da funcao extrairInteiro para pular a linha do fgets
    for (int i = 0; i < n_vertices; i++)
    {

        char line[10000];
        fgets(line, 10000, arquivo);

        std::vector<int> aux;
        std::stringstream line_aux;
        std::string temp;

        line_aux << (std::string)line;

        for (int j = 0; j < n_vertices; j++)
        { // le palavra por palavra da linha aux, e as converte para inteiro

            line_aux >> temp;

            aux.push_back(std::stoi(temp));
        }
        matrix.push_back(aux);
        // graph.push_back(aux);
    }

    // for (int i = 0; i < matrix.size(); i++)
    // {

    //     for (int j = 0; j < matrix[i].size(); j++)
    //     {

    //         std::cout << matrix[i][j] << std::endl;
    //     }
    // }

    fclose(arquivo);
}

void Vertex::nearestNeighbor(std::vector<std::vector<int>> mtx, int n, int p)
{
    std::vector<std::vector<int>> graph_visited;
    std::vector<int> solution_indice;
    std::vector<int> solution_value;

    int sol_aux = 0;

    // entrada(graph, "instances/n52p11.txt", num_vertices, max_rout);

    for (int i = 0; i < n; i++)
    { // inicializa todos os indices do array graph_visited como 0

        std::vector<int> aux_graph_visited;

        for (int j = 0; j < n; j++)
        {
            aux_graph_visited.push_back(0);
        }
        graph_visited.push_back(aux_graph_visited);
    }

    for (int i = 0; i < graph_visited.size(); i++)
    {
        for (int j = 0; j < graph_visited.size(); j++)
        {
            if (i == j)
            {
                graph_visited[i][j] = 1;
            }
        }
    }

    int vertice_atual = 0, vertice_inicial = 0;
    for (int k = 0; k < n; k++)
    {
        graph_visited[k][vertice_inicial] = 1;
    }

    for (int i = 1; i < n;)
    {
        solution_indice.push_back(vertice_inicial); // comeca colocando o vertice inical na solucao

        for (int j = 0; j < p; j++)
        { // tem o teto de linha horizontais analisadas pelo valor P
            int min_value = 99999, min_indice;

            for (int k = 0; k < n; k++)
            {

                if (mtx[vertice_atual][k] < min_value && graph_visited[vertice_atual][k] == 0)
                { // compara cada indice da linha(horizontal), encontrando o minimo dessa linha
                    // se o indice não foi visitado ainda, armazena o valor e o indice do "minimo local"
                    min_value = mtx[vertice_atual][k];
                    min_indice = k;
                }
                if (k == (n - 1) && i < n)
                { // Na ultima interacao, adiciona ao vector da solucao o valor e/ou indice do minimo da linha(horizontal), "minimo local"

                    solution_indice.push_back(min_indice);
                    solution_value.push_back(min_value);
                    vertice_atual = min_indice;
                    i++; //incrementa o for mais a fora somente quando uma solucao e achada
                    for (int l = 0; l < n; l++)
                    {                                     // Marca a linha vertical do indice encontrado como minimo local
                        graph_visited[l][min_indice] = 1; // para que esse indice nao entre novamente na solucao
                    }
                }
            }
        }
        solution_indice.push_back(vertice_inicial);
        solution_value.push_back(mtx[vertice_atual][vertice_inicial]); // fecha o ciclo e recomeca colocando o vertice atual como o inicial novamente
        vertice_atual = vertice_inicial;
    }

    // printf("indice da solucao (rotas):");
    for (int i = 0; i < solution_indice.size(); i++)
    {
        verIndex.push_back(solution_indice[i]);
        // printf("- %d ", solution_indice[i]);
    }

    // puts("");
    // printf("valores da solucao:");
    for (int i = 0; i < solution_value.size(); i++)
    {
        sol_aux = sol_aux + solution_value[i];
        // printf("- %d ", solution_value[i]);
    }

    setSolution(sol_aux);
    // puts("");

    FILE *resposta;

    resposta = fopen("dump.txt", "w");

    for( int i = 0 ; i < solution_indice.size() ; i++)
    {
        if (solution_indice[i] == 0 && i >= 1 && solution_indice[i+1] == 0)
        {
            fprintf(resposta, "%d; ", solution_indice[i]);
        }else{
            fprintf(resposta, "%d, ", solution_indice[i]);
        }
    }
}

int Vertex::moveSwap(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index)
{
    int new_sol;
    int aux;

    for (int i = 1; i < index.size() - 1; i++)
    {
        for (int j = i + 1; j < index.size() - 1; j++)
        {
            aux = sol - mtx[index[i - 1]][index[i]] - mtx[index[i]][index[j]] - mtx[index[j]][index[j + 1]] + mtx[index[i - 1]][index[j]] + mtx[index[j]][index[i]] + mtx[index[i]][index[j+1]];
        }

        if(aux < sol)
        {
            new_sol = aux;
        }
    }
    return new_sol;
}

int Vertex::moveOpt(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index)
{
    std::vector<int> apt_two;
    int opt_value = 0;
    int aux;

    for (int i = 0; i < index.size(); i++)
    {
        apt_two.push_back(index[i]);
    }

    for (int i = 1; i < apt_two.size() - 1; i++)
    {
        for (int j = 3; j < apt_two.size() - 1; j++)
        {
            aux = sol - mtx[apt_two[i - 1]][apt_two[i]] - mtx[apt_two[j]][apt_two[j + 1]] + mtx[apt_two[i - 1]][apt_two[j]] + mtx[apt_two[i]][apt_two[j + 1]];
        }
        if(aux < sol)
        {
            opt_value = aux;
        }
    }

    // i = 1
    // j = i + 2 = 3
    // nova_sol = sol - matrix[index[i-1]][index[i]] - matrix[index[j]][index[j+1]] + matrix[index[i-1]][index[j]] +matrix[index[i]][index[j+1]];

    // printf("value apt = %d , final value = %d \n",apt_value,final_value);

    return opt_value;
}

int Vertex::moveSelect(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index)
{
    int sol_select;
    int aux;

    for(int i = 1; i < index.size() - 1; i++)
    {
        for(int j = i + 1; j < index.size() - 1; j++)
        {
            aux = sol - matrix[index[i - 1]][index[i]] - matrix[index[i]][index[j]] - matrix[index[j]][index[j + 1]] + matrix[index[i - 1]][index[j]] + matrix[index[j]][index[i]] + matrix[index[i]][index[j + 1]];
        }
        if(aux < sol)
        {
            sol_select = aux;
        }
    }

    return sol_select;
}

int Vertex::vnd(int sol, int moves, std::vector<std::vector<int>> mtx, std::vector<int> index)
{
    int final_sol = sol;
    int variable = 1;

    // while(variable < moves)
    // {
    //     if(final_sol >= sol)
    //     {
    //         switch (variable)
    //         {
    //         case 1:
    //             final_sol = moveSwap(sol, mtx, index);
    //             break;
    //         case 2:
    //             final_sol = moveOpt(sol, mtx, index);
    //             break;
    //         case 3:
    //             final_sol = moveSelect(sol, mtx, index);
    //             break;
    //         }
    //         variable++;
    //     }
    // }

    for(variable; variable < moves; variable++)
    {
        if(final_sol >= sol)
        {
            switch (variable)
            {
            case 1:
                final_sol = moveSwap(sol, mtx, index);
                break;
            case 2:
                final_sol = moveOpt(sol, mtx, index);
                break;
            case 3:
                final_sol = moveSelect(sol, mtx, index);
                break;
            }
        }
    }

    return final_sol;
}