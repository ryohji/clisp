#include <tr1/unordered_map>
#include <stdexcept>

namespace sp_detail {
  namespace {
    static std::tr1::unordered_map<void*, unsigned> cmap;
  }

  unsigned ref_up(void *obj) {
    return ++cmap[obj];
  }

  unsigned ref_down(void *obj) {
    std::tr1::unordered_map<void*, unsigned>::iterator it = cmap.find(obj);
    if (cmap.end() == it) {
      throw std::runtime_error("attempt unexpected object reference down!");
    } else {
      const unsigned count = --cmap[obj];
      if (0 == count)
	cmap.erase(it);
      return count;
    }
  }
}
