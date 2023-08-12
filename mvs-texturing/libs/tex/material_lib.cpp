/*
 * Copyright (C) 2015, Nils Moehrle
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>

#include <mve/image_io.h>
#include <mve/util/exception.h>
#include <mve/util/file_system.h>

#include "material_lib.h"

void MaterialLib::save_to_files(std::string const& prefix) const {
  std::string filename = prefix + ".mtl";
  std::ofstream out(filename.c_str());
  std::cout << "Saving material lib to " << filename << std::endl;
  if (!out.good())
    throw util::FileException(filename, std::strerror(errno));

  std::string const name = util::fs::basename(prefix);

  for (Material const& material : *this) {
    std::string diffuse_map_postfix = "_" + material.name + "_map_Kd.png";
    out << "newmtl " << material.name << '\n'
        << "Ka 0.2 0.2 0.2" << '\n'
        << "Kd 0.8 0.8 0.8" << '\n'
        << "Ks 1.0 1.0 1.0" << '\n'
        << "d 1.0" << '\n'  // *Tr*ansparancy vs. *d*issolve: Tr = 1.0 - d
        << "Ns 75.0" << '\n'
        << "illum 2.0" << '\n'
        << "map_Kd " << name + diffuse_map_postfix << std::endl;
  }
  out.close();

  std::cout << "Saving diffuse maps..." << std::endl;

  for (Material const& material : *this) {
    std::string filename = prefix + "_" + material.name + "_map_Kd.png";
    mve::image::save_png_file(material.diffuse_map, filename);
  }
}
