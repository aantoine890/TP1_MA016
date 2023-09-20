//
// Created by Antoine on 11/09/2023.
//

#ifndef TP1_TRIANGLE2D_H
#define TP1_TRIANGLE2D_H

// Define the Vertex structure for 2D
typedef struct{
    double x;
    double y;
} Vertex ;

// Define the Triangle structure
typedef struct {
    int index[3];
} Triangle;

// Define the Mesh2D structure
typedef struct{
    int nv; // Number of vertices
    Vertex * vert;
    int nt; // Number of triangles
    Triangle * tri;
} Mesh2D ;

#endif //TP1_TRIANGLE2D_H
