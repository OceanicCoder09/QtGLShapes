#include "MainWindow.h"
#include "glWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *topLayout = new QHBoxLayout();
    
    QLabel *shapeLabel = new QLabel("Select Shape:", this);
    shapeCombo = new QComboBox(this);
    shapeCombo->addItem("Triangle");
    shapeCombo->addItem("Square");
    shapeCombo->addItem("Rectangle");
    shapeCombo->addItem("Circle");
    
    QPushButton *clearBtn = new QPushButton("Clear", this);
    QPushButton *convert3DBtn = new QPushButton("Convert to 3D", this);
    QPushButton *exportBtn = new QPushButton("Export STL", this);
    QPushButton *importBtn = new QPushButton("Import STL", this);
    
    topLayout->addWidget(shapeLabel);
    topLayout->addWidget(shapeCombo);
    topLayout->addWidget(clearBtn);
    topLayout->addWidget(convert3DBtn);
    topLayout->addWidget(exportBtn);
    topLayout->addWidget(importBtn);
    topLayout->addStretch();
    
    mainLayout->addLayout(topLayout);
    
    glWidget = new glWindow(this);
    mainLayout->addWidget(glWidget);

    connect(shapeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeSelectionChanged(int)));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(convert3DBtn, SIGNAL(clicked()), this, SLOT(onConvertTo3DClicked()));
    connect(exportBtn, SIGNAL(clicked()), this, SLOT(onExportSTLClicked()));
    connect(importBtn, SIGNAL(clicked()), this, SLOT(onImportSTLClicked()));
    
    resize(800, 600);
    setWindowTitle("2D Shapes");
}

MainWindow::~MainWindow() {}

void MainWindow::onShapeSelectionChanged(int index) {
    glWidget->setPendingShapeType(index);
    glWidget->setFocus(); 
}

void MainWindow::onClearClicked() {
    glWidget->clearShape();
}

void MainWindow::onConvertTo3DClicked() {
    glWidget->convertTo3D();
}

void MainWindow::onExportSTLClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save ASCII STL"), "", tr("STL Files (*.stl);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }
    
    if (glWidget->exportToSTL(fileName)) {
        QMessageBox::information(this, tr("Export Successful"), tr("Successfully exported 3D shape to STL file."));
    } else {
        QMessageBox::warning(this, tr("Export Failed"), tr("Could not export shape. Please ensure you have placed a shape and converted it to 3D first."));
    }
}

void MainWindow::onImportSTLClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open ASCII STL"), "", tr("STL Files (*.stl);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }
    
    glWidget->importSTL(fileName);
}
