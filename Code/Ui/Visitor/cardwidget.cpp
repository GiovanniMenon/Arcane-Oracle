#include "cardwidget.h"



#include "../../class/Generator/dall_eapi.h"

#include <QPixmap>
#include <QScreen>
#include <QPainter>
#include <QMovie>
#include <thread>
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

cardWidget::cardWidget(Deck * currDeck,QWidget *parent) : QWidget(parent) ,deck(currDeck)
{
    main = new QHBoxLayout(this);
    centerImage = new QHBoxLayout();
    gif = new QMovie("asset/Icon/gif1.gif");

    QGroupBox * menu = new QGroupBox();
    loading = new QLabel();

    loading->setMovie(gif);




    cardGroup = new QGroupBox();
    outside = new QHBoxLayout(menu);
    outsideVertical = new QVBoxLayout();
    QHBoxLayout*  outsideVerticalCentral = new QHBoxLayout();
    QHBoxLayout*  header = new QHBoxLayout();

    inside = new QVBoxLayout(cardGroup);

    image = new QGroupBox();
    imageLayout = new QVBoxLayout(image);
    costCard = new QLineEdit();
    QIntValidator *validator = new QIntValidator(costCard);
    imageLabel = new QLabel();


    validator->setRange(1, 9);
    costCard->setValidator(validator);



    nameCard = new QLineEdit();
    desc = new QTextEdit();
    desc -> setPlaceholderText("Descrizione Immagine");


    nameCard -> setPlaceholderText("Nome Carta");
    nameCard ->  setAlignment(Qt::AlignCenter);
    costCard ->  setAlignment(Qt::AlignCenter);

    header->addWidget(nameCard);
    header -> addWidget(costCard);

    centerImage->addStretch();
    centerImage ->addWidget(image);
    centerImage->addStretch();





    outside -> addWidget(cardGroup);
    outside -> addWidget(loading);


    outsideVerticalCentral ->  addWidget(desc);

    outsideVerticalCentral ->  setAlignment(Qt::AlignCenter);

    outsideVertical -> addStretch();
    outsideVertical -> addLayout(outsideVerticalCentral);

    outside-> addLayout(outsideVertical);
    outside-> setAlignment(Qt::AlignCenter);


    inside -> addLayout(header);
    inside -> addLayout(centerImage);


    cardGroup->setLayout(inside);



    main ->addWidget(menu);




    nameCard -> setMaxLength(22);
    nameCard ->setFixedWidth(300);
    cardGroup -> setFixedSize(370,600);
    menu -> setMinimumWidth(1200);
    menu ->setFixedHeight(620);
    desc -> setFixedSize(350,250);
    image -> setFixedSize(290,290);
    costCard -> setFixedWidth(45);
    costCard -> setMaxLength(1);

    cardGroup->setObjectName("cardGroup");
    nameCard ->setObjectName("cardName");
    costCard -> setObjectName("cardCost");
    image -> setObjectName("cardImage");
    desc ->setObjectName("cardDesc");

    //Manual
    manuale = new QDialog();
    textLabel = new QLabel();
    imageLabelManual = new QLabel();
    manualLayout = new QVBoxLayout(manuale);
    manualLayout->addWidget(imageLabelManual, 0, Qt::AlignCenter);
    manuale ->setStyleSheet("background-color: #323232;color : white ;font-size: 14px;");
    textLabel->setText("Tutti gli Attributi numerici hanno un valore in scala da 0 a 9. \n1)Nome Della carta\n2)Costo Della carta\n3)Descrizione della immagine della carta, meglio se in inglese e piu' dettagliata possibile.\n  In base a quello che si scrive in questo campo verra' generata l'immagine.\n");

}



