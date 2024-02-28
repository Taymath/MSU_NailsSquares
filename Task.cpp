#include "Task.h"
#include <time.h>
#include <iostream>


Point* Task::middle(unsigned int first, unsigned int second)
{
    Square *sq1 = new Square;
    Segment x1{}, x2{}, y1{}, y2{};
    Point *res = nullptr;

    x1.begin = data.squares.at(first).left_corner.x;
    x1.end = x1.begin + data.side_length;

    y1.begin = data.squares.at(first).left_corner.y;
    y1.end = y1.begin + data.side_length;

    x2.begin = data.squares.at(second).left_corner.x;
    x2.end = x2.begin + data.side_length;

    y2.begin = data.squares.at(second).left_corner.y;
    y2.end = y2.begin + data.side_length;

    if (((x1.end > x2.begin) || (x2.end > x1.begin)) && ((y1.end > y2.begin) || (y2.end > y1.begin)))
    {
        res = new Point;

        res->x = (x1.end + x2.begin) / 2;
        res->y = (y1.end + y2.begin) / 2;
    }

    return res;
}

void Task::simple_version()
{
    Point *req;
    bool intersected = false;

    for (int i = 0; i < data.squares.size(); ++i)
    {
        if (intersected)
        {
            intersected = false;
            continue;
        }

        for (int j = i + 1; j < data.squares.size(); ++j)
        {
            req = middle(i, j);

            if (++res.steps && !data.squares.at(i).covered && !data.squares.at(j).covered && (req != nullptr))
            {
                data.squares.at(i).covered = data.squares.at(j).covered = true;
                res.points.push_back(*req);

                intersected = true;
                break;
            }
        }
    }

    for (int i = 0; i < data.squares.size(); ++i)
        if (++res.steps && !data.squares.at(i).covered)
            res.points.push_back(*middle(i, i));

}


int Task::intersection(const Segment &first, const Segment &second)
{
    if((first.begin < second.begin) && (first.end > second.begin))
        return -1;//первый отрезок пересекается со вторым находясь слева от него
    else if((first.begin < second.end) && (first.end > second.end))
        return 1;//первый отрезок пересекается со вторым находясь справа от него
    else if((first.begin >= second.begin) && (first.end <= second.end))
        return 2;//первый содержится внутри второго
    else
        return 0;
}

void Task::complex_version()
{
    Point point{};

    Segment x_intersection{}, y_intersection{}, x_current{}, y_current{};

    int x_flag, y_flag;

    for(int i = 0; i < data.squares.size(); i ++)
    {
        if(!data.squares.at(i).covered)
        {
            x_intersection.begin = data.squares.at(i).left_corner.x;
            x_intersection.end = x_intersection.begin + data.side_length;

            y_intersection.begin = data.squares.at(i).left_corner.y;
            y_intersection.end = y_intersection.begin + data.side_length;

            for(int j = i + 1; j < data.squares.size(); j ++)
                if (++res.steps && !data.squares.at(j).covered)
                {
                    x_current.begin = data.squares.at(j).left_corner.x;
                    x_current.end = x_current.begin + data.side_length;

                    y_current.begin = data.squares.at(j).left_corner.y;
                    y_current.end = y_current.begin + data.side_length;

                    x_flag = intersection(x_intersection, x_current);
                    y_flag = intersection(y_intersection, y_current);

                    if (x_flag && y_flag)
                    {
                        if (x_flag == -1)
                            x_intersection.begin = x_current.begin;//если слева идем правее по иксу
                        else if (x_flag == 1)
                            x_intersection.end = x_current.end;//если справа идем левее по иксу

                        if (y_flag == -1)
                            y_intersection.begin = y_current.begin;//если первый ниже, идем выше по y
                        else if (y_flag == 1)
                            y_intersection.end = y_current.end;//если первый выше, идем ниже по y

                        data.squares.at(j).covered = true;

                    } else
                        continue;
                }

                data.squares.at(i).covered = true;

                point.x = (x_intersection.begin + x_intersection.end) / 2.0;
                point.y = (y_intersection.begin + y_intersection.end) / 2.0;

                res.points.push_back(point);

        }
    }
}








