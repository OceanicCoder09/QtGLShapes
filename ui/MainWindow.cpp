#include "MainWindow.h"
#include "GLWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QWidget>

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
    
    topLayout->addWidget(shapeLabel);
    topLayout->addWidget(shapeCombo);
    topLayout->addWidget(clearBtn);
    topLayout->addWidget(convert3DBtn);
    topLayout->addStretch();
    
    mainLayout->addLayout(topLayout);
    
    glWidget = new GLWidget(this);
    mainLayout->addWidget(glWidget);

    connect(shapeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeSelectionChanged(int)));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(convert3DBtn, SIGNAL(clicked()), this, SLOT(onConvertTo3DClicked()));
    
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
