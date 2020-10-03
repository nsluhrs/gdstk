/*
Copyright 2020-2020 Lucas Heitzmann Gabrielli.
This file is part of gdstk, distributed under the terms of the
Boost Software License - Version 1.0.  See the accompanying
LICENSE file or <http://www.boost.org/LICENSE_1_0.txt>
*/

// Docstring should have 72 characters per line at maximum.

PyDoc_STRVAR(gdstk_module_doc, "Module for creation and manipulation of GDSII stream files.");

// Curve

PyDoc_STRVAR(curve_object_type_doc, R"!(Curve(xy, tolerance=0.01)

Curve object for construction of complex polygons.

The methods are loosely based on the definition of SVG paths.

Args:
    xy: Curve starting point. It can be a sequence of 2 numbers or a
      single complex value.
    tolerance: Tolerance used for calculating the polygonal
      approximation of the curve.

Examples:
    >>> curve = gdstk.Curve((3, 4), tolerance=1e-3)
    >>> curve.segment((1, 1), True)
    >>> curve.turn(1, -numpy.pi / 2)
    >>> curve.segment((1, -1), True)
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/init.*
       :align: center)!");

PyDoc_STRVAR(curve_object_points_doc, R"!(points() -> numpy.ndarray

Return the polygonal approximation of this curve.

Examples:
    >>> curve = gdstk.Curve((0, 0))
    >>> curve.segment([(1, 0), (0, 1)])
    >>> curve.points()
    array([[0., 0.],
           [1., 0.],
           [0., 1.]]))!");

PyDoc_STRVAR(curve_object_horizontal_doc, R"!(horizontal(x, relative=False) -> self

Append horizontal segments to this curve.

Args:
    x (number or sequence): End point x coordinates.
    relative: If ``True``, coordinates are relative to the last point.)!");

PyDoc_STRVAR(curve_object_vertical_doc, R"!(vertical(y, relative=False) -> self

Append vertical segments to this curve.

Args:
    y (number or sequence): End point y coordinates.
    relative: If ``True``, coordinates are relative to the last point.)!");

PyDoc_STRVAR(curve_object_segment_doc, R"!(segment(xy, relative=False) -> self

Append straight segments to this curve.

Args:
    xy: Segment end point. It can be a sequence of 2 numbers or a single
      complex. Multiple segments can be constructed by using a sequence
      of points.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> curve = gdstk.Curve((1, 0))
    >>> curve.segment((0, 1))
    >>> curve.segment([0j, -1+0j])
    >>> curve.segment([(0, -1), (2, -1)], True)
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/segment.*
       :align: center)!");

PyDoc_STRVAR(curve_object_cubic_doc, R"!(cubic(xy, relative=False) -> self

Append cubic Bézier curves to this curve.

Args:
    xy (sequence of points): Each set of 3 consecutive points is
      interpreted as 2 control points and an end point.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> curve = gdstk.Curve((0, 0), tolerance=1e-3)
    >>> curve.cubic([(1, -2), (2, -2), (3, 0)])
    >>> curve.cubic([(2.7, 1), (1.8, 1), (1.5, 0),
    ...              (1.3, -0.2), (0.3, -0.2), (0, 0)])
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/cubic.*
       :align: center)!");

PyDoc_STRVAR(curve_object_cubic_smooth_doc, R"!(cubic_smooth(xy, relative=False) -> self

Append smooth cubic Bézier curves to this curve.

The first control point is assumed to be the reflection of the last
control point of this curve with respect to its end point.

Args:
    xy (sequence of points): Each set of 2 consecutive points is
      interpreted as the second control point and an end point.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> curve = gdstk.Curve((0, 0), tolerance=1e-3)
    >>> curve.cubic([1 + 0j, 2.5 + 1.5j, 2 + 2j])
    >>> curve.cubic_smooth([1j, 0j])
    >>> polygon = gdstk.Polygon(curve.points())
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/cubic_smooth.*
       :align: center)!");

PyDoc_STRVAR(curve_object_quadratic_doc, R"!(quadratic(xy, relative=False) -> self

Append quadratic Bézier curves to this curve.

Args:
    xy (sequence of points): Each set of 2 consecutive points is
      interpreted as control point and an end point.
    relative: If ``True``, coordinates are relative to the last point.

See also:
    :meth:`gdstk.Curve.cubic`)!");

PyDoc_STRVAR(curve_object_quadratic_smooth_doc, R"!(quadratic_smooth(xy, relative=False) -> self

Append smooth quadratic Bézier curves to this curve.

The control point is assumed to be the reflection of the last control
point of this curve with respect to its end point.

Args:
    xy (sequence of points): Curve end points.
    relative: If ``True``, coordinates are relative to the last point.

See also:
    :meth:`gdstk.Curve.cubic_smooth`)!");

PyDoc_STRVAR(curve_object_bezier_doc, R"!(bezier(xy, relative=False) -> self

Append a Bézier curve to this curve.

Args:
    xy (sequence of points): Curve control points.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> points = [(4, 1), (4, 3), (0, 5), (-4, 3), (-4, -2), (0, -4),
    ...           (0, 0)]
    >>> curve = gdstk.Curve((0, 0))
    >>> curve.segment(points)
    >>> control_poly = gdstk.Polygon(curve.points(), datatype=1)
    >>> curve = gdstk.Curve((0, 0), tolerance=1e-3)
    >>> curve.bezier(points)
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/bezier.*
       :align: center)!");

