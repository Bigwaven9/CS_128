#include <iostream>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

int main() {
  ElevationDataset dataset("example-data/ex_input_data/test1.dat", 5, 3);

  GrayscaleImage image(dataset);
  PathImage pathimage(image, dataset);
  pathimage.ToPpm("test1.output");
}