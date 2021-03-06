#ifndef __NSHTMLTOPDF_H#define __NSHTMLTOPDF_H

#include "nsoutil/nsexport.h"
#include "wkhtmltox/pdf.h"

// #define HTMLTOPDF_DYNAMIC 1

// LibCurl Functions
//
/*
#define HTMLTOPDF_INIT 		               183
#define HTMLTOPDF_DEINIT                 169
#define HTMLTOPDF_CREATE_GLOBAL_SETTINGS 163
#define HTMLTOPDF_CREATE_OBJECT_SETTINGS 165
#define HTMLTOPDF_SET_GLOBAL_SETTINGS    195
#define HTMLTOPDF_SET_OBJECT_SETTINGS    197
#define HTMLTOPDF_CREATE_CONVERTER       161
#define HTMLTOPDF_ADD_OBJECT             157
#define HTMLTOPDF_CONVERT                159
#define HTMLTOPDF_HTTP_ERROR_CODE        181
#define HTMLTOPDF_DESTROY_CONVERTE       171

#define HTMLTOPDF_INIT 		               184
#define HTMLTOPDF_DEINIT                 170
#define HTMLTOPDF_CREATE_GLOBAL_SETTINGS 164
#define HTMLTOPDF_CREATE_OBJECT_SETTINGS 166
#define HTMLTOPDF_SET_GLOBAL_SETTINGS    196
#define HTMLTOPDF_SET_OBJECT_SETTINGS    198
#define HTMLTOPDF_CREATE_CONVERTER       162
#define HTMLTOPDF_ADD_OBJECT             158
#define HTMLTOPDF_CONVERT                160
#define HTMLTOPDF_HTTP_ERROR_CODE        182
#define HTMLTOPDF_DESTROY_CONVERTE       172
*/

#define HTMLTOPDF_INIT 		               "wkhtmltopdf_init"
#define HTMLTOPDF_DEINIT                 "wkhtmltopdf_deinit"
#define HTMLTOPDF_CREATE_GLOBAL_SETTINGS "wkhtmltopdf_create_global_settings"
#define HTMLTOPDF_CREATE_OBJECT_SETTINGS "wkhtmltopdf_create_object_settings"
#define HTMLTOPDF_SET_GLOBAL_SETTINGS    "wkhtmltopdf_set_global_setting"
#define HTMLTOPDF_SET_OBJECT_SETTINGS    "wkhtmltopdf_set_object_setting"
#define HTMLTOPDF_CREATE_CONVERTER       "wkhtmltopdf_create_converter"
#define HTMLTOPDF_ADD_OBJECT             "wkhtmltopdf_add_object"
#define HTMLTOPDF_CONVERT                "wkhtmltopdf_convert"
#define HTMLTOPDF_HTTP_ERROR_CODE        "wkhtmltopdf_http_error_code"
#define HTMLTOPDF_DESTROY_CONVERTE       "wkhtmltopdf_destroy_converter"

#define HTMLTOPDF_INIT_1 	                 "wkhtmltopdf_init@4"
#define HTMLTOPDF_DEINIT_1                 "wkhtmltopdf_deinit@0"
#define HTMLTOPDF_CREATE_GLOBAL_SETTINGS_1 "wkhtmltopdf_create_global_settings@0"
#define HTMLTOPDF_CREATE_OBJECT_SETTINGS_1 "wkhtmltopdf_create_object_settings@0"
#define HTMLTOPDF_SET_GLOBAL_SETTINGS_1    "wkhtmltopdf_set_global_setting@12"
#define HTMLTOPDF_SET_OBJECT_SETTINGS_1    "wkhtmltopdf_set_object_setting@12"
#define HTMLTOPDF_CREATE_CONVERTER_1       "wkhtmltopdf_create_converter@4"
#define HTMLTOPDF_ADD_OBJECT_1             "wkhtmltopdf_add_object@12"
#define HTMLTOPDF_CONVERT_1                "wkhtmltopdf_convert@4"
#define HTMLTOPDF_HTTP_ERROR_CODE_1        "wkhtmltopdf_http_error_code@4"
#define HTMLTOPDF_DESTROY_CONVERTE_1       "wkhtmltopdf_destroy_converter@4"

class _NSOUTILCLASSE NSHtmlToPdfConverter : public NSSuperRoot
{
  public:

    NSHtmlToPdfConverter(NSSuper* pSuper) ;
    ~NSHtmlToPdfConverter() ;

    int  convertHtmlToPdf(string sHtmlFileName, string sPdfFileName, bool bVerbose = true) ;

    bool bIsReady() ;

  protected:

    TModule* pConverterModule ;

    void init() ;

    wkhtmltopdf_global_settings *_pGlobalSettings ;

#ifdef HTMLTOPDF_DYNAMIC

