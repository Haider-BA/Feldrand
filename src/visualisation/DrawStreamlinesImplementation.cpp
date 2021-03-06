/* Copyright (C) 2013  Marco Heisig, Dominik Ernst

This file is part of Feldrand.

Feldrand is free software: you can redistribute it and/or modify it under the
terms of the GNU Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
details.

You should have received a copy of the GNU Affero General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "DrawStreamlinesImplementation.hpp"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace Feldrand {

namespace {
const size_t LINE_COUNT = 1000;
const size_t BORDER_PADDING = 3;
const float LINE_WIDTH = 1;
}

void DrawStreamlinesImplementation::operator()(
    const Grid<Vec2D<float>>& vector_field, const Grid<float>& scalar_field) {
  glScalef(1.0 / (vector_field.x() - 1), 1.0 / (vector_field.y() - 1), 1.0);
  calibrateColor(vector_field, scalar_field);

  vector<Vec2D<float>> seeds;

  srand(23123);
  for (size_t i = 0; i < LINE_COUNT; ++i) {
    Vec2D<float> point((float)(1 + rand() % 1000) / 999.0,
                       (float)(1 + rand() % 1000) / 999.0);
    seeds.push_back(point);
  }

  float depth = 0;
  for (auto& seed : seeds) {
    depth += 2.0 / LINE_COUNT;
    drawStreamline(seed, 0.5, vector_field, scalar_field, depth);
    drawStreamline(seed, -0.5, vector_field, scalar_field, depth);
  }
}

/* Calculates the nearest, positive intersection with the grid. Expects and
 * returns coordinates in grid space. */
Vec2D<float> step(Vec2D<float> origin, Vec2D<float> v) {
  // Determine nearest grid line
  float tx1 = (floor(origin.x - 1.0e-5) - origin.x) / v.x;
  float tx2 = (ceil(origin.x + 1.0e-5) - origin.x) / v.x;
  float ty1 = (floor(origin.y - 1.0e-5) - origin.y) / v.y;
  float ty2 = (ceil(origin.y + 1.0e-5) - origin.y) / v.y;

  float tx = (tx1 > tx2) ? tx1 : tx2;
  float ty = (ty1 > ty2) ? ty1 : ty2;

  float t = (tx < ty) ? tx : ty;

  return origin + v * t;
}

void addVertices(vector<float>& vertices, vector<float>& colors,
                 Vec2D<float> point, Vec2D<float> v1, QColor color,
                 float z = 0.0) {
  Vec2D<float> normal = v1;
  swap(normal.x, normal.y);
  normal.x *= -1;
  normal.normalize();

  Vec2D<float> p1 = point + normal * LINE_WIDTH;
  Vec2D<float> p2 = point - normal * LINE_WIDTH;

  for (int i = 0; i < 2; i++) {
    colors.push_back(color.redF());
    colors.push_back(color.greenF());
    colors.push_back(color.blueF());
    colors.push_back( (color.greenF() + color.redF()) *0.3f  );
  }

  vertices.push_back(p1.x);
  vertices.push_back(p1.y);
  vertices.push_back(z);

  vertices.push_back(p2.x);
  vertices.push_back(p2.y);
  vertices.push_back(z);
}

void DrawStreamlinesImplementation::drawStreamline(
    Vec2D<float> point, float dir, const Grid<Vec2D<float>>& vector_field,
    const Grid<float>& scalar_field, float z) {
  Vec2D<float> gridpoint{point.x * (vector_field.x() - 1),
                         point.y * (vector_field.y() - 1)};

  vector<float> vertices;
  vector<float> colors;

  Vec2D<float> v1 = interpolate(vector_field, point);

  v1 *= dir;
  addVertices(vertices, colors, gridpoint, v1,
              getColorAtPoint(vector_field, scalar_field, point), z);

  Vec2D<float> last_point = gridpoint;

  bool early_exit = false;
  for (size_t i = 0; i < vector_field.x() * 3 && early_exit == false; i++) {
    Vec2D<float> v1 =
        interpolate(vector_field, {gridpoint.x / (vector_field.x() - 1),
                                   gridpoint.y / (vector_field.y() - 1)});
    v1 *= dir;

    // Calculate the predictor point and get the direction at that point.
    Vec2D<float> predictor = step(gridpoint, v1);
    Vec2D<float> v2 =
        interpolate(vector_field, {predictor.x / (vector_field.x() - 1),
                                   predictor.y / (vector_field.y() - 1)});

    v2 *= dir;

    v1 = (v1 + v2) / 2.0;
    if (v1.x * v1.x + v1.y * v1.y < 0.0000001) early_exit = true;

    gridpoint = step(gridpoint, v1);

    if (gridpoint.x < BORDER_PADDING) {
      gridpoint.x = BORDER_PADDING;
      early_exit = true;
    }
    if (gridpoint.x > vector_field.x() - BORDER_PADDING) {
      gridpoint.x = vector_field.x() - BORDER_PADDING;
      early_exit = true;
    }
    if (gridpoint.y < BORDER_PADDING ||
        gridpoint.y > vector_field.y() - BORDER_PADDING)
      early_exit = true;

    auto point = Vec2D<float>{gridpoint.x / (vector_field.x() - 1),
                              gridpoint.y / (vector_field.y() - 1)};

    v1 = interpolate(vector_field, point);
    v1 = v1.normalize();
    v1 *= dir;
    if (early_exit || (gridpoint - last_point).normalize() * v1 < 0.99999999) {
      addVertices(vertices, colors, gridpoint, v1,
                  getColorAtPoint(vector_field, scalar_field, point), z);
      last_point = gridpoint;
    }
  }

  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, (float*)vertices.data());
  glColorPointer(4, GL_FLOAT, 0, (float*)colors.data());

  glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
}
