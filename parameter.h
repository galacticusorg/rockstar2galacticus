#ifndef PARAMETER_H
#define PARAMETER_H


enum dataType {INT, DOUBLE, STRING};

struct parameter {
  char name[100];
  char group [150]; // name of the group where parameter should be written as attribute
  char s_val[300];
  int i_val;
  double d_val;
  enum dataType dtype;
  int found; // 0 false, 1 true
  int required;  // 0 false, 1 true
};




#endif
