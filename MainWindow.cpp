//
// Created by Lorenzo Pesci on 2019-02-11.
//

#include "MainWindow.h"
#include <string>

MainWindow::MainWindow(ResourcesLoader * concreteLoader) {  //creazione parte grafica
    //imposta una dimensione fissa alla finestra
    this->setFixedSize(QSize(600, 400));

    //imopsta il titolo della finestra
    this->setWindowTitle("Resources loader");
    this->setFixedSize(QSize(600, 400));

    //imposta il testo di info
    text = new QLabel("Classe che carica file di risorse e aggiorna una progress bar con QT.", this);
    text->setGeometry(QRect(QPoint(150, 15), QSize(300, 100)));
    text->setStyleSheet("QLabel { background-color : white; color : black; }");
    text->setWordWrap(true);
    text->setAlignment(Qt::AlignCenter);

    //imposta il bottone
    button = new QPushButton("Load resources!", this);
    button->setGeometry(QRect(QPoint(225, 143), QSize(150, 30)));

    //imposta la progress bar
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(QRect(QPoint(150, 190), QSize(300, 30)));
    //button->setGeometry(QRect(QPoint(225, 125), QSize(150, 30)));

    progressBar->setMinimum(0);
    progressBar->setMaximum(1000);
    progressBar->setValue(0);


    //imposta il campo di testo
    textBox = new QTextEdit(this);
    textBox->setGeometry(QRect(QPoint(50, 240), QSize(500, 140)));
    textBox->setText("---> Ready to load resources!\n");
    textBox->setReadOnly(true);


    //assegna il loader alla mainwindow
    loader = concreteLoader;


    //connette il bottone alla funzione che deve attivare
    connect(button, SIGNAL (released()), this, SLOT (startLoadingResources()));
}

void MainWindow::startLoadingResources() {  //viene creato un vettore di file generici
    progressBar->setValue(0);
    textBox->setText("");
    std::vector<std::string> files;
    files.push_back("File1.txt");
    files.push_back("File2.txt");
    files.push_back("pizza.jpg");
    files.push_back("book.jpg");
    files.push_back("florence.jpg");
    files.push_back("iPhone.jpg");

    try {
        loader->loadFiles(files);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void MainWindow::update() {
    if (loader->isLoadingCompleted() == true) {

        //Update Progress Bar Percentage
        progressBar->setValue(progressBar->value() + (1000/loader->getNumOfResources()));

        //Update text log
        QString log = "✅ Loaded file '" + QString(loader->getFilename()) + QString("' successfully (") + QString::number(loader->getFileSize()) + QString(" bytes).") + "\n";
        textBox->append(log);

        //Update Button Text
        QString percentText = QString::number(progressBar->value() / 10) + QString("% loaded!");
        button->setText(percentText);
    } else {
        //Update text
        QString log = "❌ Could not load file '" + QString(loader->getFilename()) + "'\n";
        textBox->append(log);
    }
}