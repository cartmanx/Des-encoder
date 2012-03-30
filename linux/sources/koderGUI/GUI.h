/* 
 * File:   GUI.h
 * Author: cartman
 *
 * Created on 26 grudzień 2010, 16:47
 */

#ifndef GUI_H
#define	GUI_H

#include <QDialog>
#include <string>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class GUI : public QDialog {

    Q_OBJECT

public:
    GUI(QWidget *parent = 0);

private slots:
    void setCodeFileName();
    void setKeyFileName();
    void setSzyfrowanie();
    void setDeszyfrowanie();
    //--
    void setEncodedFileName();

private:
    QString codeFileName;
    QString keyFileName;
    //--
    QString encodedFileName;

    std::string s_keyFileName;
    std::string s_codeFileName;
    //--
    std::string s_encodedFileName;
    QLabel *pathCodeLabel;
    QLabel *pathKeyLabel;
    //--
    QLabel *pathEncodedLabel;
};

#endif	/* GUI_H */

