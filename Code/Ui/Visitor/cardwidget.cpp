#include "cardwidget.h"
#include "class/Generator/dall_eapi.h"

std::string cardWidget::getUrl() const{ return path; }

//Costruttore
cardWidget::cardWidget(Deck * currDeck,QWidget *parent) : QWidget(parent) ,deck(currDeck)
{
    main = new QHBoxLayout(this);
    centerImage = new QHBoxLayout();
    gif = new QMovie("asset/Icon/gif.gif");

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
    //Ritorna 0 se i vari requisiti non sono soddisfatti
    if(Deck::verifyInput(nameCard ->text().simplified().toStdString()) || desc -> toPlainText().simplified().isEmpty() || nameCard ->text().simplified().isEmpty() || costCard ->text().simplified().isEmpty() || deck->verifyCardName(nameCard ->text().toStdString())){
        return 0;
    }else{
         return 1;
    }
}


void cardWidget::generate() {
    //Genera l'immagine in base a cosa e' stato scritto nella descrizione
    //Utilizziamo QFutureWatcher e QFuture per rendere asincrono l'esecuzione di questa funzione.
    //Emette un segnale quando ha finito di generare la carta.

    DALL_E_generator generator;
    desc -> hide();
    cardGroup -> hide();
    loading ->show();

    gif->start();

    nameCard -> setReadOnly(true);
    costCard -> setReadOnly(true);
    descText = desc -> toPlainText();
    std::string futureDesc = descText.toStdString();

    QFutureWatcher<std::string>* watcher = new QFutureWatcher<std::string>(this);
    QObject::connect(watcher, &QFutureWatcher<std::string>::finished, this, [=]() {
        QFuture<std::string> future = watcher->future();
        path = future.result();

        QPixmap pixmap(QString::fromStdString(path));

        std::string searchString = "CardImg";

        size_t lastSlashPos = path.find_last_of('/');
        size_t secondLastSlashPos = path.find_last_of('/', lastSlashPos - 1);
        size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
        size_t index = path.find(searchString, secondLastSlashPos + 1);
        if (index != std::string::npos) {
            path.replace(index, substringLength, "Card");
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

        emit generateFinishSignal();
    });

    QFuture<std::string> AsyncG = QtConcurrent::run([&generator,futureDesc, this]() {
        std::string result = generator.generate(futureDesc);
        std::string path = generator.convert(result,nameCard->text().toStdString(),deck ->getName());
        return path;
    });

    watcher->setFuture(AsyncG);


}

 QPixmap cardWidget::takeScreen(bool i) const{
     //Esegue lo screenShot della carta, puo' salvarlo oppure no,
     QRect area = cardGroup->geometry();
     QPixmap screenshot(area.size());
     QPainter painter(&screenshot);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
     painter.setRenderHint(QPainter::TextAntialiasing, true);
     cardGroup->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
     if(i){

        screenshot.save(QString::fromStdString(path));
     }
     return screenshot;

 }

 void cardWidget::takeScreen(Card* c){
     //Data una carta esegue lo screenshot e salva l'immagine nel suo url.
    QRect area = cardGroup->geometry();
    QPixmap screenshot(area.size());
    QPainter painter(&screenshot);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    cardGroup->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);

    screenshot.save(QString::fromStdString(c->getUrl()));

    imageLabel->setPixmap(screenshot);
    imageLabel->setScaledContents(true);
 }

 bool cardWidget::isNameCardUnique(const std::string& nameToCheck) const{
    //Controlla che il nome della carta sia univoco nel deck.
    std::string url = card->getUrl();
    size_t lastSlashPos = url.find_last_of('/');
        std::string newPath = url.substr(0, lastSlashPos + 1);
        QDir directory(QString::fromStdString(newPath));
        QStringList filters;
        filters << "*.jpg";

        QStringList fileList = directory.entryList(filters, QDir::Files);
        foreach(const QString& fileName, fileList) {
            QString cardName = fileName.section('.', 0, 0);
            if (nameToCheck == cardName.toStdString()) {
                return false;
            }
        }
        return true;
}

 void cardWidget::setFieldsCardSlot() {
    //Pre: Si ha una carta
    //Post : Si modifica la carta e i suoi parametri andando ad aggiornare eventualemente anche la sua immagine in memoria.
    oldName = card->getName();
    oldCost = card->getCost();

    if((isNameCardUnique(nameCard->text().toStdString()) || nameCard->text().toStdString() == oldName) && !(Deck::verifyInput(nameCard->text().toStdString()))){
    card->setName(nameCard->text().toStdString());
    card->setCost(costCard->text().toInt());

    std::string path = card->getUrl();
    std::string newUrl;
    size_t lastSlashPos = path.find_last_of('/');

    if (lastSlashPos != std::string::npos) {
    std::string newPath = path.substr(0, lastSlashPos + 1);
    std::string newFileName = card->getName()+ ".jpg";
    newPath += newFileName;
    newUrl = newPath;
    }

     card->setPath(newUrl);

     std::string imgPathOld = path;
     std::string imgPathNew = newUrl;
     std::string searchString = "Card";

     size_t lastSlashPos1 = imgPathOld.find_last_of('/');
     size_t lastSlashPos2 = imgPathNew.find_last_of('/');

     size_t secondLastSlashPos1 = imgPathOld.find_last_of('/', lastSlashPos1 - 1);
     size_t secondLastSlashPos2 = imgPathNew.find_last_of('/', lastSlashPos2 - 1);

     size_t substringLength1 = lastSlashPos1 - secondLastSlashPos1 - 1;
     size_t substringLength2 = lastSlashPos2 - secondLastSlashPos2 - 1;

     size_t index1 = imgPathOld.find(searchString, secondLastSlashPos1 + 1);
     size_t index2 = imgPathNew.find(searchString, secondLastSlashPos2 + 1);
     if (index1 != std::string::npos && index2 != std::string::npos) {
        imgPathOld.replace(index1, substringLength1, "CardImg");
        imgPathNew.replace(index2, substringLength2, "CardImg");
        screenshot = 1;

        QFile::rename(QString::fromStdString(path), QString::fromStdString(newUrl));
        QFile::rename(QString::fromStdString(imgPathOld), QString::fromStdString(imgPathNew));
        }
    }
    else{
        QMessageBox::critical(this, "Errore", "ERRORE\nModifiche non apportate, non utilizzare nomi già esistenti o caratteri non ammessi");
        card->setName(oldName);
        card->setCost(oldCost);
        screenshot = 0;
    }
}



