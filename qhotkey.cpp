#ifndef QHOTKEY_WIN_H
#define QHOTKEY_WIN_H
#include <QtCore>

#ifdef Q_OS_WIN
#include "qhotkey.h"
#include <Windows.h>

int QHotkey::_ghkid = 1800;
struct QHotkey::PlatformData
{
    int thrId;
    UINT wmId;
};

QHotkey::QHotkey(const uint modifiers, const uint key)
    : _modifiers(modifiers), _key(key),
      _hkid(_ghkid++), _registered(false),
      _loop(&QHotkey::registerHotkey, this),
      _pData(new PlatformData) {}

QHotkey::~QHotkey()
{
    // Send WM_QHOTKEY_UNHOOK message to messageLoop()
    PostThreadMessage(_pData->thrId, _pData->wmId, NULL, NULL);
    _loop.join();
    UnregisterHotKey(NULL, _hkid);
    delete _pData;
}

void QHotkey::registerHotkey()
{
    _pData->wmId = RegisterWindowMessage(L"WM_QHOTKEY_UNHOOK");
    _pData->thrId = GetCurrentThreadId();

    try {
        if (_registered)
            throw std::runtime_error("This QHotkey instance is already registered!");

        int result = RegisterHotKey(NULL, _hkid, _modifiers, _key);
        if (result == 0)
            throw std::runtime_error("Could not register hotkey! #"); // + GetLastError()

        _registered = (result == 0);
    }  catch (std::runtime_error ex) {
        qDebug() << ex.what();
    }

    messageLoop();
}

void QHotkey::messageLoop() const
{
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL)) {
        if (msg.message == _pData->wmId) return;
        if (msg.message == WM_HOTKEY && msg.wParam == _hkid) {
            emit pressed(*this);
        }
    }
}
#endif // Q_OS_WIN

#endif // QHOTKEY_WIN_H
