// This is a project to add support for C++ features:
//
// libCurl - HTTPS POST
// jsoncpp - Constructing JSON
// libzip - Compressing ASCII Text
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <json/json.h>

#include <zlib.h>

#define CURL_STATICLIB
#include <curl.h>

using namespace std;

string DoJson()
{
    // create sample json
    Json::Value json;
    json[0]["name"] = "Jabberwock";
    json[0]["chapter"] = 1;
    json[1]["name"] = "Cheshire Cat";
    json[1]["chapter"] = 6;
    json[2]["name"] = "Mad Hatter";
    json[2]["chapter"] = 7;

    cout << "Json:" << endl;
    //cout << json << endl;

    Json::FastWriter fastWriter;
    std::string strJson = fastWriter.write(json);
    cout << strJson << endl;

    return strJson;
}

int DoCompression(const char* istream)
{
    cout << "zlib version is " << ZLIB_VERSION << endl;

    cout << "Original size: " << strlen(istream) << endl;
    cout << istream << endl;

    size_t srcLen = (size_t)strlen(istream) + 1;      // +1 for the trailing `\0`
    size_t destLen = (size_t)compressBound((uLong)srcLen); // this is how you should estimate size 
                                           // needed for the buffer
    char* ostream = (char*)malloc(destLen);
    int res = compress((Bytef*)ostream, (uLongf*)&destLen, (const Bytef*)istream, (uLong)srcLen);
    // destLen is now the size of actuall buffer needed for compression
    // you don't want to uncompress whole buffer later, just the used part
    if (res == Z_BUF_ERROR) {
        printf("Buffer was too small!\n");
        free(ostream);
        return 1;
    }
    if (res == Z_MEM_ERROR) {
        printf("Not enough memory for compression!\n");
        free(ostream);
        return 2;
    }

    cout << "Compressed size: " << destLen << endl;
    cout << ostream << endl << endl;

    const char* i2stream = ostream;
    char* o2stream = (char*)malloc(srcLen);
    size_t destLen2 = destLen; //destLen is the actual size of the compressed buffer
    int des = uncompress((Bytef*)o2stream, (uLongf*)&srcLen, (const Bytef*)i2stream, (uLong)destLen2);

    cout << "Uncompressed size: " << strlen(o2stream) << endl;
    cout << o2stream << endl;

    free(ostream);
    free(o2stream);

    return 0;
}

size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, string* s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch (std::bad_alloc&)
    {
        //handle memory problem
        return 0;
    }
    return newLength;
}

void DoHttpPost()
{
    CURL* curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if (curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "https://tagenigma.com/post/");
        // ignore SSL errors
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //uncomment to see verbose output
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        string content;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        cout << "Curl Response CURLE_OK: " << (res == CURLE_OK ? "YES" : "NO") << endl;

        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }
        else
        {
            cout << "CURL RESPONSE BEGIN:::" << endl;
            cout << content;
            cout << ":::CURL RESPONSE END" << endl;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main()
{
	fprintf(stdout, "Hello World!\r\n");

    string strJson = DoJson();

    DoCompression(strJson.c_str());   

    DoHttpPost();
    
    return 0;
}

#ifdef _DEBUG
#pragma comment( lib, "msvcrtd" )
#else
#pragma comment( lib, "msvcrt" )
#endif
#pragma comment( lib, "Wldap32" )
#pragma comment( lib, "Ws2_32" )
#pragma comment (lib, "crypt32")
#pragma comment( lib, "libcurl" )
#pragma comment( lib, "libssh2" )
#pragma comment( lib, "libcrypto" )
#pragma comment( lib, "libssl" )
#pragma comment( lib, "zlibstat" )
#pragma comment (lib, "jsoncpp")
