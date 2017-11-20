/**
 * @file InterprocessMessage.cpp
 * @author calligp
 * @date 22/02/2015
 * @brief Abstraction Layer for IPC message
 * @details Contains data regarding IPC message content
 */

//System includes
//Libraries includes
//Application includes
#include "InterprocessMessage.h"

// Using directives
using namespace std;

namespace CommunicationModule
{
    InterprocessMessage::InterprocessMessage()
    : mIdentifier(IPCID_NONE),
      mType(IPCTYPE_NONE),
      mParameters({})
    {
    }

    InterprocessMessage::~InterprocessMessage()
    {
    }

    void InterprocessMessage::SetIpcIdentifier(std::string aIdentifier)
    {
        mIdentifier = aIdentifier;
    }

    std::string InterprocessMessage::GetIpcIdentifier()
    {
        return mIdentifier;
    }

    void InterprocessMessage::SetIpcType(std::string aType)
    {
        mType = aType;
    }

    std::string InterprocessMessage::GetIpcType()
    {
        return mType;
    }

    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, std::string aValue)
    {
        mParameters[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, int aValue)
    {
        mParameters[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, double aValue)
    {
        mParameters[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, bool aValue)
    {
        mParameters[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, IpcArray aValue)
    {
        mParameters[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::SetIpcParameters(std::string aKey, IpcObject aValue)
    {
        mParameters[aKey] = aValue;
    }

    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, std::string aValue)
    {
        aArray.push_back(aValue);
    }
    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, int aValue)
    {
        aArray.push_back(aValue);
    }
    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, double aValue)
    {
        aArray.push_back(aValue);
    }
    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, bool aValue)
    {
        aArray.push_back(aValue);
    }
    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, IpcArray aValue)
    {
        aArray.push_back(aValue);
    }
    /*virtual */void InterprocessMessage::AddValueToArray(IpcArray& aArray, IpcObject aValue)
    {
        aArray.push_back(aValue);
    }

    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, std::string aValue)
    {
        aObject[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, int aValue)
    {
        aObject[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, double aValue)
    {
        aObject[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, bool aValue)
    {
        aObject[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, IpcArray aValue)
    {
        aObject[aKey] = aValue;
    }
    /*virtual */void InterprocessMessage::AddValueToObject(IpcObject& aObject, std::string aKey, IpcObject aValue)
    {
        aObject[aKey] = aValue;
    }

    bool InterprocessMessage::Serialize(std::string& arIpcMessage)
    {
        bool wRet = false;
        try
        {
            json_spirit::mObject wIpcJson;
            wIpcJson[IPCPROPERTY_ID] = mIdentifier;
            wIpcJson[IPCPROPERTY_TYPE] = mType;
            wIpcJson[IPCPROPERTY_PARAMETERS] = mParameters;

            arIpcMessage = json_spirit::write_string(json_spirit::mValue(wIpcJson), json_spirit::raw_utf8 | json_spirit::remove_trailing_zeros);

            wRet = true;
        }
        catch( const std::exception& arException )
        {
            stringstream wMsg;
            wMsg << "Failed to serialize IPC message: " << arException.what();
            COMMUNICATIONMODULE_LOG_ERROR_MESSAGE(wMsg.str());
        }
        return wRet;
    }

    bool InterprocessMessage::SerializeParameters(std::string& arIpcMessage)
    {
        bool wRet = false;
        try
        {
            arIpcMessage = json_spirit::write_string(json_spirit::mValue(mParameters), json_spirit::raw_utf8 | json_spirit::remove_trailing_zeros);

            wRet = true;
        }
        catch( const std::exception& arException )
        {
            stringstream wMsg;
            wMsg << "Failed to serialize IPC message: " << arException.what();
            COMMUNICATIONMODULE_LOG_ERROR_MESSAGE(wMsg.str());
        }
        return wRet;
    }

    bool InterprocessMessage::Deserialize(const std::string& arIpcMessage)
    {
        bool wRet = false;
        json_spirit::mObject wObj;
        json_spirit::mValue wValue;
        try
        {
            json_spirit::read_string(arIpcMessage, wValue);
            wObj = wValue.get_obj();
            // Read property tree
            json_spirit::mObject::iterator wIdIterator = wObj.find(IPCPROPERTY_ID);
            json_spirit::mObject::iterator wTypeIterator =  wObj.find(IPCPROPERTY_TYPE);
            if (wObj.end() != wIdIterator && wObj.end() != wTypeIterator)
            {
                mIdentifier = wIdIterator->second.get_str();
                mType = wTypeIterator->second.get_str();

                // Parameters are optional
                json_spirit::mObject::iterator wParamIterator = wObj.find(IPCPROPERTY_PARAMETERS);
                if (wObj.end() != wParamIterator)
                {
                    mParameters = wParamIterator->second.get_obj();
                }
                wRet = true;
            }
        }
        catch( const std::exception& arException )
        {
            stringstream wMsg;
            wMsg << "Failed to deserialize IPC message (" << arIpcMessage << "): " << arException.what();
            COMMUNICATIONMODULE_LOG_ERROR_MESSAGE(wMsg.str());
        }
        return wRet;
    }

    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, std::string* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_str();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, int* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_int();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, double* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_real();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, bool* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_bool();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, IpcArray* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_array();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFor(std::string aKey, IpcObject* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = mParameters.find(aKey);
        if (mParameters.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_obj();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, std::string* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_str();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, int* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_int();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, double* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_real();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, bool* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_bool();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, IpcArray* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_array();
            wReturn = true;
        }
        return wReturn;
    }
    /*virtual */bool InterprocessMessage::GetValueFromObject(IpcObject aObject, std::string aKey, IpcObject* aValue)
    {
        bool wReturn = false;
        json_spirit::mObject::iterator wValueIterator = aObject.find(aKey);
        if (aObject.end() != wValueIterator)
        {
            *aValue = wValueIterator->second.get_obj();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, std::string* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_str();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, int* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_int();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, double* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_real();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, bool* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_bool();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, IpcArray* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_array();
            wReturn = true;
        }
        return wReturn;
    }

    /*virtual */bool InterprocessMessage::GetValueFromArray(IpcArray aArray, uint16_t aIndex, IpcObject* aValue)
    {
        bool wReturn = false;
        if (aArray.size() > aIndex)
        {
            *aValue = aArray[aIndex].get_obj();
            wReturn = true;
        }
        return wReturn;
    }
}
