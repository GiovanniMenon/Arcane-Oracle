QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
INCLUDEPATH += /Users/endyhysa/Qt/jsoncpp-master/include
LIBS += -L/usr/local/lib -ljsoncpp -lcurl
MOC_DIR = profiles
OBJECTS_DIR = profiles

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ui/DeckHomePage/cardinfopage.cpp \
    Ui/DeckHomePage/cardpage.cpp \
    Ui/DeckHomePage/homedeckpage.cpp \
    Ui/DeckHomePage/showdeckpage.cpp \
    Ui/DeckHomePage/typepage.cpp \
    Ui/HomePage/homepage.cpp \
    Ui/HomePage/loadpage.cpp \
    Ui/HomePage/manualdeck.cpp \
    Ui/HomePage/newdeckpage.cpp \
    Ui/Utils/clickablelabel.cpp \
    Ui/Visitor/artifactwidget.cpp \
    Ui/Visitor/cardwidget.cpp \
    Ui/Visitor/effectwidget.cpp \
    Ui/Visitor/fieldwidget.cpp \
    Ui/Visitor/monsterwidget.cpp \
    Ui/Visitor/spellwidget.cpp \
    Ui/Visitor/trapwidget.cpp \
    Ui/Visitor/visitor.cpp \
    class/Cards/abstractcard.cpp \
    class/Cards/artifactcard.cpp \
    class/Generator/dall_eapi.cpp \
    class/Deck/deck.cpp \
    class/Cards/effectcards.cpp \
    class/Generator/imagegenerator.cpp \
    main.cpp \
    class/Cards/monstercard.cpp \
    class/Cards/spellcard.cpp \
    class/Cards/territorycard.cpp \
    class/Cards/trapcard.cpp \
    Ui/mainwindow.cpp \

HEADERS += \
    Ui/DeckHomePage/cardinfopage.h \
    Ui/DeckHomePage/cardpage.h \
    Ui/DeckHomePage/homedeckpage.h \
    Ui/DeckHomePage/showdeckpage.h \
    Ui/DeckHomePage/typepage.h \
    Ui/HomePage/homepage.h \
    Ui/HomePage/loadpage.h \
    Ui/HomePage/manualdeck.h \
    Ui/HomePage/newdeckpage.h \
    Ui/Utils/clickablelabel.h \
    Ui/Visitor/artifactwidget.h \
    Ui/Visitor/cardwidget.h \
    Ui/Visitor/effectwidget.h \
    Ui/Visitor/fieldwidget.h \
    Ui/Visitor/monsterwidget.h \
    Ui/Visitor/spellwidget.h \
    Ui/Visitor/trapwidget.h \
    Ui/Visitor/visitor.h \
    class/Template/Dlist.h \
    class/Cards/abstractcard.h \
    class/Cards/artifactcard.h \
    class/Generator/dall_eapi.h \
    class/Deck/deck.h \
    class/Cards/effectcards.h \
    class/Generator/imagegenerator.h \
    class/Cards/monstercard.h \
    class/Cards/spellcard.h \
    class/Cards/territorycard.h \
    class/Cards/trapcard.h \
    Ui/mainwindow.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    asset/Manual/manualDeck.txt
