#include "ethan/core/main.h"

#include "ethan/utils/utils.h"

namespace ethan {

Main::Main() {}

Main::~Main() {}

} // namespace ethan

/////////////////////////////////////
// --------- Entry Point --------- //
extern ethan::Application* ethan::CreateApplication();

int main(int argc, char *argv[]) {
  ethan::Console::Init();
  ETLOG_CORE_INFO("Initialize Console!");
  std::string name = "Nghia";
  ETLOG_INFO("Hello {0}", name);

  auto app = ethan::CreateApplication();
  app->Init();
  delete app;
 
  return 0;
}
// ------- End Entry Point ------- //
/////////////////////////////////////
