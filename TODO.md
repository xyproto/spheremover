# Plans

- [ ] Add a menu
- [ ] Make it possible to configure the joystick
- [ ] Create an RGB and an RGBA color class.
- [ ] Move the clamp function to the RGB and RGBA classes.
- [ ] Once the sphere intersection is working, add a Triangle class and add Ray and Triangle intersection.
- [ ] Try alternative algorithms for intersection, like traversing the ray at steps (minimum object width - 1),
      possibly inside a tree structure with bounding boxes, to first find the correct box.
- [ ] Save to /tmp/output.png and chown afr:users, by default.

## Maybe

- [ ] For each sphere/object, trace the entire surface,
      then store the normals in a lookup table?

## Safety

- [ ] No division by zero when normalizing. Add a check!

## Performance

- [ ] Faster square root by approximation?
- [ ] Faster quaternion * vector formula?


### Notes

Faster quaternion * vector formula:

    t = 2 * cross(q.xyz, v)
    v' = v + q.w * t + cross(q.xyz, t)

From [this blog post](https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/).
