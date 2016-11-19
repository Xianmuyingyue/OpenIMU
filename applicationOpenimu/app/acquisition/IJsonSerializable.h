#ifndef IJSONSERIALIZABLE_H
#define IJSONSERIALIZABLE_H

#include "ObjectInfo.h"
#include "json/json.h"

class IJsonSerializable
{
public:
   virtual ~IJsonSerializable( void ) {}
   virtual void Serialize( Json::Value& root, ObjectInfo* info, std::string& output) =0;
   virtual void Deserialize( Json::Value& root) =0;
};
#endif
