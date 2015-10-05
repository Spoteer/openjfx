/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef ResourceHandleInternal_h
#define ResourceHandleInternal_h

#include "NetworkingContext.h"
#include "ResourceHandle.h"
#include "ResourceRequest.h"
#include "AuthenticationChallenge.h"
#include "Timer.h"

#if USE(CFNETWORK)
#include "ResourceHandleCFURLConnectionDelegate.h"
#include <CFNetwork/CFURLConnectionPriv.h>
#endif

#if USE(WININET) || (USE(CURL) && PLATFORM(WIN))
#include <winsock2.h>
#include <windows.h>
#endif

#if USE(CURL)
#include <curl/curl.h>
#include "FormDataStreamCurl.h"
#include "MultipartHandle.h"
#endif

#if USE(SOUP)
#include "GUniquePtrSoup.h"
#include <libsoup/soup.h>
#include <wtf/gobject/GRefPtr.h>
class Frame;
#endif

#if PLATFORM(COCOA)
OBJC_CLASS NSURLAuthenticationChallenge;
OBJC_CLASS NSURLConnection;
#endif

#if PLATFORM(JAVA)
#include "URLLoader.h"
#endif

#if PLATFORM(COCOA) || USE(CFNETWORK)
typedef const struct __CFURLStorageSession* CFURLStorageSessionRef;
#endif

// The allocations and releases in ResourceHandleInternal are
// Cocoa-exception-free (either simple Foundation classes or
// WebCoreResourceLoaderImp which avoids doing work in dealloc).

namespace WebCore {
    class ResourceHandleClient;

    class ResourceHandleInternal {
        WTF_MAKE_NONCOPYABLE(ResourceHandleInternal); WTF_MAKE_FAST_ALLOCATED;
    public:
        ResourceHandleInternal(ResourceHandle* loader, NetworkingContext* context, const ResourceRequest& request, ResourceHandleClient* client, bool defersLoading, bool shouldContentSniff)
            : m_context(context)
            , m_client(client)
            , m_firstRequest(request)
            , m_lastHTTPMethod(request.httpMethod())
            , status(0)
            , m_defersLoading(defersLoading)
            , m_shouldContentSniff(shouldContentSniff)
#if USE(CFNETWORK)
            , m_connection(0)
            , m_currentRequest(request)
#endif
#if USE(WININET)
            , m_fileLoadTimer(loader, &ResourceHandle::fileLoadTimer)
            , m_internetHandle(0)
            , m_connectHandle(0)
            , m_requestHandle(0)
            , m_sentEndRequest(false)
            , m_bytesRemainingToWrite(0)
            , m_loadSynchronously(false)
            , m_hasReceivedResponse(false)
#endif
#if USE(CURL)
            , m_handle(0)
            , m_url(0)
            , m_customHeaders(0)
            , m_cancelled(false)
            , m_authFailureCount(0)
            , m_formDataStream(loader)
            , m_sslErrors(0)
#endif
#if USE(SOUP)
            , m_cancelled(false)
            , m_bodySize(0)
            , m_bodyDataSent(0)
            , m_redirectCount(0)
            , m_previousPosition(0)
#endif
#if PLATFORM(COCOA)
            , m_startWhenScheduled(false)
            , m_needsSiteSpecificQuirks(false)
            , m_currentMacChallenge(nil)
#endif
            , m_scheduledFailureType(ResourceHandle::NoFailure)
            , m_failureTimer(loader, &ResourceHandle::failureTimerFired)
        {
            const URL& url = m_firstRequest.url();
            m_user = url.user();
            m_pass = url.pass();
            m_firstRequest.removeCredentials();
        }
        
        ~ResourceHandleInternal();

        ResourceHandleClient* client() { return m_client; }

        RefPtr<NetworkingContext> m_context;
        ResourceHandleClient* m_client;
        ResourceRequest m_firstRequest;
        String m_lastHTTPMethod;

        // Suggested credentials for the current redirection step.
        String m_user;
        String m_pass;
        
        Credential m_initialCredential;
        
        int status;

        bool m_defersLoading;
        bool m_shouldContentSniff;
#if USE(CFNETWORK)
        RetainPtr<CFURLConnectionRef> m_connection;
        ResourceRequest m_currentRequest;
        RefPtr<ResourceHandleCFURLConnectionDelegate> m_connectionDelegate;
#endif
#if PLATFORM(COCOA) && !USE(CFNETWORK)
        RetainPtr<NSURLConnection> m_connection;
        RetainPtr<id> m_delegate;
#endif
#if PLATFORM(COCOA)
        bool m_startWhenScheduled;
        bool m_needsSiteSpecificQuirks;
#endif
#if PLATFORM(COCOA) || USE(CFNETWORK)
        RetainPtr<CFURLStorageSessionRef> m_storageSession;
#endif
#if USE(WININET)
        Timer<ResourceHandle> m_fileLoadTimer;
        HINTERNET m_internetHandle;
        HINTERNET m_connectHandle;
        HINTERNET m_requestHandle;
        bool m_sentEndRequest;
        Vector<char> m_formData;
        size_t m_bytesRemainingToWrite;
        bool m_loadSynchronously;
        bool m_hasReceivedResponse;
        String m_redirectUrl;
#endif
#if USE(CURL)
        CURL* m_handle;
        char* m_url;
        struct curl_slist* m_customHeaders;
        ResourceResponse m_response;
        bool m_cancelled;
        unsigned short m_authFailureCount;

        FormDataStream m_formDataStream;
        unsigned m_sslErrors;
        Vector<char> m_postBytes;

        OwnPtr<MultipartHandle> m_multipartHandle;
#endif
#if USE(SOUP)
        GRefPtr<SoupMessage> m_soupMessage;
        ResourceResponse m_response;
        bool m_cancelled;
        GRefPtr<SoupRequest> m_soupRequest;
        GRefPtr<GInputStream> m_inputStream;
        GRefPtr<SoupMultipartInputStream> m_multipartInputStream;
        GRefPtr<GCancellable> m_cancellable;
        GRefPtr<GAsyncResult> m_deferredResult;
        GRefPtr<GSource> m_timeoutSource;
        GUniquePtr<SoupBuffer> m_soupBuffer;
        unsigned long m_bodySize;
        unsigned long m_bodyDataSent;
        SoupSession* soupSession();
        int m_redirectCount;
        size_t m_previousPosition;
#endif
#if PLATFORM(GTK)
        struct {
            Credential credential;
            AuthenticationChallenge challenge;
        } m_credentialDataToSaveInPersistentStore;
#endif
#if PLATFORM(JAVA)
        OwnPtr<URLLoader> m_loader;
#endif

#if PLATFORM(COCOA)
        // We need to keep a reference to the original challenge to be able to cancel it.
        // It is almost identical to m_currentWebChallenge.nsURLAuthenticationChallenge(), but has a different sender.
        NSURLAuthenticationChallenge *m_currentMacChallenge;
#endif
        AuthenticationChallenge m_currentWebChallenge;
        ResourceHandle::FailureType m_scheduledFailureType;
        Timer<ResourceHandle> m_failureTimer;
    };

} // namespace WebCore

#endif // ResourceHandleInternal_h