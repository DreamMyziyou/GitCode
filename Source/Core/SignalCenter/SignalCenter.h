//
// Created by WeslyChen on 2024/1/20.
//

#ifndef WORKENGINE_SIGNALCENTER_H
#define WORKENGINE_SIGNALCENTER_H

#include <boost/signals2.hpp>

#include "SignalCenterExport.h"

namespace SignalCenter
{
    template <typename T>
    using Signal = ::boost::signals2::signal<T>;

    struct ICenter
    {
        virtual ~ICenter() {}
    };

    SIGNALCENTER_API ICenter* GetCenter();

}  // namespace SignalCenter

#endif  // WORKENGINE_SIGNALCENTER_H
