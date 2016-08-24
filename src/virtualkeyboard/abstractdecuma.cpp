#include "abstractdecuma.h"
#include "virtualkeyboarddebug.h"

#include "decuma_hwr.h"
#include "decuma_hwr_cjk.h"
#include "decuma_hwr_cursive.h"
#include "decumaStatus.h"
#include "decumaSymbolCategories.h"
#include "decumaLanguages.h"
#include "xxt9wOem.h"


AbstractDecuma::AbstractDecuma(QObject *parent) :
    QObject(parent),
    m_DecumaMethodType(DecumaMethodType::Unused)
{
}

AbstractDecuma::~AbstractDecuma()
{
}

void AbstractDecuma::setDecumaMethodType(DECUMA_UINT32 language)
{
    switch(language) {
    case DECUMA_LANG_PRC:
    case DECUMA_LANG_JP:
    case DECUMA_LANG_KO:
    case DECUMA_LANG_HK:
    case DECUMA_LANG_TW:
        m_DecumaMethodType = AbstractDecuma::CJK;
        break;
    case DECUMA_LANG_AR:
        m_DecumaMethodType = AbstractDecuma::Cursive;
        break;
    default:
        m_DecumaMethodType = AbstractDecuma::Latin;
        break;
    }
}

AbstractDecuma::DecumaMethodType AbstractDecuma::getDecumaMethodType(void)
{
    return m_DecumaMethodType;
}

DECUMA_UINT32 AbstractDecuma::aDecumaGetSessionSize()
{
    VIRTUALKEYBOARD_DEBUG() << "AbstractDecuma::aDecumaGetSessionSize(): m_DecumaMethodType = "
                            << m_DecumaMethodType;
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaGetSessionSize();
        break;
    case AbstractDecuma::CJK:
        return decumaCJKGetSessionSize();
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveGetSessionSize();
        break;
    default:
        return 0;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaBeginSession(DECUMA_SESSION * pSession,
    DECUMA_SESSION_SETTINGS * pSessionSettings,
    const DECUMA_MEM_FUNCTIONS * pMemoryFunctions)
{
    VIRTUALKEYBOARD_DEBUG() << "AbstractDecuma::aDecumaBeginSession(): " << pSession
                            << "m_DecumaMethodType = " << m_DecumaMethodType;
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaBeginSession(pSession, pSessionSettings, pMemoryFunctions);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKBeginSession(pSession, pSessionSettings, pMemoryFunctions);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveBeginSession(pSession, pSessionSettings, pMemoryFunctions);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaEndSession(DECUMA_SESSION * pSession)
{
    VIRTUALKEYBOARD_DEBUG() << "AbstractDecuma::aDecumaEndSession(): " << pSession;
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaEndSession(pSession);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKEndSession(pSession);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveEndSession(pSession);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaDetachDictionary(DECUMA_SESSION * pSession,
    const void * pDictionary)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaDetachDictionary(pSession, pDictionary);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKDetachDictionary(pSession, pDictionary);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveDetachDictionary(pSession, pDictionary);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaAttachDictionary(DECUMA_SESSION * pSession,
    const void * pDictionary, DECUMA_UINT32 nDictionarySize)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaAttachDictionary(pSession, pDictionary, nDictionarySize);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKAttachDictionary(pSession, pDictionary, nDictionarySize);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveAttachDictionary(pSession, pDictionary, nDictionarySize);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaChangeSessionSettings(DECUMA_SESSION * pSession,
    const DECUMA_SESSION_SETTINGS * pSessionSettings)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaChangeSessionSettings(pSession, pSessionSettings);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKChangeSessionSettings(pSession, pSessionSettings);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveChangeSessionSettings(pSession, pSessionSettings);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaBeginArcAddition(DECUMA_SESSION * pSession)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaBeginArcAddition(pSession);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKBeginArcAddition(pSession);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveBeginArcAddition(pSession);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaStartNewArc(DECUMA_SESSION * pSession, DECUMA_UINT32  arcID)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaStartNewArc(pSession, arcID);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKStartNewArc(pSession, arcID);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveStartNewArc(pSession, arcID);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaEndArcAddition(DECUMA_SESSION * pSession)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaEndArcAddition(pSession);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKEndArcAddition(pSession);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveEndArcAddition(pSession);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaCancelArc(DECUMA_SESSION * pSession, DECUMA_UINT32 arcID)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaCancelArc(pSession, arcID);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKCancelArc(pSession, arcID);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveCancelArc(pSession, arcID);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaAddPoint(DECUMA_SESSION * pSession,
                             DECUMA_COORD x, DECUMA_COORD y,
                             DECUMA_UINT32 arcID)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaAddPoint(pSession, x, y, arcID);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKAddPoint(pSession, x, y, arcID);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveAddPoint(pSession, x, y, arcID);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}


DECUMA_STATUS AbstractDecuma::aDecumaCommitArc(DECUMA_SESSION * pSession,DECUMA_UINT32 arcID)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaCommitArc(pSession, arcID);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKCommitArc(pSession, arcID);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveCommitArc(pSession, arcID);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaNoteSelectedCandidate(DECUMA_SESSION * pSession, int nResultIdx)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaNoteSelectedCandidate(pSession, nResultIdx);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKNoteSelectedCandidate(pSession, nResultIdx);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveNoteSelectedCandidate(pSession, nResultIdx);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}
DECUMA_STATUS AbstractDecuma::aDecumaIndicateInstantGesture(DECUMA_SESSION * pSession,
    int * pbInstantGesture,
    const DECUMA_INSTANT_GESTURE_SETTINGS * pInstantGestureSettings)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaIndicateInstantGesture(pSession, pbInstantGesture, pInstantGestureSettings);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKIndicateInstantGesture(pSession, pbInstantGesture, pInstantGestureSettings);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveIndicateInstantGesture(pSession, pbInstantGesture, pInstantGestureSettings);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaRecognize(DECUMA_SESSION * pSession,
    DECUMA_HWR_RESULT * pResults,
    DECUMA_UINT16 nMaxResults,
    DECUMA_UINT16 * pnResults,
    DECUMA_UINT16 nMaxCharsPerResult,
    const DECUMA_RECOGNITION_SETTINGS * pRecognitionSettings,
    const DECUMA_INTERRUPT_FUNCTIONS * pInterruptFunctions)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaRecognize(pSession, pResults, nMaxResults, pnResults, nMaxCharsPerResult,
                               pRecognitionSettings, pInterruptFunctions);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKRecognize(pSession, pResults, nMaxResults, pnResults, nMaxCharsPerResult,
                                  pRecognitionSettings, pInterruptFunctions);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveRecognize(pSession, pResults, nMaxResults, pnResults, nMaxCharsPerResult,
                                      pRecognitionSettings, pInterruptFunctions);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}


