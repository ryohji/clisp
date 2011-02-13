#include "read.h"
#include "list.h"
#include "symbol.h"
#include "number.h"

#include <list>
#include <sstream>
#include <stdexcept>

NS_CLISP_BEGIN

namespace {
  expression_t read_atom(std::list<std::string> &ts) {
    const std::string &token = ts.front();
    if (")" == token) {
      throw std::runtime_error("unexprected end of list ')'");
    } else {
      if ('-' == token[0]) {
	return new symbol(token);
      } else {
	std::istringstream is(token);
	double d;
	is >> d;
	return is.fail() ? expression_t(new symbol(token)) : new number(d);
      }
    }
  }

  expression_t read_list(std::list<std::string> &ts) {
    list *l(new list);
    ts.pop_front(); // discard "(".
    while (!ts.empty() && ")" != ts.front()) {
      l->push_back( "(" == ts.front() ? read_list(ts) : read_atom(ts) );
      ts.pop_front();
    }
    if (ts.empty())
      throw std::runtime_error("incomplete list");
    ts.pop_front(); // discard ")".
    return l;
  }

  expression_t read_aux(std::list<std::string> &ts) {
    return "(" == ts.front() ? read_list(ts) : read_atom(ts);
  }

  std::istream& add_ws_(std::istream &from, std::stringstream &to) {
    char c;
    while (from.read(&c, 1)) {
      if ('(' == c) {
	to.write("( ", 2);
      } else if (')' == c) {
	to.write(" )", 2);
      } else {
	to.write(&c, 1);
      }
    }
    return to;
  }

  std::list<std::string> tokenize(std::istream &S) {
    std::list<std::string> ss;
    std::string s;
    while ((S >> s, !S.fail())) {
      ss.push_back(s);
    }
    return ss;
  }
}

expression_t read(std::istream &S) {
  std::stringstream buf;
  std::list<std::string> ts = tokenize(add_ws_(S, buf));
  return read_aux(ts);
}

NS_CLISP_END
