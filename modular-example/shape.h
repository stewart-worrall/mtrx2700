//
// Created by stew on 13/04/21.
//

#ifndef MODULAR_EXAMPLE_SHAPE_H
#define MODULAR_EXAMPLE_SHAPE_H


const int SHAPE_SPHERE;
const int SHAPE_CUBE;
const int SHAPE_CONE;

#define true 1
#define false 0



struct shape {
  int dimension_1;
  int dimension_2;
  int type; // 0 = sphere, 1 = cube, 2 = cone
  float location;
  unsigned char is_initialised;
};


struct shape generate_shape(int type, int dimension_1, int dimension_2);

int initialise_shape(struct shape *_shape, int type, int dimension_1, int dimension_2);

#endif //MODULAR_EXAMPLE_SHAPE_H
