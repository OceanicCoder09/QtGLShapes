#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class glWindow;
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
    void onExportSTLClicked();

private:
    glWindow *glWidget;
    QComboBox *shapeCombo;
};

#endif 
