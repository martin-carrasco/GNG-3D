#ifndef GRAPH_NULL_GNG_ALGO_H
#define GRAPH_NULL_GNG_ALGO_H

#include "../graph.h"
#include <cmath>

template <class Trait>
class GNGAlgorithm {
protected:
    typedef typename Graph<Trait>::NodeContent NodeContent;
    typedef ::Edge<Graph<Trait>>* EdgePtr;
    typedef ::Node<Graph<Trait>>* NodePtr;

    double mean_error_sum = 0; //Sum of mean error until reset
    int mean_error_check = 5000; // Mean error iteration check

    double K = 3; //Medida de utilidad para eliminar un nodo
    int SIGMA = 300; //Iteraciones hasta insertar
    double ALFA = 0.5; //Decremento de error por insercion
    double BETA =0.0005; //Decremento del error por ejecucion
    double E_W = 0.05; //Movimiento del el nodo ganador hacia el input
    double E_N = 0.0006; //Movimiento de los vecinos del nodo ganador hacia el input
    double MAX_AGE = 100; //Maximo de age
    int MAX_NODES = 100; //Max nodes


    unsigned int SCREEN_HEIGHT;
    unsigned int SCREEN_WIDTH;

    unsigned int iteracion = 1;

    Graph<Trait> base_graph; 
   

    //Finds the neighbor with the max error of said node
    auto findMaxErrorLink(NodePtr node);

    void logMeanError(double sum);

public:
    GNGAlgorithm(unsigned int screen_width, unsigned int screen_height) : SCREEN_HEIGHT(screen_height), SCREEN_WIDTH(screen_width) {}
    bool isConnected(NodePtr node1, NodePtr node2);
    double getDistance(NodePtr node, pair<int, int> input);
    int getMaxAge(); 
    
    //Finds the node with the max error
    auto findMaxError(Graph<Trait> &graph);
    unsigned int get_iteracion(){
        return this->iteracion;
    }
    auto get_graph(){
        return base_graph;
    }
    virtual void exec(pair<int, int> input); 
    virtual void init();
};

template <class Trait>
class UGNGAlgorithm : public GNGAlgorithm<Trait> { 
    typedef typename Graph<Trait>::NodeContent NodeContent;
    typedef ::Edge<Graph<Trait>>* EdgePtr;
    typedef ::Node<Graph<Trait>>* NodePtr;


    double K = 200; //Medida de utilidad para eliminar un nodo
    int SIGMA = 600; //Mean error (Medida de error maxima aceptable)
    double ALFA = 0.5;
    double BETA =0.0005; //Decremento del error por ejecucion
    double E_W = 0.09; //Movimiento del nodo de comparacion respecto al input
    double E_N = 0.006; //Movimiento del nodo input respecto al nodo de comparacion
    double MAX_AGE = 100; //Vida de los edges de los nodos con minimo error
    int MAX_NODES = 60; //TODO cambiar ???

    //Encuentra el nodo con la minima utilidad
	auto findMinUtility(Graph<Trait> &graph);

 public:
    UGNGAlgorithm(unsigned int screen_width, unsigned int screen_height) : GNGAlgorithm<Trait>(screen_height, screen_width){}
    virtual void init();
    virtual	void exec(pair<int, int> input);
};
#include "gng_algo.cpp"
#endif //GRAPH_NULL_GNG_H

