#include <iostream>
#include <ctime>
#include "amx/amx.h"
#include "plugincommon.h"
#include "settings.h"
#include "AmxUtils.h"

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

int gettime()
{
    std::time_t result = std::time(nullptr);
    std::asctime(std::localtime(&result));
    return result;
}

cell AMX_NATIVE_CALL time_convert(AMX* amx, cell* params)
{
    int timestamp = 0;

    if (params[1] == -1)
        timestamp = gettime();
    else
        timestamp = params[1];

    std::string format = AmxUtils::amx_GetStdString(amx, &params[2]);

    time_t t = timestamp;
    struct tm *tm = localtime(&t);
    char date[20] = { 0 };
    strftime(date, sizeof(date), format.c_str(), tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[3], &addr);
    amx_SetString(addr, date, 0, 0, params[4]);

    return 1;
}

cell AMX_NATIVE_CALL datetime(AMX* amx, cell* params)
{
    time_t t = gettime();
    struct tm *tm = localtime(&t);

    if (tm == NULL)
        return 0;

    char datetime[25] = { 0 };
    strftime(datetime, sizeof(datetime), "%F %T", tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[1], &addr);
    amx_SetString(addr, datetime, 0, 0, params[2]);

    return 1;
}

cell AMX_NATIVE_CALL timestamp_to_datetime(AMX* amx, cell* params)
{
    time_t t = params[1];
    struct tm *tm = localtime(&t);

    if (tm == NULL)
        return 0;

    char datetime[25] = { 0 };
    strftime(datetime, sizeof(datetime), "%F %T", tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[2], &addr);
    amx_SetString(addr, datetime, 0, 0, params[3]);

    return 1;
}

cell AMX_NATIVE_CALL datetime_to_timestamp(AMX* amx, cell* params)
{
    std::string datetime = AmxUtils::amx_GetStdString(amx, &params[1]);

    struct tm tm;

    if (strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return -1;

    // auto-detect daylight saving time
    tm.tm_isdst = -1;

    return mktime(&tm);
}

cell AMX_NATIVE_CALL date(AMX* amx, cell* params)
{
    time_t t = gettime();
    struct tm *tm = localtime(&t);

    if (tm == NULL)
        return 0;

    char date[12] = { 0 };
    strftime(date, sizeof(date), "%F", tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[1], &addr);
    amx_SetString(addr, date, 0, 0, params[2]);

    return 1;
}

cell AMX_NATIVE_CALL datetime_to_date(AMX* amx, cell* params)
{
    std::string datetime = AmxUtils::amx_GetStdString(amx, &params[1]);

    struct tm tm;

    if (strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return 0;

    cell *addr = NULL;
    char date[25] = { 0 };

    strftime(date, sizeof(date), "%F", &tm);

    amx_GetAddr(amx, params[2], &addr);
    amx_SetString(addr, date, 0, 0, params[3]);

    return 1;
}

cell AMX_NATIVE_CALL date_to_datetime(AMX* amx, cell* params)
{
    std::string date = AmxUtils::amx_GetStdString(amx, &params[1]);

    struct tm tm;

    if (strptime(date.c_str(), "%Y-%m-%d", &tm) == NULL)
        return 0;

    char datetime[25] = { 0 };
    strftime(datetime, sizeof(datetime), "%F 00:00:00", &tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[2], &addr);
    amx_SetString(addr, datetime, 0, 0, params[3]);

    return 1;
}

cell AMX_NATIVE_CALL date_to_timestamp(AMX* amx, cell* params)
{
    std::string date = AmxUtils::amx_GetStdString(amx, &params[1]);
    date += " 00:00:00";

    struct tm tm;

    if (strptime(date.c_str(), "%Y-%m-%d %H:%M:%S", &tm) == NULL)
        return -1;

    // auto-detect daylight saving time
    tm.tm_isdst = -1;

    return mktime(&tm);
}

cell AMX_NATIVE_CALL timestamp_to_date(AMX* amx, cell* params)
{
    time_t t = params[1];
    struct tm *tm = localtime(&t);

    if (tm == NULL)
        return 0;

    char date[12] = { 0 };
    strftime(date, sizeof(date), "%F", tm);

    cell *addr = NULL;

    amx_GetAddr(amx, params[2], &addr);
    amx_SetString(addr, date, 0, 0, params[3]);

    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

    logprintf(" --------------------------------------------------------");
    logprintf(" timeutils version %s successfully loaded!", PLUGIN_VERSION);
    logprintf(" Developer: Manuel Schnitzer");
    logprintf(" Website: https://github.com/mschnitzer/time");
    logprintf(" --------------------------------------------------------");

    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf(" * timeutils was unloaded.");
}

extern "C" const AMX_NATIVE_INFO PluginNatives[] =
{
    { "time_convert", time_convert },
    // datetime functions
    { "datetime", datetime },
    { "timestamp_to_datetime", timestamp_to_datetime },
    { "datetime_to_timestamp", datetime_to_timestamp },
    // date functions
    { "date", date },
    { "datetime_to_date", datetime_to_date },
    { "date_to_datetime", date_to_datetime },
    { "date_to_timestamp", date_to_timestamp },
    { "timestamp_to_date", timestamp_to_date },
    { 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
    return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
    return AMX_ERR_NONE;
}