PyDoc_STRVAR(
    curve_object_interpolation_doc,
    R"!(interpolation(points, angles=None, tension_in=1, tension_out=1, initial_curl=1, final_curl=1, cycle=False, relative=False) -> self

Append a smooth interpolating curve through the given points.

Use the Hobby algorithm [#]_ to calculate a smooth interpolating
curve made of cubic Bezier segments between each pair of points.  Angle
and tension parameters can be specified at each point, and the curve can
be open or closed.

Args:
    points (sequence[N] of points): Vertices in the interpolating curve.
    angles (``None`` or sequence[N + 1]): Tangent angles at each point
      (in radians). Angles defined as ``None`` are automatically
      calculated.
    tension_in (number or sequence[N + 1]): Tension parameter when
      arriving at each point. One value per point or a single value used
      for all points.
    tension_out (number or sequence[N + 1]): Tension parameter when
      leaving each point. One value per point or a single value used for
      all points.
    initial_curl: Ratio between the mock curvatures at the first point
      and at its neighbor. A value of 1 renders the first segment a good
      approximation for a circular arc. A value of 0 will better
      approximate a straight segment. It has no effect for closed curves
      or when an angle is defined for the first point.
    final_curl: Ratio between the mock curvatures at the last point and
      at its neighbor. It has no effect for closed curves or when an
      angle is defined for the first point.
    cycle: If ``True``, calculates control points for a closed curve,
      with an additional segment connecting the first and last points.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> points = [(4, 1), (4, 3), (0, 5), (-4, 3), (-4, -2), (0, -4)]
    >>> curve = gdstk.Curve((0, 0))
    >>> curve.segment(points)
    >>> control_poly_1 = gdstk.Polygon(curve.points(), datatype=1)
    >>> curve = gdstk.Curve((0, 0), tolerance=1e-3)
    >>> curve.interpolation(points, cycle=True)
    >>> polygon_1 = gdstk.Polygon(curve.points())

    >>> half_pi = numpy.pi / 2
    >>> angles = [half_pi, None, None, None, -half_pi, -half_pi, None]
    >>> curve = gdstk.Curve((4, -9))
    >>> curve.segment(points, relative=True)
    >>> control_poly_2 = gdstk.Polygon(curve.points(), datatype=1)
    >>> curve = gdstk.Curve((4, -9), tolerance=1e-3)
    >>> curve.interpolation(points, angles, cycle=True, relative=True)
    >>> polygon_2 = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/interpolation.*
       :align: center

.. [#] Hobby, J.D. "Smooth, easy to compute interpolating splines."
   *Discrete Comput Geom* 1, 123–140 (1986). `DOI: 10.1007/BF02187690
   <https://doi.org/10.1007/BF02187690>`_.)!");

PyDoc_STRVAR(curve_object_arc_doc, R"!(arc(radius, initial_angle, final_angle, rotation=0) -> self

Append an elliptical arc to this curve.

Args:
    radius (number or sequence[2]): Circular arc radius or elliptical
      arc radii.
    initial_angle: Starting angle (in radians).
    final_angle: Ending angle (in radians).
    rotation: Arc rotation.

Examples:
    >>> curve = gdstk.Curve((-0.6, 0), tolerance=1e-3)
    >>> curve.segment((1, 0), True)
    >>> curve.arc(1, 0, numpy.pi / 2)
    >>> polygon_1 = gdstk.Polygon(curve.points())

    >>> curve = gdstk.Curve((0.6, 0), tolerance=1e-3)
    >>> curve.segment((1, 0), True)
    >>> curve.arc((2 ** -0.5, 0.4), -numpy.pi / 4, 3 * numpy.pi / 4,
    ...           -numpy.pi / 4)
    >>> polygon_2 = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/arc.*
       :align: center)!");

PyDoc_STRVAR(curve_object_turn_doc, R"!(turn(radius, angle) -> self

Append a circular turn to this curve.

Args:
    radius: Circular arc radius.
    angle: Turning angle. Positive values turn counter clockwise and
      negative values, clockwise.)!");

PyDoc_STRVAR(curve_object_parametric_doc, R"!(parametric(curve_function, relative=True) -> self

Append a parametric curve to this curve.

Args:
    curve_function (callable): Function that defines the curve. Must be
      a function of one argument (that varies from 0 to 1) that returns
      a 2-element sequence or complex with the coordinates of the curve.
    relative: If ``True``, the return values of ``curve_function`` are
      used as offsets from the current path position, i.e., to ensure a
      continuous path, ``curve_function(0)`` must be (0, 0). Otherwise,
      they are used as absolute coordinates.

Examples:
    >>> pi = numpy.pi
    >>> def top(u):
    ...     x = 4 * u
    ...     y = 1 - numpy.cos(4 * pi * u)
    ...     return (x, y)
    ...
    >>> curve = gdstk.Curve((-2, 0), tolerance=1e-3)
    >>> curve.parametric(top)
    >>> curve.parametric(
    ...     lambda u: (4 - 2 * u ** 0.5) * numpy.exp(-1.5j * pi * u) - 4
    ... )
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/parametric.*
       :align: center)!");

PyDoc_STRVAR(curve_object_commands_doc, R"!(commands(*args) -> self

Parse commands to append sections to this curve.

Commands are single characters followed by a pre-defined number of
numerical arguments, according to the table below:

======= ======================= ===========================
Command Primitive               Arguments
======= ======================= ===========================
L/l     Line segment            x, y
H/h     Horizontal segment      x
V/v     Vertical segment        y
C/c     Cubic Bézier            x0, y0, x1, y1, x2, y2
S/s     Smooth cubic Bézier     x0, y0, x1, y1
Q/q     Quadratic Bézier        x0, y0, x1, y1
T/t     Smooth quadratic Bézier x, y
a       Circular turn           rad, ang
A       Circular arc            rad, ang0, ang1
E       Elliptical arc          rad0, rad1, ang0, ang1, rot
======= ======================= ===========================

Uppercase commands assume that coordinates are absolute, whereas the
lowercase versions assume they are relative to the previous endpoint.

Notes:
    The meaning and order of the arguments of all commands are identical
    to the corresponding method.

Examples:
    >>> curve = gdstk.Curve((0, 0), tolerance=1e-3)
    >>> curve.commands("l", 1, 1, "a", 1, -numpy.pi / 2, "l", 1, -1,
    ...                "S", 1, -2, 0, -2)
    >>> polygon = gdstk.Polygon(curve.points())

    .. image:: ../_static/curve/commands.*
       :align: center)!");

PyDoc_STRVAR(curve_object_tolerance_doc,
             R"!(Tolerance used for calculating the polygonal approximation of the curve.

Examples:
    >>> curve = gdstk.Curve((-2.5, 0), tolerance=1e-1)
    >>> curve.arc((2, 3), 0, numpy.pi)
    >>> polygon_1 = gdstk.Polygon(curve.points())
    >>> print(polygon_1.size)
    7
    >>> curve = gdstk.Curve((2.5, 0), tolerance=1e-3)
    >>> curve.arc((2, 3), 0, numpy.pi)
    >>> polygon_2 = gdstk.Polygon(curve.points())
    >>> print(polygon_2.size)
    62

    .. image:: ../_static/curve/tolerance.*
       :align: center)!");

// Polygon

PyDoc_STRVAR(polygon_object_type_doc, R"!(Polygon(points, layer=0, datatype=0)

Polygonal geometric object.

Args:
    points (sequence): Vertices of the polygon. Each element can be a
      pair of coordinates or a complex value.
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.

Examples:
    >>> polygon_1 = gdstk.Polygon([(0, 0), (1, 0), 1 + 1.5j, 1j])
    >>> polygon_2 = gsdkt.Polygon([0j, (-1, 1), (-1, 0)], 2, 3)

    .. image:: ../_static/polygon/init.*
       :align: center)!");

PyDoc_STRVAR(polygon_object_copy_doc, R"!(copy() -> gdstk.Polygon

Create a copy this polygon.

Returns:
    Copy of this polygon.)!");

PyDoc_STRVAR(polygon_object_area_doc, R"!(area() -> float

Polygon area.

Returns:
    float: Area of the polygon.)!");

PyDoc_STRVAR(polygon_object_bounding_box_doc, R"!(bounding_box() -> tuple

Calculate the polygon bounding box.

Returns:
    The lower-left and upper-right corners of the bounding box of the
    polygon: ``((min_x, min_y), (max_x, max_y))``.

Examples:
    >>> polygon = gdstk.Polygon([(0, 1), (1, 2), (3, -1)])
    >>> bbox = polygon.bounding_box()
    >>> print(bbox)
    ((0.0, -1.0), (3.0, 2.0))
    >>> polygon_bb = gdstk.rectangle(*bbox, datatype=1)

    .. image:: ../_static/polygon/bounding_box.*
       :align: center)!");

PyDoc_STRVAR(polygon_object_translate_doc, R"!(translate(dx, dy) -> self

Translate this polygon.

Args:
    dx: Translation in the x coordinate.
    dy: Translation in the y coordinate.)!");

PyDoc_STRVAR(polygon_object_scale_doc, R"!(scale(sx, sy=0, center=(0, 0)) -> self

Scale this polygon.

Args:
    sx: Scaling in the x direction.
    sy: Scaling in the y direction. If set to 0, ``sx`` is used instead.
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(polygon_object_mirror_doc, R"!(mirror(p1, p2=(0, 0)) -> self

Mirror this polygon across the line through ``p1`` and ``p2``.

Args:
    p1 (coordinate pair or complex): First point in the mirror line.
    p2 (coordinate pair or complex): Second point in the mirror line.)!");

PyDoc_STRVAR(polygon_object_rotate_doc, R"!(rotate(angle, center=(0, 0)) -> self

Rotate this polygon.

Args:
    angle: Rotation angle (in radians).
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(polygon_object_fillet_doc, R"!(fillet(radius, tolerance=0.01) -> self

Fillet the corners of this polygon.

Args:
    radius (number or sequence): Fillet radius. A sequence of values can
      be used to define the fillet radius for each vertex.
    tolerance: Tolerance used for calculating the polygonal
      approximation of the filleted corners.

Notes:
    The actual fillet radius for a given corner is the specified value
    or half the lenght of the shortest segment adjacent to that corner,
    whichever is smaller.

Examples:
    >>> points = [(0, 0), (1.2, 0), (1.2, 0.3), (1, 0.3), (1.5, 1),
    ...           (0, 1.5)]
    >>> polygon_1 = gdstk.Polygon(points, datatype=1)
    >>> polygon_2 = gdstk.Polygon(points).fillet(0.3, tolerance=1e-3)

    .. image:: ../_static/polygon/fillet.*
       :align: center)!");

PyDoc_STRVAR(polygon_object_fracture_doc, R"!(fracture(max_points=199, precision=0.001) -> self

Fracture this polygon into a list of polygons.

Args:
    max_points: Maximal number of vertices for each resulting polygon.
      Official GDSII documentation requires that all polygons have at
      most 199 vertices, but 8190 is usually supported by most software.
    precision: Desired vertex precision for fracturing.

Examples:
    >>> polygon = gdstk.racetrack((0, 0), 30, 60, 40, tolerance=1e-3)
    >>> poly_list = polygon.fracture()
    >>> print(len(poly_list))
    10
    >>> print([p.size for p in poly_list])
    [102, 103, 103, 101, 101, 102, 102, 103, 103, 102]

    .. image:: ../_static/polygon/fracture.*
       :align: center)!");

PyDoc_STRVAR(polygon_object_set_property_doc, R"!(set_property(attr, value) -> self

Set a GDSII property for this polygon.

Args:
    attr (number): Property number.
    value (str): Property value.)!");

PyDoc_STRVAR(polygon_object_get_property_doc, R"!(get_property(attr) -> str

Return a property of this polygon.

Args:
    attr (number): Property number.

Returns:
   str or None: Property value. If the property number does not exist,
   ``None`` is returned.)!");

PyDoc_STRVAR(polygon_object_delete_property_doc, R"!(delete_property(attr) -> self

Delete property of this polygon.

Args:
    attr (number): Property number.)!");

PyDoc_STRVAR(polygon_object_points_doc, R"!(Vertiecs of the polygon.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(polygon_object_layer_doc, R"!(Polygon layer.)!");

PyDoc_STRVAR(polygon_object_datatype_doc, R"!(Polygon data type.)!");

PyDoc_STRVAR(polygon_object_size_doc, R"!(Number of vertices in this polygon.

Notes:
    This attribute is read-only.)!");

// Reference

PyDoc_STRVAR(
    reference_object_type_doc,
    R"!(Reference(cell, origin=(0, 0), rotation=0, magnification=1, x_reflection=False, columns=1, rows=1, spacing=(0, 0))

Reference to another cell.

References are used to instance repetitive geometries across different
cells, optionally applying a transformation.

Args:
    cell (gdstk.Cell, gdstk.RawCell, str): referenced cell.
    origin: Insertion position of the referenced cell.
    rotation: Cell rotation angle (in radians).
    magnification: Geometry scaling for this reference.
    x_reflection: If ``True``, the geometry is reflected across the
      horizontal axis before rotation.
    columns: Number of repetitions along the horizontal direction.
    rows: Number of repetitions along the vertical direction.
    spacing: Distance between insertion points of adjacent columns and
      rows.

Examples:
    >>> polygons = gdstk.text("F", 10, (0, 0))
    >>> f_cell = gdstk.Cell("F_CELL")
    >>> f_cell.add(*polygons)
    >>> ref = gdstk.Reference(f_cell, rotation=numpy.pi / 2)
    >>> array_ref = gdstk.Reference(f_cell, columns=3, rows=2,
    ...                             spacing=(8, 10))

    .. image:: ../_static/reference/init.*
       :align: center

Notes:
    If ``cell`` is a str (cell name), operations on the referenced cell
    are not performed, such as computing the bounding box.)!");

PyDoc_STRVAR(reference_object_copy_doc, R"!(copy() -> gdstk.Reference

Create a copy this reference.

Returns:
    Copy of this reference.)!");

PyDoc_STRVAR(reference_object_bounding_box_doc, R"!(bounding_box() -> tuple

Calculate the bounding box of this reference.

Returns:
    The lower-left and upper-right corners of the bounding box of the
    polygon: ``((min_x, min_y), (max_x, max_y))``.

Notes:
    This operation can be slow because the precise bounding box
    calculation requires recursively querying the polygonal
    representations of all shapes created by this reference.

Examples:
    >>> polygons = gdstk.text("F", 10, (0, 0))
    >>> f_cell = gdstk.Cell("F_CELL")
    >>> f_cell.add(*polygons)
    >>> array_ref = gdstk.Reference(f_cell, rotation=numpy.pi / 4,
    ...                             columns=3, rows=2, spacing=(8, 10))
    >>> bbox = array_ref.bounding_box()
    >>> print(bbox)
    ((-12.816310409006173, 1.7677669529663689),
     (11.313708498984761, 27.66555281392367))
    >>> polygon_bb = gdstk.rectangle(*bbox, datatype=1)

    .. image:: ../_static/reference/bounding_box.*
       :align: center)!");

PyDoc_STRVAR(reference_object_set_property_doc, R"!(set_property(attr, value) -> self

Set a GDSII property for this reference.

Args:
    attr (number): Property number.
    value (str): Property value.)!");

PyDoc_STRVAR(reference_object_get_property_doc, R"!(get_property(attr) -> str

Return a property of this polygon.

Args:
    attr (number): Property number.

Returns:
   str or None: Property value. If the property number does not exist,
   ``None`` is returned.)!");

PyDoc_STRVAR(reference_object_delete_property_doc, R"!(delete_property(attr) -> self

Delete property of this polygon.

Args:
    attr (number): Property number.)!");

PyDoc_STRVAR(reference_object_cell_doc, R"!(Cell referenced by this object.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(reference_object_origin_doc, R"!(Reference origin.)!");

PyDoc_STRVAR(reference_object_rotation_doc, R"!(Reference rotation angle (in radians).)!");

PyDoc_STRVAR(reference_object_magnification_doc, R"!(Reference magnification.)!");

PyDoc_STRVAR(reference_object_x_reflection_doc, R"!(Reference reflection across the x axis.)!");

PyDoc_STRVAR(reference_object_columns_doc, R"!(Number of columns in the array.)!");

PyDoc_STRVAR(reference_object_rows_doc, R"!(Number of rows in the array.)!");

PyDoc_STRVAR(reference_object_spacing_doc, R"!(Spacing between copies in the array.)!");

// FlexPath

PyDoc_STRVAR(
    flexpath_object_type_doc,
    R"!(FlexPath(points, width, offset=0, joins="natural", ends="flush", bend_radius=0, bend_function=None, tolerance=1e-2, gdsii_path=False, scale_width=True, layer=0, datatype=0)

Flexible path creation.

FlexPath can be used to create single and multiple parallel paths with
controlled widths and offsets. Joins and end caps can be customized
freely and, if desired, bends can be automatically created to join path
segments continuously.

Adjacent sections are expected to be joined smoothly when at least one
of them is curved.  If that condition cannot be met,
:class:`gdstk.RobustPath` should be used instead.

Args:
    points: Single point or sequence of points that make up the path.
      Each point can be a pair of coordinates or a complex value.
    width (number or sequence): Width of the paths. If this is a
      sequence, its length defines the number of paths created.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path.
    joins: Definition for the joins. One of "natural", "miter", "bevel",
      "round", "smooth", or a callable. A callable must accept 6
      arguments (end point and direction vector for each edge adjacent
      to the join, the center of the join, and the path width) and
      return a sequence of points that define the join shape.
    ends: Definition for the end caps. One of "flush", "extended",
      "round", "smooth", a 2-tuple, or a callable. A 2-tuple defines the
      extension length on both ends of the path. A callable must accept
      4 arguments (cap end point and direction for both path sides) and
      return a sequence of points that define the cap shape.
    bend_radius (number or sequence): If a positive number, path
      segments are joined by a bend shape (defaults to a circular arc)
      when possible.
    bend_function (callable): A callable that takes 4 arguments (radius,
      initial and final angles, and the bend center) and returns a
      sequence of points defining the bend shape.
    tolerance: Tolerance used for calculating the polygonal
      approximation of the paths.
    gdsii_path: If ``True``, the paths will be stored as GDSII path
      elements. They require less memory, but do not support "smooth" or
      callable joins and end caps, or width changes along the path.
    scale_width: If ``False``, the path widths are not scaled when
      transforming this path.
    layer: GDSII layer number assigned to this path.
    datatype: GDSII data type number assigned to this path.

Notes:
    If ``width`` is a number and ``offset`` a sequence, the number of
    parallel paths is defined by the latter.

    Arguments ``joins``, ``ends``, ``bend_radius``, ``bend_function``,
    ``layer``, and ``datatype`` can also be lists with one definition
    for each path created.

Examples:
    >>> path = gdstk.FlexPath(
    ...     [(0, 5), (0, 0), (5, 0), (15, 10), (15, -5)],
    ...     [0.8, 0.8, 0.8, 0.8],
    ...     1.0,
    ...     joins=["natural", "bevel", "miter", "round"],
    ...     ends=["flush", "extended", (0.4, 0.8), "round"],
    ...     layer=[0, 1, 2, 3],
    ... )

    .. image:: ../_static/flexpath/init.*
       :align: center

    >>> points = [(0, 8), (0, 0), (8, 0), (18, 13), (18, -8)]
    >>> path_1 = gdstk.FlexPath(points , 1, datatype=1)
    >>> path_2 = gdstk.FlexPath(points , 1, bend_radius=3)

    .. image:: ../_static/flexpath/init0.*
       :align: center

    >>> def custom_broken_join(p0, v0, p1, v1, center, width):
    ...     p0 = numpy.array(p0)
    ...     v0 = numpy.array(v0)
    ...     p1 = numpy.array(p1)
    ...     v1 = numpy.array(v1)
    ...     center = numpy.array(center)
    ...     # Calculate intersection point p between lines defined by
    ...     # p0 + u0 * v0 (for all u0) and p1 + u1 * v1 (for all u1)
    ...     den = v1[1] * v0[0] - v1[0] * v0[1]
    ...     lim = 1e-12 * ((v0[0] ** 2 + v0[1] ** 2) *
    ...                    (v1[0] ** 2 + v1[1] ** 2))
    ...     if den ** 2 < lim:
    ...         # Lines are parallel: use mid-point
    ...         u0 = u1 = 0
    ...         p = 0.5 * (p0 + p1)
    ...     else:
    ...         dx = p1[0] - p0[0]
    ...         dy = p1[1] - p0[1]
    ...         u0 = (v1[1] * dx - v1[0] * dy) / den
    ...         u1 = (v0[1] * dx - v0[0] * dy) / den
    ...         p = 0.5 * (p0 + v0 * u0 + p1 + v1 * u1)
    ...     if u0 <= 0 and u1 >= 0:
    ...         # Inner corner
    ...         return [p]
    ...     # Outer corner
    ...     return [p0, center, p1]
    >>> def custom_pointy_end(p0, v0, p1, v1):
    ...     p0 = numpy.array(p0)
    ...     v0 = numpy.array(v0)
    ...     p1 = numpy.array(p1)
    ...     v1 = numpy.array(v1)
    ...     r = 0.5 * numpy.sqrt(numpy.sum((p0 - p1) ** 2))
    ...     v0 /= numpy.sqrt(numpy.sum(v0 ** 2))
    ...     v1 /= numpy.sqrt(numpy.sum(v1 ** 2))
    ...     return [p0, 0.5 * (p0 + p1) + 0.5 * (v0 - v1) * r, p1]
    >>> path = gdstk.FlexPath(
    ...     [(0, 5), (0, 0), (5, 0), (15, 10), (15, -5)],
    ...     3,
    ...     joins=custom_broken_join,
    ...     ends=custom_pointy_end,
    ... )

    .. image:: ../_static/flexpath/init1.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_copy_doc, R"!(copy() -> gdstk.FlexPath

Create a copy this flexpath.

Returns:
    Copy of this flexpath.)!");

PyDoc_STRVAR(flexpath_object_spine_doc, R"!(spine() -> numpy.ndarray

Central path spine.

Returns:
    Copy of the points that make up the path at zero offset.)!");

PyDoc_STRVAR(flexpath_object_widths_doc, R"!(widths() -> numpy.ndarray

Widths of all paths at every point.

Returns:
    The widths of each path at each point.)!");

PyDoc_STRVAR(flexpath_object_offsets_doc, R"!(offsets() -> numpy.ndarray

Offsets of all paths at every point.

Returns:
    The offsets of each path at each point.)!");

PyDoc_STRVAR(flexpath_object_to_polygons_doc, R"!(to_polygons() -> list

Calculate the polygonal representations of this path.

Returns:
    The polygonal contours defined by this path.)!");

PyDoc_STRVAR(flexpath_object_set_layers_doc, R"!(set_layers(*layers) -> self

Sets the layers for all paths.

Args:
    layers: GDSII layer numbers for all paths.)!");

PyDoc_STRVAR(flexpath_object_set_datatypes_doc, R"!(set_datatypes(*datatypes) -> self

Sets the datatypes for all paths.

Args:
    datatypes: GDSII data type numbers for all paths.)!");

PyDoc_STRVAR(flexpath_object_horizontal_doc,
             R"!(horizontal(x, width=None, offset=None, relative=False) -> self

Append horizontal segments to this path.

Args:
    x (number or sequence): End point x coordinates.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    If ``x`` is a sequence, changes in width and offset are split
    equally among segments.

Examples:
    >>> path = gdstk.FlexPath([(0, 0)], 0.2)
    >>> path.horizontal(2, width=0.4, relative=True)
    >>> path.horizontal(2, offset=[0.4], relative=True)
    >>> path.horizontal(2, relative=True)
    >>> print(path.spine())
    ... [[0. 0.]
    ...  [2. 0.]
    ...  [4. 0.]
    ...  [6. 0.]]

    .. image:: ../_static/flexpath/horizontal.*
       :align: center

See also:
    :meth:`gdstk.FlexPath.segment`)!");

PyDoc_STRVAR(flexpath_object_vertical_doc,
             R"!(vertical(y, width=None, offset=None, relative=False) -> self

Append vertical segments to this path.

Args:
    y (number or sequence): End point y coordinates.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    If ``y`` is a sequence, changes in width and offset are split
    equally among segments.

See also:
    :meth:`gdstk.FlexPath.segment`, :meth:`gdstk.FlexPath.horizontal`)!");

PyDoc_STRVAR(flexpath_object_segment_doc,
             R"!(segment(xy, width=None, offset=None, relative=False) -> self

Append straight segments to this path.

Args:
    xy: Segment end point or sequence of end points. Each point can be a
      pair of coordinates or a complex value.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    If ``xy`` is a sequence, changes in width and offset are split
    equally among segments.

Examples:
    >>> points = [(1, 0), (1, 1), (-1, 1), (-1, -1), (1, -1)]
    >>> path_1 = gdstk.FlexPath((0, 0), 0.2)
    >>> path_1.segment(points, 0.6)
    >>> path_2 = gdstk.FlexPath((3, 0), [0.1, 0.1], 0.2)
    >>> path_2.segment(points, offset=0.6, relative=True)

    .. image:: ../_static/flexpath/segment.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_cubic_doc,
             R"!(cubic(xy, width=None, offset=None, relative=False) -> self

Append cubic Bézier curves to this path.

Args:
    xy (sequence of points): Each set of 3 consecutive points is
      interpreted as 2 control points and an end point.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Changes in width and offset are split equally among curve parts
    defined by ``xy``.

Examples:
    >>> path = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.cubic([(0, 1), (1, 1), (1, 0)])
    >>> path.cubic([(1, -1), (2, -1), (2.5, -0.5),
    ...             (3, 0), (3, 1), (2, 1)], width=0.5)

    .. image:: ../_static/flexpath/cubic.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_cubic_smooth_doc,
             R"!(cubic_smooth(xy, width=None, offset=None, relative=False) -> self

Append smooth cubic Bézier curves to this path.

The first control point is assumed to be the reflection of the last
control point of this path with respect to its end point.

Args:
    xy (sequence of points): Each set of 2 consecutive points is
      interpreted as the second control points and an end point.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Changes in width and offset are split equally among curve parts
    defined by ``xy``.

Examples:
    >>> path = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.cubic([(0, 1), (1, 1), (1, 0)])
    >>> path.cubic_smooth([(2, -1), (2.5, -0.5), (3, 1), (2, 1)],
    ...                   width=0.5)

    .. image:: ../_static/flexpath/cubic_smooth.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_quadratic_doc,
             R"!(quadratic(xy, width=None, offset=None, relative=False) -> self

Append quadratic Bézier curves to this path.

Args:
    xy (sequence of points): Each set of 2 consecutive points is
      interpreted as control point and an end point.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Changes in width and offset are split equally among curve parts
    defined by ``xy``.

See also:
    :meth:`gdstk.FlexPath.cubic`)!");

PyDoc_STRVAR(flexpath_object_quadratic_smooth_doc,
             R"!(quadratic_smooth(xy, width=None, offset=None, relative=False) -> self

Append smooth quadratic Bézier curves to this path.

The control point is assumed to be the reflection of the last control
point of this curve with respect to its end point.

Args:
    xy (sequence of points): Curve end points.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Changes in width and offset are split equally among curve parts
    defined by ``xy``.

See also:
    :meth:`gdstk.FlexPath.cubic_smooth`)!");

PyDoc_STRVAR(flexpath_object_bezier_doc,
             R"!(bezier(xy, width=None, offset=None, relative=False) -> self

Append a Bézier curve to this path.

Args:
    xy (sequence of points): Curve control points.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> path = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.bezier([(4, 1), (4, 3), (0, 5),
    ...              (-4, 3), (-4, -2), (0, -4)])

    .. image:: ../_static/flexpath/bezier.*
       :align: center)!");

PyDoc_STRVAR(
    flexpath_object_intepolation_doc,
    R"!(interpolation(points, angles=None, tension_in=1, tension_out=1, initial_curl=1, final_curl=1, cycle=False, width=None, offset=None, relative=True) -> self

Append a smooth interpolating curve through the given points.

Use the Hobby algorithm [#]_ to calculate a smooth interpolating
path made of cubic Bezier segments between each pair of points.  Angle
and tension parameters can be specified at each point, and the path can
be open or closed.

Args:
    points (sequence[N] of points): Vertices in the interpolating path.
    angles (``None`` or sequence[N + 1]): Tangent angles at each point
      (in radians). Angles defined as ``None`` are automatically
      calculated.
    tension_in (number or sequence[N + 1]): Tension parameter when
      arriving at each point. One value per point or a single value used
      for all points.
    tension_out (number or sequence[N + 1]): Tension parameter when
      leaving each point. One value per point or a single value used for
      all points.
    initial_curl: Ratio between the mock curvatures at the first point
      and at its neighbor. A value of 1 renders the first segment a good
      approximation for a circular arc. A value of 0 will better
      approximate a straight segment. It has no effect for closed paths
      or when an angle is defined for the first point.
    final_curl: Ratio between the mock curvatures at the last point and
      at its neighbor. It has no effect for closed paths or when an
      angle is defined for the first point.
    cycle: If ``True``, calculates control points for a closed path,
      with an additional segment connecting the first and last points.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> half_pi = numpy.pi / 2
    >>> points = [(4, 1), (4, 3), (0, 5), (-4, 3), (-4, -2), (0, -4)]
    >>> angles = [half_pi, None, None, None, -half_pi, -half_pi, None]
    >>> path_1 = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path_1.interpolation(points, cycle=True)
    >>> path_2 = gdstk.FlexPath((6, -8), 0.2, tolerance=1e-3)
    >>> path_2.interpolation(points, angles, cycle=True, relative=True)

    .. image:: ../_static/flexpath/interpolation.*
       :align: center

.. [#] Hobby, J.D. "Smooth, easy to compute interpolating splines."
   *Discrete Comput Geom* 1, 123–140 (1986). `DOI: 10.1007/BF02187690
   <https://doi.org/10.1007/BF02187690>`_.)!");

PyDoc_STRVAR(
    flexpath_object_arc_doc,
    R"!(arc(radius, initial_angle, final_angle, rotation=0, width=None, offset=None) -> self

Append an elliptical arc to this path.

Args:
    radius (number or sequence[2]): Circular arc radius or elliptical
      arc radii.
    initial_angle: Starting angle (in radians).
    final_angle: Ending angle (in radians).
    rotation: Arc rotation.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.

Examples:
    >>> path = gdstk.FlexPath((0, 0), [0.2, 0.3], 0.4, tolerance=1e-3)
    >>> path.vertical(5)
    >>> path.arc(2.5, numpy.pi, 0)
    >>> path.arc(5, -numpy.pi, -numpy.pi / 2)

    .. image:: ../_static/flexpath/arc.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_turn_doc, R"!(turn(radius, angle, width=None, offset=None) -> self

Append a circular turn to this path.

Args:
    radius: Circular arc radius.
    angle: Turning angle. Positive values turn counter clockwise and
      negative values, clockwise.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.)!");

PyDoc_STRVAR(flexpath_object_parametric_doc,
             R"!(parametric(path_function, width=None, offset=None, relative=True) -> self

Append a parametric curve to this path.

Args:
    path_function (callable): Function that defines the path. Must be a
      function of one argument (that varies from 0 to 1) that returns a
      2-element sequence or complex with the coordinates of the path.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, the return values of ``path_function`` are
      used as offsets from the current path position, i.e., to ensure a
      continuous path, ``path_function(0)`` must be (0, 0). Otherwise,
      they are used as absolute coordinates.

Examples:

    >>> def spiral(u):
    ...     rad = 2 * u ** 0.5
    ...     ang = 3 * numpy.pi * u
    ...     return (rad * numpy.cos(ang), rad * numpy.sin(ang))
    >>> path = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.parametric(spiral)

    .. image:: ../_static/flexpath/parametric.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_commands_doc, R"!(commands(path_commands...) -> self

Append sections to this path according to commands.

Commands are single characters followed by a pre-defined number of
numerical arguments, according to the table below:

======= ======================= ===========================
Command Primitive               Arguments
======= ======================= ===========================
L/l     Line segment            x, y
H/h     Horizontal segment      x
V/v     Vertical segment        y
C/c     Cubic Bézier            x0, y0, x1, y1, x2, y2
S/s     Smooth cubic Bézier     x0, y0, x1, y1
Q/q     Quadratic Bézier        x0, y0, x1, y1
T/t     Smooth quadratic Bézier x, y
a       Circular turn           rad, ang
A       Circular arc            rad, ang0, ang1
E       Elliptical arc          rad0, rad1, ang0, ang1, rot
======= ======================= ===========================

Uppercase commands assume that coordinates are absolute, whereas the
lowercase versions assume they are relative to the previous endpoint.

Notes:
    The meaning and order of the arguments of all commands are identical
    to the corresponding method.

Examples:
    >>> path = gdstk.FlexPath((0, 0), [0.2, 0.4, 0.2], 0.5,
    ...                       tolerance=1e-3)
    >>> path.commands("l", 3, 4,
    ...               "A", 2, numpy.arctan2(3, -4), numpy.pi / 2,
    ...               "h", 0.5,
    ...               "a", 3, -numpy.pi)

    .. image:: ../_static/flexpath/commands.*
       :align: center)!");

PyDoc_STRVAR(flexpath_object_translate_doc, R"!(translate(dx, dy) -> self

Translate this path.

Args:
    dx: Translation in the x coordinate.
    dy: Translation in the y coordinate.)!");

PyDoc_STRVAR(flexpath_object_scale_doc, R"!(scale(s, center=(0, 0)) -> self

Scale this path.

Args:
    s: Scaling factor.
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(flexpath_object_mirror_doc, R"!(mirror(p1, p2=(0, 0)) -> self

Mirror this path across the line through `p1` and `p2`.

Args:
    p1 (coordinate pair or complex): First point in the mirror line.
    p2 (coordinate pair or complex): Second point in the mirror line.)!");

PyDoc_STRVAR(flexpath_object_rotate_doc, R"!(rotate(angle, center=(0, 0)) -> self

Rotate this path.

Args:
    angle: Rotation angle (in radians).
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(flexpath_object_set_property_doc, R"!(set_property(attr, value) -> self

Set a GDSII property for this path.

Args:
    attr (number): Property number.
    value (str): Property value.)!");

PyDoc_STRVAR(flexpath_object_get_property_doc, R"!(get_property(attr) -> str

Return a property of this path.

Args:
    attr (number): Property number.

Returns:
   str or None: Property value. If the property number does not exist,
   ``None`` is returned.)!");

PyDoc_STRVAR(flexpath_object_delete_property_doc, R"!(delete_property(attr) -> self

Delete property of this path.

Args:
    attr (number): Property number.)!");

PyDoc_STRVAR(flexpath_object_layers_doc, R"!(FlexPath layer.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(flexpath_object_datatypes_doc, R"!(FlexPath data type.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(flexpath_object_num_paths_doc, R"!(Number of paths.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(flexpath_object_size_doc, R"!(Number of points in the path spine.

Notes:
    This attribute is read-only.)!");

// RobustPath

PyDoc_STRVAR(
    robustpath_object_type_doc,
    R"!(RobustPath(initial_point, width, offset=0, ends="flush",tolerance=1e-2, max_evals=1000, gdsii_path=False, scale_width=True, layer=0, datatype=0)

Robust path creation.

RobusPath can be used to create single and multiple parallel paths with
parametrized widths and offsets. End caps can be customized freely.
Intersections between adjacent sections are numerically determined so
that curved sections do not need to be joined smoothly.

Args:
    initial_point (coordinate pair or complex): Starting point of the
      path.
    width (number or sequence): Width of the paths. If this is a
      sequence, its length defines the number of paths created.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path.
    ends: Definition for the end caps. One of "flush", "extended",
      "round", "smooth", a 2-tuple, or a callable. A 2-tuple defines the
      extension length on both ends of the path. A callable must accept
      4 arguments (cap end point and direction for both path sides) and
      return a sequence of points that define the cap shape.
    tolerance: Tolerance used for calculating the polygonal
      approximation of the paths.
    max_evals: Maximal number of path evaluations per section.  Used for
      intersection finding at joins and to create the polygonal
      approximation for each section.
    gdsii_path: If ``True``, the paths will be stored as GDSII path
      elements. They require less memory, but do not support "smooth" or
      callable joins and end caps, or width changes along the path.
    scale_width: If ``False``, the path widths are not scaled when
      transforming this path.
    layer: GDSII layer number assigned to this path.
    datatype: GDSII data type number assigned to this path.

Notes:
    If ``width`` is a number and ``offset`` a sequence, the number of
    parallel paths is defined by the latter.

    Arguments ``ends``, ``layer``, and ``datatype`` can also be lists
    with one definition for each path created.

Examples: 
    >>> fpath = gdstk.FlexPath((0, 0), 0.5, tolerance=1e-3)
    >>> fpath.arc(1, 0, numpy.pi/2)
    >>> fpath.arc(1, 0, -numpy.pi/2)
    >>> rpath = gdstk.RobustPath((3, 0), 0.5, tolerance=1e-3)
    >>> rpath.arc(1, 0, numpy.pi/2)
    >>> rpath.arc(1, 0, -numpy.pi/2)

    .. image:: ../_static/robustpath/init.*
       :align: center

    >>> path = gdstk.RobustPath((0, 0),
    ...     [0.8, 0.8, 0.8, 0.8],
    ...     1.0,
    ...     ends=["flush", "extended", (0.4, 0.8), "round"],
    ...     tolerance=1e-3,
    ...     layer=[0, 1, 2, 3],
    ... )
    >>> path.horizontal(5)

    .. image:: ../_static/robustpath/init1.*
       :align: center)!");

PyDoc_STRVAR(robustpath_object_copy_doc, R"!(copy() -> gdstk.RobustPath

Create a copy this robustpath.

Returns:
    Copy of this robustpath.)!");

PyDoc_STRVAR(robustpath_object_spine_doc, R"!(spine() -> numpy.ndarray

Central path spine.

Returns:
    Copy of the points that make up the path at zero offset.)!");

PyDoc_STRVAR(robustpath_object_widths_doc, R"!(widths(u, from_below=True) -> numpy.ndarray

Calculate the width of this path.

Args:
    u (number): Where in the path to calculate the width. The value must
      be in the range 0 thru :attr:`gdstk.RobustPath.size`, inclusive.
    from_below: If there is a discontinuity at ``u``, use the value
      approaching from below.

Returns:
    The widths of each path at ``u``.)!");

PyDoc_STRVAR(robustpath_object_offsets_doc, R"!(offsets(u, from_below=True) -> numpy.ndarray

Calculate the offset of this path.

Args:
    u (number): Where in the path to calculate the width. The value must
      be in the range 0 thru :attr:`gdstk.RobustPath.size`, inclusive.
    from_below: If there is a discontinuity at ``u``, use the value
      approaching from below.

Returns:
    The offsets of each path at ``u``.)!");

PyDoc_STRVAR(robustpath_object_position_doc, R"!(position(u, from_below=True) -> numpy.ndarray

Calculate the position of this path.

Args:
    u (number): Where in the path to calculate the position. The value
      must be in the range 0 thru :attr:`gdstk.RobustPath.size`,
      inclusive.
    from_below: If there is a discontinuity at ``u``, use the value
      approaching from below.

Returns:
    The spine position of the path at ``u``.)!");

PyDoc_STRVAR(robustpath_object_gradient_doc, R"!(gradient(u, from_below=True) -> numpy.ndarray

Calculate the gradient of this path.

Args:
    u (number): Where in the path to calculate the position. The value
      must be in the range 0 thru :attr:`gdstk.RobustPath.size`,
      inclusive.
    from_below: If there is a discontinuity at ``u``, use the value
      approaching from below.

Returns:
    The spine gradient of the path at ``u``.)!");

PyDoc_STRVAR(robustpath_object_to_polygons_doc, R"!(to_polygons() -> list

Calculate the polygonal representations of this path.

Returns:
    The polygonal contours defined by this path.)!");

PyDoc_STRVAR(robustpath_object_set_layers_doc, R"!(set_layers(*layers) -> self

Sets the layers for all paths.

Args:
    layers: GDSII layer numbers for all paths.)!");

PyDoc_STRVAR(robustpath_object_set_datatypes_doc, R"!(set_datatypes(*datatypes) -> self

Sets the datatypes for all paths.

Args:
    datatypes: GDSII data type numbers for all paths.)!");

PyDoc_STRVAR(robustpath_object_horizontal_doc,
             R"!(horizontal(x, width=None, offset=None, relative=False) -> self

Append a horizontal segment to this path.

Args:
    x (number): End point x coordinate.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

See also:
    :meth:`gdstk.RobustPath.segment`)!");

PyDoc_STRVAR(robustpath_object_vertical_doc,
             R"!(vertical(y, width=None, offset=None, relative=False) -> self

Append a vertical segment to this path.

Args:
    y (number): End point x coordinate.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

See also:
    :meth:`gdstk.RobustPath.segment`)!");

PyDoc_STRVAR(robustpath_object_segment_doc,
             R"!(segment(xy, width=None, offset=None, relative=False) -> self

Append a straight segment to this path.

Args:
    xy (coordinate pair or complex): Segment end point.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

Examples:
    >>> path = gdstk.RobustPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.segment((5, 0), 1.0)
    >>> path.segment((5, 3), (0.2, "constant"))
    >>> path.segment((0, 3), (1.2, "smooth"))
    >>> path.segment(
    ...     (0, 7),
    ...     lambda u: 0.2 + 0.8 * numpy.cos(2 * numpy.pi * u) ** 2
    ... )

    .. image:: ../_static/robustpath/segment.*
       :align: center

    >>> path = gdstk.RobustPath((0, 0), [0.2, 0.2], 0.3, tolerance=1e-3)
    >>> path.segment((5, 0), offset=0.8)
    >>> path.segment((5, 3), offset=(0.3, "constant"))
    >>> path.segment((0, 3), offset=(1.0, "smooth"))
    >>> path.segment((0, 7), offset=[
    ...     lambda u: -0.2 - 0.8 * numpy.cos(2 * numpy.pi * u) ** 2,
    ...     lambda u: 0.2 + 0.8 * numpy.cos(2 * numpy.pi * u) ** 2
    ... ])

    .. image:: ../_static/robustpath/segment1.*
       :align: center)!");

PyDoc_STRVAR(robustpath_object_cubic_doc,
             R"!(cubic(xy, width=None, offset=None, relative=False) -> self

Append a cubic Bézier curve to this path.

Args:
    xy (sequence of 3 points): Control points and end point for the
      Bézier. Each point can be a coordinate pair or a complex.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

Examples:
    >>> path = gdstk.RobustPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.cubic([(0.5, 0.8), (0.5, 2.2), (0, 3)])
    >>> path.cubic([(0.8, -0.5), (2.2, -0.5), (3, 0)], relative=True)
    >>> path.cubic([(-0.5, -0.8), (-0.5, -2.2), (0, -3)], relative=True)

    .. image:: ../_static/robustpath/cubic.*
       :align: center

See also:
    :meth:`gdstk.RobustPath.segment`)!");

PyDoc_STRVAR(robustpath_object_cubic_smooth_doc,
             R"!(cubic_smooth(xy, width=None, offset=None, relative=False) -> self

Append a smooth cubic Bézier curve to this path.

The first control point of the Bézier is such that the gradient of the
path is continuous.

Args:
    xy (sequence of 2 points): Second control point and end point for
      the Bézier. Each can be a coordinate pair or a complex.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

Examples:
    >>> path = gdstk.RobustPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.cubic([(0.5, 0.8), (0.5, 2.2), (0, 3)])
    >>> path.cubic_smooth([(3.5, 0.8), (3, 0)], relative=True)
    >>> path.cubic_smooth([(-0.5, -2.2), (0, -3)], relative=True)

    .. image:: ../_static/robustpath/cubic_smooth.*
       :align: center

See also:
    :meth:`gdstk.RobustPath.segment`, :meth:`gdstk.RobustPath.cubic`)!");

PyDoc_STRVAR(robustpath_object_quadratic_doc,
             R"!(quadratic(xy, width=None, offset=None, relative=False) -> self

Append a quadratic Bézier curve to this path.

Args:
    xy (sequence of 2 points): Control point and end point for the
      Bézier. Each point can be a coordinate pair or a complex.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

See also:
    :meth:`gdstk.RobustPath.segment`, :meth:`gdstk.RobustPath.cubic`)!");

PyDoc_STRVAR(robustpath_object_quadratic_smooth_doc,
             R"!(quadratic_smooth(xy, width=None, offset=None, relative=False) -> self

Append a smooth quadratic Bézier curve to this path.

The control point of the Bézier is such that the gradient of the path is
continuous.

Args:
    xy (coordinate pair or complex): End point for the Bézier.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

See also:
    :meth:`gdstk.RobustPath.segment`,
    :meth:`gdstk.RobustPath.cubic_smooth`)!");

PyDoc_STRVAR(robustpath_object_bezier_doc,
             R"!(bezier(xy, width=None, offset=None, relative=False) -> self

Append a Bézier curve to this path.

Args:
    xy (sequence of points): Control points for the Bézier. Each point
      can be a coordinate pair or a complex.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Notes:
    Arguments ``width`` and ``offset`` can also be lists with one
    definition for each path.

    If ``offset`` is a single number or tuple, it is treated as the
    distance between adjacent paths.

Examples:
    >>> path = gdstk.RobustPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.bezier(
    ...     [(4, 1), (4, 3), (0, 5), (-4, 3), (-4, -2), (0, -4)],
    ...     width=lambda u: 0.2 + 0.8 * u ** 2,
    ... )

    .. image:: ../_static/robustpath/bezier.*
       :align: center

See also:
    :meth:`gdstk.RobustPath.segment`)!");

PyDoc_STRVAR(
    robustpath_object_intepolation_doc,
    R"!(interpolation(points, angles=None, tension_in=1, tension_out=1, initial_curl=1, final_curl=1, cycle=False, width=None, offset=None, relative=True) -> self

Append a smooth interpolating curve through the given points.

Use the Hobby algorithm [#]_ to calculate a smooth interpolating
path made of cubic Bezier segments between each pair of points.  Angle
and tension parameters can be specified at each point, and the path can
be open or closed.

Args:
    points (sequence[N] of points): Vertices in the interpolating path.
    angles (``None`` or sequence[N + 1]): Tangent angles at each point
      (in radians). Angles defined as ``None`` are automatically
      calculated.
    tension_in (number or sequence[N + 1]): Tension parameter when
      arriving at each point. One value per point or a single value used
      for all points.
    tension_out (number or sequence[N + 1]): Tension parameter when
      leaving each point. One value per point or a single value used for
      all points.
    initial_curl: Ratio between the mock curvatures at the first point
      and at its neighbor. A value of 1 renders the first segment a good
      approximation for a circular arc. A value of 0 will better
      approximate a straight segment. It has no effect for closed paths
      or when an angle is defined for the first point.
    final_curl: Ratio between the mock curvatures at the last point and
      at its neighbor. It has no effect for closed paths or when an
      angle is defined for the first point.
    cycle: If ``True``, calculates control points for a closed path,
      with an additional segment connecting the first and last points.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.
    relative: If ``True``, coordinates are relative to the last point.

Examples:
    >>> half_pi = numpy.pi / 2
    >>> points = [(4, 1), (4, 3), (0, 5), (-4, 3), (-4, -2), (0, -4)]
    >>> angles = [half_pi, None, None, None, -half_pi, -half_pi, None]
    >>> path_1 = gdstk.RobustPath((0, 0), 0.2, tolerance=1e-3)
    >>> path_1.interpolation(points, cycle=True)
    >>> path_2 = gdstk.RobustPath((6, -8), 0.2, tolerance=1e-3)
    >>> path_2.interpolation(points, angles, cycle=True, relative=True)

    .. image:: ../_static/robustpath/interpolation.*
       :align: center

See also:
    :meth:`gdstk.RobustPath.segment`

.. [#] Hobby, J.D. "Smooth, easy to compute interpolating splines."
   *Discrete Comput Geom* 1, 123–140 (1986). `DOI: 10.1007/BF02187690
   <https://doi.org/10.1007/BF02187690>`_.)!");

PyDoc_STRVAR(
    robustpath_object_arc_doc,
    R"!(arc(radius, initial_angle, final_angle, rotation=0, width=None, offset=None) -> self

Append an elliptical arc to this path.

Args:
    radius (number or sequence[2]): Circular arc radius or elliptical
      arc radii.
    initial_angle: Starting angle (in radians).
    final_angle: Ending angle (in radians).
    rotation: Arc rotation.
    width (number, tuple, or callable): Width of this section. A tuple
      of 2 elements (number, str) can be used to define the width value
      and the interpolation type from the previous section to the end
      point ("constant", "linear", or "smooth"). I only a number is
      used, the interpolation defaults to "linear". A callable must
      accept a single number from 0 to 1 and return the desired width at
      the corresponding position along the section.
    offset (number, tuple, or callable): Offset from the central path
      position. A tuple or callable can be used as in ``width``.

Examples:
    >>> path = gdstk.FlexPath((0, 0), [0.2, 0.3], 0.4, tolerance=1e-3)
    >>> path.vertical(5)
    >>> path.arc(2.5, numpy.pi, 0)
    >>> path.arc((3, 5), -numpy.pi, -numpy.pi / 2)

    .. image:: ../_static/robustpath/arc.*
       :align: center)!");

PyDoc_STRVAR(robustpath_object_turn_doc, R"!(turn(radius, angle, width=None, offset=None) -> self

Append a circular turn to this path.

Args:
    radius: Circular arc radius.
    angle: Turning angle. Positive values turn counter clockwise and
      negative values, clockwise.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.)!");

PyDoc_STRVAR(robustpath_object_parametric_doc,
             R"!(parametric(path_function, width=None, offset=None, relative=True) -> self

Append a parametric curve to this path.

Args:
    path_function (callable): Function that defines the path. Must be a
      function of one argument (that varies from 0 to 1) that returns a
      2-element sequence or complex with the coordinates of the path.
    width (number or sequence): Width at the end point(s). If this is a
      sequence, it must define the width for each path. The width is
      linearly tapered from its previous value.
    offset (number or sequence): If this is a number, it is treated as
      the distance between centers of adjacent paths. If it is a
      sequence, each number represents the absolute offset from the
      center of the path. The offsets are linearly tapered from their
      previous values.
    relative: If ``True``, the return values of ``path_function`` are
      used as offsets from the current path position, i.e., to ensure a
      continuous path, ``path_function(0)`` must be (0, 0). Otherwise,
      they are used as absolute coordinates.

Examples:

    >>> def spiral(u):
    ...     rad = 2 * u ** 0.5
    ...     ang = 3 * numpy.pi * u
    ...     return (rad * numpy.cos(ang), rad * numpy.sin(ang))
    >>> path = gdstk.FlexPath((0, 0), 0.2, tolerance=1e-3)
    >>> path.parametric(spiral)

    .. image:: ../_static/robustpath/parametric.*
       :align: center)!");

PyDoc_STRVAR(robustpath_object_commands_doc, R"!(commands(path_commands...) -> self

Append sections to this path according to commands.

Commands are single characters followed by a pre-defined number of
numerical arguments, according to the table below:

======= ======================= ===========================
Command Primitive               Arguments
======= ======================= ===========================
L/l     Line segment            x, y
H/h     Horizontal segment      x
V/v     Vertical segment        y
C/c     Cubic Bézier            x0, y0, x1, y1, x2, y2
S/s     Smooth cubic Bézier     x0, y0, x1, y1
Q/q     Quadratic Bézier        x0, y0, x1, y1
T/t     Smooth quadratic Bézier x, y
a       Circular turn           rad, ang
A       Circular arc            rad, ang0, ang1
E       Elliptical arc          rad0, rad1, ang0, ang1, rot
======= ======================= ===========================

Uppercase commands assume that coordinates are absolute, whereas the
lowercase versions assume they are relative to the previous endpoint.

Notes:
    The meaning and order of the arguments of all commands are identical
    to the corresponding method.

Examples:
    >>> path = gdstk.RobustPath((0, 0), [0.2, 0.4, 0.2], 0.5,
    ...                         tolerance=1e-3)
    >>> path.commands("l", 3, 4,
    ...               "A", 2, numpy.arctan2(3, -4), numpy.pi / 2,
    ...               "h", 0.5,
    ...               "a", 3, -numpy.pi)

    .. image:: ../_static/robustpath/commands.*
       :align: center)!");

PyDoc_STRVAR(robustpath_object_translate_doc, R"!(translate(dx, dy) -> self

Translate this path.

Args:
    dx: Translation in the x coordinate.
    dy: Translation in the y coordinate.)!");

PyDoc_STRVAR(robustpath_object_scale_doc, R"!(scale(s, center=(0, 0)) -> self

Scale this path.

Args:
    s: Scaling factor.
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(robustpath_object_mirror_doc, R"!(mirror(p1, p2=(0, 0)) -> self

Mirror this path across the line through `p1` and `p2`.

Args:
    p1 (coordinate pair or complex): First point in the mirror line.
    p2 (coordinate pair or complex): Second point in the mirror line.)!");

PyDoc_STRVAR(robustpath_object_rotate_doc, R"!(rotate(angle, center=(0, 0)) -> self

Rotate this path.

Args:
    angle: Rotation angle (in radians).
    center (coordinate pair or complex): Center of the transformation.)!");

PyDoc_STRVAR(robustpath_object_set_property_doc, R"!(set_property(attr, value) -> self

Set a GDSII property for this path.

Args:
    attr (number): Property number.
    value (str): Property value.)!");

PyDoc_STRVAR(robustpath_object_get_property_doc, R"!(get_property(attr) -> str

Return a property of this path.

Args:
    attr (number): Property number.

Returns:
   str or None: Property value. If the property number does not exist,
   ``None`` is returned.)!");

PyDoc_STRVAR(robustpath_object_delete_property_doc, R"!(delete_property(attr) -> self

Delete property of this path.

Args:
    attr (number): Property number.)!");

PyDoc_STRVAR(robustpath_object_layers_doc, R"!(RobustPath layer.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(robustpath_object_datatypes_doc, R"!(RobustPath data type.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(robustpath_object_num_paths_doc, R"!(Number of paths.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(robustpath_object_size_doc, R"!(Number of sections in this path.

Notes:
    This attribute is read-only.)!");

// Label

PyDoc_STRVAR(
    label_object_type_doc,
    R"!(Label(text, origin, anchor="o", rotation=0, magnification=1, x_reflection=False, layer=0, texttype=0)

Text objects with out geometrical information.

Labels do not create any new geometry in the layout. They can be used to
add descriptions, flags, or comments to the design. For polygonal text,
:func:`gdstk.text` should be used instead.

Args:
    text (str): Text string.
    origin (coordinate pair or complex): Label position.
    anchor (str): Origin position with respect to the label text. One of
      "n", "s", "e", "w", "o", "ne", "nw", "se", or "sw".
    rotation: Rotation angle (in radians).
    magnification: Scaling factor.
    x_reflection: If ``True``, the label is reflected across the
      horizontal axis before rotation.
    layer: GDSII layer number assigned to this label.
    texttype: GDSII text type number assigned to this label.

Examples:
    >>> frame = gdstk.rectangle((-2, -1), (2, 1), datatype=1)
    >>> label_o = gdstk.Label("Center", (0, 0), rotation=numpy.pi / 6)
    >>> label_n = gdstk.Label("North", (0, 1), "n")
    >>> label_s = gdstk.Label("South", (0, -1), "s")
    >>> label_e = gdstk.Label("East", (2, 0), "e")
    >>> label_w = gdstk.Label("West", (-2, 0), "w")
    >>> label_ne = gdstk.Label("Northeast", (2, 1), "ne")
    >>> label_se = gdstk.Label("Southeast", (2, -1), "se")
    >>> label_nw = gdstk.Label("Northwest", (-2, 1), "nw")
    >>> label_sw = gdstk.Label("Southwest", (-2, -1), "sw")

    .. image:: ../_static/label/init.*
       :align: center

    Note that this example can only be correctly displayed in browsers
    with good support for text alignment in SVG images.)!");

PyDoc_STRVAR(label_object_copy_doc, R"!(copy() -> gdstk.Label

Create a copy this label.

Returns:
    Copy of this label.)!");

PyDoc_STRVAR(label_object_set_property_doc, R"!(set_property(attr, value) -> self

Set a GDSII property for this label.

Args:
    attr (number): Property number.
    value (str): Property value.)!");

PyDoc_STRVAR(label_object_get_property_doc, R"!(get_property(attr) -> str

Return a property of this label.

Args:
    attr (number): Property number.

Returns:
   str or None: Property value. If the property number does not exist,
   ``None`` is returned.)!");

PyDoc_STRVAR(label_object_delete_property_doc, R"!(delete_property(attr) -> self

Delete property of this label.

Args:
    attr (number): Property number.)!");

PyDoc_STRVAR(label_object_text_doc, R"!(Label text.)!");

PyDoc_STRVAR(label_object_origin_doc, R"!(Label origin.)!");

PyDoc_STRVAR(label_object_anchor_doc, R"!(Label anchor.)!");

PyDoc_STRVAR(label_object_rotation_doc, R"!(Label rotation angle.)!");

PyDoc_STRVAR(label_object_magnification_doc, R"!(Label scaling factor.)!");

PyDoc_STRVAR(label_object_x_reflection_doc, R"!(Label reflection across the x axis.)!");

PyDoc_STRVAR(label_object_layer_doc, R"!(Label layer.)!");

PyDoc_STRVAR(label_object_texttype_doc, R"!(Label text type.)!");

// Cell

PyDoc_STRVAR(cell_object_type_doc, R"!(Cell(name)

Cell structure.

A cell is a fundamental structure in the GDSII layout. It stores the
geometry, labels and references that make up the final layout. A single
GDSII library can contain any number of independent cells, which can,
themselves, contain references to other cells in the form of
:class:`gdstk.Reference`.

Args:
    name (str): Cell name. It must be unique within a library and,
      according to the GDSII specifications, it must be ASCII-encoded.)!");

PyDoc_STRVAR(cell_object_add_doc, R"!(add(*elements) -> self

Add polygons, paths, labels and references to this cell.)!");

PyDoc_STRVAR(cell_object_area_doc, R"!(area(by_spec=False) -> float or dictionary

Calulate the area of this cell.

Args:
    by_spec: If ``True``, return a dictionary with keys
      ``(layer, datatype)``.

Returns:
    Area of the geometry in this cell, optionally indexed by layer and
    data type.

Notes:
    This operation can be slow because all paths and references are
    included in the computation.)!");

PyDoc_STRVAR(cell_object_bounding_box_doc, R"!(bounding_box() -> tuple or None

Calculate the cell bounding box.

Returns:
    The lower-left and upper-right corners of the bounding box of the
    cell: ``((min_x, min_y), (max_x, max_y))``.

Examples:
    >>> polygons = gdstk.text("F", 10, (0, 0))
    >>> f_cell = gdstk.Cell("F_CELL")
    >>> f_cell.add(*polygons)
    >>> array_ref = gdstk.Reference(f_cell, rotation=numpy.pi / 4,
    ...                             columns=3, rows=2, spacing=(8, 10))
    >>> path = gdstk.FlexPath([(-5, 0), (0, -5), (5, 0)], 1,
    ...                       gdsii_path=True)
    >>> main_cell = gdstk.Cell("MAIN")
    >>> main_cell.add(array_ref, path)
    >>> print(main_cell.bounding_box())
    ((-12.816310409006173, -5.707106781186548),
     (11.313708498984761, 27.66555281392367))
    >>> polygon_bb = gdstk.rectangle(*bbox, datatype=1)

    .. image:: ../_static/cell/bounding_box.*
       :align: center

Notes:
    This operation can be slow because all paths and references are
    included in the computation.)!");

PyDoc_STRVAR(cell_object_flatten_doc, R"!(flatten() -> self

Transform all references into polygons, paths and labels.

Examples:
    >>> poly1 = gdstk.Polygon([(0, 0), (1, 0), (0.5, 1)])
    >>> cell1 = gdstk.Cell('CELL_1')
    >>> cell1.add(poly1)
    >>> poly2 = gdstk.Polygon([(1, 0), (1.5, 1), (0.5, 1)], layer=1)
    >>> ref = gdstk.Reference(cell1, columns=2, rows=2, spacing=(1, 1))
    >>> cell2 = gdstk.Cell('CELL_2')
    >>> cell2.add(poly2, ref)
    >>> print(len(cell2.polygons), len(cell2.references),
    ...       len(cell2.dependencies(True)))
    1 1 1
    >>> cell2.flatten()
    >>> print(len(cell2.polygons), len(cell2.references),
    ...       len(cell2.dependencies(True)))
    5 0 0

    .. image:: ../_static/cell/flatten.*
       :align: center)!");

PyDoc_STRVAR(
    cell_object_copy_doc,
    R"!(copy(name, translation=(0, 0), rotation=0, magnification=1, x_reflection=False, deep_copy=True) -> gdstk.Cell

Create a copy of this cell.

A transformation can be applied to the contents of the new cell. They
follow the same order as reference transformations.

Args:
    name (str): Name of the new cell.
    translation (coordinate pair or complex): Amount to translate the
      cell contents.
    rotation: Rotation angle (in radians).
    magnification: Scaling factor.
    x_reflection: If ``True``, the geometry is reflected across the
      horizontal axis before rotation.
    deep_copy: If ``True``, new elements (polygons, paths, references,
      and labels) are also created for the copied cell. If any
      transformation is applied, this value is always ``True``.

Returns:
    Copy of this cell.)!");

PyDoc_STRVAR(
    cell_object_write_svg_doc,
    R"!(write_svg(outfile, scaling=10, style=None, fontstyle=None, background=\"#222222\", pad=\"5%\") -> self

Export this cell to an SVG image file. Colors and attributes must follow
SVG specification.

Args:
    outfile (str or pathlib.Path): Name of the output file.
    scaling: Scaling factor for the whole geometry.
    style (dict): SVG attributes for each layer and data type. See the
      example below.
    fontstyle (dict): SVG attributes for each layer and text type.
    background (str): Image background color.
    pad (number, str): Viewport margin around the image content. It can
      be specified as an absolute dimension or a percentage of the
      largest image dimension.

Examples:
    >>> # (layer, datatype) = (0, 1)
    >>> poly1 = gdstk.ellipse((0, 0), (13, 10), datatype=1)
    >>> # (layer, datatype) = (1, 0)
    >>> poly2 = gdstk.ellipse((0, 0), (10, 7), layer=1)
    >>> cell = gdstk.Cell("SVG")
    >>> cell.add(poly1, poly2)
    >>> cell.write_svg("example.svg",
    ...                background="none",
    ...                style={(0, 1): {"fill": "none",
    ...                                "stroke": "black",
    ...                                "stroke-dasharray": "8,8"}},
    ...                pad="5%")

    .. image:: ../_static/cell/write_svg.*
       :align: center)!");

PyDoc_STRVAR(cell_object_remove_doc, R"!(remove(*elements) -> self

Remove polygons, paths, labels and references from this cell.

Examples:
    >>> polygons = gdstk.text("Filter dots\nin i and j!", 8, (0, 0))
    >>> cell = gdstk.Cell("FILTERED")
    >>> cell.add(*polygons)
    >>> dots = [poly for poly in cell.polygons if poly.area() < 2]
    >>> cell.remove(*dots)

    .. image:: ../_static/cell/remove.*
       :align: center)!");

PyDoc_STRVAR(cell_object_dependencies_doc, R"!(dependencies(recursive) -> list

List of cells and raw cells that are referenced by this cell.

Args:
   recursive: If ``True``, includes all dependencies recursively.)!");

PyDoc_STRVAR(cell_object_name_doc, R"!(Cell name.)!");

PyDoc_STRVAR(cell_object_polygons_doc, R"!(List of cell polygons.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(cell_object_references_doc, R"!(List of cell references.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(cell_object_paths_doc, R"!(List of cell paths.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(cell_object_labels_doc, R"!(List of cell labels.

Notes:
    This attribute is read-only.)!");

// RawCell

PyDoc_STRVAR(rawcell_object_type_doc, R"!(RawCell(name)

A Cell structure that is stored in binary GDSII format.

Raw cells are not meant to be created in the same way cells are. They
come from :func:`gdstk.read_rawcells` and are used when the imported
elements will not be modified in any way. They are smaller in memory and
require almost no processing to be used, making them a preferred option
when using an external GDSII file as a parts library (such as in PDKs).

Notes:
    The units of the imported ``RawCell`` are not checked against the
    current user units. It is up to the user to ensure they are equal.

See also:
    :func:`gdstk.read_rawcells`, :func:`gdstk.gds_units`)!");

PyDoc_STRVAR(rawcell_object_dependencies_doc, R"!(dependencies(recursive) -> list

List of raw cells that are referenced by this raw cell.

Args:
   recursive: If ``True``, includes all dependencies recursively.)!");

PyDoc_STRVAR(rawcell_object_name_doc, R"!(Raw cell name.

Notes:
    This attribute is read-only.)!");

PyDoc_STRVAR(rawcell_object_size_doc, R"!(Raw cell size (in bytes).

Notes:
    This attribute is read-only.)!");

// Library

PyDoc_STRVAR(library_object_type_doc, R"!(Library(name="library", unit=1e-6, precision=1e-9)

GDSII library.

The library is a container for multiple cells which keeps track of the
units used to generate the design. The library can be saved to a GDSII
stream file and vice-versa.

Args:
    name: Library name.
    unit: User units in meters.
    precision: Desired precision to store the units once written to a
      GDSII file.

See also:
    :ref:`units-in-gds`)!");

PyDoc_STRVAR(library_object_add_doc, R"!(add(*cells) -> self

Add cells to this library.

Examples:
    >>> polygon = gdstk.rectangle((0, 0), (1, 1))
    >>> cell = gdstk.Cell("MAIN")
    >>> cell.add(polygon)
    >>> lib = gdstk.Library()
    >>> lib.add(cell))!");

PyDoc_STRVAR(library_object_remove_doc, R"!(remove(*cells) -> self

Remove cells from this library.)!");

PyDoc_STRVAR(library_object_new_cell_doc, R"!(new_cell(name) -> gdstk.Cell

Create a new cell and add it to this library.

Args:
    name (str): Name of the new cell.

Examples:
    >>> lib = gdstk.Library()
    >>> cell = lib.new_cell("MAIN")
    >>> polygon = gdstk.rectangle((0, 0), (1, 1))
    >>> cell.add(polygon))!");

PyDoc_STRVAR(library_object_top_level_doc, R"!(top_level() -> list

Return the top-level cells in the library.

Top-level cells are cells that do not appear as dependency of any other
cells in the library.)!");

PyDoc_STRVAR(library_object_write_gds_doc, R"!(write_gds(outfile, max_points=199) -> None

Save this library to a GDSII file.

Args:
    outfile (str or pathlib.Path): Name of the output file.
    max_points: Maximal number of vertices per polygon. Polygons with
      more vertices that this are automatically fractured.

See also:
    :ref:`getting-started`)!");

PyDoc_STRVAR(library_object_name_doc, R"!(Library name.)!");
PyDoc_STRVAR(library_object_cells_doc, R"!(List of library cells.

Notes:
    This attribute is read-only.)!");

// GdsWriter

PyDoc_STRVAR(gdswriter_object_type_doc,
             R"!(GdsWriter(outfile, name="library", unit=1e-6, precision=1e-9, max_points=199)

Multi-step GDSII stream file writer.

When a design is too large to be completely created in memory, it is not
possible to create a :class:`gdstk.Library` to save it as a GDSII file.
In such cases, it might be possible to still create the desired design
creating, saving and deleting one cell at a time. Saving one cell at a
time can be done thru this class.

Args:
    outfile (str or pathlib.Path): Name of the output file.
    unit: User units in meters.
    precision: Desired precision to store the units once written to a
      GDSII file.
    max_points: Maximal number of vertices per polygon. Polygons with
      more vertices that this are automatically fractured.

Example:
    >>> writer = gdstk.GdsWriter()
    >>> cell1 = some_function_that_creates_a_huge_cell()
    >>> writer.write(cell1)
    >>> del cell1
    >>> cell2 = some_function_that_creates_a_huge_cell()
    >>> writer.write(cell2)
    >>> del cell2
    >>> writer.close()

See also:
    :ref:`units-in-gds`, :meth:`gdstk.Library.write_gds`)!");

PyDoc_STRVAR(gdswriter_object_write_doc, R"!(write(*cells) -> self

Write cells to the output file.)!");

PyDoc_STRVAR(gdswriter_object_close_doc, R"!(close() -> None

Finish writing the output file and close it.)!");

// Module-level functions

PyDoc_STRVAR(rectangle_function_doc,
             R"!(rectangle(corner1, corner2, layer=0, datatype=0) -> gdstk.Polygon

Create a rectangle.

Args:
    corner1 (coordinate pair or complex): First rectangle corner.
    corner2 (coordinate pair or complex): Opposing corner.
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.)!");

PyDoc_STRVAR(cross_function_doc,
             R"!(cross(center, full_size, arm_width, layer=0, datatype=0) -> gdstk.Polygon

Create a cross shape.

Args:
    center (coordinate pair or complex): Center of the cross.
    full_size (number): Total length of the cross.
    arm_width (number): Width of the arms.
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.

Examples:
    >>> cross1 = gdstk.cross((0, 0), 10, 1)
    >>> cross2 = gdstk.cross((0.5, 0.5), 5, 0.75, layer=1)

    .. image:: ../_static/function/cross.*
       :align: center)!");

PyDoc_STRVAR(
    regular_polygon_function_doc,
    R"!(regular_polygon(center, side_length, sides, rotation=0, layer=0, datatype=0) -> gdstk.Polygon

Create a regular polygon.

Args:
    center (coordinate pair or complex): Polygon center.
    side_length (number): Length of the sides of the polygon.
    sides (integer): Number of polygon sides.
    rotation: Rotation angle (in radians).
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.

Examples:
    >>> poly3 = gdstk.regular_polygon((0, 0), 9, 3)
    >>> poly4 = gdstk.regular_polygon((10, 0), 7, 4, layer=1)
    >>> poly5 = gdstk.regular_polygon((0, 10), 5, 5, layer=2)
    >>> poly6 = gdstk.regular_polygon((10, 10), 4, 6, layer=3)

    .. image:: ../_static/function/regular_polygon.*
       :align: center)!");

PyDoc_STRVAR(
    ellipse_function_doc,
    R"!(ellipse(center, radius, inner_radius=None, initial_angle=0, final_angle=0, tolerance=0.01, layer=0, datatype=0) -> gdstk.Polygon

Create an ellipse, circle, slice or ring.

Args:
    center (coordinate pair or complex): Circle/ellipse center.
    radius (number or sequence): Circle radius of the circle. A pair of
      numbers can be used to define an ellipse.
    inner_radius (number or sequence): If set, creates a ring.
    initial_angle: Initial angle to define a slice.
    final_angle: Final slice angle.
    tolerance: Tolerance used for calculating the polygonal
      approximation of this shape.
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.

Examples:
    >>> circle = gdstk.ellipse((0, 0), 40)
    >>> ellipse = gdstk.ellipse((100, 0), (40, 30), layer=1)
    >>> ring = gdstk.ellipse((0, 100), 40, inner_radius=(30, 20),
                             layer=2)
    >>> c_slice = gdstk.ellipse((100, 100), 40,
    ...                         initial_angle=-numpy.pi / 4,
    ...                         final_angle=5 * numpy.pi / 4,
    ...                         layer=3)
    >>> r_slice = gdstk.ellipse((50, 200), (70, 30), (60, 20),
    ...                         -3 * numpy.pi / 4, numpy.pi / 2,
    ...                         layer=4)

    .. image:: ../_static/function/ellipse.*
       :align: center)!");

PyDoc_STRVAR(
    racetrack_function_doc,
    R"!(racetrack(center, straight_length, radius, inner_radius=0, vertical=False, tolerance=0.01, layer=0, datatype=0) -> gdstk.Polygon

Create a racetrack shape.

Args:
    center (coordinate pair or complex): Polygon center.
    straight_length (number): Length of the straight segment.
    radius (number): Radius of the circular arc.
    inner_radius (number): If greater than 0, create a racetrack ring.
    vertical: If ``True``, the racetrack is created vertically.
    tolerance: Tolerance used for calculating the polygonal
      approximation for the circular arcs.
    layer: GDSII layer number assigned to this polygon.
    datatype: GDSII data type number assigned to this polygon.

Examples:
    >>> racetrack1 = gdstk.racetrack((0, 0), 8, 5)
    >>> racetrack2 = gdstk.racetrack((18, 0), 8, 5, 3, True)

    .. image:: ../_static/function/racetrack.*
       :align: center)!");

PyDoc_STRVAR(text_function_doc,
             R"!(text(text, size, position, vertical=False, layer=0, datatype=0) -> list

Create polygonal text.

Args:
    text (str): Text string.
    size (number): Full height of the font.
    position (coordinate pair or complex): Text starting position.
    vertical: Writing direction.
    layer: GDSII layer number assigned to the polygons.
    datatype: GDSII data type number assigned to the polygons.

Returns:
    List of :class:`gdstk.Polygon`.

Examples:
    >>> text = gdstk.text(f"Created with\nGDSTK {gdstk.__version__}", 1,
    ...                   (0, 0))
    >>> rect = gdstk.rectangle((0, -5 / 4), (12 * 9 / 16, 1), 
    ...                        datatype=1)

    .. image:: ../_static/function/text.*
       :align: center

Notes:
    The character aspect ratio is 1:2. For horizontal text, spacing
    between characters and between lines are 9 / 16 and 5 / 4 times the
    full height ``size``, respectively. For vertical text, characters
    and columns are respectively spaced 9 / 8 and 1 times ``size``.)!");

PyDoc_STRVAR(
    offset_function_doc,
    R"!(offset(polygons, distance, join="miter", tolerance=2, precision=1e-3, use_union=False, layer=0, datatype=0) -> list

Dilate or erode polygons.

Args:
    polygons (Polygon, FlexPath, RobustPath, Reference, sequence):
      Polygons to offset. If this is a sequence, each element can be any
      of the polygonal types or a sequence of points (coordinate pairs
      or complex).
    distance (number): Offset distance. Positive values dilate the
      geometry, whereas negative values erode it.
    join: Type of joins for the offset polygon. One of "miter", "bevel",
      or "round".
    tolerance: For miter joints, this number must be at least 2 and it
      represents the maximal distance in multiples of offset between new
      vertices and their original position before beveling to avoid
      spikes at acute joints. For round joints, it indicates the
      curvature resolution in number of points per full circle.
    precision: Desired precision for rounding vertex coordinates.
    use_union: Apply a union operation before the offset to merge
      adjacent polygons.
    layer: GDSII layer number assigned to the resulting polygons.
    datatype: GDSII data type number assigned to the resulting polygons.

Returns:
    List of :class:`gdstk.Polygon`.

Examples:
    >>> text = gdstk.text("#A", 10, (0, 0), datatype=1)
    >>> circle = gdstk.ellipse((5, 11), 5, initial_angle=0,
    ...                        final_angle=numpy.pi, datatype=1)
    >>> path = gdstk.FlexPath([(0, -1), (5, -10), (10, -1)], 1, datatype=1)
    >>> dilated = gdstk.offset(text + [circle, path], 0.4)
    >>> eroded = gdstk.offset(text + [circle, path], -0.4,
    ...                       use_union=True, layer=1)

    .. image:: ../_static/function/offset.*
       :align: center)!");

PyDoc_STRVAR(boolean_function_doc,
             R"!(boolean(operand1, operand2, operation, precision=1e-3, layer=0, datatype=0) -> list

Execute boolean (clipping) operations between polygons.

Args:
    operand1 (Polygon, FlexPath, RobustPath, Reference, sequence): First
      operand. If this is a sequence, each element can be any of the
      polygonal types or a sequence of points (coordinate pairs or
      complex).
    operand2 (Polygon, FlexPath, RobustPath, Reference, sequence):
      Second operand.
    operation (str): Boolean operation to be executed. One of "or",
      "and", "xor", or "not". The "not" operation performs the set
      difference ``operand1 - operand2``.
    precision: Desired precision for rounding vertex coordinates.
    layer: GDSII layer number assigned to the resulting polygons.
    datatype: GDSII data type number assigned to the resulting polygons.

Returns:
    List of :class:`gdstk.Polygon`.

Examples:
    >>> circle = gdstk.ellipse((0, 0), 50)
    >>> path = gdstk.FlexPath((-50, 30), [5, 5], 10)
    >>> path.interpolation([(20, 15), (0, 0), (-20, -15), (50, -30)],
    ...                    angles=[0.3, None, None, None, 0.3])
    >>> text = gdstk.text("GDSTK", 40, (-2.5 * 40 * 9 / 16, -40 / 2))
    >>> result = gdstk.boolean(circle, text + [path], "not")

    .. image:: ../_static/function/boolean.*
       :align: center)!");

PyDoc_STRVAR(slice_function_doc, R"!(slice(polygons, position, axis, precision=1e-3) -> list

Slice polygons along x and y axes.

Args:
    polygons (Polygon, FlexPath, RobustPath, Reference, sequence):
      Polygons to offset. If this is a sequence, each element can be any
      of the polygonal types or a sequence of points (coordinate pairs
      or complex).
    position (number or sequence): Cut positions.
    axis (str): One of "x" or "y".
    precision: Desired precision for rounding vertex coordinates.

Returns:
    List with N + 1 elements, where N is the number of cut positions.
    Each element is a list of polygons obtained between cuts.

Examples:
    >>> triangle = gdstk.regular_polygon((-10, 0), 8, 3)
    >>> ring = gdstk.ellipse((10, 0), 8, 5, layer=1)
    >>> result = gdstk.slice([triangle, ring], (-10, -5, 0, 6, 14), "x")
    >>> print(len(result))
    6
    >>> print([len(polys) for polys in result])
    [1, 1, 0, 1, 2, 1]

    .. image:: ../_static/function/slice.*
       :align: center)!");

PyDoc_STRVAR(inside_function_doc,
             R"!(inside(points, polygons, short_circuit=*, precision=1e=3) -> tuple

Test whether the points are inside the polygons.

Args:
    points: Testing points. This can be a sequence of points or a
      sequence of point sequences (point groups).
    polygons (Polygon, FlexPath, RobustPath, Reference, sequence):
      Polygons to test against. If this is a sequence, each element can
      be any of the polygonal types or a sequence of points (coordinate
      pairs or complex).
    short_circuit: One of "any", "all", or "none". Testing (within each
      point group) can be short-circuited if "any" or "all" of the
      points are inside the polygon set. This parameter defaults to
      "any" if point groups are used, and "none" otherwise.
    precision: Desired precision for rounding vertex coordinates.

Returns:
    Tuple of booleans indicating weather points or groups are inside the
    polygons.

Examples:
    >>> rect = gdstk.rectangle((0, 0), (1, 1))
    >>> print(gdstk.inside([(0.5, 0.5), (2, 2)], rect))
    (True, False)
    >>> print(gdstk.inside([(0.5, 0.5), (2, 2)], rect, "any"))
    (True,)
    >>> print(gdstk.inside([(0.5, 0.5), (2, 2)], rect, "all"))
    (False,)
    >>> # Point groups
    >>> print(gdstk.inside([[(0.5, 0.5), (2, 2)],
    ...                     [(0, 0), (1, 1)],
    ...                     [(2, 2), (3, 3)]], rect)
    (True, True, False))!");

PyDoc_STRVAR(read_gds_function_doc, R"!(read_gds(infile, unit=0) -> gdstk.Library

Import a library from a GDSII stream file.

Args:
    infile (str or pathlib.Path): Name of the input file.
    unit (number): If greater than zero, convert the imported geometry
      to the this unit.

Returns:
    The imported library.

Examples:
    >>> library = gdstk.read_gds("layout.gds")
    >>> top_cells = library.top_level())!");

PyDoc_STRVAR(read_rawcells_function_doc, R"!(read_rawcells(infile) -> dict

Load cells form a GDSII file without decoding them.

Args:
    infile (str or pathlib.Path): Name of the input file.

Returns:
    Dictionary of :class:`gdstk.RawCell` indexed by name.

Examples:
    >>> cell1 = gdstk.Cell("CELL_1")
    >>> cell1.add(gdstk.rectangle((0, 0), (2, 1)))
    >>> cell2 = gdstk.Cell("CELL_2")
    >>> cell2.add(gdstk.Reference(cell1, (-1, 0)))
    >>> library = gdstk.Library()
    >>> library.add(cell1, cell2)
    >>> library.write_gds("test.gds")
    >>> raw_cells = gdstk.read_rawcells("test.gds")
    >>> print(raw_cells.keys())
    dict_keys(['CELL_2', 'CELL_1'])
    >>> print(len(raw_cells["CELL_1"].dependencies(True)))
    0
    >>> print(len(raw_cells["CELL_2"].dependencies(True)))
    1
    >>> deps = raw_cells["CELL_2"].dependencies(True)
    >>> print(deps[0] is raw_cells["CELL_1"])
    True)!");

PyDoc_STRVAR(gds_units_function_doc, R"!(gds_units(infile) -> tuple

Read the unit and precision of a GDSII file.

Args:
    infile (str or pathlib.Path): Name of the input file.

Returns:
    Tuple with the unit and precision of the library in the file.)!");
