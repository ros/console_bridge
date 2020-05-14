/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2020, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include <cassert>
#include <gtest/gtest.h>

#include <console_bridge/console.h>

class OutputHandlerString : public console_bridge::OutputHandler
{
public:
  OutputHandlerString()
  {
  }

  ~OutputHandlerString() override
  {
  }

  void log(const std::string & text, console_bridge::LogLevel level, const char *filename, int line) override
  {
    (void)line;
    (void)filename;
    text_ = text;
    log_level_ = level;
  }

  std::string text_;
  console_bridge::LogLevel log_level_{console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_NONE};
};

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
  // This tests that multiple arguments to the CONSOLE_BRIDGE_* macros get
  // formatted and output properly.

  OutputHandlerString string_oh;
  console_bridge::useOutputHandler(&string_oh);
  EXPECT_EQ(&string_oh, console_bridge::getOutputHandler());

  CONSOLE_BRIDGE_logError("no extra parameters");
  EXPECT_EQ(string_oh.text_, "no extra parameters");

  CONSOLE_BRIDGE_logError("one integer: %d", 42);
  EXPECT_EQ(string_oh.text_, "one integer: 42");

  CONSOLE_BRIDGE_logError("two floats: %.2f, %.2f", 42.01, 1/3.0);
  EXPECT_EQ(string_oh.text_, "two floats: 42.01, 0.33");
}

TEST(ConsoleTest, BasicOutputHandler)
{
  // This tests that we can install a custom OutputHandler and log to it.

  OutputHandlerString string_oh;
  console_bridge::useOutputHandler(&string_oh);
  EXPECT_EQ(&string_oh, console_bridge::getOutputHandler());
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);

  CONSOLE_BRIDGE_logDebug("Debug");

  EXPECT_EQ(string_oh.text_, "Debug");
  EXPECT_EQ(string_oh.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);
  EXPECT_EQ(console_bridge::getLogLevel(), console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);
}

TEST(ConsoleTest, LogLevelTooLow)
{
  // This tests that the custom OutputHandler log() method is *not* invoked if
  // the log level set in console_bridge is higher than the message log level.
  OutputHandlerString string_oh;
  console_bridge::useOutputHandler(&string_oh);
  EXPECT_EQ(&string_oh, console_bridge::getOutputHandler());
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);

  CONSOLE_BRIDGE_logDebug("Debug");

  EXPECT_EQ(string_oh.text_, "");
  EXPECT_EQ(string_oh.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_NONE);
}

TEST(ConsoleTest, SwapHandlers)
{
  // This tests the ability to swap output handlers from one to another.

  OutputHandlerString string_oh1;
  OutputHandlerString string_oh2;

  console_bridge::useOutputHandler(&string_oh1);
  EXPECT_EQ(&string_oh1, console_bridge::getOutputHandler());
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);

  CONSOLE_BRIDGE_logInform("Info1");

  console_bridge::useOutputHandler(&string_oh2);
  EXPECT_EQ(&string_oh2, console_bridge::getOutputHandler());

  CONSOLE_BRIDGE_logInform("Info2");

  EXPECT_EQ(string_oh1.text_, "Info1");
  EXPECT_EQ(string_oh1.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);

  EXPECT_EQ(string_oh2.text_, "Info2");
  EXPECT_EQ(string_oh2.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);
}

TEST(ConsoleTest, RestoreHandler)
{
  // This tests the console_bridge::restorePreviousOutputHandler() function.

  OutputHandlerString string_oh1;
  OutputHandlerString string_oh2;

  console_bridge::useOutputHandler(&string_oh1);
  EXPECT_EQ(&string_oh1, console_bridge::getOutputHandler());
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);

  console_bridge::useOutputHandler(&string_oh2);
  EXPECT_EQ(&string_oh2, console_bridge::getOutputHandler());

  CONSOLE_BRIDGE_logInform("Info2");

  console_bridge::restorePreviousOutputHandler();

  CONSOLE_BRIDGE_logInform("Info1");

  EXPECT_EQ(string_oh1.text_, "Info1");
  EXPECT_EQ(string_oh1.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);

  EXPECT_EQ(string_oh2.text_, "Info2");
  EXPECT_EQ(string_oh2.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_INFO);
}

TEST(ConsoleTest, NoOutputHandler)
{
  // This tests that calling console_bridge::noOutputHandler() results in
  // no output, even when our custom OutputHandler is "installed".

  OutputHandlerString string_oh;
  console_bridge::useOutputHandler(&string_oh);
  EXPECT_EQ(&string_oh, console_bridge::getOutputHandler());
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);

  CONSOLE_BRIDGE_logDebug("Debug");
  EXPECT_EQ(string_oh.text_, "Debug");
  EXPECT_EQ(string_oh.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);

  string_oh.text_ = "";
  string_oh.log_level_ = console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_NONE;

  console_bridge::noOutputHandler();
  EXPECT_EQ(nullptr, console_bridge::getOutputHandler());

  CONSOLE_BRIDGE_logDebug("Debug");
  EXPECT_EQ(string_oh.text_, "");
  EXPECT_EQ(string_oh.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_NONE);

  console_bridge::restorePreviousOutputHandler();
  CONSOLE_BRIDGE_logDebug("Debug2");

  EXPECT_EQ(string_oh.text_, "Debug2");
  EXPECT_EQ(string_oh.log_level_, console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);
}

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
