#ifndef CENTRALREGISTRY_H
#define CENTRALREGISTRY_H

#include <string>
#include <map>

class Kiosk;

class CentralRegistry {
private:
    static CentralRegistry* instance;
    std::map<std::string, Kiosk*> kiosks;
    std::map<std::string, std::string> globalConfig;
    std::string systemStatus;

    CentralRegistry() : systemStatus("Initialized") {}
public:
    static CentralRegistry* getInstance();
    void registerKiosk(const std::string& id, Kiosk* kiosk);
    Kiosk* getKiosk(const std::string& id);
    
    // Config management
    void setConfig(const std::string& key, const std::string& val) { globalConfig[key] = val; }
    std::string getConfig(const std::string& key) { return globalConfig[key]; }
    
    // Status management
    void setStatus(const std::string& status) { systemStatus = status; }
    std::string getStatus() const { return systemStatus; }

    CentralRegistry(const CentralRegistry&) = delete;
    void operator=(const CentralRegistry&) = delete;
};

#endif
