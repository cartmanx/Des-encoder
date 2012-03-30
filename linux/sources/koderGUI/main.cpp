/*
 * File:   main.cpp
 * Author: cartman
 *
 * Created on 26 grudzień 2010, 16:45
 * http://devplus.zzl.org
 * Patryk Pawlak
 * patryk.dev@gmail.com
 *
 *	Des Encoder	*
 */

#include <QtGui/QApplication>
#include "GUI.h"
#include "cEncode.h"
#include "cKey.h"
int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    GUI gui;
    return gui.exec();
}
