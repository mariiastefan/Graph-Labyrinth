#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include "arc.h"
#include <QFile>
#include <QMatrix>
class Graph
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    int **matriceAD;
    std::vector<std::vector<int>> matriceAdiacenta;
    std::vector<std::vector<int>> lista;
    std::vector<Arc>listaAdiacenta;
    std::vector<std::vector<int>> matr;
    int nr_linii;
    int nr_coloane;
public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();
    std::vector<Arc> GetArce();
    std::vector<Node> GetNoduri();
    bool Add(Node n);
    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    void AdListCreating();
    Node GetLastNode();
    int getNumberofNodes();
    QVector<QVector<int>>matrix;
    QVector<QVector<int>>matr_noduri;
    QVector<int> iesiri;
    void reading();
    void PBF(int begin,std::vector<Node> out,std::vector<Node> &vect);
    void readMatrix(QFile& f,QVector<QVector<int>>&matrix);
    void ListaAdiacenta();
  };


#endif // GRAPH_H
