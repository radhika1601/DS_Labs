#include "lineintersection.h"
#include "ui_lineintersection.h"

LineIntersection::LineIntersection(QWidget *parent,vector< pair<pair<int,int> , pair<int,int>> >lineSet,vector<pair<double,double>>intersectionPoint )
    : QMainWindow(parent)
    , ui(new Ui::LineIntersection)
{
    this->lineSet = lineSet;
    this->intersectionPoint = intersectionPoint;
    ui->setupUi(this);
}

LineIntersection::~LineIntersection()
{
    delete ui;
}

void LineIntersection::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen_pts;
    QPen pen_text;

    pen_pts.setCapStyle(Qt::RoundCap);
    pen_pts.setWidth(4);
    pen_text.setWidth(2);

    double sx2=0,sxy=0,sx=0,sy=0;
    int n1 = intersectionPoint.size();
    for (int i = 0; i < intersectionPoint.size(); ++i)
    {
        double a = intersectionPoint[i].first;
        double b = intersectionPoint[i].second;
        sx += a;
        sy += b;
        sx2 += (a*a);
        sxy += (a*b);
    }

    double m = (  (n1*sxy)-(sx*sy)  )/( (n1*sx2)-(sx*sx) );
    double bi = ( sy - (m*sx) )/n1 ;


    painter.drawText(QPoint(10,20),"number of intersections : " + QString::number(intersectionPoint.size()));
    painter.setPen(Qt::blue);
    painter.drawText(QPoint(10,40),"The fit line is of the form "+QString::number(m)+"x + "+QString::number(bi));


    for (int i = 0; i < lineSet.size();i++) {
        QPointF p1(lineSet[i].first.first,lineSet[i].first.second);
        QPointF p2(lineSet[i].second.first,lineSet[i].second.second);
        painter.setPen(Qt::black);
        painter.drawLine(p1,p2);
        painter.setPen(pen_pts);
        painter.drawPoint(p1);
        painter.drawPoint(p2);
        painter.setPen(pen_text);
        painter.drawText(p1,"("+QString::number(p1.rx())+","+QString::number(p1.ry())+")");
        painter.drawText(p2,"("+QString::number(p2.rx())+","+QString::number(p2.ry())+")");
    }






    pen_pts.setColor(Qt::red);
    pen_text.setColor(Qt::red);
    for (int i = 0; i < intersectionPoint.size(); i++) {
        QPointF p(intersectionPoint[i].first,intersectionPoint[i].second);
        painter.setPen(pen_pts);
        painter.drawPoint(p);
        painter.setPen(pen_text);
        painter.drawText(p,"("+QString::number(p.rx())+","+QString::number(p.ry())+")");
    }

    double temp1 = bi;
    double temp2 = m*999 + bi;

    painter.setPen(Qt::blue);
    painter.drawLine(QPointF(0,temp1),QPointF(999,temp2));


}

