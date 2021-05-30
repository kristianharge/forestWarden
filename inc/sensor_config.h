/*==========================================================
 * Copyright 2020 QuickLogic Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *==========================================================*/
/* sensor message macros */
#if !defined(SENSOR_CONFIG_H)
#define SENSOR_CONFIG_H

/* these are used to initialize
 * const struct sensor_config_msg 
 */
#include "Mqttsn_MessageHandler.h"

#define SENSOR_CONFIG_ARRAY(...) {__VA_ARGS__}

#define SENSOR_CONFIG_IMU_MSG(SENSOR_ID, RATE, RANGE) \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_ADD), \
    .sensor_common.sensor_id=(uint32_t)SENSOR_ID,\
    .sensor_common.rate_hz=(uint32_t)RATE, \
    .unpacked.imu_config.sensor1_range =(uint8_t)RANGE \
}

#define SENSOR_CONFIG_IMU_2_MSG(SENSOR_ID, RATE, RANGE1, RANGE2) \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_ADD), \
    .sensor_common.sensor_id=(uint32_t)SENSOR_ID,\
    .sensor_common.rate_hz=(uint32_t)RATE, \
    .unpacked.imu_config.sensor1_range =(uint8_t)RANGE1, \
    .unpacked.imu_config.sensor2_range =(uint8_t)RANGE2 \
}

#define SENSOR_CONFIG_AUDIO_MSG(ID, RATE, NBITS, MIC_CFG) \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_ADD), \
    .sensor_common.sensor_id=(uint32_t)ID,\
    .sensor_common.rate_hz=(uint32_t)RATE, \
    .unpacked.audio.nbits=(uint8_t)NBITS, \
    .unpacked.audio.mic_config = MIC_CFG \
}

#define SENSOR_CONFIG_ADC_MSG(ID, RATE, CHANNEL_CFG) \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_ADD), \
    .unpacked.ltc1859_a.common.sensor_id=(uint32_t)ID,\
    .unpacked.ltc1859_a.common.rate_hz=(uint32_t)RATE, \
    .unpacked.ltc1859_a.chnl_config = CHANNEL_CFG \
}

#define SENSOR_CONFIG_ADD_MSG(ID, RATE, CFG)    \
{ \
  .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_ADD), \
  .sensor_common.sensor_id=(uint32_t)ID,\
  .sensor_common.rate_hz=(uint32_t)RATE, \
  .unpacked.as_u8=CFG    \
}

#define SENSOR_CONFIG_CLEAR_MSG() \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_CLEAR)\
}

/* NOTE: All canned sequences *MUST* end with *this* message */
#define SENSOR_CONFIG_DONE_MSG() \
{ \
    .msg_type=(uint8_t)GET_TOPIC_MINOR(TOPIC_SENSOR_DONE)\
}

typedef struct 
{
    bool isIMUEnabled;
    bool isAccelEnabled;
    bool isGyroEnabled;
    bool isMagEnabled;
    bool isAudioEnabled;
    bool isADCEnabled;   
}SensorEnableStatus;

/* IMU virtual sensors are mapped to physical sensor's configuration. The purpose of
 * virtual sensor is to allow flexible select of live stream samples and eliminate
 * sending redundand samples from the same sensor. Redundant could happen if the same
 * sample were put in multiple packets. An example of this senario is when DCL add Accel
 * and Accel+Gyro. Samples generated by accel would then be added to packet for A, and
 * packet for A+G. The design is to sending A+G only in this senario. The details are 
 * documented in QAI-518. Only Accel, Gyro and their diffenent combinations are defined:
 *
 * IMU_V_SENSOR_NO - Initial type, no virtual sensor is enabled.
 * IMU_V_SENSOR_ACCEL - ACCEL only, only samples from accel will be sent.
 * IMU_V_SENSOR_GYRO  - GYRO only, only samples from gyro will be sent.
 * IMU_V_SENSOR_A_G_SEP - Samples from A and G will be sent in separated packets.
 * IMU_V_SENSOR_A_G_COM - Samples from A and G will be combined and sent in same packets.
 */
typedef enum
{
    IMU_V_SENSOR_NO=0,
    IMU_V_SENSOR_ACCEL=1,
    IMU_V_SENSOR_GYRO=2,
    IMU_V_SENSOR_A_G_SEP=3,
    IMU_V_SENSOR_A_G_COM=4,
} IMU_VIRTUAL_SENSOR_t;

typedef enum
{
    IMU_DATA_COLLECT=0,
    IMU_RECOGNITION=1,
} IMU_SENSOR_MODE_t;

/* configure all sensors */
extern void configure_all_sensors(Mqttsn_IOMsgData_t *pIoMsgData);

extern void sensor_config_apply_sequence( const struct sensor_config_msg *pCfg, SensorEnableStatus *pStatus );

extern void wait_for_sensor_config(void);
extern void sensor_clear(SensorEnableStatus *pStatus);
extern void sensor_add(SensorEnableStatus *pStatus);
extern bool is_sensor_available(uint32_t sensor_id);
extern bool is_sensor_active(uint32_t sensor_id, IMU_SENSOR_MODE_t mode);
extern uint32_t sensor_get_sampling_rate(uint32_t sensor_id);
extern IMU_VIRTUAL_SENSOR_t sensor_get_virtual_sensor(void);
extern IMU_VIRTUAL_SENSOR_t sensor_set_virtual_sensor(IMU_VIRTUAL_SENSOR_t v_sensor);

#endif
