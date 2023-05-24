#include "cardwidget.h"



#include "../../class/Generator/dall_eapi.h"

#include <QPixmap>
#include <QScreen>
#include <QPainter>
#include <QMovie>
#include <thread>

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


    DALL_E_generator generator;



    //Nascondo il campo desc
    //Setto La carta come non piu modificabile
    nameCard -> setReadOnly(true);
    costCard -> setReadOnly(true);
    descText = desc -> toPlainText();
    path = generator.convert(generator.generate(desc->toPlainText().toStdString()),nameCard->text().toStdString(),deck ->getName());


    QPixmap pixmap(QString::fromStdString(path)); // path

    std::string searchString = "CardImg";

    size_t index = path.find(searchString);
    path.replace(index, searchString.length(), "Card");

    scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel -> setPixmap(scaledPixmap);

    imageLayout -> addWidget(imageLabel);
    imageLayout -> setContentsMargins(0,0,0,0);

    gif->stop();
    loading ->hide();
    cardGroup -> show();


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

