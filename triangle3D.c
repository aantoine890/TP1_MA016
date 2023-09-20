//
// Created by Antoine on 11/09/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the Vertex structure for 3D
typedef struct {
    double x;
    double y;
    double z;
} Vertex3D;

// Define the Triangle structure
typedef struct {
    int index[3];
} Triangle;

// Define the Mesh3D structure
typedef struct {
    int nv; // Number of vertices
    Vertex3D *vert;
    int nt; // Number of triangles
    Triangle *tri;
} Mesh3D;

int initialize_mesh3D(Mesh3D *m, int vtx_capacity, int tri_capacity) {
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    m->vert = malloc(vtx_capacity * sizeof(Vertex3D));
    if (m->vert == NULL) {
        printf("malloc error\n");
        return -1;
    }
    m->tri = malloc(tri_capacity * sizeof(Triangle));
    if (m->tri == NULL) {
        printf("malloc error\n");
        free(m->vert);
        return -1;
    }

    return 0;
}

void dispose_mesh3D(Mesh3D *m) {
    free(m->tri);
    free(m->vert);
}

double triangle_area_3D(Vertex3D v1, Vertex3D v2, Vertex3D v3) {
    // Cross product of two edges of the triangle divided by 2 gives the area
    double cross_product_x = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
    double cross_product_y = (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z);
    double cross_product_z = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    return 0.5 * sqrt(cross_product_x * cross_product_x + cross_product_y * cross_product_y + cross_product_z * cross_product_z);
}

double area_mesh3D(Mesh3D *m) {
    double totalArea = 0.0;

    // Iterate through each triangle in the mesh
    for (int i = 0; i < m->nt; i++) {
        int idx1 = m->tri[i].index[0];
        int idx2 = m->tri[i].index[1];
        int idx3 = m->tri[i].index[2];

        // Get the vertices of the triangle
        Vertex3D v1 = m->vert[idx1];
        Vertex3D v2 = m->vert[idx2];
        Vertex3D v3 = m->vert[idx3];

        // Calculate the area of the triangle and add it to the total area
        double triangleArea = triangle_area_3D(v1, v2, v3);
        totalArea += triangleArea;
    }
    return totalArea;
}

double volume_mesh3D(Mesh3D *m) {
    double totalVolume = 0.0;

    // Iterate through each triangle in the mesh
    for (int i = 0; i < m->nt; i++) {
        int idx1 = m->tri[i].index[0];
        int idx2 = m->tri[i].index[1];
        int idx3 = m->tri[i].index[2];

        // Get the vertices of the triangle
        Vertex3D v1 = m->vert[idx1];
        Vertex3D v2 = m->vert[idx2];
        Vertex3D v3 = m->vert[idx3];

        // Calculate the area of the triangle
        double triangleArea = triangle_area_3D(v1, v2, v3);

        // Calculate the contribution to the volume using the triangle area and its normal vector
        totalVolume += triangleArea * (v1.x + v2.x + v3.x) / 3.0; // X-component of the triangle barycenter
    }

    return totalVolume / 3.0; // Divide by 3 to account for the divergence theorem (divX = 3)
}


int main() {
    Mesh3D * mesh = malloc(sizeof(Mesh3D));

    if (mesh == NULL) {
        printf("malloc error\n");
        return -1;
    }

    if (initialize_mesh3D(mesh, 8, 12) != 0) {
        free(mesh);
        return -1;
    }

    mesh->vert[0].x = 0.0;
    mesh->vert[0].y = 0.0;
    mesh->vert[0].z = 0.0;

    mesh->vert[1].x = 1.0;
    mesh->vert[1].y = 0.0;
    mesh->vert[1].z = 0.0;

    mesh->vert[2].x = 0.0;
    mesh->vert[2].y = 1.0;
    mesh->vert[2].z = 0.0;

    mesh->vert[3].x = 0.0;
    mesh->vert[3].y = 0.0;
    mesh->vert[3].z = 1.0;

    mesh->vert[4].x = 1.0;
    mesh->vert[4].y = 1.0;
    mesh->vert[4].z = 0.0;

    mesh->vert[5].x = 0.0;
    mesh->vert[5].y = 1.0;
    mesh->vert[5].z = 1.0;

    mesh->vert[6].x = 1.0;
    mesh->vert[6].y = 0.0;
    mesh->vert[6].z = 1.0;

    mesh->vert[7].x = 1.0;
    mesh->vert[7].y = 1.0;
    mesh->vert[7].z = 1.0;

    mesh->tri[0].index[0] = 0;
    mesh->tri[0].index[1] = 1;
    mesh->tri[0].index[2] = 2;

    mesh->tri[1].index[0] = 1;
    mesh->tri[1].index[1] = 4;
    mesh->tri[1].index[2] = 2;

    mesh->tri[2].index[0] = 0;
    mesh->tri[2].index[1] = 1;
    mesh->tri[2].index[2] = 3;

    mesh->tri[3].index[0] = 1;
    mesh->tri[3].index[1] = 6;
    mesh->tri[3].index[2] = 3;

    mesh->tri[4].index[0] = 1;
    mesh->tri[4].index[1] = 4;
    mesh->tri[4].index[2] = 7;

    mesh->tri[5].index[0] = 1;
    mesh->tri[5].index[1] = 7;
    mesh->tri[5].index[2] = 6;

    mesh->tri[6].index[0] = 3;
    mesh->tri[6].index[1] = 6;
    mesh->tri[6].index[2] = 7;

    mesh->tri[7].index[0] = 3;
    mesh->tri[7].index[1] = 7;
    mesh->tri[7].index[2] = 5;

    mesh->tri[8].index[0] = 0;
    mesh->tri[8].index[1] = 2;
    mesh->tri[8].index[2] = 3;

    mesh->tri[9].index[0] = 2;
    mesh->tri[9].index[1] = 5;
    mesh->tri[9].index[2] = 3;

    mesh->tri[10].index[0] = 2;
    mesh->tri[10].index[1] = 4;
    mesh->tri[10].index[2] = 7;

    mesh->tri[11].index[0] = 2;
    mesh->tri[11].index[1] = 7;
    mesh->tri[11].index[2] = 5;


    printf("The area of the mesh is : %f\n", area_mesh3D(mesh));
    printf("The volume of the structure enclose by the mesh is : %f\n", volume_mesh3D(mesh));
    dispose_mesh3D(mesh);
    free(mesh);
    return 0;
}
