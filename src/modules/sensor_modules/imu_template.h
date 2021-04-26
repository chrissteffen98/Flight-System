#ifndef IMU_TEMPLATE_H
#define IMU_TEMPLATE_H



#include "modules/module_template.h"

#include "3d_math.h"



class IMUTemplate: public Module_Abstract {
public:

    IMUTemplate(uint32_t rate, eTaskPriority_t priority) : Module_Abstract(rate, priority) {}

    /**
     * Returns rate (in Hz) of the thread
     *
     * @param values none.
     * @return uint32_t.
     */
    virtual uint32_t loopRate() = 0;

    /**
     * Returns true if gyro data available
     *
     * @param values none.
     * @return bool.
     */
    virtual bool gyroAvailable() = 0;

    /**
     * Returns rate (in Hz) of the new sensor data
     *
     * @param values none.
     * @return uint32_t.
     */
    virtual uint32_t gyroRate() = 0;

    /**
     * Returns true if gyro data valid.
     * Variables given as parameters will be overridden.
     * This will remove sensor data from queue, peek will not.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool getGyro(Vector* gyroData, uint32_t* gyroTimestamp) = 0;

    /**
     * Returns true if gyro data valid.
     * Variables given as parameters will be overridden.
     * Will not remove data from queue, get will.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool peekGyro(Vector* gyroData, uint32_t* gyroTimestamp) = 0;

    /**
     * Removes all elements from queue.
     *
     * @param values none.
     * @return none.
     */
    virtual void flushGyro() = 0;

    /**
     * Returns true if accel data available
     *
     * @param values none.
     * @return bool.
     */
    virtual bool accelAvailable() = 0;

    /**
     * Returns rate (in Hz) of the new sensor data
     *
     * @param values none.
     * @return uint32_t.
     */
    virtual uint32_t accelRate() = 0;

    /**
     * Returns true if accel data valid.
     * Variables given as parameters will be overridden.
     * This will remove sensor data from queue, peek will not.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool getAccel(Vector* accelData, uint32_t* accelTimestamp) = 0;

    /**
     * Returns true if accel data valid.
     * Variables given as parameters will be overridden.
     * Will not remove data from queue, get will.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool peekAccel(Vector* accelData, uint32_t* accelTimestamp) = 0;

    /**
     * Removes all elements from queue.
     *
     * @param values none.
     * @return none.
     */
    virtual void flushAccel() = 0;
    /**
     * Returns true if Magnetometer data available
     *
     * @param values none.
     * @return bool.
     */
    virtual bool magAvailable() = 0;

    /**
     * Returns rate (in Hz) of the new sensor data
     *
     * @param values none.
     * @return uint32_t.
     */
    virtual uint32_t magRate() = 0;

    /**
     * Returns true if Magnetometer data valid.
     * Variables given as parameters will be overridden.
     * This will remove sensor data from queue, peek will not.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool getMag(Vector* magData, uint32_t* magTimestamp) = 0;

    /**
     * Returns true if Magnetometer data valid.
     * Variables given as parameters will be overridden.
     * Will not remove data from queue, get will.
     *
     * @param values Vector and uint32_t.
     * @return bool.
     */
    virtual bool peekMag(Vector* magData, uint32_t* magTimestamp) = 0;

    /**
     * Removes all elements from queue.
     *
     * @param values none.
     * @return none.
     */
    virtual void flushMag() = 0;


private:



    
};





#endif