/**
 * @file web_interface.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef WEB_WEB_INTERFACE_H_
#define WEB_WEB_INTERFACE_H_

#include "src/data_structs.h"
#include "src/bus.h"
#include "src/route.h"

class WebInterface {
 public:
    virtual ~WebInterface() {}

    virtual void UpdateBus(const BusData& bus, bool deleted = false) = 0;
    virtual void UpdateRoute(const RouteData& route, bool deleted = false) = 0;
};

#endif  // WEB_WEB_INTERFACE_H_
