#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
    private:
        std::shared_ptr<ConfigClass> cfg;
        int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
        double x_min,x_max; // zakres zmiennej x
        double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje


        double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
        static inline double function1(double x) { return x * x; }
        static inline double function2(double x) { return 0.5 * exp(4 * x - 3 * x * x); }
        static inline double function3(double x) { return x + sin(4 * x); }

        void line2d(wxDC* dc, Matrix t,double x1,double y1,double x2,double y2);




    public:
        ChartClass(std::shared_ptr<ConfigClass> c);
        void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
        double Get_Y_min(); // zwraca y_min
        double Get_Y_max(); // zwraca y_max

        Matrix GetRotationTransform(double alpha);
        Matrix GetScaleTransform(double w, double h, double x0, double y0, double x1, double y1);
        Matrix GetTranslationTransform(double deltaX, double deltaY);
        void DrawMarkers(wxDC* dc, Matrix t, double alpha, double x, double y, double value);
        void Draw(wxDC *dc, int w, int h);  // rysuje wykres
        inline static double degToRad(double degrees) {return degrees* M_PI / 180.0; }
};

#endif
