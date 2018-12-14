#include <string>
#include "vector2f.h"

class PlayerPostion {
public:
  virtual ~PlayerPostion(){}
  virtual void setPlayerPos(const Vector2f& p) = 0;
};