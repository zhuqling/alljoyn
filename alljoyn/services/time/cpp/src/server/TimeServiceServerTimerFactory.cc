/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <alljoyn/time/TimeServiceServerTimerFactory.h>
#include "TimeServiceTimerFactoryBusObj.h"

using namespace ajn;
using namespace services;

//Constructor
TimeServiceServerTimerFactory::TimeServiceServerTimerFactory() : m_TimerFactoryBusObj(NULL)
{

    QCC_DbgTrace(("%s", __FUNCTION__));
}

//Destructor
TimeServiceServerTimerFactory::~TimeServiceServerTimerFactory()
{

    QCC_DbgTrace(("%s", __FUNCTION__));
    release();
}

//Releases object resources
void TimeServiceServerTimerFactory::release()
{

    QCC_DbgTrace(("%s", __FUNCTION__));

    if (!m_TimerFactoryBusObj) {

        return;
    }

    QCC_DbgHLPrintf(("Releasing the TimerFactory '%s'", m_TimerFactoryBusObj->getObjectPath().c_str()));

    delete m_TimerFactoryBusObj;
    m_TimerFactoryBusObj = NULL;
}

//Returns object path of this TimerFactory
qcc::String const& TimeServiceServerTimerFactory::getObjectPath() const
{

    if (!m_TimerFactoryBusObj) {

        QCC_LogError(ER_FAIL, ("This TimerFactory hasn't been created yet"));
        return qcc::String::Empty;
    }

    return m_TimerFactoryBusObj->getObjectPath();
}

//Associate this TimerFactory with the TimerFactoryBusObj which implements AllJoyn functionality
QStatus TimeServiceServerTimerFactory::setTimerFactoryBusObj(TimeServiceTimerFactoryBusObj* TimerFactoryBusObj)
{

    if (!TimerFactoryBusObj) {

        QCC_LogError(ER_FAIL, ("No TimerFActoryBusObj given"));
        return ER_FAIL;
    }

    if (m_TimerFactoryBusObj) {

        QCC_LogError(ER_FAIL, ("TimerFactoryBusObj has been previously set"));
        return ER_FAIL;
    }

    m_TimerFactoryBusObj = TimerFactoryBusObj;
    return ER_OK;
}
