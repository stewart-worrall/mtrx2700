
#include <stdio.h>

#include "shape.h"
#include "movement.h"




const int NUMBER_OF_SHAPES = 16;


int main() {

  int counter = 0;


  struct shape shape_1 = generate_shape(SHAPE_SPHERE, 5, 5);

  struct shape shape_2;

  initialise_shape(&shape_2, SHAPE_CUBE, 3, 4);

  printf("%d, %d\n", shape_1.type, shape_2.type);


  struct shape shape_array[NUMBER_OF_SHAPES];

  for (counter = 0; counter < NUMBER_OF_SHAPES; counter++) {
    if (initialise_shape(&shape_array[counter], counter % 3, 3, 4)) {
      printf("new shape type %d\n", shape_array[counter].type);
    } else {
      printf("invalid shape %d\n", shape_array[counter].type);
    }
  }

  // slide the shapes
  printf("sliding the shapes by 1.5 units\n");
  for (counter = 0; counter < NUMBER_OF_SHAPES; counter++) {
    slide_shape(&shape_array[counter], 1.5);
    printf("shape %d of type %d is now at location %.2f\n", counter, shape_array[counter].type, shape_array[counter].location);
  }

  // roll the shapes
  printf("rolling the shapes by 2.5 units\n");
  for (counter = 0; counter < NUMBER_OF_SHAPES; counter++) {
    roll_shape(&shape_array[counter], 2.5);
    printf("shape %d of type %d is now at location %.2f\n", counter, shape_array[counter].type, shape_array[counter].location);
  }

}