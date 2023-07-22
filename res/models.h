//
//  models.h
//  risklike
//
//  Created by Frank Collebrusco on 6/3/23.
//
//

#ifndef models_h
#define models_h

#include <vector>
#include "../lib/flgl/src/Vertex.h"

#define MESH_DEFINE_ASP \
const std::vector<Vertex> asp_vertices = {\
   Vertex(glm::vec3(-0.16015625f, 0.38671875f,   0.f), 	glm::vec2(0.33984375f, 0.88671875f)),	\
   Vertex(glm::vec3(0.16015625f, 0.38671875f,    0.f), 	glm::vec2(0.66015625f, 0.88671875f)),	\
   Vertex(glm::vec3(0.29296875f, 0.21484375f,    0.1f), glm::vec2(0.79296875f, 0.71484375f)),	\
   Vertex(glm::vec3(0.47265625f, -0.08984375f,   0.f), 	glm::vec2(0.97265625f, 0.41015625f)),	\
   Vertex(glm::vec3(0.36328125f, -0.48046875f,   0.f), 	glm::vec2(0.86328125f, 0.01953125f)),	\
   Vertex(glm::vec3(0.30078125f, -0.48828125f,   0.f), 	glm::vec2(0.80078125f, 0.01171875f)),	\
   Vertex(glm::vec3(0.30859375f, -0.44140625f,   0.f), 	glm::vec2(0.80859375f, 0.05859375f)),	\
   Vertex(glm::vec3(0.f, -0.44140625f,           0.1f), glm::vec2(0.5f, 0.05859375f)),			\
   Vertex(glm::vec3(-0.30859375f, -0.44140625f,  0.f), glm::vec2(0.19140625f, 0.05859375f)),	\
   Vertex(glm::vec3(-0.30078125f, -0.48828125f,  0.f), glm::vec2(0.19921875f, 0.01171875f)),	\
   Vertex(glm::vec3(-0.36328125f, -0.48046875f,  0.f), glm::vec2(0.13671875f, 0.01953125f)),	\
   Vertex(glm::vec3(-0.47265625f, -0.08984375f,  0.f), glm::vec2(0.02734375f, 0.41015625f)),	\
   Vertex(glm::vec3(-0.29296875f, 0.21484375f,   0.1f), glm::vec2(0.20703125f, 0.71484375f)),	\
   Vertex(glm::vec3(0.f, 0.046875f,              0.2f), glm::vec2(0.5f, 0.546875f))				\
};																								\
const std::vector<uint32_t> asp_elements = {	\
    0, 1, 13,									\
    0, 13, 12,									\
    1, 2, 13,									\
    11, 12, 13,									\
    13, 2, 3,									\
    11, 13, 8,									\
    8, 7, 13,									\
    7, 6, 13,									\
    13, 3, 6,									\
    3, 6, 4,									\
    11, 8, 10,									\
    10, 9, 8,									\
    4, 5, 6 									\
};												\
																	\
const ConstMesh asp_mesh(asp_vertices, asp_elements, TRIANGLES);	\

#endif /* models_h */
