#include "iostream"
#include "queue"

//地图 - 不考虑地形
const int map[10][10] = {
  1,2,3,0,0,0,0,0,0,0,
  4,0,5,0,0,0,0,0,0,0,
  6,7,8,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,2,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0
};

//节点
struct Point{
  int x;
  int y;
  int value;
  int Fvalue;
  friend bool operator< (Point A, Point B)
  {
    return B.Fvalue < A.Fvalue;
  }
  friend bool operator== (Point A, Point B)
  {
    return ((A.x == B.x) && (A.y == B.y));
  }
};

//节点信息
class SpecialPoint
{
public:
  SpecialPoint(Point Start_Point, Point GOAL_Point);
  int SpecialAbs(int x, int y);
  int setFvalue(Point A, Point B, Point goal);
  int setGvalue(Point A, Point B);
  int setHvalue(Point A, Point goal);
  void AStartSearch();

private:
  Point Start, GOAL, current, validPassPoint;
  //优先队列 - 其元素若为自定义类型，则必须重载<
  std::priority_queue<Point> OPEN_quere;
};

SpecialPoint::SpecialPoint(Point Start_Point, Point GOAL_Point)
{
  current.x = Start.x = Start_Point.x;
  current.y = Start.y = Start_Point.y;
  current.value = Start.value = Start_Point.value;
  current.Fvalue = Start.Fvalue = Start_Point.Fvalue;
  GOAL.x = GOAL_Point.x;
  GOAL.y = GOAL_Point.y;
  GOAL.value = GOAL_Point.value;
  GOAL.Fvalue = GOAL_Point.Fvalue;
  std::cout << "Start Point: "<< Start.x << ":" << Start.y << std::endl;
  std::cout << "GOAL Point: "<< GOAL.x << ":" << GOAL.y << std::endl;
  validPassPoint.x = 0;
  validPassPoint.y = 0;
  validPassPoint.value = 0;
  validPassPoint.Fvalue = 0;
}

int SpecialPoint::SpecialAbs(int x, int y)
{
  return (x-y > 0) ? (x-y) : (y-x);
}

//启发式函数
int SpecialPoint::setFvalue(Point A, Point B, Point goal)
{
  return setGvalue(A, B) + setHvalue(A, goal);
}

int SpecialPoint::setGvalue(Point A, Point B)
{
  if (A.x == B.x)
  {
    return SpecialAbs(A.y, B.y)*10;
  }
  else if (A.y == B.y)
  {
    return SpecialAbs(A.x, B.x)*10;
  }
  else
  {
    return SpecialAbs(A.y, B.y)*14;
  }
}

int SpecialPoint::setHvalue(Point A, Point goal)
{
  return SpecialAbs(A.y, goal.y)*10 + SpecialAbs(A.x, goal.x)*10;
}

//不标记父节点
void SpecialPoint::AStartSearch()
{
  //需重载==
  if (! (current == GOAL))
  {
    for (int i = -1; i <= 1; ++i)
      for (int j = -1; j <= 1; ++j)
      {
        if(i == 0 && j == 0) continue;
        validPassPoint.x = current.x+i;
        validPassPoint.y = current.y+j;
        validPassPoint.value = map[current.x+i][current.y+j];
        validPassPoint.Fvalue = setFvalue(validPassPoint, current, GOAL);
        OPEN_quere.push(validPassPoint);
      }
    current = OPEN_quere.top();
    std::cout << "[F值最小]的节点: " << current.x << ":" << current.y << " : " << current.Fvalue << std::endl;
    //迭代
    AStartSearch();
  }
}

int main()
{
  Point Start_Point, GOAL_Point;
  Start_Point.x = 1;
  Start_Point.y = 1;
  Start_Point.value = map[Start_Point.x][Start_Point.y];
  Start_Point.Fvalue = 0;
  GOAL_Point.x = 6;
  GOAL_Point.y = 9;
  GOAL_Point.value = map[GOAL_Point.x][GOAL_Point.y];
  GOAL_Point.Fvalue = 0;

  SpecialPoint sp(Start_Point, GOAL_Point);
  sp.AStartSearch();

  return 0;
}
