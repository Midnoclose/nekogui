
#include "functional.hpp"

#include "input.hpp"

namespace input {



namespace events {

cat::FastEvent<std::pair<int, int>> bounds;
cat::FastEvent<std::pair<int, int>> mouse;
cat::FastEvent<CatKey, bool> key;

}}
