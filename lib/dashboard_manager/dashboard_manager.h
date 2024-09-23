#pragma once

#include <config.h>
#include <screen_manager.h>
#include <input_handler.h>
#include <dashboard.h>

class DashboardManager
{
public:
    DashboardManager();
    DashboardManager(ScreenManager *screenManager, Dashboard *dashboards[]);
    void init();
    void update();
    void setScreenManager(ScreenManager *screenManager);
    Dashboard *getAllDashboards();
    Dashboard *getDashboard(uint8_t index);
    void setDashboard(uint8_t index, Dashboard *dashboard);
    void setDashboards(Dashboard *dashboards[]);
    void handleInput(InputEvent event, uint8_t index);

private:
    ScreenManager *screenManager;
    Dashboard **dashboards;
};