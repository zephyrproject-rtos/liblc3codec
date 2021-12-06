/*
 * DatapointsDummy.cpp
 *
 * Copyright 2019 HIMSA II K/S - www.himsa.com. Represented by EHIMA - www.ehima.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Datapoints.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>


class ContainerRealization
{
};

DatapointContainer::DatapointContainer() : m_pContainer(nullptr)
{
    // nothing stored yet; we may integrate a complete datapoint container when more debugging
    // is needed in the android context
    (void) m_pContainer;
}

DatapointContainer::~DatapointContainer()
{
}

void DatapointContainer::addDatapoint(const char* label, Datapoint* pDatapoint)
{
}

void DatapointContainer::addDatapoint(const char* label, void* pData, uint16_t sizeInBytes)
{
}

void DatapointContainer::addDatapoint(const char* label, const void* pData, uint16_t sizeInBytes)
{
}

void DatapointContainer::log(const char* label, const void* pData,  uint16_t sizeInBytes)
{
    // Note: this is just a first simple step to demonstrate the possibilities we have.
    //   In this case the datapoint label its size in bytes and its content as hex-byte-stream
    //   is send to the android LOG.
    const uint8_t* pByteData = reinterpret_cast<const uint8_t*>(pData);
    std::string valueAsHexString("0x");
    std::ostringstream vStream;
    vStream << "0x";
    for (uint16_t byteNr=0; byteNr < sizeInBytes; byteNr++)
    {
        vStream << std::right
                << std::setw(2)
                << std::setfill('0')
                << std::hex
                << static_cast<int>(pByteData[byteNr]);
    }
    std::cout << label << "[" << sizeInBytes << "]:" << vStream.str();
}


uint16_t DatapointContainer::getDatapointSize(const char* label)
{
    return 0;
}

bool DatapointContainer::getDatapointValue(const char* label, void* pDataBuffer, uint16_t bufferSize)
{
    return false;
}

bool DatapointContainer::setDatapointValue(const char* label, const void* pDataBuffer, uint16_t bufferSize)
{
    return false;
}
