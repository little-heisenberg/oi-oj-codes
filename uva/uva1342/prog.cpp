#include <bits/stdc++.h>
using namespace std;
struct Point
{
    double x, y;
    Point(double X = 0, double Y = 0)
    {
        x = X;
        y = Y;
    }
};
typedef Point Vector;
Vector operator+(Vector A, Vector B)
{
    return Vector(A.x + B.x, A.y + B.y);
}
Vector operator-(Point A, Point B)
{
    return Vector(A.x - B.x, A.y - B.y);
}
Vector operator*(Vector A, double p)
{
    return Vector(A.x * p, A.y * p);
}
Vector operator/(Vector A, double p)
{
    return Vector(A.x / p, A.y / p);
}
bool operator<(const Point &a, const Point &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
const double eps = 1e-10;
int dcmp(double x)
{
    if (fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
bool operator==(const Point &a, const Point &b)
{
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector A, Vector B)
{
    return A.x * B.x + A.y * B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A, A));
}
double Angle(Vector A, Vector B)
{
    return acos(Dot(A, B) / Length(A) / Length(B));
}
double Cross(Vector A, Vector B)
{
    return A.x * B.y - A.y * B.x;
}
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w)
{
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
Point P[1000], V[100000];
int main()
{
    int n, cnt = 0;
    while (scanf("%d", &n) == 1 && n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> P[i].x >> P[i].y;
            V[i] = P[i];
        }
        n--;
        int c = n, e = n;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (SegmentProperIntersection(P[i], P[i + 1], P[j], P[j + 1]))
                    V[c++] = GetLineIntersection(P[i], P[i + 1] - P[i], P[j], P[j + 1] - P[j]);
            }
        }
        sort(V, V + c);
        c = unique(V, V + c) - V;
        for (int i = 0; i < c; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (OnSegment(V[i], P[j], P[j + 1]))
                    e++;
            }
        }
        printf("Case %d: There are %d pieces.\n", ++cnt, e + 2 - c);
    }
    return 0;
}
