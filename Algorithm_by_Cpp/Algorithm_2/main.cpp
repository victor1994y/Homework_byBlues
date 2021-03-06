#include "mainwindow.h"
#include <QApplication>
#include "qcustomplot.h"

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MAX 10000
#define MIN 0
//#define N 100

class TimeCheck{
public:
  timeval startTime,endTime;//计时用结构体
  double takeTime;//记录的时间差

  void start(){
    gettimeofday(&startTime,NULL);//开始计时
  }
  void stop(){
    gettimeofday(&endTime,NULL);//结束计时

  }
  double getTime(){
    takeTime = 1000000*(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec);
    takeTime /= 1000;//单位为ms
    return takeTime;
  }
} tc;

class Point{
public:
  int x,y;
  int id;
  Point(int id,int x,int y){
    int
    this->x=x;
    this->y=y;
  }
  void setPoint(int x,int y){
    this->x=x;
    this->y=y;
  }
};

class PairofPoint{
public:
  double distance;
  Point a,b;
  PairofPoint(){

  }
};

class Grid{
private:
  int size;
  Point *list;
  int locA,locB;
  double minDis;
  void exchange(int i,int j);
  void quickSort(int first,int last);
  void insertionSort(int first,int last);
  void partition(int first,int last);

public:
  Grid();
  Grid(int size);
  ~Grid();
  void sort();
  void exhaustiveMindis();


  double distance();
  int getSize();
  bool isXSorted();
};

Grid::Grid(int size){
  minDis=MAX;
  locA=size;
  locB=size;
  srand(time(NULL));
  this->size = size;
  list = new Point[size];
  for(int i=0;i<size;i++){
    list[i]=new Point((rand()%MAX+MIN),(rand()%MAX+MIN));
  }
}

Grid::Grid(){
  minDis=MAX;
  locA=size;
  locB=size;
  size=0;
}

void Grid::exchange(int i,int j){//数据互换
  Point temp=list[i];
  list[i]=list[j];
  list[j]=temp;
}

int Grid::getSize(){
  return size;
}

bool Grid::isXSorted(){//最后判断各个点的x坐标是否已经成功排序
  for(int i=1;i<size;i++){
    if( list[i-1]->x > list[i]->x ) return false;
  }
  return true;
}

Grid::~Grid(){
  for(int i=0;i<size;i++){
    delete list[i];
  }
  delete[] list;
}

void Grid::insertionSort(int first,int last){
  for(int i=first+1;i<last;i++){
    Point temp=list[i];
    int j;
    for(j=i-1;j>=0 && list[j]->x>temp->x;j--){
      list[j+1] = list[j];
    }
    list[j+1]=temp;
  }
}

void Grid::quickSort(int first,int last){//递归调用该函数
  if(first >= last)  return;//退出条件
  if((last-first)<=20){
    insertionSort(first,last);
  }
  else{
    int key=partition(first,last);
    quickSort(first,key-1);
    quickSort(key+1,last);
  }

}

int Grid::partition(int first,int last){
  int key=first;
  int i=first+1,j=last;
  while(1){
    while(list[key]->x>=list[i]->x && i<last) i++;
    while(list[key]->x<=list[j]->x && j>first) j--;
    if(i>=j)  break;
    exchange(i,j);
  }
  exchange(key,j);
  key=j;
  return key;
}

void Grid::sort(){
    quickSort(0,size-1);
}

void Grid::exhaustiveMinDis(){
  minDis=MAX;
  for(int i=0;i<size-1;i++){
    for(int j=i;j<size;j++){
      if(distance(i,j)<minDis) {
        minDis=distance(i,j);
        locA=i;
        locB=j;
      }
    }
  }
}

void Grid::mergeMinDis(){
  int locLA,locLB,locRA,locRB;
  sort();

}

double Grid::mergeDistance(int left,int right){
  double minDistance;
  if(right-left <= 0){//1 point or Error case
    minDistance=MAX;
  }
  else if(right-lift == 1){//2 points
    minDistance=distance(left,right);
  }
  else if(right-left == 2){//3 points
    minDistance=distance(left,right);
    if(distance())
  }
  else{//more than 3 points
    int middle=(list[right]->x-list[left]->x);
    int locMid;
    for(locMid=left;locMid<right && list[locMid]->x > middle;locMid++);


    mergeDistance(left,locMid);
    mergeDistance(locMid,right);

  }
}



double Grid::distance(int a,int b){
  double dis;
  dis=sqrt(pow(( list[a]->x - list[b]->x ),2) + pow(( list[a]->y - list[b]->y ),2));
  return dis;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
