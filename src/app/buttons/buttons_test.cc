
#include "buttons/buttons.h"

#include "pw_unit_test/framework_backend.h"

namespace tupa::buttons {
namespace {

TEST(ButtonsTest, Trivial) {
  [[maybe_unused]] Buttons buttons;
  EXPECT_TRUE(true);
}
}  // namespace
}  // namespace tupa::buttons