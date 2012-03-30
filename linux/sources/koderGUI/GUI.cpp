/*
 * File:   GUI.cpp
 * Author: cartman
 *
 * Created on 26 grudzień 2010, 16:47
 */
#include <QtGui>
#include <qt4/QtGui/qpushbutton.h>
#include "GUI.h"
#include "cEncode.h"
#include "cKey.h"

GUI::GUI(QWidget *parent) : QDialog(parent) {

    pathCodeLabel = new QLabel;
    int frameStyle = QFrame::Sunken | QFrame::Panel;

    pathCodeLabel->setFrameStyle(frameStyle);
    QPushButton *codeButton = new QPushButton;
    codeButton->setText("Wczytaj plik do zaszyfrowania");

    pathKeyLabel = new QLabel;
    pathKeyLabel->setFrameStyle(frameStyle);
    QPushButton *keyButton = new QPushButton;
    keyButton->setText("Wczytaj plik z kluczem");

    pathEncodedLabel = new QLabel;
    pathEncodedLabel->setFrameStyle(frameStyle);
    QPushButton *encodedFileNameButton = new QPushButton;
    encodedFileNameButton->setText("Wskaz zakodowany plik aby zdeszyfrowac");

    QPushButton *deszyfruj = new QPushButton;
    deszyfruj->setText(tr("Odszyfruj wiadomosc"));

    QPushButton *szyfruj = new QPushButton;
    szyfruj->setText(tr("Zaszyfruj wiadomosc"));

    connect(codeButton,SIGNAL(clicked()), this, SLOT(setCodeFileName()));
    connect(keyButton,SIGNAL(clicked()), this, SLOT(setKeyFileName()));
    connect(szyfruj, SIGNAL(clicked()), this, SLOT(setSzyfrowanie()));
    connect(encodedFileNameButton, SIGNAL(clicked()), this, SLOT(setEncodedFileName()));
    connect(deszyfruj, SIGNAL(clicked()), this, SLOT(setDeszyfrowanie()));

    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1,1);
    layout->setColumnMinimumWidth(1,250);
    layout->addWidget(codeButton, 0,0);
    layout->addWidget(pathCodeLabel,0,1);
    layout->addWidget(keyButton,1,0);
    layout->addWidget(pathKeyLabel,1,1);
    layout->addWidget(encodedFileNameButton,2,0);
    layout->addWidget(pathEncodedLabel,2,1);
    layout->addWidget(szyfruj, 3, 0);
    layout->addWidget(deszyfruj,4,0);
    setLayout(layout);

    setWindowTitle(tr("szyfrator DES -- Pawlak Patryk"));

}

void GUI::setCodeFileName(){

    QString selectedFilter;
    codeFileName = QFileDialog::getOpenFileName(this,
                                                tr("Wybierz plik"),
                                                tr(""),
                                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter);
    if(!codeFileName.isEmpty()){
        pathCodeLabel->setText(codeFileName);
        s_codeFileName = codeFileName.toStdString();
    }

}

void GUI::setKeyFileName(){

    QString selectedFilter1;
    keyFileName = QFileDialog::getOpenFileName(this,
                                                tr("Wybierz plik"),
                                                tr(""),
                                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter1);
    if(!keyFileName.isEmpty()){
        pathKeyLabel->setText(keyFileName);
        s_keyFileName = keyFileName.toStdString();
    }


}

void GUI::setEncodedFileName(){

    QString selectedFilter2;
    encodedFileName = QFileDialog::getOpenFileName(this,
                                                tr("Wybierz plik"),
                                                tr(""),
                                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter2);
    if(!encodedFileName.isEmpty()){
        pathEncodedLabel->setText(encodedFileName);
        s_encodedFileName = encodedFileName.toStdString();
    }
}

void GUI::setSzyfrowanie(){
    cKey o_klucz;
    o_klucz.read_f(s_keyFileName);
o_klucz.make_K();
o_klucz.make_Kplus();
o_klucz.make_C_and_D();

o_klucz.make_Kn();

cEncode o_enco;
o_enco.iterations(o_klucz); //proces szyfrowania

}

void GUI::setDeszyfrowanie(){
    cKey o_klucz;
    o_klucz.read_f(s_keyFileName);
o_klucz.make_K();
o_klucz.make_Kplus();
o_klucz.make_C_and_D();

o_klucz.make_Kn();
cEncode o_decrypt;
o_decrypt.iterations_decrypt(o_klucz, s_encodedFileName);

}
