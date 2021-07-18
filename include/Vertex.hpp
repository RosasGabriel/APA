#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

class Vertex{
private:
    int n_vertices;
    int max_routes;
    int solution;

    std::vector<std::vector<int>> matrix;
    std::vector<int> verIndex;
    
public:
    int getVertices();
    int getMaxRoutes();
    int getSolution();
    std::vector<std::vector<int>> getMatrix();
    std::vector<int> getVerIndex();

    void setVertices(int num);
    void setMaxRoutes(int max);
    void setSolution(int sol);

    int fileExtract(FILE* file);
    void entryRead(std::string file);

    void nearestNeighbor(std::vector<std::vector<int>> mtx, int n, int p);
    int moveSwap(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index);
    int moveOpt(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index);
    int moveSelect(int sol, std::vector<std::vector<int>> mtx, std::vector<int> index);

    int vnd(int sol, int moves, std::vector<std::vector<int>> mtx, std::vector<int> index);

    Vertex(std::vector<std::vector<int>> mtx, std::string file, int n, int p);
    Vertex();
    ~Vertex();
};

#endif