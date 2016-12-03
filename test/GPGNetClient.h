#pragma once

#include <giomm.h>

#include "GPGNetMessage.h"

class GPGNetClient
{
public:
  GPGNetClient();
  void connect(int port);
protected:
  bool onRead(Glib::IOCondition);
  Glib::RefPtr<Gio::Socket> mSocket;
};
