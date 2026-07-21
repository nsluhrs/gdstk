#!/usr/bin/env python

# Copyright 2020 Lucas Heitzmann Gabrielli.
# This file is part of gdstk, distributed under the terms of the
# Boost Software License - Version 1.0.  See the accompanying
# LICENSE file or <http://www.boost.org/LICENSE_1_0.txt>

import pytest
import gdstk


def test_inside():
    ring = gdstk.ellipse((0, 0), 1, inner_radius=0.5, tolerance=1e-3)
    circle = gdstk.ellipse((0, 0), 0.5, tolerance=1e-3)

    points = [(0, 0), (0.2, 0), (-0.1, -0.8), (0.9, 0.7), (-0.4, 0.4)]
    truth_ring = tuple(0.25 <= p[0] ** 2 + p[1] ** 2 <= 1 for p in points)
    truth_circle = tuple(p[0] ** 2 + p[1] ** 2 <= 0.25 for p in points)

    assert ring.contain(*points) == truth_ring
    assert ring.contain_all(*points) == all(truth_ring)
    assert ring.contain_any(*points) == any(truth_ring)

    assert circle.contain(*points) == truth_circle
    assert circle.contain_all(*points) == all(truth_circle)
    assert circle.contain_any(*points) == any(truth_circle)

    assert gdstk.inside(points, [ring, circle]) == tuple(
        r or c for r, c in zip(truth_ring, truth_circle)
    )
    assert gdstk.all_inside(points, [ring, circle]) == all(
        [r or c for r, c in zip(truth_ring, truth_circle)]
    )
    assert gdstk.any_inside(points, [ring, circle]) == any(
        [r or c for r, c in zip(truth_ring, truth_circle)]
    )

    polys = [gdstk.rectangle((0, 0), (10, 10)), gdstk.rectangle((10, 0), (20, 10))]
    for pts, _any, _all in (
        ([(1, 1), (-1, -1)], True, False),
        ([(2, 2), (-2, 2), (2, -2)], True, False),
        ([(5, 5), (10, 5)], True, True),
        ([(-1, -1), (-2, -2)], False, False),
        ([(2, 3)], True, True),
    ):
        assert gdstk.any_inside(pts, polys) == _any
        assert gdstk.all_inside(pts, polys) == _all


def test_filter_holes():
    # Ring: 1 shell, 1 hole
    ring = gdstk.ellipse((0, 0), 5, inner_radius=3)
    shells, holes = gdstk.filter_holes([ring])
    assert len(shells) == 1
    assert len(holes) == 1
    assert shells[0].area() > holes[0].area()

    # Rectangle: no holes
    rect = gdstk.rectangle((0, 0), (10, 10))
    shells, holes = gdstk.filter_holes([rect])
    assert len(shells) == 1
    assert len(holes) == 0

    # Mesh with 2 holes: 1 shell, 2 holes
    outer = gdstk.rectangle((0, 0), (10, 10))
    hole1 = gdstk.rectangle((2, 2), (3, 3))
    hole2 = gdstk.rectangle((5, 5), (6, 6))
    mesh = gdstk.boolean(outer, [hole1, hole2], "not")
    shells, holes = gdstk.filter_holes(mesh)
    assert len(shells) == 1
    assert len(holes) == 2

    # Two separate rectangles: 2 shells, 0 holes
    r1 = gdstk.rectangle((0, 0), (5, 5))
    r2 = gdstk.rectangle((10, 10), (15, 15))
    shells, holes = gdstk.filter_holes([r1, r2])
    assert len(shells) == 2
    assert len(holes) == 0

    # Empty input
    shells, holes = gdstk.filter_holes([])
    assert len(shells) == 0
    assert len(holes) == 0

    # Layer and datatype
    shells, holes = gdstk.filter_holes([ring], layer=2, datatype=3)
    assert shells[0].layer == 2
    assert shells[0].datatype == 3
    assert holes[0].layer == 2
    assert holes[0].datatype == 3

    # Nested holes (ring with island inside the hole): should detect at least 1 shell and 1 hole
    outer_rect = gdstk.rectangle((-10, -10), (10, 10))
    inner_hole = gdstk.rectangle((-5, -5), (5, 5))
    island = gdstk.rectangle((-2, -2), (2, 2))
    nested = gdstk.boolean(outer_rect, [inner_hole], "not")
    nested = gdstk.boolean(nested, [island], "or")
    shells, holes = gdstk.filter_holes(nested)
    # After union: outer shell with a hole, and an island inside the hole
    assert len(shells) >= 1
    assert len(holes) >= 1

    # mapped=True: process each input element independently
    ring = gdstk.ellipse((0, 0), 5, inner_radius=3)
    rect = gdstk.rectangle((0, 0), (10, 10))
    results = gdstk.filter_holes([ring, rect], mapped=True)
    assert len(results) == 2
    assert len(results[0][0]) == 1  # ring has 1 shell
    assert len(results[0][1]) == 1  # ring has 1 hole
    assert len(results[1][0]) == 1  # rect has 1 shell
    assert len(results[1][1]) == 0  # rect has 0 holes

    # mapped=True with point sequences
    pts = [(0, 0), (10, 0), (10, 10), (0, 10)]
    results = gdstk.filter_holes([pts], mapped=True)
    assert len(results) == 1
    assert len(results[0][0]) == 1
    assert len(results[0][1]) == 0

    # mapped=True empty input
    results = gdstk.filter_holes([], mapped=True)
    assert len(results) == 0
