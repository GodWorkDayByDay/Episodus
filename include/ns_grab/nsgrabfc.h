#ifndef __NSGRABFC_H#define __NSGRABFC_H
#include "ns_grab\mil.h"
#include "ns_grab\mwinmil.h"
#include "partage\ns_vector.h"

class NSContexte;
class ParamArray;

class NSCamera
{
    public:

        long    digNum;
        long    channel;
        string  format;
        MIL_ID  digitizer;
        MIL_ID  buffer;
        MIL_ID  buffer1;
        MIL_ID  buffer2;
        HWND    handleClient;
        int     numCam;

        NSCamera(int noCamera, string dataFormat, HWND handle);
        ~NSCamera();

        NSCamera(const NSCamera& rv);
        NSCamera& operator=(const NSCamera& src);

        void AssociateChannel(string sChannel);
};

typedef vector<NSCamera*>              NSCameraVector ;
typedef NSCameraVector::iterator       NSCameraIter ;typedef NSCameraVector::const_iterator NSCameraConstIter ;
class NSCameraArray : public NSCameraVector{	public :
		// Constructeurs		NSCameraArray() : NSCameraVector() {}		NSCameraArray(const NSCameraArray& rv);        NSCameraArray& operator=(const NSCameraArray& src);
		// Destructeur		virtual ~NSCameraArray();        void vider();};

class NSMatrox
{
    public:

        MIL_ID  MilApplication;
        MIL_ID  MilSystem;
        MIL_ID  MilDisplay;
        NSCameraArray Camera;
        int nbCamera;
        ParamArray* pParamArray;

        NSMatrox(NSContexte* pCtx);
        ~NSMatrox();

        NSMatrox(const NSMatrox& rv);
        NSMatrox& operator=(const NSMatrox& src);
        void LireParams(NSContexte* pCtx);
        int IndexCamera(int noCamera);
        void AddCamera(int noCamera, string format, HWND handle);
        void RemoveCamera(int noCamera);
};

// Fonctions de capture Matrox
bool _export GrabInit(NSMatrox far **ppMatrox, NSContexte far *pCtx);bool _export GrabFree(NSMatrox far **ppMatrox);bool _export InitCamera(NSMatrox far *pMatrox, int far noCamera, HWND far ClientWndHandle,                        NSContexte far *pCtx, long far *pSizeX = 0, long far *pSizeY = 0);bool _export FreeCamera(NSMatrox far *pMatrox, int far noCamera);bool _export GrabFrame(NSMatrox far *pMatrox, int far noCamera);bool _export CaptureImage(NSMatrox far *pMatrox, int far noCamera, string far filename, NSContexte far *pCtx);bool _export GrabOneBuffer(NSMatrox far *pMatrox, int far noCamera);int  _export NbCamera(NSMatrox far *pMatrox);void _export PanImage(NSMatrox far *pMatrox, long far XOffset, long far YOffset);void _export StopCamera(NSMatrox far *pMatrox, int far noCamera);void _export ZoomImage(NSMatrox far *pMatrox, long far XFactor, long far YFactor);// Fonctions de conversionbool _export ConvertBmpToJpg(string far *filename, NSContexte far *pCtx);// Fonctions de capture Twainbool _export TwainAcquire(string far filename, HWND far ClientWndHandle) ;int  _export TwainSelectSource(HWND far ClientWndHandle) ;#endif
