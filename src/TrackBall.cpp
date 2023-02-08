#include "math.h"
#include "Algebra.h"
#include "TrackBall.h"


#ifndef min
#define min(x, y) ((x < y)? x : y)
#endif
#ifndef max
#define max(x, y) ((x > y)? x : y)
#endif



//***********************************************************************************
TrackBall::TrackBall()
//***********************************************************************************
{
    orientation.fillDefault();
    rotate.fillDefault();
}

void mat3C::fillDefault()
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[j][i] = 0;
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
}


//***********************************************************************************
void TrackBall::PointOnTrackBall(float &x, float &y, float &z, int mouseX, int mouseY, int mouseWidth, int mouseHeight)
//***********************************************************************************
{
    x =  (float)(mouseX - mouseWidth/2)  / (float)min(mouseWidth, mouseHeight)*2;
    y =  (float)(mouseY - mouseHeight/2) / (float)min(mouseWidth, mouseHeight)*2;

    float rr = x*x+y*y;

    if ( rr < 1)
        z = sqrt(1- rr);
    else
    {
        x = x / sqrt(rr);
        y = y / sqrt(rr);
        z = 0;
    }
}


//***********************************************************************************
void TrackBall::DragStart(int mouseX, int mouseY, int mouseWidth, int mouseHeight)
//***********************************************************************************
{
    PointOnTrackBall(x0, y0, z0, mouseX, mouseY, mouseWidth, mouseHeight);
}
//***********************************************************************************
void TrackBall::DragMove(int mouseX, int mouseY, int mouseWidth, int mouseHeight)
//***********************************************************************************
{
    PointOnTrackBall(x1, y1, z1, mouseX, mouseY, mouseWidth, mouseHeight);

    // rotation axis  = cross(p0, p1)
    float xa = y0*z1 - y1*z0;
    float ya = z0*x1 - z1*x0;
    float za = x0*y1 - x1*y0;

    // rotation angle = acos(dot(p0,p1))
    float angle = 2*acos(min(max(x0*x1+y0*y1+z0*z1,-1),1)); // multiply angle by 2 for 360 degree range

    // rotate matrix around axis
    rotate.rotateAroundAxisC(xa, ya, za, angle);
}

//***********************************************************************************
void TrackBall::DragEnd()
//***********************************************************************************
{
    // multiply current orientation with dragged rotation
    orientation = orientation*rotate;
    rotate.fillDefault();
}

//***********************************************************************************
mat3C TrackBall::GetRotationMatrix()
//***********************************************************************************
{
    return orientation*rotate;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////




// matrix multiplication
//***********************************************************************************
mat3C mat3C::operator * (mat3C& m2) const
//***********************************************************************************
{
    mat3C res;
    for (int j = 0; j<3; j++)
        for (int i = 0; i<3; i++)
        {
            res(j, i) = 0;
            for (int k = 0; k<3; k++)
                res(j, i) += m[j][k] * m2(k, i);
        }
    return res;
}

// access operator
//***********************************************************************************
float& mat3C::operator () (int Row, int Col)
//***********************************************************************************
{
    return m[Row][Col];
}

// casting operators
//***********************************************************************************
mat3C::operator float* ()
//***********************************************************************************
{
    return &m[0][0];
}

// rotate 'angle' around axis (xa, ya, za)
//***********************************************************************************
void mat3C::rotateAroundAxisC(float xa, float ya, float za, float angle)
//***********************************************************************************
{
    // normalize axis for safety else rotation can include scale
    float t = sqrt(xa*xa + ya*ya + za*za);
    if (t != 0)
    {
        xa /= t;
        ya /= t;
        za /= t;
    }

    m[0][0] = 1 + (1 - cos(angle))*(xa*xa - 1);
    m[1][1] = 1 + (1 - cos(angle))*(ya*ya - 1);
    m[2][2] = 1 + (1 - cos(angle))*(za*za - 1);

    m[0][1] = +za*sin(angle) + (1 - cos(angle))*xa*ya;
    m[1][0] = -za*sin(angle) + (1 - cos(angle))*xa*ya;

    m[0][2] = -ya*sin(angle) + (1 - cos(angle))*xa*za;
    m[2][0] = +ya*sin(angle) + (1 - cos(angle))*xa*za;

    m[1][2] = +xa*sin(angle) + (1 - cos(angle))*ya*za;
    m[2][1] = -xa*sin(angle) + (1 - cos(angle))*ya*za;
}




