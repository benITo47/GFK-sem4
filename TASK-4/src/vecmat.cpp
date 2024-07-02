#include "vecmat.h"

Vector::Vector()
{
    data[0] = 0.0; data[1] = 0.0; data[2] = 1.0;
}

void Vector::Print(void)
{
    printf("(%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2]);
}

void Vector::Set(double d1, double d2)
{
    data[0] = d1; data[1] = d2;
}

double Vector::GetX()
{
    return data[0];
}

double Vector::GetY()
{
    return data[1];
}

Matrix::Matrix()
{
    data[0][0] = 0.0; data[0][1] = 0.0; data[0][2] = 0.0;
    data[1][0] = 0.0; data[1][1] = 0.0; data[1][2] = 0.0;
    data[2][0] = 0.0; data[2][1] = 0.0; data[2][2] = 1.0;
}

Matrix::Matrix(double n11, double n12, double n13, double n21, double n22, double n23, double n31, double n32, double n33)
{
    data[0][0] = n11; data[0][1] = n12; data[0][2] = n13;
    data[1][0] = n21; data[1][1] = n22; data[1][2] = n23;
    data[2][0] = n31; data[2][1] = n32; data[2][2] = n33;
}

void Matrix::Print(void)
{
    printf("\n|%2.3lf,%2.3lf,%2.3lf|\n", data[0][0], data[0][1], data[0][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[1][0], data[1][1], data[1][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[2][0], data[2][1], data[2][2]);
}

Matrix Matrix::operator* (const Matrix gMatrix)
{
    int i, j, k;
    Matrix tmp;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            tmp.data[i][j] = 0.0;
            for (k = 0; k < 3; k++)
                tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
        }
    return tmp;
}

Vector operator* (const Matrix gMatrix, const Vector gVector)
{
    unsigned int i, j;
    Vector tmp;

    for (i = 0; i < 3; i++)
    {
        tmp.data[i] = 0.0;
        for (j = 0; j < 3; j++) tmp.data[i] = tmp.data[i] + (gMatrix.data[i][j] * gVector.data[j]);
    }
    return tmp;
}