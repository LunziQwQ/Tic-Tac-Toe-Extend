#ifndef _OOXX_ANALYSIS_H
#define _OOXX_ANALYSIS_H
#include <string>
class Param {
 public:
   std::string param_code(code);
   std::string param_point(point);
   point return_point(str);
   void err(str);
   void param(str);
};

Param::param_code(code) {
  std::string code(code);
  return "code:" + code;
}

Param::param_point(point) {
  std::string x(code.x),
              y(code.y);
  return x + ',' + y;
}

Param::return_point(str) {
  return point(str);
}

Param::err(str) {
  string e = str[6];
  senderr(e);
}

Param::param(str) {
  if (str.find("error")==-1) {
    return_point(str);
  } else {
    err(str);
  }
}


#endif
