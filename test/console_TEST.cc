#include <cassert>
#include <gtest/gtest.h>

#include <console_bridge/console.h>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(const std::string& str, char delim = '\n')
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }
    return result;
}

//////////////////////////////////////////////////
TEST(ConsoleTest, TestLogLevel)
{
  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_DEBUG);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::CONSOLE_BRIDGE_LOG_DEBUG);

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_INFO);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::CONSOLE_BRIDGE_LOG_INFO);

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_WARN);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::CONSOLE_BRIDGE_LOG_WARN);

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_ERROR);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::CONSOLE_BRIDGE_LOG_ERROR);

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_NONE);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::CONSOLE_BRIDGE_LOG_NONE);
}

//////////////////////////////////////////////////
TEST(ConsoleTest, MultipleArguments)
{
  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_DEBUG);

  // This can be an ofstream as well or any other ostream
  std::stringstream buffer;
  // Save cout's buffer here
  std::streambuf *sbuf = std::cerr.rdbuf();
  // Redirect cerr to our stringstream buffer or any other ostream
  std::cerr.rdbuf(buffer.rdbuf());

  // get cout
  testing::internal::CaptureStdout();

  CONSOLE_BRIDGE_logError("no extra parameters");
  CONSOLE_BRIDGE_logDebug("no extra parameters");
  std::string output_debug = testing::internal::GetCapturedStdout();
  std::vector<std::string> output_error = split(buffer.str(), '\n');
  EXPECT_STREQ("Debug:   no extra parameters\n", output_debug.c_str());
  EXPECT_EQ(output_error.size(), 2u);
  EXPECT_STREQ("Error:   no extra parameters", output_error[0].c_str());

  // get cout
  testing::internal::CaptureStdout();
  buffer.str("");
  CONSOLE_BRIDGE_logError("one integer: %d", 42);
  CONSOLE_BRIDGE_logDebug("one integer: %d", 42);
  output_error = split(buffer.str(), '\n');
  EXPECT_EQ(output_error.size(), 2u);
  output_debug = testing::internal::GetCapturedStdout();
  EXPECT_STREQ("Debug:   one integer: 42\n", output_debug.c_str());
  EXPECT_STREQ("Error:   one integer: 42", output_error[0].c_str());

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_ERROR);
  // get cout
  testing::internal::CaptureStdout();
  buffer.str("");
  CONSOLE_BRIDGE_logError("two floats: %f, %.2f", 42.01, 1/3.0);
  CONSOLE_BRIDGE_logDebug("two floats: %f, %.2f", 42.01, 1/3.0);
  output_error = split(buffer.str(), '\n');
  EXPECT_EQ(output_error.size(), 2u);
  output_debug = testing::internal::GetCapturedStdout();
  EXPECT_STREQ("", output_debug.c_str());
  EXPECT_STREQ("Error:   two floats: 42.010000, 0.33", output_error[0].c_str());

  console_bridge::setLogLevel(console_bridge::CONSOLE_BRIDGE_LOG_NONE);
  // get cout
  testing::internal::CaptureStdout();
  buffer.str("");
  CONSOLE_BRIDGE_logError("two floats: %f, %.2f", 42.01, 1/3.0);
  CONSOLE_BRIDGE_logDebug("two floats: %f, %.2f", 42.01, 1/3.0);
  output_error = split(buffer.str(), '\n');
  EXPECT_EQ(output_error.size(), 0u);
  output_debug = testing::internal::GetCapturedStdout();
  EXPECT_STREQ("", output_debug.c_str());

  // When done redirect cout to its old self
  std::cerr.rdbuf(sbuf);
}
