// Regression for logging storage destroyed before application static objects.
#include <console_bridge/console.h>

namespace
{
struct ShutdownLogger
{
    ~ShutdownLogger()
    {
        CONSOLE_BRIDGE_logWarn("Logging from an application static destructor");
    }
};

ShutdownLogger shutdown_logger;
}  // namespace

int main()
{
    // Without eager shared-library initialization, this first call constructs
    // the logger after shutdown_logger; reverse destruction makes logging unsafe.
    (void)console_bridge::getLogLevel();
    return 0;
}
