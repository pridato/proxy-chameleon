#include <stdio.h>
#include "../include/proxy.h"
#include "../include/constants.h"

int main(void) {
    start_proxy(PROXY_PORT, SERVER_IP, SERVER_PORT);
    return 0;
}
