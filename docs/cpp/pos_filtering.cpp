/*
Copyright 2020-2020 Lucas Heitzmann Gabrielli.
This file is part of gdstk, distributed under the terms of the
Boost Software License - Version 1.0.  See the accompanying
LICENSE file or <http://www.boost.org/LICENSE_1_0.txt>
*/

#include <cstdio>

#include "gdstk.h"

using namespace gdstk;

int main(int argc, char* argv[]) {
    char lib_name[] = "library";
    Library lib = {.name = lib_name, .unit = 1e-6, .precision = 1e-9};

    char unit_cell_name[] = "Unit";
    Cell unit_cell = {.name = unit_cell_name};

    Polygon cross_ = cross(Vec2{0, 0}, 1, 0.2, 0, 0);
    unit_cell.polygon_array.append(&cross_);

    char main_cell_name[] = "Main";
    Cell main_cell = {.name = main_cell_name};
    lib.cell_array.append(&main_cell);

    double d = 2;
    Reference unit_refs[] = {
        {
            .type = ReferenceType::Cell,
            .cell = &unit_cell,
            .magnification = 1,
            .repetition = {RepetitionType::Rectangular, 11, 6, Vec2{d, d * sqrt(3)}},
        },
        {
            .type = ReferenceType::Cell,
            .cell = &unit_cell,
            .origin = Vec2{d / 2, d * sqrt(3) / 2},
            .magnification = 1,
            .repetition = {RepetitionType::Rectangular, 10, 5, Vec2{d, d * sqrt(3)}},
        },
    };
    main_cell.reference_array.append(unit_refs);
    main_cell.reference_array.append(unit_refs + 1);

    Array<Reference*> removed_references = {0};
    main_cell.flatten(removed_references);
    removed_references.clear();

    Array<Polygon*> txt = {0};
    text("PY", 8 * d, Vec2{0.5 * d, 0}, false, 1, 0, txt);
    Array<bool> test = {0};
    inside(main_cell.polygon_array, txt, ShortCircuit::Any, 1000, test);
    for (int64_t i = 0, j = 0; i < test.size; i++, j++) {
        if (test[i]) main_cell.polygon_array.remove(j--);
    }
    test.clear();

    main_cell.polygon_array.extend(txt);

    lib.write_gds("pos_filtering.gds", 0, NULL);
    return 0;
}
