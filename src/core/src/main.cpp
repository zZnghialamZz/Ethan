#include "ethan/core/main.h"

namespace ethan {

Main::Main() {}

Main::~Main() {}

} // namespace ethan

/////////////////////////////////////
// --------- Entry Point --------- //
extern ethan::Application* ethan::CreateApplication();

int main(int argc, char *argv[]) {
  auto app = ethan::CreateApplication();
  app->Init();
  delete app;
 
  return 0;
}
// ------- End Entry Point ------- //
/////////////////////////////////////
