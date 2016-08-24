#ifndef ABSTRACTDECUMA_H
#define ABSTRACTDECUMA_H

#include <QObject>

#include "decuma_hwr.h"
#include "decuma_hwr_cjk.h"
#include "decuma_hwr_cjk.h"
#include "decuma_hwr_cursive.h"
#include "decumaStatus.h"
#include "decumaSymbolCategories.h"
#include "decumaLanguages.h"
#include "xxt9wOem.h"

class AbstractDecuma : public QObject
{
    Q_OBJECT

public:
    explicit AbstractDecuma(QObject *parent = 0);
    ~AbstractDecuma();

    // Session

    DECUMA_UINT32 aDecumaGetSessionSize(void);

    DECUMA_STATUS aDecumaBeginSession(DECUMA_SESSION * pSession,
                                      DECUMA_SESSION_SETTINGS * pSessionSettings,
                                      const DECUMA_MEM_FUNCTIONS * pMemoryFunctions);

    DECUMA_STATUS aDecumaVerifySession(const DECUMA_SESSION * pSession);

    DECUMA_STATUS aDecumaEndSession(DECUMA_SESSION * pSession);

    DECUMA_STATUS aDecumaGetSessionSettings(DECUMA_SESSION * pSession,
                                            const DECUMA_SESSION_SETTINGS ** pSessionSettings);

    DECUMA_STATUS aDecumaChangeSessionSettings(DECUMA_SESSION * pSession,
                                               const DECUMA_SESSION_SETTINGS * pSessionSettings);

    DECUMA_STATUS aDecumaDatabaseIsLanguageSupported(DECUMA_ANY_DB_PTR pDB,
                                                     DECUMA_UINT32 lang,
                                                     int * pbIsSupported);

    // Recognition

    DECUMA_STATUS aDecumaBeginArcAddition(DECUMA_SESSION * pSession);

    DECUMA_STATUS aDecumaStartNewArc(DECUMA_SESSION * pSession,
                                     DECUMA_UINT32  arcID);

    DECUMA_STATUS aDecumaAddPoint(DECUMA_SESSION * pSession,
                                  DECUMA_COORD x,
                                  DECUMA_COORD y,
                                  DECUMA_UINT32 arcID);

    DECUMA_STATUS aDecumaCancelArc(DECUMA_SESSION * pSession,
                                   DECUMA_UINT32 arcID);

    DECUMA_STATUS aDecumaCommitArc(DECUMA_SESSION * pSession,
                                   DECUMA_UINT32 arcID);

    DECUMA_STATUS aDecumaRecognize(DECUMA_SESSION * pSession,
                                   DECUMA_HWR_RESULT * pResults,
                                   DECUMA_UINT16 nMaxResults,
                                   DECUMA_UINT16 * pnResults,
                                   DECUMA_UINT16 nMaxCharsPerResult,
                                   const DECUMA_RECOGNITION_SETTINGS * pRecognitionSettings,
                                   const DECUMA_INTERRUPT_FUNCTIONS * pInterruptFunctions);


    DECUMA_STATUS aDecumaIndicateInstantGesture(DECUMA_SESSION * pSession,
                                                int * pbInstantGesture,
                                                const DECUMA_INSTANT_GESTURE_SETTINGS * pInstantGestureSettings);

    DECUMA_STATUS aDecumaEndArcAddition(DECUMA_SESSION * pSession);

    DECUMA_STATUS aDecumaNoteSelectedCandidate(DECUMA_SESSION * pSession, int nResultIdx);

    // Dictionary

    DECUMA_STATUS aDecumaConvertDictionary(void ** ppDestDictionary,
                                           const void * pSrcDictionary,
                                           DECUMA_UINT32 srcDictionarySize,
                                           const DECUMA_SRC_DICTIONARY_INFO * pSrcDictionaryInfo,
                                           DECUMA_UINT32 * pDestDictionarySize,
                                           const DECUMA_MEM_FUNCTIONS * pMemoryFunctions);

    DECUMA_STATUS aDecumaDestroyConvertedDictionary(void ** ppDictionary, const DECUMA_MEM_FUNCTIONS * pMemoryFunctions);

    DECUMA_STATUS aDecumaAttachDictionary(DECUMA_SESSION * pSession, const void * pDictionary, DECUMA_UINT32 nDictionarySize);

    DECUMA_STATUS aDecumaDetachDictionary(DECUMA_SESSION * pSession, const void * pDictionary);

    // Logging

    DECUMA_STATUS aDecumaStartLogging(DECUMA_SESSION * pSession,
                                      void * pUserData,
                                      DECUMA_LOG_STRING_FUNC * pfLogStringFunction);

    DECUMA_STATUS aDecumaStopLogging(DECUMA_SESSION * pSession);

    DECUMA_STATUS aDecumaLogAcceptedResult(DECUMA_SESSION * pSession,
                                         const DECUMA_UNICODE * pResult,
                                         DECUMA_UINT32 nResultLength);

    enum DecumaMethodType
    {
        Latin = 0,
        CJK,
        Cursive,
        Unused
    };

    void setDecumaMethodType(DECUMA_UINT32 language);
    DecumaMethodType getDecumaMethodType(void);
    DECUMA_UINT32 getLanguage(void);

private:
    DecumaMethodType m_DecumaMethodType;
};

#endif // ABSTRACTDECUMA_H
