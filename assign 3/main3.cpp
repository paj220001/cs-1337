#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <stdio.h>
#include <cmath>
using namespace std;

#define      GroundStationOutputChannel        cout
#define      masterInfoSatellite               masterInfoDiscriminatedUnionStruct.masterUnion.satelliteInformation
#define      masterInfoExperiment              masterInfoDiscriminatedUnionStruct.masterUnion.expirimentInformation
#define      infoStoredArrayatindexSatellite   infoStoredArray[index].masterUnion.satelliteInformation
#define      infoStoredArrayatindexExperiment  infoStoredArray[index].masterUnion.expirimentInformation

const string TELEMETRY_INPUT_CHANNEL = "inputTelemetryData.txt";

enum class MESSAGE_ID_ENUM_CLASS { SATELLITE_INFORMATION_MESSAGE = 1, EXPERIMENT_INFORMATION_MESSAGE = 2};
MESSAGE_ID_ENUM_CLASS messageIdEnum;

enum class INFO_TYPE_ENUM_CLASS  { SATELLITE_INFORMATION, EXPIRIMENT_INFORMATION, EMPTY };

const uint8_t ARRAY_DATA_STORAGE_SIZE = 5;

float_t minTemperature  = 212,       // -50 - 212
        maxTemperature  = -50;
float_t minVoltage = 100.0,          // 0.0 - 100.0
        maxVoltage = 0.0;

struct SatelliteInfoStruct 
{
    float_t temperature;
    float_t voltage;
};
struct ExperimentInfoStruct 
{
    uint16_t radiationCount;
    uint16_t latchupEventsCount;
};
union MasterUnion 
{
    SatelliteInfoStruct  satelliteInformation;
    ExperimentInfoStruct expirimentInformation;
};

// Descriminated Union
struct MasterInfoDiscriminatedUnionStruct 
{
    INFO_TYPE_ENUM_CLASS infoTypeEnum;
    MasterUnion          masterUnion;
};

