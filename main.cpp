// This is a project to add support for C++ features:
//
// libCurl - HTTPS POST
// jsoncpp - Constructing JSON
// libzip - Compressing ASCII Text
//

#include <stdio.h>
#include <iostream>

#include <json/json.h>

#include <zlib.h>

#define CURL_STATICLIB
#include <curl.h>

using namespace std;



int main()
{
	fprintf(stdout, "Hello World!\r\n");

    fprintf(stdout, "zlib version is %s\r\n", ZLIB_VERSION);


    // create the characters array
    Json::Value ch;
    ch[0]["name"] = "Jabberwock";
    ch[0]["chapter"] = 1;
    ch[1]["name"] = "Cheshire Cat";
    ch[1]["chapter"] = 6;
    ch[2]["name"] = "Mad Hatter";
    ch[2]["chapter"] = 7;

    cout << "Json:" << endl;
    cout << ch << endl;


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
        curl_easy_setopt(curl, CURLOPT_URL, "http://postit.example.com/moo.cgi");
        // ignore SSL errors
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        // don't print response
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}

#pragma comment( lib, "legacy_stdio_definitions" )
//#pragma comment( lib, "legacy_stdio_wide_specifiers" )
#pragma comment( lib, "Wldap32" )
#pragma comment( lib, "Ws2_32" )
//#pragma comment( lib, "ucrt" )
#pragma comment( lib, "vcruntime" )
#pragma comment( lib, "msvcrt" )
#pragma comment( lib, "libcurl" )
#pragma comment( lib, "libssh2" )
#pragma comment( lib, "libcrypto" )
#pragma comment( lib, "libssl" )
#pragma comment( lib, "zlibstat" )
#pragma comment (lib, "crypt32")
#pragma comment (lib, "jsoncpp")
