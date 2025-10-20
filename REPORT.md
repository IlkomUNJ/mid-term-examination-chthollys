# Segment Detection: Ideal Window Size and Pattern Optimization Report

## Ideal Window Size

### Finding

A **5×5 pixel window** offers the best balance between spatial accuracy and tolerance for small visual variations.

### Justification

- **3×3** is too small — it captures only single-pixel variations and misses broader line continuity.
- **5×5** effectively represents line structures (center pixel + immediate context) while remaining computationally light.

---

## Optimal Segment Patterns

### Finding

The most accurate detection occurs when using **structurally balanced patterns** that cover both linear and intersecting geometries:

#### Intersection Patterns

1. Cross (+) — central pixel plus orthogonal arms
2. T-junctions (top, bottom, left, right) — partial extensions of the cross pattern

These patterns represent all possible 2D linear combinations within a 5×5 matrix.