int main() {
    MasterInfoDiscriminatedUnionStruct infoStoredArray[ARRAY_DATA_STORAGE_SIZE];
    MasterInfoDiscriminatedUnionStruct masterInfoDiscriminatedUnionStruct;
    uint8_t entryPositionIndex = 0;
    uint8_t index = entryPositionIndex;
    ifstream telemetryInputChannel(TELEMETRY_INPUT_CHANNEL);
    bool loop = false;

    if(telemetryInputChannel)
    {

      GroundStationOutputChannel << setprecision(1) << fixed << showpoint;

      // in infoStoredArray set each element infoType to EMPTY
      for(int count = 0; count < ARRAY_DATA_STORAGE_SIZE; count++)
      {
        infoStoredArray[count].infoTypeEnum = INFO_TYPE_ENUM_CLASS::EMPTY;
      }
      uint16_t messageIdUInt;
      while (telemetryInputChannel >> messageIdUInt) {
          GroundStationOutputChannel <<
              "Current Telemetry Information: " << endl <<
              "------------------------------ " << endl;

          // convert file number messageIdUInt to enumerated messageIdEnum variable 
          if(messageIdUInt == 1)
          {
            messageIdEnum = MESSAGE_ID_ENUM_CLASS::SATELLITE_INFORMATION_MESSAGE;
          }
          else 
          if(messageIdUInt == 2)
          {
            messageIdEnum = MESSAGE_ID_ENUM_CLASS::EXPERIMENT_INFORMATION_MESSAGE;
          }
          switch (messageIdEnum) {
          
            case MESSAGE_ID_ENUM_CLASS::SATELLITE_INFORMATION_MESSAGE:

              // set discriminated union masterInfoDiscriminatedUnionStruct infoType to SATELLITE INFORMATION
              infoStoredArray[entryPositionIndex].infoTypeEnum = INFO_TYPE_ENUM_CLASS::SATELLITE_INFORMATION;
              // read in from telemetryInputChannel into union masterInfoSatellite temperature and voltage
              telemetryInputChannel >> masterInfoSatellite.temperature >> masterInfoSatellite.voltage;
              // send this information to the Ground Station Output Channel, see output in the assignment
              GroundStationOutputChannel << "Temperature : " << masterInfoSatellite.temperature << endl;
              GroundStationOutputChannel << "Voltage     : " << masterInfoSatellite.voltage << endl << endl;
              // put masterInfoDiscriminatedUnionStruct into stored array at the entry Position Index
              index = entryPositionIndex;
              infoStoredArrayatindexSatellite = masterInfoSatellite;
              // adjust entryPositionIndex to next entry or back to start index if past end of array
              entryPositionIndex++;
              if(entryPositionIndex == 5)
              {
                entryPositionIndex = 0;
                loop = true;
              }
            break; //MESSAGE_ID_ENUM_CLASS::SATELLITE_INFORMATION_MESSAGE:

            case MESSAGE_ID_ENUM_CLASS::EXPERIMENT_INFORMATION_MESSAGE:

              // set discriminated union masterInfoDiscriminatedUnionStruct infoTypeEnum to EXPIRIMENT INFORMATION
              infoStoredArray[entryPositionIndex].infoTypeEnum = INFO_TYPE_ENUM_CLASS::EXPIRIMENT_INFORMATION;
              // read in from telemetryInputChannel into union masterInfoSatellite radiation Count and latchupEventsCount
              telemetryInputChannel >> masterInfoExperiment.radiationCount >> masterInfoExperiment.latchupEventsCount;
              // send this information to the Ground Station Output Channel, see output in the assignment
              GroundStationOutputChannel << "Radiation Count      : " << masterInfoExperiment.radiationCount << endl;
              GroundStationOutputChannel << "Latch up Event Count : " << masterInfoExperiment.latchupEventsCount << endl << endl;
              // put masterInfoDiscriminatedUnionStruct into stored array at the entry Position Index
              index = entryPositionIndex;
              infoStoredArrayatindexExperiment = masterInfoExperiment;
              // adjust entryPositionIndex to next entry or back to start index if past end of array
              entryPositionIndex++;
              if(entryPositionIndex == 5)
              {
                entryPositionIndex = 0;
                loop = true;
              }
            break; //MESSAGE_ID::EXPERIMENT_INFORMATION_MESSAGE:

          }//switch (infoStoredArray[index].infoType)

          // set summary information initialization

          uint16_t totalRadiationCount    = 0,
                  totalLatchupEventCount = 0,
                  infoSICount            = 0,
                  infoEICount            = 0;

          
          GroundStationOutputChannel <<
              "History:" << endl <<
              "--------" << endl;

          for (uint8_t index = 0; index < ARRAY_DATA_STORAGE_SIZE; index++) 
          {
            if(index == 0 && loop == false)
            {
              minTemperature  = infoStoredArray[0].masterUnion.satelliteInformation.temperature;       // -50 - 212
              maxTemperature  = infoStoredArray[0].masterUnion.satelliteInformation.temperature;
              minVoltage = infoStoredArray[0].masterUnion.satelliteInformation.voltage;         // 0.0 - 100.0
              maxVoltage = infoStoredArray[0].masterUnion.satelliteInformation.voltage;
            }
              switch (infoStoredArray[index].infoTypeEnum) 
              {

                case INFO_TYPE_ENUM_CLASS::SATELLITE_INFORMATION:

                  // send to ground station output channel temperature and voltage
                  GroundStationOutputChannel << "Temperature : " << infoStoredArrayatindexSatellite.temperature << endl;
                  GroundStationOutputChannel << "Voltage     : " << infoStoredArrayatindexSatellite.voltage << endl << endl;;
                  // see assignment output example
                  // increment info SI Count
                  infoSICount++;
                  // set running min max summary information (temperature, voltage)
                  if(infoStoredArrayatindexSatellite.temperature > maxTemperature)
                  {
                    maxTemperature = infoStoredArrayatindexSatellite.temperature;
                  }
                  else if(infoStoredArrayatindexSatellite.temperature < minTemperature)
                  {
                    minTemperature = infoStoredArrayatindexSatellite.temperature;
                  }

                  if(infoStoredArrayatindexSatellite.voltage > maxVoltage)
                  {
                    maxVoltage = infoStoredArrayatindexSatellite.voltage;
                  }
                  else if(infoStoredArrayatindexSatellite.voltage < minVoltage)
                  {
                    minVoltage = infoStoredArrayatindexSatellite.voltage;
                  }
                    
                break; //case SATELLITE_INFORMATION:

                case INFO_TYPE_ENUM_CLASS::EXPIRIMENT_INFORMATION:

                  // send to ground station output channel radiation and latchup Events Count
                  GroundStationOutputChannel << "Radiation Count      : " << infoStoredArrayatindexExperiment.radiationCount << endl;
                  GroundStationOutputChannel << "Latch up Event Count : " << infoStoredArrayatindexExperiment.latchupEventsCount << endl << endl;
                  // see assignemnt output example
                  // increment info EI Count
                  infoEICount++;
                  // increase sum up totals for radiationCount and LatchupEventCount
                  totalRadiationCount += infoStoredArrayatindexExperiment.radiationCount;
                  totalLatchupEventCount += infoStoredArrayatindexExperiment.latchupEventsCount;  
                  // from infoStoredArrayatindexExperiment for radiationCount and latchupEventCount                  
                      
                break;//case EXPIRIMENT_INFORMATION:

                case INFO_TYPE_ENUM_CLASS::EMPTY:
                  // do nothing for empty array items (skip)
                break; // EMPTY:
                
              }//switch (messageID)

          }//for summary

          GroundStationOutputChannel <<
              "Summary Information" << endl <<
              "-------------------" << endl <<
              "Number of Satellite  Information Records: " << infoSICount << endl <<
              "Number of Experiment Information Records: " << infoEICount << endl <<
              "Total Radiation Count      : " << totalRadiationCount      << endl <<
              "Total Latch Up Event Count : " << totalLatchupEventCount   << endl <<
              "Maximum Temperature        : " << maxTemperature           << endl <<
              "Minimum Temperature        : " << minTemperature           << endl <<
              "Maximum Voltage            : " << maxVoltage               << endl <<
              "Minimum Voltage            : " << minVoltage               << endl << endl <<
              "Press the enter key once or twice to contine..." << endl;
              cin.ignore();
              cin.get();


          // hold screen GroundStationOutputChannel


      }//while

      GroundStationOutputChannel << "Program Done" << endl;
    }//if
    else 
    {

      GroundStationOutputChannel << "File " << TELEMETRY_INPUT_CHANNEL << " could not be opened.\n";
    }

    exit(EXIT_SUCCESS);

}//main()