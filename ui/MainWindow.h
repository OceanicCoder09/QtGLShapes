#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;
class QComboBox;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onShapeSelectionChanged(int index);
    void onClearClicked();
    void onConvertTo3DClicked();

private:
    GLWidget *glWidget;
    QComboBox *shapeCombo;
};

#endif 
