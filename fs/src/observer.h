#ifndef OBSERVER_H
#define OBSERVER_H

class Node;
class Observer {
public:
  virtual void update(Node* node) = 0;

  virtual void update() = 0;

};

#endif
