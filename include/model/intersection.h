#ifndef INTERSECTION_H
#define INTERSECTION_H

struct Shape;
struct Circle;
struct ReverseCircle;

#include "primitives.h"

bool are_intersecting(Shape& first, Shape& second);
bool are_intersecting(Circle& first, Circle& second);
bool are_intersecting(Circle& first, ReverseCircle& second);
bool are_intersecting(ReverseCircle& first, ReverseCircle& second);


class IntersectionVisitorBase
{
public:
  virtual bool visit(Circle&) = 0;
  virtual bool visit(ReverseCircle&) = 0;

};

class IntersectionVisitor : public IntersectionVisitorBase
{
private:
  Shape& shape_;

public:
  IntersectionVisitor(Shape&);
  virtual bool visit(Circle&);
  virtual bool visit(ReverseCircle&);
};

class CircleVisitor : public IntersectionVisitorBase
{
private:
  Circle& circle_;

public:
  CircleVisitor(Circle&);
  virtual bool visit(Circle&);
  virtual bool visit(ReverseCircle&);
};

class ReverseCircleVisitor : public IntersectionVisitorBase
{
private:
  ReverseCircle& reverse_circle_;

public:
  ReverseCircleVisitor(ReverseCircle&);
  virtual bool visit(Circle&);
  virtual bool visit(ReverseCircle&);
};

class Shape
{
public:
  virtual bool accept(IntersectionVisitor& visitor) = 0;
  virtual bool accept(CircleVisitor& visitor) = 0;
  virtual bool accept(ReverseCircleVisitor& visitor) = 0;
};

struct Circle : public Shape
{
  Circle(const Coordinates& coordinates, const Distance& radius);
  virtual bool accept(IntersectionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(ReverseCircleVisitor& visitor);

  const Coordinates coordinates;
  const Distance radius;
};

struct ReverseCircle : public Shape
{
  ReverseCircle(const Coordinates& coordinates, const Distance& radius);
  virtual bool accept(IntersectionVisitor& visitor);
  virtual bool accept(CircleVisitor& visitor);
  virtual bool accept(ReverseCircleVisitor& visitor);

  const Coordinates coordinates;
  const Distance radius;
};

#endif /* INTERSECTION_H_ */
