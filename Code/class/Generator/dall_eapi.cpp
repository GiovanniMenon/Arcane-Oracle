#include "dall_eapi.h"
#include "curl/curl.h"
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>

DALL_E_generator::DALL_E_generator() : imageGenerator() {}

size_t DALL_E_generator::callback(char* data, size_t size, size_t nmemb, std::string* buffer) {
   // Calculate the size of the response
   size_t realsize = size * nmemb;
   // Append the response to the buffer
   buffer->append(data, realsize);
   // Return the size of the response
   return realsize;
 }

std::string DALL_E_generator::generate(std::string text) {
    CURL *curl = curl_easy_init();
    CURLcode res;

    if(curl) {
    // Set the Url for the DALL-E API
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/images/generations");

    // Set the HTTP method to POST
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    //Set the request body
    std::string data = "{\"prompt\": \""+ text + "\",\"n\": 1 , \"size\":\"512x512\" , \"response_format\":\"b64_json\" }";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

    // Set the request headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer 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"); //api_key
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string response;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    //Perform the request
    res = curl_easy_perform(curl);

    //Clear up
    curl_easy_cleanup(curl);

    if (res != CURLE_OK){
            std::cerr << "Error: Res Error ";
    }

    // Parsing the response with Json

    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(response, jsonData))
    {
        const Json::Value image = jsonData["data"][0];
        std::string b64 = image["b64_json"].asString();

        return b64;
    }
    }
    std::cerr << "Error Curl Request " ;
    return "error" ;
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
    if(b64=="error" || b64=="" || b64==" "){
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


