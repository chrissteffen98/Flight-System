#ifndef NAVIGATION_KALMAN_MIX_H
#define NAVIGATION_KALMAN_MIX_H



#include "navigation_abstract.h"

#include "KraftKontrol/modules/sensor_modules/gyroscope_modules/gyroscope_abstract.h"
#include "KraftKontrol/modules/sensor_modules/accelerometer_modules/accelerometer_abstract.h"
#include "KraftKontrol/modules/sensor_modules/magnetometer_modules/magnetometer_abstract.h"
#include "KraftKontrol/modules/sensor_modules/barometer_modules/barometer_abstract.h"
#include "KraftKontrol/modules/sensor_modules/gnss_modules/gnss_abstract.h"

#include "KraftKontrol/modules/system_models/system_model_abstract.h"

#include "KraftKontrol/modules/actuator_modules/actuator_abstract.h"

#include "KraftKontrol/utils/topic_subscribers.h"

#include "KraftKontrol/utils/Simple-Schedule/task_autorun_class.h"
#include "KraftKontrol/utils/buffer.h"
#include "KraftKontrol/utils/low_pass_filter.h"
#include "lib/MathHelperLibrary/FML.h"

#include "lib/uNavAHRS-master/uNavAHRS.h"



class NavigationKalmanMix: public Navigation_Abstract, public Task_Abstract {
private:

    //Subscriber for gyro with fifo function
    /*Buffer_Subscriber<DataTimestamped<Vector<>>, 100> gyroSub_;
    //Subscriber for accel with fifo function
    Buffer_Subscriber<DataTimestamped<Vector<>>, 100> accelSub_;
    //Subscriber for mag with fifo function
    Buffer_Subscriber<DataTimestamped<Vector<>>, 100> magSub_;
    //Subscriber for baro with fifo function
    Buffer_Subscriber<DataTimestamped<float>, 20> baroSub_;
    //Subscriber for gnssdata with fifo function
    Buffer_Subscriber<DataTimestamped<GNSSData>, 10> gnssSub_;*/

    uNavAHRS attFilter = uNavAHRS();

    //Subscriber for gyro with fifo function
    Simple_Subscriber<DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>>> gyroSub_;
    //Subscriber for accel with fifo function
    Simple_Subscriber<DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>>> accelSub_;
    //Subscriber for mag with fifo function
    Simple_Subscriber<DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>>> magSub_;
    //Subscriber for baro with fifo function
    Simple_Subscriber<DataTimestamped<float>> baroSub_;
    //Subscriber for gnssdata with fifo function
    Simple_Subscriber<DataTimestamped<GNSSData>> gnssSub_;

    //Timestamp of last thread run
    int64_t lastLoopTimestamp_ = NOW();

    DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>> gyroData;
    DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>> accelData;
    DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>> magData;

    bool firstAccelWait = false;
    bool firstGyroWait = false;

    //Last gyroscope data
    DataTimestamped<SensorData<FML::Vector3_F, FML::Matrix33_F>> lastGyroData_;

    //Last accel value
    Vector<> lastAccelValue_ = 0;
    //Last accel value error
    Vector<> lastAccelCov_ = 10000;
    //Accel cov values
    Buffer<Vector<>, 10> accelCovBuf_;
    //Timestamp of last accel value
    int64_t lastAccelTimestamp_ = NOW();
    LowPassFilter<Vector<>> accelBias = LowPassFilter<Vector<>>(0.05);

    int64_t lastMagTimestamp_ = 0;

    //Last baro height value
    float lastBaroValue_ = 0;
    //Last baro height error
    float lastBaroCov_ = 10000;
    //Baro height cov values
    Buffer<float, 1000> baroCovBuf_;
    //Timestamp of last accel value
    int64_t lastBaroTimestamp_ = NOW();
    //Baro sea level pressure
    float sealevelPressure_ = 1015e2;

    //Timestamp of last accel value
    int64_t lastGNSSTimestamp_ = NOW();

    //Model of vehicle
    SystemModel_Abstract& systemModel_;


public:

    NavigationKalmanMix(SystemModel_Abstract& systemModel);

    /**
     * Sets the gyroscope to be used.
     * @param gyro Gyroscope to use.
     */
    void setGyroscopeInput(const Gyroscope_Abstract& gyro);

    /**
     * Removes the gyroscope input.
     */
    void removeGyroscopeInput();

    /**
     * Sets the accelerometer to be used.
     * @param accel Accelerometer to use.
     */
    void setAccelerometerInput(const Accelerometer_Abstract& accel);

    /**
     * Removes the accelerometer input.
     */
    void removeAccelerometerInput();

    /**
     * Sets the magnetometer to be used.
     * @param mag Magnetometer to use.
     */
    void setMagnetometerInput(const Magnetometer_Abstract& mag);

    /**
     * Removes the magnetometer input.
     */
    void removeMagnetometerInput();

    /**
     * Sets the barometer to be used.
     * @param baro Barometer to use.
     */
    void setBarometerInput(const Barometer_Abstract& baro);

    /**
     * Removes the barometer input.
     */
    void removeBarometerInput();

    /**
     * Sets the GNSS to be used.
     * @param gnss GNSS to use.
     */
    void setGNSSInput(const GNSS_Abstract& gnss);

    /**
     * Removes the GNSS input.
     */
    void removeGNSSInput();

    /**
     * Initialises module. Is automatically called by scheduler.
     */
    void init() override;

    /**
     * Gives module time to do calculations and publish values. Is automatically called by scheduler.
     */
    void thread() override;


};




#endif