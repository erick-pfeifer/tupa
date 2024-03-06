
#include "pw_unit_test/framework.h"

#include "buttons/buttons.h"

namespace tupa::buttons {
namespace  {

TEST(ButtonsTest, Trivial) {
  [[maybe_unused]]Buttons buttons;
  EXPECT_TRUE(true);
}
}
}