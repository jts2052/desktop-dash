#include "dashboard_manager.h"

DashboardManager::DashboardManager()
    : screenManager(nullptr), dashboards(nullptr)
{
}
DashboardManager::DashboardManager(ScreenManager *screenManager, Dashboard *dashboards[])
    : screenManager(screenManager), dashboards(dashboards)
{
}

void DashboardManager::init()
{
    for (uint8_t i = 0; i < NUM_SCREENS; i++)
    {
        dashboards[i]->init(i);
    }
}

void DashboardManager::update()
{
    for (uint8_t i = 0; i < NUM_SCREENS; i++)
    {
        dashboards[i]->update();
    }
}

void DashboardManager::setScreenManager(ScreenManager *screenManager)
{
    this->screenManager = screenManager;
}

Dashboard *DashboardManager::getAllDashboards()
{
    return *dashboards;
}

Dashboard *DashboardManager::getDashboard(uint8_t index)
{
    return dashboards[index];
}

void DashboardManager::setDashboard(uint8_t index, Dashboard *dashboard)
{
    dashboards[index] = dashboard;
}

void DashboardManager::setDashboards(Dashboard *dashboards[])
{
    this->dashboards = dashboards;
}

void DashboardManager::handleInput(InputEvent event, uint8_t index)
{
    dashboards[index]->handleInput(event);
}