DECUMA_STATUS AbstractDecuma::aDecumaConvertDictionary(void ** ppDestDictionary,
    const void * pSrcDictionary, DECUMA_UINT32 srcDictionarySize,
    const DECUMA_SRC_DICTIONARY_INFO * pSrcDictionaryInfo,
    DECUMA_UINT32 * pDestDictionarySize,const DECUMA_MEM_FUNCTIONS * pMemoryFunctions)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaConvertDictionary(ppDestDictionary, pSrcDictionary, srcDictionarySize, pSrcDictionaryInfo,
                                       pDestDictionarySize, pMemoryFunctions);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKConvertDictionary(ppDestDictionary, pSrcDictionary, srcDictionarySize, pSrcDictionaryInfo,
                                          pDestDictionarySize, pMemoryFunctions);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveConvertDictionary(ppDestDictionary, pSrcDictionary, srcDictionarySize, pSrcDictionaryInfo,
                                              pDestDictionarySize, pMemoryFunctions);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaDestroyConvertedDictionary(void ** ppDictionary,
    const DECUMA_MEM_FUNCTIONS * pMemoryFunctions)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaDestroyConvertedDictionary(ppDictionary, pMemoryFunctions);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKDestroyConvertedDictionary(ppDictionary, pMemoryFunctions);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveDestroyConvertedDictionary(ppDictionary, pMemoryFunctions);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}

DECUMA_STATUS AbstractDecuma::aDecumaDatabaseIsLanguageSupported(DECUMA_ANY_DB_PTR pDB,
    DECUMA_UINT32 lang, int * pbIsSupported)
{
    switch(m_DecumaMethodType) {
    case AbstractDecuma::Latin:
        return decumaDatabaseIsLanguageSupported(pDB, lang, pbIsSupported);
        break;
    case AbstractDecuma::CJK:
        return decumaCJKDatabaseIsLanguageSupported(pDB, lang, pbIsSupported);
        break;
    case AbstractDecuma::Cursive:
        return decumaCursiveDatabaseIsLanguageSupported(pDB, lang, pbIsSupported);
        break;
    default:
        return decumaSessionNotInitialized;
        break;
    }
}
