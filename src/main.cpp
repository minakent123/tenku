#include "app/tenku.h"

int main(int arc, char** argv)
{
    Tenku tenku;
    if (tenku.Initialize()) {
        tenku.Run();
    }
    tenku.Finalize();
    return 0;
}