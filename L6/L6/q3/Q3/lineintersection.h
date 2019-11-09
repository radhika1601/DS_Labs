#ifndef LINEINTERSECTION_H
#define LINEINTERSECTION_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QPainter>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class LineIntersection; }
QT_END_NAMESPACE

class LineIntersection : public QMainWindow
{
    Q_OBJECT

public:
    vector< pair<pair<int,int> , pair<int,int>> >lineSet;
    vector<pair<double,double>>intersectionPoint;
    LineIntersection(QWidget *parent,vector< pair<pair<int,int> , pair<int,int>> >lineSet, vector<pair<double,double>>intersectionPoint );
    ~LineIntersection();
    virtual void paintEvent(QPaintEvent * event);

private:
    Ui::LineIntersection *ui;
};
#endif // LINEINTERSECTION_H