    // Pointers to functions
    //
    static int                           (FAR* pWkHtmlToPdf_Init)   (int) ;
    static int                           (FAR* pwkhtmltopdf_DeInit) (void) ;
    static wkhtmltopdf_global_settings * (FAR* pWkHtmlToPdf_CreateGlobalSettings) (void) ;
    static wkhtmltopdf_object_settings * (FAR* pWkHtmlToPdf_CreateObjectSettings) (void) ;
    static int                           (FAR* pWkHtmlToPdf_SetGlobalSetting) (wkhtmltopdf_global_settings*, const char*, const char*) ;
    static int                           (FAR* pWkHtmlToPdf_SetObjectSetting) (wkhtmltopdf_object_settings*, const char*, const char*) ;
    static wkhtmltopdf_converter *       (FAR* pWkHtmlToPdf_CreateConverter)  (wkhtmltopdf_global_settings*) ;
    static void                          (FAR* pWkHtmlToPdf_AddObject)        (wkhtmltopdf_converter*, wkhtmltopdf_object_settings*, const char*) ;
    static int                           (FAR* pWkHtmlToPdf_Convert)          (wkhtmltopdf_converter*) ;
    static int                           (FAR* pWkHtmlToPdf_HttpErrorCode)    (wkhtmltopdf_converter*) ;
    static void                          (FAR* pWkHtmlToPdf_DestroyConverter) (wkhtmltopdf_converter*) ;

    int WkHtmlToPdf_Init(int use_graphics) { return (*pWkHtmlToPdf_Init)(use_graphics) ; }
    int WkHtmlToPdf_DeInit()               { return (*pwkhtmltopdf_DeInit)() ; }

    wkhtmltopdf_global_settings* WkHtmlToPdf_CreateGlobalSettings() { return (*pWkHtmlToPdf_CreateGlobalSettings)() ; }
    wkhtmltopdf_object_settings* WkHtmlToPdf_CreateObjectSettings() { return (*pWkHtmlToPdf_CreateObjectSettings)() ; }

    int WkHtmlToPdf_SetGlobalSetting(wkhtmltopdf_global_settings * settings, const char * name, const char * value) { return (*pWkHtmlToPdf_SetGlobalSetting)(settings, name, value) ; }
    int WkHtmlToPdf_SetObjectSetting(wkhtmltopdf_object_settings * settings, const char * name, const char * value) { return (*pWkHtmlToPdf_SetObjectSetting)(settings, name, value) ; }

    wkhtmltopdf_converter* WkHtmlToPdf_CreateConverter(wkhtmltopdf_global_settings * settings) { return (*pWkHtmlToPdf_CreateConverter)(settings) ; }
    void                   WkHtmlToPdf_DestroyConverter(wkhtmltopdf_converter * converter)     { (*pWkHtmlToPdf_DestroyConverter)(converter) ; }

    int WkHtmlToPdf_Convert(wkhtmltopdf_converter * converter)       { return (*pWkHtmlToPdf_Convert)(converter) ; }
    int WkHtmlToPdf_HttpErrorCode(wkhtmltopdf_converter * converter) { return (*pWkHtmlToPdf_HttpErrorCode)(converter) ; }

    void WkHtmlToPdf_AddObject(wkhtmltopdf_converter * converter, wkhtmltopdf_object_settings * setting, const char * data) { (*pWkHtmlToPdf_AddObject)(converter, setting, data) ; }

#else

    int WkHtmlToPdf_Init(int use_graphics) { return wkhtmltopdf_init(use_graphics) ; }
    int WkHtmlToPdf_DeInit()               { return wkhtmltopdf_deinit() ; }

    wkhtmltopdf_global_settings* WkHtmlToPdf_CreateGlobalSettings() { return wkhtmltopdf_create_global_settings() ; }
    wkhtmltopdf_object_settings* WkHtmlToPdf_CreateObjectSettings() { return wkhtmltopdf_create_object_settings() ; }

    int WkHtmlToPdf_SetGlobalSetting(wkhtmltopdf_global_settings * settings, const char * name, const char * value) { return wkhtmltopdf_set_global_setting(settings, name, value) ; }
    int WkHtmlToPdf_SetObjectSetting(wkhtmltopdf_object_settings * settings, const char * name, const char * value) { return wkhtmltopdf_set_object_setting(settings, name, value) ; }

    wkhtmltopdf_converter* WkHtmlToPdf_CreateConverter(wkhtmltopdf_global_settings * settings) { return wkhtmltopdf_create_converter(settings) ; }
    void                   WkHtmlToPdf_DestroyConverter(wkhtmltopdf_converter * converter)     { wkhtmltopdf_destroy_converter(converter) ; }

    int WkHtmlToPdf_Convert(wkhtmltopdf_converter * converter)       { return wkhtmltopdf_convert(converter) ; }
    int WkHtmlToPdf_HttpErrorCode(wkhtmltopdf_converter * converter) { return wkhtmltopdf_http_error_code(converter) ; }

