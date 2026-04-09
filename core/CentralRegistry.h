#ifndef CENTRALREGISTRY_H
#define CENTRALREGISTRY_H
#include <string>
#include <map>
class Kiosk;
class CentralRegistry {
private:
    static CentralRegistry* instance;
    std::map<std::string, Kiosk*> kiosks;
    CentralRegistry() {}
public:
    static CentralRegistry* getInstance();
    void registerKiosk(const std::string& id, Kiosk* kiosk);
    Kiosk* getKiosk(const std::string& id);
    CentralRegistry(const CentralRegistry&) = delete;
    void operator=(const CentralRegistry&) = delete;
};
#endif
