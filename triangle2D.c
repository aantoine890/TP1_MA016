//
// Created by Antoine on 11/09/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "triangle2D.h"

int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    m->vert = malloc(vtx_capacity*sizeof(Vertex));
    if (m->vert == NULL){
        printf("malloc error\n");
        return -1;
    }
    m->tri = malloc(tri_capacity*sizeof(Triangle));
    if (m->tri == NULL){
        printf("malloc error\n");
        return -1;
    }

    return 0;
}

void dispose_mesh2D(Mesh2D* m){
    free(m->tri);
    free(m->vert);
    free(m);
}

double triangle_area(Vertex v1, Vertex v2, Vertex v3) {
    return 0.5 * ((v1.x * (v2.y - v3.y)) + (v2.x * (v3.y - v1.y)) + (v3.x * (v1.y - v2.y)));
}

double area_mesh2D(Mesh2D *m) {
    double totalArea = 0.0;

    // Iterate through each triangle in the mesh
    for (int i = 0; i < m->nt; i++) {
        int idx1 = m->tri[i].index[0];
        int idx2 = m->tri[i].index[1];
        int idx3 = m->tri[i].index[2];

        // Get the vertices of the triangle
        Vertex v1 = m->vert[idx1];
        Vertex v2 = m->vert[idx2];
        Vertex v3 = m->vert[idx3];

        // Calculate the area of the triangle and add it to the total area
        double triangleArea = triangle_area(v1, v2, v3);
        totalArea += triangleArea;
    }
    return totalArea;
}

int main(){
    Mesh2D * mesh = malloc(sizeof(Mesh2D));

    if (mesh == NULL){
        printf("malloc error\n");
        return -1;
    }

    if (initialize_mesh2D(mesh,3,1) !=0){
        free(mesh);
        return -1;
    }

    mesh->vert[0].x = 0.0;
    mesh->vert[0].y = 0.0;
    mesh->vert[1].x = 1.0;
    mesh->vert[1].y = 0.0;
    mesh->vert[2].x = 1.0;
    mesh->vert[2].y = 1.0;
    mesh->vert[3].x = 0.0;
    mesh->vert[3].y = 1.0;


    mesh->tri->index[0] = 0;
    mesh->tri->index[1] = 1;
    mesh->tri->index[2] = 2;


    printf("The area of the mesh is : %f\n", area_mesh2D(mesh));
    dispose_mesh2D(mesh);
    return 0;
}
