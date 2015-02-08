/*Copyright (c) 2014 Gennady Gaidukov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "World.h"
#include <QMainWindow>
#include <QFileDialog>
#include "aboutwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void toolBarSlot(bool checked);
    void statusBarSlot(bool checked);
    void exitSlot();
    void onAboutClick();
    void onOpenClick();
    void onSaveClick();
    void onSaveAsClick();
    void onNewClick();
public slots:
    void onWorldInitialized();

protected:
    void resizeEvent(QResizeEvent * event);
private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;
    //actions for menuBar
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QAction *New;
    QAction *open;
    QAction *save;
    QAction *saveAs;
    QAction *print;
    QAction *printPrev;
    QAction *printSetup;
    QAction *recFile;
    QAction *exit;

    QAction *undo;
    QAction *cut;
    QAction *copy;
    QAction *paste;

    QAction *toolBar;
    QAction *statusBr;

    QAction *about;

};

#endif // MAINWINDOW_H