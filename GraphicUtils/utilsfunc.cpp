/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** utilsfunc
*/

#include "../mtgManager.hpp"

static size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void checkUrl(std::string &url)
{
    const std::string http = "http:";
    const std::string https = "https:";
    if (url.substr(0, http.length()) == http)
    {
        url.replace(0, http.length(), https);
    }
}

sf::Texture *loadTextureFromUrl(const std::string &url, std::string filename)
{
    CURL *curl;
    FILE *fp;
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    std::string filepath = "GraphicUtils/Assets/Cards/" + filename;

    if (access(filepath.c_str(), F_OK) != -1) {
        if (!texture->loadFromFile(filepath))
            std::cerr << "Error loading texture" << std::endl;
    } else {
        curl = curl_easy_init();
        if (curl) {
            fp = fopen(filepath.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);
        }

        if (!texture->loadFromFile(filepath))
            std::cerr << "Error loading texture" << std::endl;
    }

    return texture.release();
}