#include <iostream>
#include "HydraEngine.h"

int main() {

    HydraEngine engine;

    engine.startup();
    engine.run();
    engine.shutdown();

    return 0;

}