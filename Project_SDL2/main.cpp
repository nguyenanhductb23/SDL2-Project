#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"
#include "StandardObject.h"
#include "PrintText.h"
#include "MainEngine.h"
#include "Sound.h"
#include "Struct.h"

using namespace std;

int main(int argc, char* argv[])
{
    Media* media = new Media();
    startMenu(media);
    delete media;
    return 0;
}
