//
// Created by stew on 13/04/21.
//

#include "shape.h"

const int SHAPE_SPHERE = 0;
const int SHAPE_CUBE = 1;
const int SHAPE_CONE = 2;


struct shape generate_shape(int type, int dimension_1, int dimension_2) {
  struct shape new_shape;

  new_shape.type = type;
  new_shape.dimension_1 = dimension_1;
  new_shape.dimension_2 = dimension_2;
  new_shape.location = 0.;
  new_shape.is_initialised = true;

  return new_shape;
}


// returns true for success, false for failure
int initialise_shape(struct shape *_shape, int type, int dimension_1, int dimension_2) {

  if (dimension_1 <= 0 || dimension_2 <= 0)
    return false;

  _shape->type = type;
  _shape->dimension_1 = dimension_1;
  _shape->dimension_2 = dimension_2;
  _shape->location = 0.;
  _shape->is_initialised = true;

  return true;
}