    void WkHtmlToPdf_AddObject(wkhtmltopdf_converter * converter, wkhtmltopdf_object_settings * setting, const char * data) { wkhtmltopdf_add_object(converter, setting, data) ; }

#endif
} ;

// From
//
// The wkhtmltopdf_global_settings structure contains the following settings:
//
//    size.paperSize The paper size of the output document, e.g. "A4".
//    size.width The with of the output document, e.g. "4cm".
//    size.height The height of the output document, e.g. "12in".
//    orientation The orientation of the output document, must be either "Landscape" or "Portrait".
//    colorMode Should the output be printed in color or gray scale, must be either "Color" or "Grayscale"
//    resolution Most likely has no effect.
//    dpi What dpi should we use when printing, e.g. "80".
//    pageOffset A number that is added to all page numbers when printing headers, footers and table of content.
//    copies How many copies should we print?. e.g. "2".
//    collate Should the copies be collated? Must be either "true" or "false".
//    outline Should a outline (table of content in the sidebar) be generated and put into the PDF? Must be either "true" or false". - \b outlineDepth The maximal depth of the outline, e.g. "4".
//    dumpOutline If not set to the empty string a XML representation of the outline is dumped to this file.
//    out The path of the output file, if "-" output is sent to stdout, if empty the output is stored in a buffer.
//    documentTitle The title of the PDF document.
//    useCompression Should we use loss less compression when creating the pdf file? Must be either "true" or "false".
//    margin.top Size of the top margin, e.g. "2cm"
//    margin.bottom Size of the bottom margin, e.g. "2cm"
//    margin.left Size of the left margin, e.g. "2cm"
//    margin.right Size of the right margin, e.g. "2cm"
//    outputFormat The format of the output document, must be ether "", "pdf" or "ps".
//    imageDPI The maximal DPI to use for images in the pdf document.
//    imageQuality The jpeg compression factor to use when producing the pdf document, e.g. "92".
//    load.cookieJar Path of file used to load and store cookies.
//
// Pdf object settings
//
// The wkhtmltopdf_object_settings structure contains the following settings:
//
//    toc.useDottedLines Should we use a dotted line when creating a table of content? Must be either "true" or "false".
//    toc.captionText The caption to use when creating a table of content.
//    toc.forwardLinks Should we create links from the table of content into the actual content? Must be either "true or "false.
//    toc.backLinks Should we link back from the content to this table of content.
//    toc.indentation The indentation used for every table of content level, e.g. "2em".
//    toc.fontScale How much should we scale down the font for every toc level? E.g. "0.8"
//    page The URL or path of the web page to convert, if "-" input is read from stdin.
//    header.* Header specific settings see Header and footer settings.
//    footer.* Footer specific settings see Header and footer settings.
//    useExternalLinks Should external links in the HTML document be converted into external pdf links? Must be either "true" or "false.
//    useLocalLinks Should internal links in the HTML document be converted into pdf references? Must be either "true" or "false"
//    replacements TODO
//    produceForms Should we turn HTML forms into PDF forms? Must be either "true" or file".
//    load.* Page specific settings related to loading content, see Object Specific loading settings.
//    web.* See Web page specific settings.
//    includeInOutline Should the sections from this document be included in the outline and table of content?
//    pagesCount Should we count the pages of this document, in the counter used for TOC, headers and footers?
//    tocXsl If not empty this object is a table of content object, "page" is ignored and this xsl style sheet is used to convert the outline XML into a table of content.
//
// Image settings
//
// The wkhtmltoimage_global_settings structure contains the following settings:
//
//    crop.left left/x coordinate of the window to capture in pixels. E.g. "200"
//    crop.top top/y coordinate of the window to capture in pixels. E.g. "200"
//    crop.width Width of the window to capture in pixels. E.g. "200"
//    crop.height Heigt of the window to capture in pixels. E.g. "200"
//    load.cookieJar Path of file used to load and store cookies.
//    load.* Page specific settings related to loading content, see Object Specific loading settings.
//    web.* See Web page specific settings.
//    transparent When outputting a PNG or SVG, make the white background transparent. Must be either "true" or "false"
//    in The URL or path of the input file, if "-" stdin is used. E.g. "http://google.com"
//    out The path of the output file, if "-" stdout is used, if empty the content is storred to a internalBuffer.
//    fmt The output format to use, must be either "", "jpg", "png", "bmp" or "svg".
//    screenWidth The with of the screen used to render is pixels, e.g "800".
//    smartWidth Should we expand the screenWidth if the content does not fit? must be either "true" or "false".
//    quality The compression factor to use when outputting a JPEG image. E.g. "94".
//

#endif 		// __NSHTMLTOPDF_H

