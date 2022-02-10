#include "graph.h"
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <queue>

std::vector<Arc> Graph::GetArce()
{
    return arce;
}

std::vector<Node> Graph::GetNoduri()
{
    return noduri;
}
void Graph::PBF(int begin,std::vector<Node> out,std::vector<Node> &vect)
{
    std::queue<int> v;
    v.push(begin);
    std::vector<int> p;
    std::vector<int> u,w,l;
    std::vector<std::vector<int>> ad;
    std::vector<int> row;
    for(int i=0;i<getNumberofNodes();i++)
   {
      for(int indice=0;indice<arce.size();indice++)
    {
        if(arce[indice].getFirstPoint().getNumber()==i)
        {
            row.push_back(arce[indice].getSecondPoint().getNumber());
        }
    }
      ad.push_back(row);
      row.clear();
    }
    for(auto ind:noduri)
       {
        if(ind.getNumber()!=begin)
        {
            u.push_back(ind.getNumber());
        }
        p.push_back(-1);
    }
    for(auto ind1:noduri)
       {
        if(ind1.getNumber()!=begin)
            l.push_back(1000);
        else
            l.push_back(0);
       }

    while(!v.empty())
    {
        int x=v.front();
        for(int index=0;index<ad[x].size();index++)
        {
            int y=ad[x][index];
            if(std::find(u.begin(),u.end(),y)!=u.end())
            {
                u.erase(std::find(u.begin(),u.end(),y));
                v.push(y);
                p[y]=x;
                l[y]=l[x]+1;
            }

        }
        v.pop();
        w.push_back(x);
    }
    int s;
    for(auto& nod: out)
        {
           s = nod.getNumber();
            nod.setColor("red");
            int ok;
            ok=0;
            while(ok==0)
            {
                s=p[s];
                for(auto nod2: noduri)
                {

                    if(s==nod2.getNumber())
                    {
                        std::cout<<"*";
                        nod2.setColor("green");
                    }
                }
                if(s==begin)
                {
                    ok=1;
                    nod.setColor("cyan");
                }
            }
        }
vect=noduri;
}

void Graph::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graph::AddArc(Arc n)
{
    for(auto index:arce)
    {
        if(index.getFirstPoint().getNumber()==n.getFirstPoint().getNumber()&&index.getSecondPoint().getNumber()==n.getSecondPoint().getNumber())
        {
            return;
           }
    }
    arce.push_back(n);
}
void Graph::readMatrix(QFile& f,QVector<QVector<int>>&matrix)
{
    QString matrixStrSize;
    QTextStream in(&f);
    in >> matrixStrSize;
    int matSize = matrixStrSize.toInt();
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(!line.isEmpty()){
            QStringList numsStr = line.split(" ");
            QVector<int> temp;
            for(int i(0); i < matSize; ++i){
                temp.push_back(numsStr[i].toInt());
            }
            matrix.push_back(temp);
        }
    }
}

/*void Graph::ListaAdiacenta()
{
        listaAdiacenta.reserve(noduri.size());
        for(int i=0;i<noduri.size();i++)
            lista[i].reserve(noduri.size());
        for(auto& arc: arce)
        {
            int i,j;
            i=arc.getFirstPoint().getNumber();
            j=arc.getSecondPoint().getNumber();
            lista[i].push_back(j);
        }

}
*/


Node Graph::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graph::getNumberofNodes()
{
    return noduri.size();
}

void Graph::GenerareMatriceAdiacenta()
{

}

void Graph::GenerareListaAdiacenta()
{
    listaAdiacenta=GetArce();

}
