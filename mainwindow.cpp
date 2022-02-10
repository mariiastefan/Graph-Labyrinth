#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graph.h"
#include <iostream>
#include "arc.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <algorithm>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <QVector>
#include <QString>
#include<fstream>
#include <vector>
#include <QDebug>
#include <QTimer>
#include <random>
#include <queue>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    buton=false;
    bfs=false;
   lab_init=false;
   drum=false;
    ui->setupUi(this);


}

void MainWindow::paintEvent(QPaintEvent *event)
{
QPainter painter(this);

    if(buton==true)
  {
std::vector<Node> noduri=g.GetNoduri();
    for(int index=0;index<noduri.size();index++)
    {
        if(noduri[index].getColor()=="cyan")
        {
            painter.setBrush(Qt::cyan);
            painter.setPen(QPen(Qt::black));
        }

            if(noduri[index].getColor()=="red")
            {
                painter.setBrush(Qt::red);
                painter.setPen(QPen(Qt::black));
            }
        if(noduri[index].getColor()=="white")
        {
            painter.setBrush(Qt::white);
            painter.setPen(QPen(Qt::black));
        }
        //painter.setBrush(Qt::magenta);
        //painter.setPen(QPen(Qt::black));
        QRect cerc(noduri[index].getPoint().x()-10,noduri[index].getPoint().y()-10,20,20);
        painter.drawEllipse(cerc);
        painter.drawText(cerc,Qt::AlignCenter,QString::number(index));

    }
   for(auto& nod1: noduri)
            {
                for(auto& nod2: noduri)
                {
                    if(nod1.getNumber()!=nod2.getNumber())
                    {
                        if(nod1.getPoint().y()==nod2.getPoint().y()+50 && nod1.getPoint().x()==nod2.getPoint().x())
                        {
                            g.AddArc(Arc(nod1,nod2));
                            g.AddArc(Arc(nod2,nod1));
                            int x1 = nod1.getPoint().x();
                                                    int y1 = nod1.getPoint().y();
                                                    int x2 = nod2.getPoint().x();
                                                    int y2 = nod2.getPoint().y();
                                                    QPoint x(x1, y1);
                                                    QPoint y(x2, y2);
                                                    painter.drawLine(QLine(x, y));
                        }
                        if(nod1.getPoint().x()==nod2.getPoint().x()+50 && nod1.getPoint().y()==nod2.getPoint().y())
                        {
                            g.AddArc(Arc(nod1,nod2));
                            g.AddArc(Arc(nod2,nod1));
                            painter.setPen(QPen(Qt::black));
                        int x1 = nod1.getPoint().x();
                        int y1 = nod1.getPoint().y();
                        int x2 = nod2.getPoint().x();
                        int y2 = nod2.getPoint().y();
                        QPoint x(x1, y1);
                        QPoint y(x2, y2);
                        painter.drawLine(QLine(x, y));
                        }
                    }
                }
    }
}

    if(lab_init==true)
    {
        int y=50;
        for(int ind1=0;ind1<g.matrix.size();ind1++)
        {
            int x=580;
            for(int ind2=0;ind2<g.matrix[ind1].size();ind2++)
            {
                if(g.matrix[ind1][ind2]==-1)
                {
                   painter.setPen(QPen(Qt::black));
                   painter.setBrush(Qt::black);
                    QRect rectangle(x,y,25,25);
                   painter.drawRect(rectangle);
                }
                if(g.matrix[ind1][ind2]==1)
                {
                    painter.setPen(QPen(Qt::black));
                    painter.setBrush(Qt::white);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
                if(g.matrix[ind1][ind2]==2)
                {
                    painter.setPen(QPen(Qt::red));
                    painter.setBrush(Qt::red);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
                else
                if(g.matrix[ind1][ind2]==3)
                {
                    painter.setPen(QPen(Qt::darkCyan));
                    painter.setBrush(Qt::darkCyan);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
               x+=25;
            }
            y+=25;
        }
        update();

        }

    if(bfs==true && buton==true)
    {
        std::queue<int> v;
        v.push(begin);
        std::vector<int> p;
        std::vector<int> u,w,l;
        std::vector<Node> noduri,noutate;
        std::vector<std::vector<int>> ad;
        noduri=g.GetNoduri();
        std::vector<Arc> arce;
        arce=g.GetArce();
        std::vector<int> row;
        for(int i=0;i<g.getNumberofNodes();i++)
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
        for(auto nod: out)
          {
              s = nod.getNumber();
              int ok;
              ok=0;
              while(ok==0)
              {
                  s=p[s];
                  for(auto& nod2: noduri)
                  {
                      if(s==nod2.getNumber())
                      {
                          for(int i=0;i<g.matr_noduri.size();i++)
                               for(int j=0;j<g.matr_noduri.size();j++)
                               {
                                   if(g.matr_noduri[i][j]==nod2.getNumber())
                                       g.matrix[i][j]=5;
                               }
                          nod2.setColor("green");
                          noutate.push_back(nod2);
                          break;
                      }
                  }
                  if(s==begin)
                  {
                      ok=1;
                      for(auto& nod2: noduri)
                      {
                          if(s==nod2.getNumber())
                          {
                              nod2.setColor("cyan");
                              noutate.push_back(nod2);
                              break;
                          }
                      }
                  }
              }
          }

          for(auto nod: out)
          {
              for(auto nod2: noduri)
              {
                  if(nod.getNumber()==nod2.getNumber())
                  {
                      for(int i=0;i<g.matr_noduri.size();i++)
                           {for(int j=0;j<g.matr_noduri.size();j++)
                           {
                               if(g.matr_noduri[i][j]==nod2.getNumber())
                                   g.matrix[i][j]=2;
                          }
                      }
                      nod2.setColor("red");
                      noutate.push_back(nod2);
                  }
              }
          }

    for(auto ind:noutate)
    {
        if(ind.getColor()=="cyan")
        {
            painter.setBrush(Qt::cyan);
            painter.setPen(QPen(Qt::black));
        }
            if(ind.getColor()=="red")
            {
                painter.setBrush(Qt::red);
                painter.setPen(QPen(Qt::black));
            }
        if(ind.getColor()=="white")
        {
            painter.setBrush(Qt::white);
            painter.setPen(QPen(Qt::black));
        }
            if(ind.getColor()=="green")
            {
                    painter.setBrush(Qt::green);
                    painter.setPen(QPen(Qt::black));
            }
        QRect cerc(ind.getPoint().x()-10,ind.getPoint().y()-10,20,20);
        painter.drawEllipse(cerc);
        painter.drawText(cerc,Qt::AlignCenter,QString::number(ind.getNumber()));

    }

        }
    if(drum==true)
    {

        int y=50;
        for(int ind1=0;ind1<g.matrix.size();ind1++)
        {
            int x=580;
            for(int ind2=0;ind2<g.matrix[ind1].size();ind2++)
            {
                if(g.matrix[ind1][ind2]==-1)
                {
                   painter.setPen(QPen(Qt::black));
                   painter.setBrush(Qt::black);
                    QRect rectangle(x,y,25,25);
                   painter.drawRect(rectangle);
                }
                if(g.matrix[ind1][ind2]==1)
                {
                    painter.setPen(QPen(Qt::black));
                    painter.setBrush(Qt::white);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
                if(g.matrix[ind1][ind2]==2)
                {
                    painter.setPen(QPen(Qt::red));
                    painter.setBrush(Qt::red);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
                else
                if(g.matrix[ind1][ind2]==3)
                {
                    painter.setPen(QPen(Qt::darkCyan));
                    painter.setBrush(Qt::darkCyan);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
                if(g.matrix[ind1][ind2]==5)
                {
                    painter.setPen(QPen(Qt::green));
                    painter.setBrush(Qt::green);
                    QRect rectangle(x,y,25,25);
                    painter.drawRect(rectangle);
                }
               x+=25;
            }
            y+=25;
        }
     //update();

        }


}


/*void MainWindow::PBF()
{
    std::queue<int> v;
    v.push(begin);
    std::vector<int> p;
    std::vector<int> u,w,l;
    std::vector<Node> noduri;
    std::vector<std::vector<int>> ad;
    noduri=g.GetNoduri();
    std::vector<Arc> arce;
    arce=g.GetArce();
    std::vector<int> row;
    for(int i=0;i<g.getNumberofNodes();i++)
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

}
*/

void MainWindow::on_pushButton_clicked()
{
    buton=true;
    QFile file("D:/AG/tema3/matrix.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    g.readMatrix(file,g.matrix);
    for(int index=0;index<6;index++)
           {
            for(int index2=0;index2<6;index2++)
            {
                std::cout<<g.matrix[index][index2]<<" ";
            }
            std::cout<<std::endl;
        }
    int x=100,y=100;
    g.matr_noduri=g.matrix;
    for (int ind1 = 0; ind1 < g.matrix.size(); ind1++)
            {
                  x=100;
                for (int ind2 = 0; ind2 < g.matrix[ind1].size(); ind2++)
                {
                    if(g.matrix[ind1][ind2]>0)
                   {
                    QPoint point(x,y);
                    Node nod(point);
                    if(g.matrix[ind1][ind2]==3)
                         nod.setColor("cyan");
                    if(g.matrix[ind1][ind2]==2)
                          nod.setColor("red");
                     if(g.matrix[ind1][ind2]==1)
                          nod.setColor("white");
                       g.AddNod(nod);
                       g.matr_noduri[ind1][ind2]=g.GetLastNode().getNumber();

                    if(g.matrix[ind1][ind2]==3)
                    {
                        begin=g.matr_noduri[ind1][ind2];
                    }
                    if(g.matrix[ind1][ind2]==2)
                    {
                        out.push_back(g.GetLastNode());

                    }
                    }
                      x+=50;
                }
                y+=50;
    }
     update();
}


void MainWindow::on_pushButton_2_clicked()
{
    lab_init=true;
    update();
}


void MainWindow::on_pushButton_3_clicked()
{
    bfs=true;
      update();
}
MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    drum=true;
    update();
}

