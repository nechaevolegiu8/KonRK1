#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
const double M_PI = 3.14; 

//Класс тройного вектора
class Vec3
{
protected:
    
public:
    float x, y, z;
    
    Vec3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {}
};

//Функция выдающая случайное double число
double random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

//Функция рассчета расстояния между двумя точками в пространстве
double ras(double x1, double y1, double z1, double x2, double y2, double z2) {
    return pow(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2), 0.5);
}

int rasall(double x, double y, double z, vector<Vec3> v, double e) {
    int ok = 0;
    for (int i = 0; i < v.size(); i++) {
        if (ras(x, y, z, v[i].x, v[i].y, v[i].z) <= e) {
            ok = 1;
        }
    }
    return ok;
}

//Функция расставления num_points точек равномерно на сфере (единичного радиуса в 0)
//Метод золотого сечения
vector<Vec3> fibonacci(const int num_points) {
    vector<Vec3> vectors;
    vectors.reserve(num_points);

    const double gr = (sqrt(5.0) + 1.0) / 2.0;  // golden ratio = 1.6180339887498948482
    const double ga = (2.0 - gr) * (2.0 * M_PI);  // golden angle = 2.39996322972865332

    for (size_t i = 1; i <= num_points; ++i) {
        const double lat = asin(-1.0 + 2.0 * double(i) / (num_points + 1));
        const double lon = ga * i;

        const double x = cos(lon) * cos(lat);
        const double y = sin(lon) * cos(lat);
        const double z = sin(lat);

        vectors.emplace_back(x, y, z);
    }

    return vectors;
}

int main()
{
    srand((unsigned)time(NULL));
    setlocale(0, "");
    vector<Vec3> v3; //Вектор координат ловящих точек
    int n, t;
    double x, y, z, e, c;
    cout << "Введите кол-во точек: "; cin >> n; cout << endl;
    
    x = 10.0; 
    y = 5.0;
    z = 5.0;
    e = 1.0; //Радиус ловящих сфер
    c = 0.001; //Точность для работы с double
    t = 5000000; //Кол-во экспериментов

    v3 = fibonacci(n);
    cout << setw(9) << setprecision(3) << "X " << setw(9) << "Y " << setw(9) << "Z" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(9) << v3[i].x << " " << setw(9) << v3[i].y << " " << setw(9) << v3[i].z << " | " << i << endl;
    }

    cout << endl;
    cout << "----------------------------------------------" << endl;
    
    vector<Vec3> par; //Вектор координат точек, спроецированных на поверхность параллелепипеда со сферы

    //Проецирование равномерно расставленных точек с поверхности сферы на поверхность параллелепипеда
    for (int i = 0; i < n; i++) {
        double cx, cy, cz;
        cx = 1; cy = 1; cz = 1;

        if ((v3[i].x < 0) && (v3[i].y < 0) && (v3[i].z < 0)) { //Случай < < < 000
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp > (-x / 2.0)) && (ytemp > (-y / 2.0)) && (ztemp > (-z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;                
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

        if ((v3[i].x < 0) && (v3[i].y < 0) && (v3[i].z > 0)) { //Случай < < > 001
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp > (-x / 2.0)) && (ytemp > (-y / 2.0)) && (ztemp < (z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

        if ((v3[i].x < 0) && (v3[i].y > 0) && (v3[i].z < 0)) { //Случай < > < 010
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp > (-x / 2.0)) && (ytemp < (y / 2.0)) && (ztemp > (-z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

        if ((v3[i].x < 0) && (v3[i].y > 0) && (v3[i].z > 0)) { //Случай < > > 011
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp > (-x / 2.0)) && (ytemp < (y / 2.0)) && (ztemp < (z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

        if ((v3[i].x > 0) && (v3[i].y < 0) && (v3[i].z < 0)) { //Случай > < < 100
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp < (x / 2.0)) && (ytemp > (-y / 2.0)) && (ztemp > (-z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);

        }

        if ((v3[i].x > 0) && (v3[i].y < 0) && (v3[i].z > 0)) { //Случай > < > 101
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp < (x / 2.0)) && (ytemp > (-y / 2.0)) && (ztemp < (z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);

        }

        if ((v3[i].x > 0) && (v3[i].y > 0) && (v3[i].z < 0)) { //Случай > > < 110
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp < (x / 2.0)) && (ytemp < (y / 2.0)) && (ztemp > (-z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

        if ((v3[i].x > 0) && (v3[i].y > 0) && (v3[i].z > 0)) { //Случай > > > 111
            double xtemp, ytemp, ztemp;
            xtemp = v3[i].x; ytemp = v3[i].y; ztemp = v3[i].z;

            while ((xtemp < (x / 2.0)) && (ytemp < (y / 2.0)) && (ztemp < (z / 2.0))) {
                cx = cx + c; xtemp = v3[i].x * cx;
                cy = cy + c; ytemp = v3[i].y * cy;
                cz = cz + c; ztemp = v3[i].z * cz;
            }
            cout << setw(9) << xtemp << " " << setw(9) << ytemp << " " << setw(9) << ztemp << " | " << i << endl;
            par.emplace_back(xtemp, ytemp, ztemp);
        }

    }

    cout << "----------------" << endl;
    vector<Vec3> pos; //Все места куда попадает случайно точка
    
    //Кидание точки на поверхность параллелепипеда
    for (int i = 0; i < t; i++) {
        int rng, znak;
        rng = 1 + rand() % 3; 
        znak = 1 + rand() % 2;

        //Розыгрыш на какую грань попадет
        if (rng == 1) {
            if (znak == 1) pos.emplace_back((x / 2.0), random(-y / 2.0, y / 2.0), random(-z / 2.0, z / 2.0));
            if (znak == 2) pos.emplace_back((-x / 2.0), random(-y / 2.0, y / 2.0), random(-z / 2.0, z / 2.0));
        }

        if (rng == 2) {
            if (znak == 1) pos.emplace_back(random(-x / 2.0, x / 2.0), (y / 2.0), random(-z / 2.0, z / 2.0));
            if (znak == 2) pos.emplace_back(random(-x / 2.0, x / 2.0), (-y / 2.0), random(-z / 2.0, z / 2.0));
        }

        if (rng == 3) {
            if (znak == 1) pos.emplace_back(random(-x / 2.0, x / 2.0), random(-y / 2.0, y / 2.0), (z / 2.0));
            if (znak == 2) pos.emplace_back(random(-x / 2.0, x / 2.0), random(-y / 2.0, y / 2.0), (-z / 2.0));
        }
    }
   
    double count = 0;
    //Подсчет количества попаданий в сферы
    for (int i = 0; i < t; i++) {
        if (rasall(pos[i].x, pos[i].y, pos[i].z, par, e) == 1) {
            count++;
        }       
    }
    
    cout << endl << "Цена игры = " << (double) count / (double) t << endl;
    
}
