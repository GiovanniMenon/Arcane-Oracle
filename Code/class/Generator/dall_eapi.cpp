#include "dall_eapi.h"
#include "curl/curl.h"
#include <fstream>


DALL_E_generator::DALL_E_generator()  {
    std::ifstream file("APIKEY.txt");
        if (file.is_open()) {
            std::string key;
            std::getline(file, key);
            apiKey = "Authorization: Bearer " + key;
            file.close();
        }
}

size_t DALL_E_generator::callback(char* data, size_t size, size_t nmemb, std::string* buffer) {

   size_t realsize = size * nmemb;
   buffer->append(data, realsize);
   return realsize;
 }

std::string DALL_E_generator::generate(const std::string text) {



    CURL *curl = curl_easy_init();
    CURLcode res;

    if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/images/generations");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);


    std::string data = "{\"prompt\": \""+ text + "\",\"n\": 1 , \"size\":\"512x512\" , \"response_format\":\"b64_json\" }";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, apiKey.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    std::string response;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK){
           qDebug() << "Errore nella richiesta: " << curl_easy_strerror(res);
    }else{
    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(response, jsonData)){
        if (jsonData.isMember("error")) {
                            std::string errorMessage = jsonData["error"]["message"].asString();
                            return std::string("Errore: ") + errorMessage;
        }else {
                const Json::Value image = jsonData["data"][0];
                std::string b64 = image["b64_json"].asString();
                return b64;
                        }
    }else{
             return "default";
        }
    }
    }

    return "default";
}

std::string DALL_E_generator::convert(std::string b64,std::string name, std::string deck_name) const{
    //PRE : Si ha l'immagine in b64 , il Nome della Carta e il deckName
    //POST : Si ritorna la path di sistema in cui si e' salvata l'immagine, questa comporra il campo url.
    name.erase(std::remove_if(name.begin(), name.end(), ::isspace),
               name.end());
    deck_name.erase(std::remove_if(deck_name.begin(), deck_name.end(), ::isspace),
              deck_name.end());
    std::string folder ="asset/Deck/";
    std::string deck = deck_name + "/CardImg/";
    std::string formato = ".jpg";

    QString path = QString::fromStdString( folder + deck + name + formato);
    if(b64=="default" || b64=="" || b64==" "){
        QPixmap img("asset/Icon/error.png");
        img.save(path);
        return path.toStdString();
    }
    //convertire da 64 a immagine

    QByteArray txt = QByteArray::fromBase64(b64.c_str());

    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        file.write(txt);
        file.close();
    }
    QImage img;
    img.loadFromData(txt,"JPG");
    img.save(path);

    return path.toStdString();


}


