#include <QApplication>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QSpacerItem>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget mainWindow;
    mainWindow.setWindowTitle("example");
    QTabWidget *tabWidget = new QTabWidget(&mainWindow);
    QWidget *tabCaptain = new QWidget();
    QVBoxLayout *captainLayout = new QVBoxLayout(tabCaptain);
    QLabel *captainLabel = new QLabel("隊長", tabCaptain);
    QLabel *member1Label = new QLabel("組員1", tabCaptain);
    QLabel *member2Label = new QLabel("組員2", tabCaptain);
    QLabel *member3Label = new QLabel("組員3", tabCaptain);
    QLabel *fileLabel = new QLabel("", tabCaptain);
    QString defaultColor = "blue";
    captainLabel->setStyleSheet(QString("color: %1;").arg(defaultColor));
    member1Label->setStyleSheet(QString("color: %1;").arg(defaultColor));
    member2Label->setStyleSheet(QString("color: %1;").arg(defaultColor));
    member3Label->setStyleSheet(QString("color: %1;").arg(defaultColor));

    // 使用QSpacerItem來居中顯示
    QSpacerItem *spacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *spacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    captainLayout->addItem(spacerTop);
    captainLayout->addWidget(captainLabel, 0, Qt::AlignLeft); // 將對齊方式改為左對齊
    captainLayout->addWidget(member1Label, 0, Qt::AlignLeft); // 將對齊方式改為左對齊
    captainLayout->addWidget(member2Label, 0, Qt::AlignLeft); // 將對齊方式改為左對齊
    captainLayout->addWidget(member3Label, 0, Qt::AlignLeft); // 將對齊方式改為左對齊
    captainLayout->addItem(spacerBottom);
    captainLayout->addWidget(fileLabel, 0, Qt::AlignLeft); // 將對齊方式改為左對齊

    tabCaptain->setLayout(captainLayout);

    QWidget *tabMember1 = new QWidget();
    QVBoxLayout *member1Layout = new QVBoxLayout(tabMember1);
    QPushButton *changeColorButton = new QPushButton("Color Select", tabMember1);
    member1Layout->addWidget(changeColorButton);
    tabMember1->setLayout(member1Layout);

    QObject::connect(changeColorButton, &QPushButton::clicked, [&]() {
        QColor newColor = QColorDialog::getColor(Qt::blue, &mainWindow, "Color Select");
        if (newColor.isValid()) {
            QString colorStyle = QString("color: %1;").arg(newColor.name());
            captainLabel->setStyleSheet(colorStyle);
            member1Label->setStyleSheet(colorStyle);
            member2Label->setStyleSheet(colorStyle);
            member3Label->setStyleSheet(colorStyle);
            fileLabel->setStyleSheet(colorStyle);
        }
    });

    QWidget *tabMember2 = new QWidget();
    QVBoxLayout *member2Layout = new QVBoxLayout(tabMember2);
    QPushButton *changeFontButton = new QPushButton("Font Select", tabMember2);
    member2Layout->addWidget(changeFontButton);
    tabMember2->setLayout(member2Layout);

    QObject::connect(changeFontButton, &QPushButton::clicked, [&]() {
        bool ok;
        QFont newFont = QFontDialog::getFont(&ok, QFont("Arial", 10), &mainWindow, "Font Select");
        if (ok) {
            captainLabel->setFont(newFont);
            member1Label->setFont(newFont);
            member2Label->setFont(newFont);
            member3Label->setFont(newFont);
            fileLabel->setFont(newFont);
        }
    });

    QWidget *tabMember3 = new QWidget();
    QVBoxLayout *member3Layout = new QVBoxLayout(tabMember3);
    QPushButton *selectFileButton = new QPushButton("File Select", tabMember3);
    member3Layout->addWidget(selectFileButton);
    tabMember3->setLayout(member3Layout);

    QObject::connect(selectFileButton, &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&mainWindow, "File Select");
        if (!fileName.isEmpty()) {
            captainLabel->clear();
            member1Label->clear();
            member2Label->clear();
            member3Label->clear();
            fileLabel->setText(QFileInfo(fileName).absoluteFilePath());
            fileLabel->setAlignment(Qt::AlignCenter);
            QString memberColor = member1Label->styleSheet().split(": ")[1].split(";")[0];
            QFont memberFont = member1Label->font();
            fileLabel->setStyleSheet(QString("color: %1;").arg(memberColor));
            fileLabel->setFont(memberFont);
        }
    });

    tabWidget->addTab(tabCaptain, "隊長");
    tabWidget->addTab(tabMember1, "組員1");
    tabWidget->addTab(tabMember2, "組員2");
    tabWidget->addTab(tabMember3, "組員3");

    mainWindow.resize(400, 300);
    mainWindow.setLayout(new QVBoxLayout);
    mainWindow.layout()->addWidget(tabWidget);
    mainWindow.show();

    return app.exec();
}
