#include <cassert>
#include <gtest/gtest.h>

#include <console_bridge/console.h>

//////////////////////////////////////////////////
TEST(ConsoleTest, MacroExpansionTest_ItShouldCompile)
{
  if (true)
    CONSOLE_BRIDGE_logDebug("Testing Log");

  if (true)
    CONSOLE_BRIDGE_logDebug("Testing Log");
  else
  {
      assert(true);
  }

  if (true)
  {
    CONSOLE_BRIDGE_logDebug("Testing Log");
  }
  else
  {
    CONSOLE_BRIDGE_logDebug("Testing Log");
  }
}

//////////////////////////////////////////////////
TEST(ConsoleTest, MultipleArguments)
{
  CONSOLE_BRIDGE_logError("no extra parameters");
  CONSOLE_BRIDGE_logError("one integer: %d", 42);
  CONSOLE_BRIDGE_logError("two floats: %f, %.2f", 42.01, 1/3.0);
}
