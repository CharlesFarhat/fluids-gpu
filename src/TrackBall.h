
class mat3C
{
    float m[3][3];

public:

    void fillDefault();
    // matrix multiplication
    mat3C operator * (mat3C& m2) const;

    // rotate 'angle' around axis (xa, ya, za)
    void rotateAroundAxisC(float xa, float ya, float za, float angle);

    // access operator
    float& operator () (int Row, int Col);

    // casting operators
    operator float* ();
};

//***********************************************************************************
class TrackBall
//***********************************************************************************
{
    float x0, y0, z0;  // point on trackball when mouse down at start rotation mouse drag
    float x1, y1, z1;  // point on trackball at mouse drag positioin

    mat3C rotate;       // delta rotation while dragging
    mat3C orientation;  // orientation of trackball

public:


    TrackBall();

    void PointOnTrackBall(float &x, float &y, float &z, int mouseX, int mouseY, int mouseWidth, int mouseHeight);

    void DragStart(int mouseX, int mouseY, int mouseWidth, int mouseHeight);
    void  DragMove(int mouseX, int mouseY, int mouseWidth, int mouseHeight);
    void DragEnd();

    mat3C GetRotationMatrix();
};



