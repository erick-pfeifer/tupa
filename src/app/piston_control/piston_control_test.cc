
#include "piston_control/piston_control.h"

#include "pw_unit_test/framework.h"

namespace tupa::piston_control {
namespace {

TEST(PistonControlTest, Trivial) {
  [[maybe_unused]] PistonControl piston;
  EXPECT_TRUE(true);
}
}  // namespace
}  // namespace tupa::piston_control