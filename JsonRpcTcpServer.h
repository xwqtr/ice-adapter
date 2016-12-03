#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <map>
#include <string>

#include <giomm.h>

#include <json/json.h>

#include "TcpServer.h"

namespace faf
{

class JsonRpcTcpServer : public TcpServer
{
public:
  JsonRpcTcpServer(int port);
  virtual ~JsonRpcTcpServer();

  typedef std::function<void (Json::Value const& paramsArray,
                              Json::Value & result,
                              Json::Value & error)> RpcCallback;
  void setRpcCallback(std::string const& method,
                      RpcCallback cb);

  typedef std::function<void (Json::Value const& result,
                              Json::Value const& error)> RpcRequestResult;
  void sendRequest(std::string const& method,
                   Json::Value const& paramsArray = Json::Value(Json::arrayValue),
                   RpcRequestResult resultCb = RpcRequestResult());
protected:
  virtual void parseMessage(TcpSession* session, std::vector<char>& msgBuffer);
  Json::Value processRequest(Json::Value const& request);
  void onRpcRequest(std::string const& method,
                    Json::Value const& paramsArray,
                    Json::Value & result,
                    Json::Value & error);
  void onRpcResponse(Json::Value const& id,
                     Json::Value const& result,
                     Json::Value const& error);

  std::map<std::string, RpcCallback> mCallbacks;
  std::map<unsigned int, RpcRequestResult> mCurrentRequests;
  int mCurrentId;
};

}
