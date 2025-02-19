#include <cstdio>

#define production
#undef production

int main(int argc, const char * argv[]) {

    #ifdef production
    printf("Production\n");
    #else
    printf("Development\n");
    #endif

    return 0;
}
 