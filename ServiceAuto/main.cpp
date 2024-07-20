#include <iostream>
#include "./modules/autoServiceManager/autoServiceManager.h"
using namespace std;

int main() {
    AutoServiceManager autoServiceManager;
    autoServiceManager.initialize();
    autoServiceManager.displayMainMenu(autoServiceManager);

    return 0;
}