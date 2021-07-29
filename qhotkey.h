#ifndef QHOTKEY_H
#define QHOTKEY_H
#include <QtCore>
#include <thread>
#include <functional>

#ifdef QHOTKEYS_SHAREDLIB
#ifdef QHOTKEYS_EXPORT
#define QHOTKEYS_DLLSPEC Q_DECL_EXPORT
#else
#define QHOTKEYS_DLLSPEC Q_DECL_IMPORT
#endif
#else
#define QHOTKEYS_DLLSPEC
#endif

class QHOTKEYS_DLLSPEC QHotkey : public QObject
{
    Q_OBJECT
    using callback_t = std::function<void(const QHotkey&)>;

public:
    QHotkey(const uint modifiers, const uint key);
    ~QHotkey();

signals:
    void pressed(const QHotkey&) const;

private:
    const uint _modifiers;
    const uint _key;
    const int _hkid;
    bool _registered;
    std::thread _loop;

    struct PlatformData;
    PlatformData* _pData;

    static int _ghkid;

private:
    void registerHotkey();
    void messageLoop() const;
};
#endif // QHOTKEY_H
