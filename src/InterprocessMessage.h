/**
 * @file InterprocessMessage.h
 * @author calligp
 * @date 22/02/2015
 * @brief Abstraction Layer for IPC message
 * @details Contains data regarding IPC message content
 */

#ifndef SRC_COMMUNICATIONMODULE_IPCMESSAGE_H_
#define SRC_COMMUNICATIONMODULE_IPCMESSAGE_H_

//System includes
//Libraries includes
#include <json_spirit_reader_template.h>
#include <json_spirit_writer_template.h>
//Application includes
#include "CommunicationModuleToolbox.h"
#include "HesProcessInterface.h"

namespace CommunicationModule
{
    typedef json_spirit::mArray IpcArray;
    typedef json_spirit::mObject IpcObject;

    class InterprocessMessage
    {
    public:
        InterprocessMessage(void);
        virtual ~InterprocessMessage(void);

        void SetIpcIdentifier(std::string aIdentifier);
        void SetIpcType(std::string aType);
        std::string GetIpcIdentifier(void);
        std::string GetIpcType(void);
        virtual void SetIpcParameters(std::string aKey, std::string aValue);
        virtual void SetIpcParameters(std::string aKey, int aValue);
        virtual void SetIpcParameters(std::string aKey, double aValue);
        virtual void SetIpcParameters(std::string aKey, bool aValue);
        virtual void SetIpcParameters(std::string aKey, IpcArray aValue);
        virtual void SetIpcParameters(std::string aKey, IpcObject aValue);

        //virtual IpcArray BuildArray();
        virtual void AddValueToArray(IpcArray& aArray, std::string aValue);
        virtual void AddValueToArray(IpcArray& aArray, int aValue);
        virtual void AddValueToArray(IpcArray& aArray, double aValue);
        virtual void AddValueToArray(IpcArray& aArray, bool aValue);
        virtual void AddValueToArray(IpcArray& aArray, IpcArray aValue);
        virtual void AddValueToArray(IpcArray& aArray, IpcObject aValue);

        //virtual IpcObject BuildObject();
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, std::string aValue);
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, int aValue);
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, double aValue);
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, bool aValue);
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, IpcArray aValue);
        virtual void AddValueToObject(IpcObject& aObject, std::string aKey, IpcObject aValue);

        bool Serialize(std::string& arIpcMessage);
        bool SerializeParameters(std::string& arIpcMessage);
        bool Deserialize(const std::string& arIpcMessage);

        virtual bool GetValueFor(std::string aKey, std::string* aValue);
        virtual bool GetValueFor(std::string aKey, int* aValue);
        virtual bool GetValueFor(std::string aKey, double* aValue);
        virtual bool GetValueFor(std::string aKey, bool* aValue);
        virtual bool GetValueFor(std::string aKey, IpcArray* aValue);
        virtual bool GetValueFor(std::string aKey, IpcObject* aValue);

        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, std::string* aValue);
        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, int* aValue);
        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, double* aValue);
        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, bool* aValue);
        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, IpcArray* aValue);
        virtual bool GetValueFromObject(IpcObject aObject, std::string aKey, IpcObject* aValue);

        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, std::string* aValue);
        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, int* aValue);
        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, double* aValue);
        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, bool* aValue);
        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, IpcArray* aValue);
        virtual bool GetValueFromArray(IpcArray aArray, uint16_t aIndex, IpcObject* aValue);

    private:
        std::string mIdentifier;
        std::string mType;
        json_spirit::mObject mParameters;
    };
}
#endif // SRC_COMMUNICATIONMODULE_IPCMESSAGE_H_

