#include "Headers/mouse_and_keyboard.h"
#include "Headers/Utils.h"
#include "Headers/Duc_s_algo.h"
#include "Headers/StandardObject.h"
#include "Headers/MainEngine.h"
#include "Headers/Media.h"

using namespace std;

int main(int argc, char* argv[])
{
    Media* media = new Media();
    startMenu(media);
    delete media;
    return 0;
}
