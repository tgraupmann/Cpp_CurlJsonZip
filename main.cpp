// This is a project to add support for C++ features:
//
// libCurl - HTTPS POST
// jsoncpp - Constructing JSON
// libzip - Compressing ASCII Text
//

#define CURL_STATICLIB

#include <stdio.h>

#include <zlib.h>

#include <curl/curl.h>

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

int main()
{
	fprintf(stdout, "Hello World!\r\n");

#ifdef HAS_ZLIB
    fprintf(stdout, "zlib version is %s\r\n", zlibVersion());
#endif


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
#pragma comment( lib, "Wldap32" )
#pragma comment( lib, "Ws2_32" )
#pragma comment( lib, "libcurl" )
#pragma comment( lib, "libssh2" )
#pragma comment( lib, "libeay32" )
#pragma comment( lib, "ssleay32" )
#pragma comment( lib, "zlib" )
