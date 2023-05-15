#include "cardwidget.h"



#include "../../class/Generator/dall_eapi.h"

#include <QPixmap>
#include <QScreen>
#include <QPainter>
cardWidget::cardWidget(Deck * currDeck,QWidget *parent) : QWidget(parent) ,deck(currDeck)
{
    main = new QHBoxLayout(this);
    centerImage = new QHBoxLayout();



    QGroupBox * menu = new QGroupBox();

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


    outside->addWidget(cardGroup);
    outsideVerticalCentral ->  addWidget(desc);
    outsideVerticalCentral ->  setAlignment(Qt::AlignCenter);
    outsideVertical -> addLayout(outsideVerticalCentral);

    outside->addLayout(outsideVertical);



    inside -> addLayout(header);
    inside -> addLayout(centerImage);


    cardGroup->setLayout(inside);


    main-> addStretch();
    main ->addWidget(menu);
    main-> addStretch();



    nameCard -> setMaxLength(22);
    nameCard ->setFixedWidth(300);
    cardGroup -> setFixedSize(370,600);
    menu -> setFixedWidth(1200);
    desc -> setFixedSize(350,250);
    image -> setFixedSize(290,290);

    cardGroup->setObjectName("cardGroup");
    nameCard ->setObjectName("cardName");
    costCard -> setObjectName("cardCost");
    image -> setObjectName("cardImage");
    desc ->setObjectName("cardDesc");

}



bool cardWidget::checkInput() const{

    if(nameCard ->text().simplified().isEmpty() || costCard ->text().simplified().isEmpty() || deck->verifyCardName(nameCard ->text().toStdString())){
        return 0;
    }else{
         return 1;
    }
}




 void cardWidget::generate() {

    DALL_E_generator generator;

    path = generator.convert(generator.generate(desc->toPlainText().toStdString()),nameCard->text().toStdString(),deck ->getName());
    descText = desc -> toPlainText();

    //Nascondo il campo desc
    desc -> hide();

    //Setto La carta come non piu modificabile
    nameCard -> setReadOnly(true);
    costCard -> setReadOnly(true);

    // Aggiungere che si stonda l'immagine;


    QPixmap pixmap(QString::fromStdString(path)); // path

    scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel -> setPixmap(scaledPixmap);

    imageLayout -> addWidget(imageLabel);
    imageLayout -> setContentsMargins(0,0,0,0);


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

