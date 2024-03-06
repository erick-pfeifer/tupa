
#include "buttons/buttons.h"

#include "pw_unit_test/framework.h"

namespace tupa::buttons {
namespace {

TEST(ButtonsTest, Trivial) {
  [[maybe_unused]] Buttons buttons;
  EXPECT_TRUE(true);
}
}  // namespace
}  // namespace tupa::buttons