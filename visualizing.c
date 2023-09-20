//
// Created by Antoine on 11/09/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "triangle2D.h"

int read_mesh2D(Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    // Read header information (e.g., number of vertices and triangles)
    fscanf(file, "%d %d", &m->nv, &m->nt);

    // Allocate memory for vertices and triangles
    m->vert = (Vertex*)malloc(m->nv * sizeof(Vertex));
    m->tri = (Triangle*)malloc(m->nt * sizeof(Triangle));

    // Read vertex data and store it in m->vert
    for (int i = 0; i < m->nv; i++) {
        fscanf(file, "%lf %lf", &m->vert[i].x, &m->vert[i].y);
    }

    // Read triangle data and store it in m->tri
    for (int i = 0; i < m->nt; i++) {
        fscanf(file, "%d %d %d", &m->tri[i].index[0], &m->tri[i].index[1], &m->tri[i].index[2]);
    }

    fclose(file);
    return 0;
}

int write_mesh2D(Mesh2D* m, const char* filename){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing\n", filename);
        return -1;
    }

    // Write header information (number of vertices and triangles)
    fprintf(file, "%d %d\n", m->nv, m->nt);

    // Write vertex data
    for (int i = 0; i < m->nv; i++) {
        fprintf(file, "%lf %lf\n", m->vert[i].x, m->vert[i].y);
    }

    // Write triangle data
    for (int i = 0; i < m->nt; i++) {
        fprintf(file, "%d %d %d\n", m->tri[i].index[0], m->tri[i].index[1], m->tri[i].index[2]);
    }

    fclose(file);
    return 0;
}

int main() {
    Mesh2D mesh;
    // Initialize the mesh structure with your data

    const char* filename = "output.mesh";

    if (write_mesh2D(&mesh, filename) == 0) {
        printf("Mesh data successfully written to %s\n", filename);
    }
    return 0;
}

