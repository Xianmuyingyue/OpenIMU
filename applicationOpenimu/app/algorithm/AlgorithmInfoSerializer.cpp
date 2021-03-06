#include"AlgorithmInfoSerializer.h"
#include <QDebug>


AlgorithmInfoSerializer::AlgorithmInfoSerializer()
{

}
AlgorithmInfoSerializer::~AlgorithmInfoSerializer()
{

}
void AlgorithmInfoSerializer::Serialize(AlgorithmInfo algorithmInfo, std::string& output)
{
    //to do : verify that possible values are correctly serialize. I think right now it isn't
    Json::Value jsonAlgorithmInfo(Json::objectValue);
    Json::Value jsonAlgorithmParametersInfo(Json::arrayValue);
    Json::Value jsonAlgorithmParametersPossibleValues(Json::arrayValue);

    // Serializing the member variables ...
    jsonAlgorithmInfo["author"] = algorithmInfo.m_author;
    jsonAlgorithmInfo["description"] = algorithmInfo.m_description;
    jsonAlgorithmInfo["details"] = algorithmInfo.m_details;
    jsonAlgorithmInfo["id"] = algorithmInfo.m_id;
    jsonAlgorithmInfo["name"] = algorithmInfo.m_name;
    jsonAlgorithmInfo["filename"] = algorithmInfo.m_filename;

    // ... and the Algorithm Parameters
    for(int i = 0; i < algorithmInfo.m_parameters.size(); i++)
    {
       ParameterInfo parameterInfo = algorithmInfo.m_parameters.at(i);
       Json::Value jsonParameter(Json::objectValue);

       jsonParameter["description"] = parameterInfo.m_description;
       jsonParameter["name"] = parameterInfo.m_name;
       jsonParameter["value"] = parameterInfo.m_value;
       jsonParameter["defaultvalue"] = parameterInfo.m_defaultValue;

       jsonAlgorithmParametersInfo.append(jsonParameter);
    }

    jsonAlgorithmInfo["parametersInfo"] = jsonAlgorithmParametersInfo;

    // Write the Serialized data in an Output String
    Json::StyledWriter writer;
    output = writer.write(jsonAlgorithmInfo);
}

void AlgorithmInfoSerializer::Deserialize(std::string& dataToDeserialize)
{
    Json::Value deserializeRoot;
    Json::Reader reader;

    if ( !reader.parse(dataToDeserialize, deserializeRoot) )
    {
        dataToDeserialize = "";
        return;
    }

    Json::Value algorithmListInJson = deserializeRoot.get("algorithms", "");
    for ( int index = 0; index < algorithmListInJson.size(); ++index )
    {
        AlgorithmInfo algorithmInfo;

        algorithmInfo.m_name = algorithmListInJson[index].get("name", "").asString();
        algorithmInfo.m_filename = algorithmListInJson[index].get("filename", "").asString();
        algorithmInfo.m_id = algorithmListInJson[index].get("id", "").asString();
        algorithmInfo.m_author = algorithmListInJson[index].get("author", "").asString();
        algorithmInfo.m_description = algorithmListInJson[index].get("description", "").asString();
        algorithmInfo.m_details = algorithmListInJson[index].get("details", "").asString();

        Json::Value parameterListInJson = algorithmListInJson[index].get("params", "");
        for ( int indexp = 0; indexp < parameterListInJson.size(); ++indexp )
        {
            ParameterInfo parameterInfo;
            parameterInfo.m_name = parameterListInJson[indexp].get("name", "").asString();
            parameterInfo.m_description = parameterListInJson[indexp].get("info", "").asString();
            parameterInfo.m_value = parameterListInJson[indexp].get("value", "").asString();
            parameterInfo.m_defaultValue = parameterListInJson[indexp].get("default", "").asString();
            parameterInfo.m_defaultValue = parameterInfo.m_defaultValue.substr(0, 4);
            algorithmInfo.m_parameters.push_back(parameterInfo);
        }

        m_algorithmList.push_back(algorithmInfo);
    }
}