bool cardWidget::checkInput() const{

    if(Deck::verifyInput(nameCard ->text().simplified().toStdString()) || desc -> toPlainText().simplified().isEmpty() || nameCard ->text().simplified().isEmpty() || costCard ->text().simplified().isEmpty() || deck->verifyCardName(nameCard ->text().toStdString())){
        return 0;
    }else{
         return 1;
    }
}



 void cardWidget::generate() {
     desc -> hide();
     cardGroup -> hide();
     loading ->show();

     gif->start();






    //Nascondo il campo desc
    //Setto La carta come non piu modificabile
    nameCard -> setReadOnly(true);
    costCard -> setReadOnly(true);
    descText = desc -> toPlainText();
    std::string futureDesc = descText.toStdString();
    DALL_E_generator generator;

    QFutureWatcher<std::string>* watcher = new QFutureWatcher<std::string>(this);
    QObject::connect(watcher, &QFutureWatcher<std::string>::finished, this, [=]() {
        QFuture<std::string> future = watcher->future();
        path = future.result();

        QPixmap pixmap(QString::fromStdString(path));

        std::string searchString = "CardImg";

        size_t index = path.find(searchString);
         if (index != std::string::npos) {
        path.replace(index, searchString.length(), "Card");
         }
        scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageLabel -> setPixmap(scaledPixmap);

        imageLayout -> addWidget(imageLabel);
        imageLayout -> setContentsMargins(0,0,0,0);
        imageLayout -> setAlignment(Qt::AlignCenter);

        cardGroup -> show();
        gif->stop();
        loading ->hide();

        watcher->deleteLater();
    });

    QFuture<std::string> AsyncG = QtConcurrent::run([&generator,futureDesc, this]() {
        std::string result = generator.generate(futureDesc);
        std::string path = generator.convert(result,nameCard->text().toStdString(),deck ->getName());
        return path;
    });

    watcher->setFuture(AsyncG);


}

 QPixmap cardWidget::takeScreen(bool i) const{

     // Catturare l'immagine dell'area specificata

     QRect area = cardGroup->geometry();
     QPixmap screenshot(area.size());
     QPainter painter(&screenshot);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
     painter.setRenderHint(QPainter::TextAntialiasing, true);
     cardGroup->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
     // Salvare l'immagine su disco
     if(i){

        screenshot.save(QString::fromStdString(path));
     }
     return screenshot;

 }

 void cardWidget::takeScreen(Card* c){
    QRect area = cardGroup->geometry();
    QPixmap screenshot(area.size());
    QPainter painter(&screenshot);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    cardGroup->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    // Salvare l'immagine su disco
    screenshot.save(QString::fromStdString(c->getUrl()));

    // Aggiorna l'immagine visualizzata nel widget
    imageLabel->setPixmap(screenshot);
    imageLabel->setScaledContents(true);
 }

 void cardWidget::setFieldsCardSlot() {
     card->setName(nameCard->text().toStdString());
     card->setCost(costCard->text().toInt());

     std::string path = card->getUrl();
     std::string newUrl;

     // Trova l'ultima occorrenza di '/'
     size_t lastSlashPos = path.find_last_of('/');

     if (lastSlashPos != std::string::npos) {
     // Estrai la parte del percorso dopo l'ultima '/'
     std::string newPath = path.substr(0, lastSlashPos + 1);

     // Nuovo nome da assegnare
     std::string newFileName = card->getName()+ ".jpg";

     // Concatena il nuovo nome al percorso
     newPath += newFileName;

     // Sostituisci la stringa originale con la nuova
     newUrl = newPath;
     }

     card->setPath(newUrl);

     std::string imgPathOld = path;
     std::string imgPathNew = newUrl;
     std::string searchString = "Card";

     size_t index1 = imgPathOld.find(searchString);
     size_t index2 = imgPathNew.find(searchString);
      if (index1 != std::string::npos && index2!= std::string::npos ) {
     imgPathOld.replace(index1, searchString.length(), "CardImg");
     imgPathNew.replace(index2, searchString.length(), "CardImg");

     QFile::rename(QString::fromStdString(path), QString::fromStdString(newUrl));
     QFile::rename(QString::fromStdString(imgPathOld), QString::fromStdString(imgPathNew));
    }
  }


