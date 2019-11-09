#include "lineintersection.h"

#include <QApplication>
#include <bits/stdc++.h>

using namespace std;
vector< pair<pair<int,int> , pair<int,int>> >lineSet;
map<double,pair<double,pair<double,double>>> sortByX;
map<double,double> sortByY;
map<double,double> intersectionPointMap;
vector<pair<double,double>>intersectionPoint;
int n;


void intersectionPnt(double aa,double bb){
    pair<pair<int,int> , pair<int,int>> a = lineSet[int(aa)];
    pair<pair<int,int> , pair<int,int>> b = lineSet[int(bb)];
    double a1 = a.second.second - a.first.second;
    double b1 = a.first.first - a.second.first;
    double c1 = a1*(a.first.first) + b1*(a.first.second);

    double a2 = b.second.second - b.first.second;
    double b2 = b.first.first - b.second.first;
    double c2 = a2*(b.first.first)+ b2*(b.first.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant != 0)
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;

        if(x>= a.first.first && x<= a.second.first && x>= b.first.first && x<= b.second.first )
        {
            intersectionPoint.push_back({x,y});
        }
    }
}


void edges(double lineNo){
    for (double i = lineNo+1; i < n; ++i)
    {
        intersectionPnt(lineNo,i);
    }
}

void check(double aa,double bb){

    pair<pair<int,int> , pair<int,int>> a = lineSet[int(aa)];
    pair<pair<int,int> , pair<int,int>> b = lineSet[int(bb)];

    double a1 = a.second.second - a.first.second;
    double b1 = a.first.first - a.second.first;
    double c1 = a1*(a.first.first) + b1*(a.first.second);

    double a2 = b.second.second - b.first.second;
    double b2 = b.first.first - b.second.first;
    double c2 = a2*(b.first.first)+ b2*(b.first.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant != 0)
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;

        if(x>= a.first.first && x<= a.second.first && x>= b.first.first && x<= b.second.first )
        {
            intersectionPointMap[x] = y;
        }
    }
}




int main(int argc, char *argv[])
{

    cin >> n;
        double px1,py1,px2,py2;
        for (int i = 0; i < n; ++i)
        {
            cin >> px1 >> py1 >> px2 >> py2;
            if (px1 < px2)
            {
                lineSet.push_back({{px1,py1},{px2,py2}});
                sortByX[px1] = {0,{i,0}};
                sortByX[px2] = {1,{i,0}};
            }
            else{
                lineSet.push_back({{px2,py2},{px1,py1}});
                sortByX[px1] = {1,{i,0}};
                sortByX[px2] = {0,{i,0}};
            }
        }

        map<double,pair<double,pair<double,double>>>::iterator itr;

        map<double,double>::iterator perv,next;

        for(itr = sortByX.begin(); itr != sortByX.end(); ++itr){
            double lineNo  = (itr->second).second.first;
            double type = (itr->second).first;
            double xofi = itr->first;

            if(type==-1){
                double bl = (itr->second).second.first;
                double ul = (itr->second).second.second;

            }

            double yofi,oppositeSideY;

            if (lineSet[lineNo].first.first==xofi){
                yofi = lineSet[lineNo].first.second;
                oppositeSideY = lineSet[lineNo].second.second;
            }
            else{
                yofi = lineSet[lineNo].second.second;
                oppositeSideY = lineSet[lineNo].first.second;
            }

            if (type==0){
                sortByY[yofi] = lineNo;

                perv = sortByY.find(yofi);
                next = sortByY.find(yofi);
                next++;
                if (perv!=sortByY.begin())
                {
                    perv--;
                    check(perv->second,lineNo);
                }
                if (next!=sortByY.end())
                {
                    check(next->second,lineNo);
                }
                edges(lineNo);
            }
            else{

                perv = sortByY.find(oppositeSideY);
                next = sortByY.find(oppositeSideY);
                next++;

                if (perv!=sortByY.begin())
                {
                    perv--;
                    if (next!=sortByY.end())
                    {
                        check(perv->second,next->second);
                    }
                }
                sortByY.erase(oppositeSideY);
            }
        }


    QApplication a(argc, argv);
    LineIntersection w(nullptr,lineSet,intersectionPoint);
    w.show();
    return a.exec();
}
